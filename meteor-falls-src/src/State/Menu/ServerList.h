#ifndef SERVERLIST_H_INCLUDED
#define SERVERLIST_H_INCLUDED

#include "../../Engine/NetworkEngine/UdpConnection.h"
#include "../../Engine/NetworkEngine/SslConnection.h"
#include "../../Engine/EngineMessage/EngineMessage.h"
#include "../State.h"
#include "../StateManager.h"
#include "../../precompiled/shared_ptr.h"
#include "../../precompiled/asio.h"
#include "../../../../GlobalServer/src/ServerGlobalMessage.h"
#include <CEGUI.h>

class ServerList : public State
{
    public:
        enum Type{
            LAN,
            WAN
        };
        ServerList(Type, StateManager*);
        ~ServerList();
        virtual bool isVisible();
        virtual void enter();
        virtual void exit();
        virtual ret_code work(unsigned int time);
    private:
        UdpConnection::pointer m_connection_udp;
        SslConnection::pointer m_connection_ssl;
        CEGUI::Listbox *m_listServer;
        boost::thread m_service_thread;
        boost::shared_ptr<boost::asio::io_service> m_service;
        boost::shared_ptr<boost::asio::io_service::work> m_work;
        std::string m_serialize(const ServerGlobalMessage *);
        ServerGlobalMessage* m_deserialize(const std::string &);
        void m_run();
        bool m_visible;
        Type m_type;
};

#endif // SERVERLIST_H_INCLUDED
