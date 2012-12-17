#ifndef SERVERCLIENT_H
#define SERVERCLIENT_H
#include "TcpConnection.h"
#include "UdpConnection.h"

class Joueur;
class ServerClient
{
    public:
        ServerClient(TcpConnection::pointer, unsigned int id);
        virtual ~ServerClient();
        TcpConnection::pointer tcp();
        unsigned int id();
		bool isConnected;
		Joueur *joueur;
		std::string sel, session;
    protected:
    private:
        TcpConnection::pointer m_tcp;
        unsigned int m_id;
};

#endif // SERVERCLIENT_H
