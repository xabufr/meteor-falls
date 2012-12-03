#ifndef CLIENTLOGIN_H_INCLUDED
#define CLIENTLOGIN_H_INCLUDED

#include "Engine/NetworkEngine/SslConnection.h"
#include "../../../GlobalServer/src/ServerGlobalMessage.h"
#include <boost/serialization/serialization.hpp>
#include <boost/serialization/map.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/string.hpp>

class ClientLogin
{
    public:
        ClientLogin(unsigned short);
        ~ClientLogin();
        bool work();
        bool get_start();
        bool send_log(std::string, std::string);
    protected:
        boost::shared_ptr<boost::asio::io_service> m_service;
        boost::shared_ptr<boost::asio::io_service::work> m_work;
        boost::thread m_thread_service;
    private:
        SslConnection::pointer m_server;
        boost::asio::ip::tcp::acceptor m_acceptor_ssl;
        boost::mutex m_mutex_server;
        void m_startAccept();
        void m_handleAccept_ssl(SslConnection::pointer conn, const boost::system::error_code& e);
        void m_run();
        std::string m_serialize(const ServerGlobalMessage *message);
        ServerGlobalMessage* m_deserialize(const std::string &data);
        bool m_start;
};

#endif // CLIENTLOGIN_H_INCLUDED
