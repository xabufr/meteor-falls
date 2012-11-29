#ifndef GLOBALSERVER_H_INCLUDED
#define GLOBALSERVER_H_INCLUDED

#include "../../meteor-falls-src/src/Engine/NetworkEngine/SslConnection.h"
#include "Server.h"
#include "ServerGlobalMessage.h"
#include <vector>
#include <boost/asio.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/thread.hpp>
#include "Creator.h"

class GlobalServer
{

    public:
        GlobalServer(unsigned short port);
        ~GlobalServer();
        void work();
        bool get_start();
    protected:
        boost::shared_ptr<boost::asio::io_service> m_service;
        boost::shared_ptr<boost::asio::io_service::work> m_work;
        boost::thread m_thread_service;
    private:
        std::vector<SslConnection::pointer> m_clients;
        std::vector<Server> m_servers;
        boost::asio::ip::tcp::acceptor m_acceptor_ssl;
        boost::mutex m_mutex_clients;
        void m_startAccept();
        void m_handleAccept_ssl(SslConnection::pointer conn, const boost::system::error_code& e);
        void removeClient(SslConnection::pointer c);
        void m_run();
        std::string m_serialize(const ServerGlobalMessage *message);
        ServerGlobalMessage* m_deserialize(const std::string &data);
        Creator *m_sql;
        bool m_start;
};
#endif // GLOBALSERVER_H_INCLUDED
