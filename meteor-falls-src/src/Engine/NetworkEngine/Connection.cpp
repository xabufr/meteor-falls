#include "Connection.h"
#include "packet.h"

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

void Connection::sendPacket(const Packet &packet)
{
    const std::vector<char> &data = packet.getData();
    send(data.data(), data.size());
}

bool Connection::hasData()
{
    boost::mutex::scoped_lock l(m_mutex_received_buffers);
    return !m_received_buffers.empty();
}

Packet Connection::nextPacket()
{
    boost::mutex::scoped_lock l(m_mutex_received_buffers);
    Packet packet(m_received_buffers.front());
    m_received_buffers.pop();
    return packet;
}

void Connection::fillPacket(Packet &packet)
{
    packet = nextPacket();
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

void Connection::addReceivedBuffer(const std::vector<char> &buffer)
{
    boost::mutex::scoped_lock l(m_mutex_received_buffers);
    m_received_buffers.push(Packet(buffer));
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
