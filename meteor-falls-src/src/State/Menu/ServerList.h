#ifndef SERVERLIST_H_INCLUDED
#define SERVERLIST_H_INCLUDED

#include "../../Engine/NetworkEngine/UdpConnection.h"
#include "../../Engine/NetworkEngine/SslConnection.h"
#include "../../Engine/EngineMessage/EngineMessage.h"
#include "../../Engine/GameEngine/Joueur/Joueur.h"
#include "../State.h"
#include "../StateManager.h"
#include "../../precompiled/shared_ptr.h"
#include "../../precompiled/asio.h"
#include "../../../../GlobalServer/src/ServerGlobalMessage.h"
#include "../../../../GlobalServer/src/Server.h"
#include <list>
#include <OIS/OIS.h>

namespace CEGUI {
	class Window;
	class EventArgs;
	class  MultiColumnList;
} // namespace CEGUI
class ServerList : public State, public OIS::MouseListener
{
    public:
        enum Type{
            LAN,
            WAN
        };
        ServerList(Type, StateManager*, Joueur **j);
        ~ServerList();
        virtual bool isVisible();
        virtual void enter();
        virtual void exit();
        virtual ret_code work(unsigned int time);
        virtual bool mouseMoved(const OIS::MouseEvent &arg);
		virtual bool mousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id );
		virtual bool mouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id );
    private:
        Joueur **m_player;
        UdpConnection::pointer m_connection_udp;
        SslConnection::pointer m_connection_ssl;
		CEGUI::Window *m_wFiltres;
		CEGUI::Window *m_window, *m_btnJoindre;
		CEGUI::MultiColumnList *m_listeServeurs;
		std::list<Server*> m_serveurs;
		Server* m_selectedServer;
        boost::thread m_service_thread;
        boost::shared_ptr<boost::asio::io_service> m_service;
        boost::shared_ptr<boost::asio::io_service::work> m_work;
        StateManager *m_state_mgr;
        Type m_type;

        std::string m_serialize(const ServerGlobalMessage *);
        ServerGlobalMessage* m_deserialize(const std::string &);

		void addServer(Server*);
		void addServerView(Server *);
		void updateServer(Server *);
		void reloadViewWithFiltre();
        void m_run();
		bool m_retour;
        bool m_visible;
        bool m_item_selected(const CEGUI::EventArgs &);
		bool showFiltre(const CEGUI::EventArgs &);
		bool hideFiltre(const CEGUI::EventArgs &);
		bool refresh(const CEGUI::EventArgs &);
		bool close(const CEGUI::EventArgs&);
		bool join(const CEGUI::EventArgs&);
		bool serverSelected(const CEGUI::EventArgs&);
		bool updateFiltre(const CEGUI::EventArgs&);

		struct Filtre{
			bool operator()(Server *);
			bool full, empty, password;
		}m_filtre;
};

#endif // SERVERLIST_H_INCLUDED
