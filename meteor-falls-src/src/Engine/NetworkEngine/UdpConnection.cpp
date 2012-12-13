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
    m_socket->async_receive_from(boost::asio::buffer(m_buffer_data, buffer_size),
                                 m_endpointSender,
                                 boost::bind(&UdpConnection::handleReadData,
                                             shared_from_this(),
                                           	 _1, 
											 _2));
}
bool UdpConnection::hasData()
{
    boost::mutex::scoped_lock l(m_mutex_buffers);
    return !m_queue_buffers.empty();
}
UdpConnection::Data UdpConnection::getData()
{
    boost::mutex::scoped_lock l(m_mutex_buffers);
    Data d = m_queue_buffers.front();
    m_queue_buffers.pop();
    return d;
}
void UdpConnection::send(std::string data)
{
    if(isConnected())
        send(data, getConnectionEndpoint());
}
void UdpConnection::send(std::string data, boost::asio::ip::udp::endpoint e)
{
    m_service->post(boost::bind(&UdpConnection::handleSendData,
                                shared_from_this(),
                                data,
                                e));
}
void UdpConnection::bind(boost::asio::ip::udp::endpoint e)
{
    setListening(true);
    setConnected(true);
    m_socket->bind(e);
}
void UdpConnection::handleReadData(const boost::system::error_code& e, size_t length)
{
    if(e){
        m_addError(e);
        setListening(false);
        return;
    }
    std::string data(m_buffer_data, length);
    {
        boost::mutex::scoped_lock l(m_mutex_buffers);
        m_queue_buffers.push(std::make_pair(m_endpointSender, data));
    }
    m_socket->async_receive_from(boost::asio::buffer(m_buffer_data, buffer_size),
                                 m_endpointSender,
                                 boost::bind(&UdpConnection::handleReadHeader,
                                             shared_from_this(),
                                             boost::asio::placeholders::error));
}
void UdpConnection::handleSendData(std::string data, boost::asio::ip::udp::endpoint e)
{
    m_socket->async_send_to(boost::asio::buffer(data), e,
                            boost::bind(&UdpConnection::handleDataSent,
                                        shared_from_this(),
                                        boost::asio::placeholders::error));
}
UdpConnection::UdpConnection(boost::shared_ptr<boost::asio::io_service> service) : Connection(service)
{
    m_socket = new boost::asio::ip::udp::socket(*service);
	m_socket->open(boost::asio::ip::udp::endpoint(boost::asio::ip::address::from_string("172.0.0.1"), 8888).protocol());
}
boost::asio::ip::udp::endpoint UdpConnection::getConnectionEndpoint()
{
    boost::mutex::scoped_lock l(m_mutex_connexion_endpoint);
    return m_endpointConnection;
}
