#include "SslConnection.h"


SslConnection::pointer SslConnection::create(boost::shared_ptr<boost::asio::io_service> s, Type t)
{
    boost::asio::ssl::context context(boost::asio::ssl::context::sslv2);
    context.set_verify_mode(boost::asio::ssl::context::verify_none);
    return pointer(new SslConnection(s,t, context));
}

void SslConnection::send(std::string data)
{

}

void SslConnection::startListen()
{

}

bool SslConnection::hasData()
{
    return false;
}

SslConnection::~SslConnection()
{

}

void SslConnection::handleReadHeader(const boost::system::error_code&)
{

}

void SslConnection::handleReadData(const boost::system::error_code&)
{

}

void SslConnection::handleSendData(std::string)
{

}

void SslConnection::handleHandshake(const boost::system::error_code&)
{

}

SslConnection::SslConnection(boost::shared_ptr<boost::asio::io_service> s, Type t, boost::asio::ssl::context& c):
    Connection(s),
    m_type(t),
    m_socket(*s, c)
{

}
