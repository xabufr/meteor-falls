#include "ServerClient.h"

ServerClient::ServerClient(TcpConnection::pointer tcp, unsigned int id) : m_tcp(tcp), m_id(id)
{
	isConnected=false;
	toDel=false;
}
ServerClient::~ServerClient()
{
    //dtor
}
TcpConnection::pointer ServerClient::tcp()
{
    return m_tcp;
}
unsigned int ServerClient::id()
{
    return m_id;
}
