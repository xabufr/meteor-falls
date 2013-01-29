#ifndef SERVERCLIENT_H
#define SERVERCLIENT_H
#include "TcpConnection.h"
#include "UdpConnection.h"
#include "../../Utils/Clock.h"
#include <boost/shared_ptr.hpp>

class Joueur;
class ServerClientData
{
public:
	bool isConnected, toDel;
	std::string sel, session;
	Clock timePing, timeSinceLastPingRep;
	bool waitingPing;
	ServerClientData()
	{
		isConnected=false;
		toDel=false;
		waitingPing = false;
	}
};
class ServerClient
{
    public:
        ServerClient(TcpConnection::pointer, unsigned int id);
        virtual ~ServerClient();
        TcpConnection::pointer tcp();
        unsigned int id();
		Joueur *joueur;
		boost::shared_ptr<ServerClientData> data;
    protected:
    private:
        TcpConnection::pointer m_tcp;
        unsigned int m_id;
};

#endif // SERVERCLIENT_H
