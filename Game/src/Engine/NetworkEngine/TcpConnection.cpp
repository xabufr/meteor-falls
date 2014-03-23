#include "TcpConnection.h"
#include "../../precompiled/bind.h"
#include <iomanip>

TcpConnection::pointer TcpConnection::create(boost::shared_ptr<boost::asio::io_service> io)
{
    return pointer(new TcpConnection(io));
}
void TcpConnection::send(const char *data, std::size_t size)
{
    boost::shared_ptr<char> tmpData(new char[size]);
    std::memcpy(tmpData.get(), data, size);
    m_service->post(boost::bind(&TcpConnection::handleSendData, shared_from_this(), tmpData, size));
}
void TcpConnection::handleReadHeader(const boost::system::error_code& e)
{
    if(e){
        if(e==boost::asio::error::misc_errors::eof){
            setConnected(false);
        }
        m_addError(e);
        setListening(false);
        return;
    }
    else{
        m_currentPacketSize = ntohl(m_currentPacketSize);
        m_data_buffer.resize(m_currentPacketSize);
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
        if(e==boost::asio::error::misc_errors::eof){
            setConnected(false);
        }
        m_addError(e);
        setListening(false);
        return;
    }
    else
    {
        addReceivedBuffer(m_data_buffer);
        boost::asio::async_read(*m_socket,
                                boost::asio::buffer(&m_currentPacketSize, sizeof(m_currentPacketSize)),
                                boost::bind(&TcpConnection::handleReadHeader,
                                            shared_from_this(),
                                            boost::asio::placeholders::error));
    }
}

void TcpConnection::handleSendData(boost::shared_ptr<char> data, std::size_t size)
{
    if(isConnected())
    {
        std::uint32_t contentSize = htonl(size);
        std::vector<boost::asio::const_buffer> buffers;
        buffers.push_back(boost::asio::buffer(&contentSize, sizeof(contentSize)));
        buffers.push_back(boost::asio::buffer(data.get(), size));
        boost::asio::async_write(*m_socket,
                                 buffers,
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
                                boost::asio::buffer(&m_currentPacketSize, sizeof(m_currentPacketSize)),
                                    boost::bind(&TcpConnection::handleReadHeader,
                                                shared_from_this(),
                                                boost::asio::placeholders::error));
    }
}
void TcpConnection::connect(boost::asio::ip::tcp::endpoint e)
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
boost::asio::ip::tcp::socket& TcpConnection::socket()
{
    return *m_socket;
}
TcpConnection::~TcpConnection()
{
    delete m_socket;
}
void TcpConnection::stop()
{
    m_socket->close();
}
