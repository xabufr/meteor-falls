#include "SslConnection.h"
#include "precompiled/bind.h"

SslConnection::pointer SslConnection::create(boost::shared_ptr<boost::asio::io_service> s, Type t)
{
    if(t==SERVER){
        boost::asio::ssl::context context(*s, boost::asio::ssl::context::sslv23);
        context.set_options(
        boost::asio::ssl::context::default_workarounds
        | boost::asio::ssl::context::no_sslv2
        | boost::asio::ssl::context::single_dh_use);
        context.use_certificate_chain_file("server.pem");
        context.use_private_key_file("server.pem", boost::asio::ssl::context::pem);
        context.use_tmp_dh_file("dh512.pem");

        return pointer(new SslConnection(s,t, context));
    }
    else
    {
        boost::asio::ssl::context context(boost::asio::ssl::context::sslv23);
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
        setListening(true);
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

    std::ostringstream os;
    os << std::setw(header_size) << std::hex << data.size();
    if( !os || os.str().size() != header_size){
        m_addError(boost::asio::error::basic_errors::invalid_argument);
        return;
    }
    m_socket.async_write_some(boost::asio::buffer(os.str() + data),
                              boost::bind(&SslConnection::handleDataSent, shared_from_this(),
                                          boost::asio::placeholders::error));
}

void SslConnection::handleHandshake(const boost::system::error_code& e)
{
    if(!e)
    {
        setConnected(true);
        startListen();
    }
    else
        m_addError(e);
}

SslConnection::SslConnection(boost::shared_ptr<boost::asio::io_service> s, Type t, boost::asio::ssl::context& c):
    Connection(s),
    m_type(t),
    m_socket(*s, c)
{
    if(t==CLIENT)
        m_socket.set_verify_mode(boost::asio::ssl::verify_none);
}

void SslConnection::handleConnect(const boost::system::error_code& e)
{
    if(!e)
    {

        if(m_type==Type::CLIENT)
        {
            m_socket.async_handshake(boost::asio::ssl::stream_base::client,
                                      boost::bind(&SslConnection::handleHandshake, shared_from_this(),
                                                  boost::asio::placeholders::error));
        }

        else
        {
            m_socket.async_handshake(boost::asio::ssl::stream_base::server,
                                      boost::bind(&SslConnection::handleHandshake, shared_from_this(),
                                                  boost::asio::placeholders::error));
        }

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
    {
        setConnected(true);
        handleConnect(boost::system::error_code());
    }

}
boost::asio::ssl::stream<boost::asio::ip::tcp::socket>::lowest_layer_type& SslConnection::socket()
{
    return m_socket.lowest_layer();
}
