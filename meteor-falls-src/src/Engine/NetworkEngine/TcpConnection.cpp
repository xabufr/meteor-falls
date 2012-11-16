#include "TcpConnection.h"
#include <boost/bind.hpp>
#include <iomanip>

TcpConnection::pointer TcpConnection::create(boost::shared_ptr<boost::asio::io_service> io)
{
    return pointer(new TcpConnection(io));
}

void TcpConnection::send(std::string data)
{
    m_service->post(boost::bind(&TcpConnection::handleSendData, shared_from_this(), data));
}

void TcpConnection::handleReadHeader(const boost::system::error_code& e)
{
    if(e){
        m_addError(e);
        setListening(false);
        return;
    }
    else{
        std::istringstream is(std::string(m_header_data, header_size));
        size_t hs;
        if(!(is>>std::hex>>hs)){
            m_addError(boost::asio::error::basic_errors::invalid_argument);
            setListening(false);
            return;
        }
        m_data_buffer.resize(hs);
        boost::asio::async_read(*m_socket,
                                boost::asio::buffer(m_data_buffer),
                                boost::bind(&TcpConnection::handleReadData,
                                            shared_from_this(),
                                            boost::asio::placeholders::error));
    }
}

void TcpConnection::handleReadData(const boost::system::error_code& e)
{
    if(e)
    {
        m_addError(e);
        setListening(false);
        return;
    }
    else
    {
        {
            boost::mutex::scoped_lock l(m_mutex_buffer);
            m_buffer_queue.push(std::string(m_data_buffer.data(), m_data_buffer.size()));
        }
        boost::asio::async_read(*m_socket,
                                boost::asio::buffer(m_header_data, header_size),
                                boost::bind(&TcpConnection::handleReadHeader,
                                            shared_from_this(),
                                            boost::asio::placeholders::error));
    }
}

void TcpConnection::handleSendData(std::string data)
{
    if(isConnected())
    {
        std::ostringstream os;
        os << std::setw(header_size) << std::hex << data.size();
        if( !os || os.str().size() != header_size){
            m_addError(boost::asio::error::basic_errors::invalid_argument);
            return;
        }
        std::vector<boost::asio::const_buffer> datas({
                                               boost::asio::buffer(os.str()),
                                               boost::asio::buffer(data)});
        boost::asio::async_write(*m_socket,
                                 datas,
                                 boost::bind(&TcpConnection::handleDataSent,
                                             shared_from_this(),
                                             boost::asio::placeholders::error));
    }
}
void TcpConnection::startListen()
{
    if(isConnected() && !isListening())
    {
        setListening(true);
        boost::asio::async_read(*m_socket,
                                    boost::asio::buffer(m_header_data, header_size),
                                    boost::bind(&TcpConnection::handleReadHeader,
                                                shared_from_this(),
                                                boost::asio::placeholders::error));
    }
}

void TcpConnection::connect(boost::asio::ip::tcp::endpoint& e)
{
    if(!isConnected()){
        m_socket->async_connect(e,boost::bind(&TcpConnection::handleConnect, shared_from_this(),
                                              boost::asio::placeholders::error));
    }
}

void TcpConnection::handleConnect(const boost::system::error_code& e)
{
    if(e)
        m_addError(e);
    else
    {
        setConnected(true);
        startListen();
    }
}

TcpConnection::TcpConnection(boost::shared_ptr<boost::asio::io_service> io): Connection(io)
{
    m_socket = new boost::asio::ip::tcp::socket(*m_service);
}
bool TcpConnection::hasData()
{
    boost::mutex::scoped_lock l(m_mutex_buffer);
    return !m_buffer_queue.empty();
}
std::string TcpConnection::getData()
{
    boost::mutex::scoped_lock l(m_mutex_buffer);
    std::string data(m_buffer_queue.front());
    m_buffer_queue.pop();
    return data;
}
boost::asio::ip::tcp::socket& TcpConnection::socket()
{
    return *m_socket;
}
