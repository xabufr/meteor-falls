#include "TcpConnection.h"
#include <boost/bind.hpp>
#include <iostream>

TcpConnection::TcpConnection(boost::asio::io_service& service, boost::asio::ip::tcp::endpoint& endpoint)
{
    m_socket = new boost::asio::ip::tcp::socket(service);
    m_socket->async_connect(endpoint,
                            boost::bind(&TcpConnection::handleConnect, shared_from_this(),
                                        boost::asio::placeholders::error));
}


TcpConnection::~TcpConnection()
{
    delete m_socket;
}
void TcpConnection::handleConnect(const boost::system::error_code& error)
{
    if(error)
    {
        boost::mutex::scoped_lock lock(m_mutex_error);
        m_queue_error.push(error);
    }
    else{
        boost::asio::async_read(*m_socket,
                                boost::asio::buffer(m_input_header_buffer, m_header_size),
                                boost::bind(&TcpConnection::readHeader,
                                            shared_from_this(),
                                            boost::asio::placeholders::error)
                                );
    }
}

TcpConnection::pointer TcpConnection::create(boost::asio::io_service& service, boost::asio::ip::tcp::endpoint& endpoint)
{
    return pointer(new TcpConnection(service, endpoint));
}

bool TcpConnection::hasData()
{
    boost::mutex::scoped_lock lock(m_mutex_buffer);
    return !m_queue_buffer.empty();
}

std::string TcpConnection::getData()
{
    boost::mutex::scoped_lock lock(m_mutex_buffer);
    std::string ret = m_queue_buffer.front();
    m_queue_buffer.pop();
    return ret;
}

void TcpConnection::send(std::string data)
{
    size_t data_size = data.size();
    std::ostringstream os;
    os << std::hex << data_size;
    std::string data_size_header = os.str();

    std::vector<boost::asio::const_buffer> buffer({boost::asio::buffer(data_size_header), boost::asio::buffer(data)});

    boost::asio::async_write(*m_socket, buffer,
                             boost::bind(&TcpConnection::handleWrite, shared_from_this(),
                                         boost::asio::placeholders::error));
}
void TcpConnection::handleWrite(const boost::system::error_code& error)
{
    if(error)
    {
        boost::mutex::scoped_lock lock(m_mutex_error);
        m_queue_error.push(error);
    }
}

void TcpConnection::readHeader(const boost::system::error_code& error)
{
    if(error)
    {
        boost::mutex::scoped_lock lock(m_mutex_error);
        m_queue_error.push(error);
        return;
    }
    std::istringstream is(std::string(m_input_header_buffer, m_header_size));
    size_t data_size;
    if(!(is>>std::hex>>data_size)){
        return;
    }
    m_input_buffer.resize(data_size);
    boost::asio::async_read(*m_socket,
                                boost::asio::buffer(m_input_buffer),
                                boost::bind(&TcpConnection::readData, shared_from_this(),
                                            boost::asio::placeholders::error));
}

void TcpConnection::readData(const boost::system::error_code& error)
{
    if(error)
    {
        boost::mutex::scoped_lock lock(m_mutex_error);
        m_queue_error.push(error);
    }
    else
    {
        {
            boost::mutex::scoped_lock lock(m_mutex_buffer);
            m_queue_buffer.push(std::string(m_input_buffer.data(), m_input_buffer.size()));
        }
        boost::asio::async_read(*m_socket,
                                    boost::asio::buffer(m_input_header_buffer, m_header_size),
                                    boost::bind(&TcpConnection::readHeader, shared_from_this(),
                                                boost::asio::placeholders::error));
    }
}
bool TcpConnection::hasError()
{
    boost::mutex::scoped_lock l(m_mutex_error);
    return !m_queue_error.empty();
}

boost::system::error_code TcpConnection::getError()
{
    boost::mutex::scoped_lock l(m_mutex_error);
    boost::system::error_code ret = m_queue_error.front();
    m_queue_error.pop();
    return ret;
}
