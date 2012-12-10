#include "UdpConnection.h"
#include "precompiled/bind.h"
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
    m_socket->async_receive_from(boost::asio::buffer(m_header_data, header_size),
                                 m_endpointSender,
                                 boost::bind(&UdpConnection::handleReadHeader,
                                             shared_from_this(),
                                             boost::asio::placeholders::error));
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
    m_socket->bind(e);
}

void UdpConnection::handleReadHeader(const boost::system::error_code& e)
{
    if(e){
        setListening(false);
        m_addError(e);
        return;
    }
    std::istringstream is(std::string(m_header_data, header_size));
    size_t hs;
    if(!(is>>std::hex>>hs)){
        setListening(false);
        m_addError(boost::asio::error::basic_errors::invalid_argument);
        return;
    }
    m_buffer_receive.resize(hs);
    m_socket->async_receive_from(boost::asio::buffer(m_buffer_receive),
                                 m_endpointSender,
                                 boost::bind(&UdpConnection::handleReadData,
                                             shared_from_this(),
                                             boost::asio::placeholders::error));
}

void UdpConnection::handleReadData(const boost::system::error_code& e)
{
    if(e){
        m_addError(e);
        setListening(false);
        return;
    }
    std::string data(m_buffer_receive.data(), m_buffer_receive.size());
    {
        boost::mutex::scoped_lock l(m_mutex_buffers);
        m_queue_buffers.push(std::make_pair(m_endpointSender, data));
    }
    m_socket->async_receive_from(boost::asio::buffer(m_header_data, header_size),
                                 m_endpointSender,
                                 boost::bind(&UdpConnection::handleReadHeader,
                                             shared_from_this(),
                                             boost::asio::placeholders::error));
}

void UdpConnection::handleSendData(std::string data, boost::asio::ip::udp::endpoint e)
{
    std::ostringstream os;
    os << std::setw(header_size) << std::hex << data.size();
    if( !os || os.str().size() != header_size){
        m_addError(boost::asio::error::basic_errors::invalid_argument);
        return;
    }
    m_socket->async_send_to(boost::asio::buffer(os.str() + data), e,
                            boost::bind(&UdpConnection::handleDataSent,
                                        shared_from_this(),
                                        boost::asio::placeholders::error));
}

UdpConnection::UdpConnection(boost::shared_ptr<boost::asio::io_service> service) : Connection(service)
{
    m_socket = new boost::asio::ip::udp::socket(*service);
}
boost::asio::ip::udp::endpoint UdpConnection::getConnectionEndpoint()
{
    boost::mutex::scoped_lock l(m_mutex_connexion_endpoint);
    return m_endpointConnection;
}

