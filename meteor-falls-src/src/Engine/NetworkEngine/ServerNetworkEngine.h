#ifndef SERVERNETWORKENGINE_H
#define SERVERNETWORKENGINE_H

#include "NetworkEngine.h"
#include "ServerClient.h"
#include <vector>
#include <boost/thread/mutex.hpp>

class ServerNetworkEngine : public NetworkEngine
{
    public:
        ServerNetworkEngine(unsigned short port);
        virtual ~ServerNetworkEngine();

        void handleMessage(const EngineMessage&);
        void work();
    protected:
        void m_startAccept();
        void m_handleAccept(TcpConnection::pointer, const boost::system::error_code&);

    private:

        std::vector<ServerClient> m_clients;
        boost::asio::ip::tcp::acceptor m_acceptor;
        boost::mutex m_mutex_clients;
        client_id m_lastClient;
};

#endif // SERVERNETWORKENGINE_H
