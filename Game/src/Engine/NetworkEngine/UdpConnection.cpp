#include "UdpConnection.h"
#include "../../precompiled/bind.h"
#include <iomanip>

UdpConnection::~UdpConnection()
{
}
UdpConnection::pointer UdpConnection::create(boost::shared_ptr<boost::asio::io_service> s)
{
    return pointer(new UdpConnection(s));
}
void UdpConnection::connect(boost::asio::ip::udp::endpoint e)
{
    setConnected(true);
    boost::mutex::scoped_lock l(m_mutex_connexion_endpoint);
    m_endpointConnection = e;
}
void UdpConnection::startListen()
{
    m_service->post(boost::bind(&UdpConnection::handleStartReceive, shared_from_this()));
}
void UdpConnection::handleStartReceive()
{
    m_socket->async_receive_from(boost::asio::buffer(m_data_buffer),
                                 m_endpointSender,
                                 boost::bind(&UdpConnection::handleReadData,
                                             shared_from_this(),
                                             _1));
}

void UdpConnection::send(const char *data, std::size_t size)
{
    if(isConnected())
        send(data, size, getConnectionEndpoint());
}

void UdpConnection::send(const char *data, std::size_t size, const boost::asio::ip::udp::endpoint &e)
{
    boost::shared_ptr<char> tmpData(new char[size]);
    std::memcpy(tmpData.get(), data, size);
    m_service->post(boost::bind(&UdpConnection::handleSendData,
                                shared_from_this(),
                                tmpData,
                                size,
                                e));
}

void UdpConnection::send(const Packet &packet, const boost::asio::ip::udp::endpoint &e)
{
    send(packet.getData().data(), packet.getData().size(), e);
}

void UdpConnection::bind(boost::asio::ip::udp::endpoint e)
{
    setListening(true);
    setConnected(true);
    m_socket->bind(e);
}
void UdpConnection::handleReadData(const boost::system::error_code& e)
{
    if(e){
        m_addError(e);
        setListening(false);
        return;
    }
    if(m_data_buffer.size() > 0) {
        Packet packet(m_data_buffer);
        packet.sender = m_endpointSender.address();
        addReceivedPacket(packet);
    }
    m_data_buffer.clear();
    m_socket->async_receive_from(boost::asio::buffer(m_data_buffer),
                                 m_endpointSender,
                                 boost::bind(&UdpConnection::handleReadData,
                                             shared_from_this(),
                                             _1));
}
void UdpConnection::handleSendData(boost::shared_ptr<char> data, std::size_t size, boost::asio::ip::udp::endpoint endpoint)
{
    std::vector<boost::asio::const_buffer> buffers;
    std::uint8_t packetSize = size;
    //buffers.push_back(boost::asio::buffer(&packetSize, sizeof(packetSize)));
    buffers.push_back(boost::asio::buffer(data.get(), size));
    m_socket->async_send_to(buffers, endpoint,
                            boost::bind(&UdpConnection::handleDataSent,
                                        shared_from_this(),
                                        boost::asio::placeholders::error));
}
UdpConnection::UdpConnection(boost::shared_ptr<boost::asio::io_service> service) : Connection(service)
{
    m_socket = new boost::asio::ip::udp::socket(*service);
    m_socket->open(boost::asio::ip::udp::endpoint(boost::asio::ip::address::from_string("172.0.0.1"), 8888).protocol());
    m_data_buffer.resize(2048);
}
const boost::asio::ip::udp::endpoint &UdpConnection::getConnectionEndpoint()
{
    boost::mutex::scoped_lock l(m_mutex_connexion_endpoint);
    return m_endpointConnection;
}
