#ifndef GLOBALSERVER_H_INCLUDED
#define GLOBALSERVER_H_INCLUDED

#include "../../meteor-falls-src/src/Engine/NetworkEngine/SslConnection.h"
#include "../../meteor-falls-src/src/Engine/NetworkEngine/NetworkEngine.h"
#include "Server.h"
#include "ServerGlobalMessage.h"
#include <vector>
#include "Creator.h"

class GlobalServer : public NetworkEngine
{

    public:
        GlobalServer(EngineManager *mng, unsigned short port);
        ~GlobalServer();
        void work();
    private:
        std::vector<SslConnection::pointer> m_clients;
        std::vector<Server> m_servers;
        boost::asio::ip::tcp::acceptor m_acceptor_ssl;
        boost::mutex m_mutex_clients;
        void m_startAccept();
        void m_handleAccept_ssl(SslConnection::pointer conn, const boost::system::error_code& e);
        void removeClient(SslConnection::pointer c);
        std::string m_serialize(const ServerGlobalMessage *message);
        ServerGlobalMessage* m_deserialize(const std::string &data);
        Creator *m_sql;
};
#endif // GLOBALSERVER_H_INCLUDED
