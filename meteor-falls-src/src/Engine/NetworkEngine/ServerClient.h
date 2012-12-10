#ifndef SERVERCLIENT_H
#define SERVERCLIENT_H
#include "TcpConnection.h"
#include "UdpConnection.h"

class ServerClient
{
    public:
        ServerClient(TcpConnection::pointer, unsigned int id);
        virtual ~ServerClient();
        TcpConnection::pointer tcp();
        UdpConnection::pointer udp();
        unsigned int id();
    protected:
    private:
        TcpConnection::pointer m_tcp;
        UdpConnection::pointer m_udp;
        unsigned int m_id;
};

#endif // SERVERCLIENT_H
