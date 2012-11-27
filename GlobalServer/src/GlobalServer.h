#ifndef GLOBALSERVER_H_INCLUDED
#define GLOBALSERVER_H_INCLUDED

#include "../../meteor-falls-src/src/Engine/NetworkEngine/SslConnection.h"
#include "../../meteor-falls-src/src/Engine/NetworkEngine/NetworkEngine.h"
#include <vector>

class GlobalServer : public NetworkEngine
{

    public:
        GlobalServer(EngineManager *mng, unsigned short port);
        ~GlobalServer();
        void work();
    private:
        std::vector<SslConnection::pointer> m_clients;
        boost::asio::ip::tcp::acceptor m_acceptor_ssl;
        boost::mutex m_mutex_clients;
        void m_startAccept();
        void m_handleAccept_ssl(SslConnection::pointer conn, const boost::system::error_code& e);
        void removeClient(SslConnection::pointer c);
};
#endif // GLOBALSERVER_H_INCLUDED
