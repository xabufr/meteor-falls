#include "ServerClient.h"

ServerClient::ServerClient(TcpConnection::pointer tcp, unsigned int id) : m_tcp(tcp), m_id(id)
{

}
ServerClient::~ServerClient()
{
    //dtor
}
TcpConnection::pointer ServerClient::tcp()
{
    return m_tcp;
}
UdpConnection::pointer ServerClient::udp()
{
    return m_udp;
}
unsigned int ServerClient::id()
{
    return m_id;
}
