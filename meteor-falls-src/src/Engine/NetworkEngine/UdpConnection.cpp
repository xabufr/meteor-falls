#include "UdpConnection.h"


UdpConnection::~UdpConnection()
{
}
UdpConnection::pointer UdpConnection::create(boost::asio::io_service& s)
{
    return pointer(new UdpConnection(s));
}
void UdpConnection::setEndpoint(boost::asio::ip::udp::endpoint& e)
{
    m_endpoint = e;
}
void UdpConnection::send(std::string data)
{
    send(data, m_endpoint);
}
void UdpConnection::send(std::string data, boost::asio::ip::udp::endpoint& e)
{
    m_socket.async_send_to(boost::asio::buffer(data), e,
                           boost::bind(&UdpConnection::handleSend, shared_from_this(),
                                        boost::asio::placeholders::error));
}
void UdpConnection::read_header(const boost::system::error_code& error)
{
    std::istringstream is(std::string(m_header_data, header_size));
    size_t h_size;
    if(!(is >> std::hex >> h_size))
        return;
    m_buffer_receive.resize(h_size);

    m_socket.async_receive(boost::asio::buffer(m_buffer_receive),
                           boost::bind(&UdpConnection::read_data, shared_from_this(),
                                       boost::asio::placeholders::error));
}
void UdpConnection::read_data(const boost::system::error_code& error)
{
    m_queue_buffers.push(std::string(m_buffer_receive.data(), m_buffer_receive.size()));

    m_socket.async_receive(boost::asio::buffer(m_header_data),
                           boost::bind(&UdpConnection::read_header, shared_from_this(),
                                       boost::asio::placeholders::error));
}
void UdpConnection::handleSend(const boost::system::error_code& error)
{

}
UdpConnection::UdpConnection(boost::asio::io_service& service) : m_socket(service)
{

}
void UdpConnection::bind(boost::asio::ip::udp::endpoint& e)
{
    m_socket.bind(e);
    m_socket.async_receive(boost::asio::buffer(m_header_data),
                           boost::bind(&UdpConnection::read_header, shared_from_this(),
                                       boost::asio::placeholders::error));
}
