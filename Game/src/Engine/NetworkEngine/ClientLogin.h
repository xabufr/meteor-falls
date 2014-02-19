#ifndef CLIENTLOGIN_H_INCLUDED
#define CLIENTLOGIN_H_INCLUDED

#include "Engine/NetworkEngine/SslConnection.h"
#include "../../../../GlobalServer/src/ServerGlobalMessage.h"
#include "../../../../GlobalServer/src/Player.h"
#include <boost/serialization/serialization.hpp>
#include <boost/serialization/map.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/string.hpp>

class ClientLogin
{
    public:
        ClientLogin(unsigned short, std::string, std::string);
        ~ClientLogin();
        bool isLogin();
        Player *getPlayer();
    protected:
        boost::shared_ptr<boost::asio::io_service> m_service;
        boost::shared_ptr<boost::asio::io_service::work> m_work;
    private:
        SslConnection::pointer m_connection;
        boost::thread m_service_thread;
        void m_run();
        bool m_login;
        Player *m_player;
        std::string m_serialize(const ServerGlobalMessage *message);
        ServerGlobalMessage* m_deserialize(const std::string &data);
};

#endif // CLIENTLOGIN_H_INCLUDED
