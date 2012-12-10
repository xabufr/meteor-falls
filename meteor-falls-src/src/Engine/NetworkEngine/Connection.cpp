#include "Connection.h"

Connection::Connection(boost::shared_ptr<boost::asio::io_service> s) : m_service(s)
{
    m_connected = m_listen = false;
}

Connection::~Connection()
{
    //dtor
}
bool Connection::hasError()
{
    boost::mutex::scoped_lock l(m_mutexError);
    return !m_errors.empty();
}

boost::system::error_code Connection::getError()
{
    boost::mutex::scoped_lock l(m_mutexError);
    boost::system::error_code error(m_errors.front());
    m_errors.pop();
    return error;
}

void Connection::m_addError(const boost::system::error_code& error)
{
    boost::mutex::scoped_lock l(m_mutexError);
    m_errors.push(error);
}
void Connection::handleDataSent(const boost::system::error_code& e)
{
    if(e){
		std::cout << "error sending"<<std::endl;
        m_addError(e);
	}
}
bool Connection::isListening()
{
    boost::mutex::scoped_lock l(m_mutex_listening);
    return m_listen;
}

void Connection::setListening(bool li)
{
    boost::mutex::scoped_lock l(m_mutex_listening);
    m_listen = li;
}
bool Connection::isConnected()
{
    boost::mutex::scoped_lock l(m_mutex_connected);
    return m_connected;
}

void Connection::setConnected(bool c)
{
    boost::mutex::scoped_lock l(m_mutex_connected);
    m_connected = c;
}
