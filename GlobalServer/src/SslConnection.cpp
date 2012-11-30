#include "../../meteor-falls-src/src/Engine/NetworkEngine/SslConnection.h"
#include <boost/bind.hpp>

SslConnection::pointer SslConnection::create(boost::shared_ptr<boost::asio::io_service> s, Type t)
{
    if(t==SERVER){
            boost::asio::ssl::context context(*s, boost::asio::ssl::context_base::method::sslv23_server);
        context.set_options(
        boost::asio::ssl::context::default_workarounds
        | boost::asio::ssl::context::no_sslv2
        | boost::asio::ssl::context::single_dh_use
        | boost::asio::ssl::context::verify_none);

        context.use_certificate_file("server.pem", boost::asio::ssl::context::pem);
        context.use_private_key_file("server.pem", boost::asio::ssl::context::pem);
        context.use_tmp_dh_file("dh512.pem");

        return pointer(new SslConnection(s,t, context));
    }
    else
    {
        boost::asio::ssl::context context(*s, boost::asio::ssl::context_base::method::sslv23_client);
        //context.load_verify_file("server.crt");
        context.set_verify_mode(boost::asio::ssl::verify_none);
        return pointer(new SslConnection(s,t, context));
    }
}

void SslConnection::send(std::string data)
{
    if(isConnected())
        m_service->post(boost::bind(&SslConnection::handleSendData, shared_from_this(), data));

}

void SslConnection::startListen()
{
    if(isConnected()&&!isListening())
    {
        m_socket.async_read_some(boost::asio::buffer(m_header_data, header_size),
                                  boost::bind(&SslConnection::handleReadHeader, shared_from_this(),
                                              boost::asio::placeholders::error));
    }
}

bool SslConnection::hasData()
{
    boost::mutex::scoped_lock l(m_mutex_data);
    return !m_dataQueue.empty();
}
std::string SslConnection::getData()
{
    boost::mutex::scoped_lock l(m_mutex_data);
    std::string data =  m_dataQueue.front();
    m_dataQueue.pop();
    return data;
}

SslConnection::~SslConnection()
{

}

void SslConnection::handleReadHeader(const boost::system::error_code& e)
{
    if(e)
    {
        if(e==boost::asio::error::misc_errors::eof)
            setConnected(false);
        m_addError(e);
        setListening(false);
    }
    else
    {
        std::istringstream is(std::string(m_header_data, header_size));
        size_t size;
        if(!(is >> std::hex >> size))
        {
            m_addError(boost::asio::error::basic_errors::invalid_argument);
            setListening(false);
            return;
        }
        m_data_buffer.resize(size);
        m_socket.async_read_some(boost::asio::buffer(m_data_buffer),
                                 boost::bind(&SslConnection::handleReadData, shared_from_this(),
                                             boost::asio::placeholders::error));
    }
}

void SslConnection::handleReadData(const boost::system::error_code&)
{
    {
        boost::mutex::scoped_lock l(m_mutex_data);
        m_dataQueue.push(std::string(m_data_buffer.data(), m_data_buffer.size()));
    }
    m_socket.async_read_some(boost::asio::buffer(m_header_data, header_size),
                                  boost::bind(&SslConnection::handleReadHeader, shared_from_this(),
                                              boost::asio::placeholders::error));
}

void SslConnection::handleSendData(std::string data)
{
    m_socket.async_write_some(boost::asio::buffer(data),
                              boost::bind(&SslConnection::handleDataSent, shared_from_this(),
                                          boost::asio::placeholders::error));
}

void SslConnection::handleHandshake(const boost::system::error_code& e)
{
    std::cout << "handshake handle" << std::endl;
    if(!e)
    {
        std::cout << "listen" << std::endl;
        setConnected(true);
        startListen();
    }
    else{
        m_addError(e);
        std::cout << e<<std::endl;
    }
}

SslConnection::SslConnection(boost::shared_ptr<boost::asio::io_service> s, Type t, boost::asio::ssl::context& c):
    Connection(s),
    m_type(t),
    m_socket(*s, c)
{

}

void SslConnection::handleConnect(const boost::system::error_code& e)
{
    std::cout << "connected" << std::endl;
    if(!e)
    {
        std::cout << "handshake" << std::endl;
        if(m_type==Type::CLIENT)
            m_socket.async_handshake(boost::asio::ssl::stream_base::client,
                                      boost::bind(&SslConnection::handleHandshake, shared_from_this(),
                                                  boost::asio::placeholders::error));
        else
            m_socket.async_handshake(boost::asio::ssl::stream_base::server,
                                      boost::bind(&SslConnection::handleHandshake, shared_from_this(),
                                                  boost::asio::placeholders::error));
    }
    else
        m_addError(e);
}
void SslConnection::connect(boost::asio::ip::tcp::endpoint e)
{
    m_socket.lowest_layer().async_connect(e,
                               boost::bind(&SslConnection::handleConnect, shared_from_this(),
                                           boost::asio::placeholders::error));
}
void SslConnection::connectionAccepted()
{
    if(m_type==Type::SERVER)
        handleConnect(boost::system::error_code());
}

boost::asio::ssl::stream<boost::asio::ip::tcp::socket>::lowest_layer_type& SslConnection::socket()
{
    return m_socket.lowest_layer();
}

