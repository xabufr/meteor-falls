#include "ServerList.h"
#include "../../State/Game/GameState.h"
#include "../../Engine/NetworkEngine/NetworkEngine.h"
#include "../../Engine/NetworkEngine/NetworkIpAdressFinder.h"
#include "../../../../GlobalServer/src/Server.h"
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/regex.hpp>
#include <boost/lexical_cast.hpp>
#include <sstream>
#include <CEGUI/CEGUI.h>

ServerList::ServerList(Type t, StateManager *mgr, Joueur **j) : State(mgr),
    m_service(new boost::asio::io_service),
    m_work(new boost::asio::io_service::work(*m_service)),
    m_visible(false),
    m_state_mgr(mgr),
    m_player(j),
    m_type(t),
	m_selectedServer(nullptr),
	m_retour(false)
{
    m_connection_udp = UdpConnection::create(m_service);
    m_connection_ssl = SslConnection::create(m_service, SslConnection::Type::CLIENT);
    switch (m_type)
    {
        case LAN:
        {
            m_connection_udp->socket()->set_option(boost::asio::ip::udp::socket::reuse_address(true));
            m_connection_udp->bind(boost::asio::ip::udp::endpoint(boost::asio::ip::address_v4::any(), 8888));
			try{
				m_connection_udp->socket()->set_option(boost::asio::ip::multicast::join_group(boost::asio::ip::address::from_string("225.125.145.155")));
			}
			catch(std::exception& e)
			{
				std::cerr << "-----------Network problem !!!------------" << std::endl;
				std::cerr << e.what() << std::endl;
			}
            m_connection_udp->startListen();
        }
        break;
        case WAN:
        {
            m_connection_ssl->connect(boost::asio::ip::tcp::endpoint(getAddress(*m_service, "178.32.103.114"), 6050));
            if (m_connection_ssl->isConnected())
            {
                ServerGlobalMessage *message = new ServerGlobalMessage();
                message->type = ServerGlobalMessageType::SERVER_LIST;
                m_connection_ssl->send(m_serialize(message));
                delete message;
            }
        }
        break;
    }
    m_service_thread = boost::thread(&ServerList::m_run, this);

    CEGUI::WindowManager &m_window_mgr = CEGUI::WindowManager::getSingleton();

	m_window   = m_window_mgr.loadWindowLayout("serveurs.layout");
	m_wFiltres = m_window->getChild("fenServeurs/fenFiltres");
	m_window->getChild("fenServeurs/btnFiltres")->subscribeEvent(CEGUI::PushButton::EventClicked,
			CEGUI::Event::Subscriber(&ServerList::showFiltre, this));
	m_wFiltres->subscribeEvent(CEGUI::FrameWindow::EventCloseClicked,
			CEGUI::Event::Subscriber(&ServerList::hideFiltre, this));
	m_wFiltres->getChild("fenServeurs/fenFiltres/btnOK")->subscribeEvent(CEGUI::PushButton::EventClicked,
			CEGUI::Event::Subscriber(&ServerList::hideFiltre, this));
	m_window->getChild("fenServeurs/btnRefresh")->subscribeEvent(CEGUI::PushButton::EventClicked,
			CEGUI::Event::Subscriber(&ServerList::refresh, this));
	m_window->getChild("fenServeurs/btnRetour")->subscribeEvent(CEGUI::PushButton::EventClicked,
			CEGUI::Event::Subscriber(&ServerList::close, this));
	m_window->subscribeEvent(CEGUI::FrameWindow::EventCloseClicked,
			CEGUI::Event::Subscriber(&ServerList::close, this));
	m_btnJoindre = m_window->getChild("fenServeurs/btnJoindre");
	m_btnJoindre->subscribeEvent(CEGUI::PushButton::EventClicked,
			CEGUI::Event::Subscriber(&ServerList::join, this));
	m_listeServeurs = (CEGUI::MultiColumnList*)m_window->getChild("fenServeurs/serveurs");
	m_listeServeurs->subscribeEvent(CEGUI::MultiColumnList::EventSelectionChanged,
			CEGUI::Event::Subscriber(&ServerList::serverSelected, this));
	m_listeServeurs->subscribeEvent(CEGUI::MultiColumnList::EventMouseDoubleClick,
			CEGUI::Event::Subscriber(&ServerList::join, this));
    CEGUI::System::getSingleton().getGUISheet()->addChildWindow(m_window);
	m_window->hide();
}
ServerList::~ServerList()
{
    m_work.reset();
    m_service->stop();
    m_service_thread.join();
	CEGUI::System::getSingleton().getGUISheet()->removeChildWindow(m_window);
	CEGUI::WindowManager::getSingleton().destroyWindow(m_window);
}
void ServerList::m_run()
{
    m_service->run();
}
bool ServerList::isVisible()
{
    return m_visible;
}
void ServerList::enter()
{
	m_window->setVisible(true);
	m_wFiltres->hide();
    m_visible = true;
	m_retour=false;
}
void ServerList::exit()
{
	m_window->hide();
    m_visible = false;
}
ret_code ServerList::work(unsigned int time)
{
	m_btnJoindre->setEnabled(m_selectedServer);
    switch (m_type)
    {
        case LAN:
        {
            if(!m_connection_udp->isConnected())
                return CONTINUE;
            if(m_connection_udp->hasError())
            {
                std::cout << std::endl << m_connection_udp->getError().message() << std::endl;
                return CONTINUE;
            }
			while(m_connection_udp->hasData()) 
			{
				EngineMessage *message;
				auto data = m_connection_udp->getData();
				message = NetworkEngine::deserialize(data.second, 0);
				if(message->message==EngineMessageType::SERVER_INFO)
				{
					Server *s =  new Server(data.first.address().to_string(),
							std::string(message->strings[EngineMessageKey::SERVER_NAME]),
							std::string(""),
							message->ints[EngineMessageKey::MAX_PLAYERS],
							message->ints[EngineMessageKey::PLAYER_NUMBER],
							false,
							std::string(message->strings[EngineMessageKey::MAP_NAME]),
							std::string(""),
							0.0
							);
					addServer(s);
				}
				delete message;
			}
        }
        break;
        case WAN:
        {
            if (!m_connection_ssl->isConnected())
                return CONTINUE;
            if (m_connection_ssl->hasError())
            {
                std::cout << std::endl << m_connection_ssl->getError().message() << std::endl;
                return CONTINUE;
            }
			while(m_connection_ssl->hasData()) 
			{
				ServerGlobalMessage* message;
				message = m_deserialize(m_connection_ssl->getData());
				for (Server s : message->servers)
					addServer(new Server(s));

				delete message;
			}
        }
        break;
    }
    return (m_retour) ?ret_code::FINISHED:ret_code::CONTINUE;
}
bool ServerList::m_item_selected(const CEGUI::EventArgs&)
{
    /*for (size_t i=0; i<m_listServer->getItemCount(); ++i)
        if (m_listServer->getListboxItemFromIndex(i)->isSelected())
        {
            Server *server = static_cast<Server*>(m_listServer->getListboxItemFromIndex(i)->getUserData());
            switch (m_type)
            {
                case LAN:
                    m_state_mgr->addState(new GameState(m_state_mgr, EngineManager::Type::CLIENT_LAN, server->ip, "", *m_player));
                    break;
                case WAN:
                    break;
            }
        }*/
    return true;
}
std::string ServerList::m_serialize(const ServerGlobalMessage *message)
{
    std::ostringstream os;
    boost::archive::text_oarchive archive(os);
    archive << *message;
    return os.str();
}
ServerGlobalMessage* ServerList::m_deserialize(const std::string &data)
{
    ServerGlobalMessage *message = new ServerGlobalMessage();
    std::istringstream iss(data);
    boost::archive::text_iarchive archive(iss);
    archive >> *message;
    return message;
}
bool ServerList::mouseMoved(const OIS::MouseEvent& arg)
{
    return true;
}
bool ServerList::mousePressed(const OIS::MouseEvent& arg, OIS::MouseButtonID id)
{
    return true;
}
bool ServerList::mouseReleased(const OIS::MouseEvent& arg, OIS::MouseButtonID id)
{
    return true;
}
bool ServerList::showFiltre(const CEGUI::EventArgs&)
{
	m_wFiltres->show();
	return true;
}
bool ServerList::hideFiltre(const CEGUI::EventArgs&)
{
	m_wFiltres->hide();
	return true;
}
bool ServerList::refresh(const CEGUI::EventArgs &)
{
	for(Server *s : m_serveurs)
		delete s;
	m_serveurs.clear();
	m_listeServeurs->resetList();
	return true;
}
bool ServerList::join(const CEGUI::EventArgs&)
{
	m_state_mgr->addState(new GameState(m_state_mgr, EngineManager::Type::CLIENT_LAN, m_selectedServer->ip, "", *m_player));
	return true;
}
bool ServerList::close(const CEGUI::EventArgs&)
{
	m_retour=true;
	return true;
}
bool ServerList::serverSelected(const CEGUI::EventArgs&)
{
	m_selectedServer = (m_listeServeurs->getFirstSelectedItem()) ?
		(Server*)m_listeServeurs->getFirstSelectedItem()->getUserData():nullptr;
	return true;
}
void ServerList::addServer(Server* s)
{
	for(Server *s_stored : m_serveurs)
	{
		if(s->ip == s_stored->ip)
		{
			*s_stored = *s;
			delete s;
			updateServer(s_stored);
			return;
		}
	}
	m_serveurs.push_back(s);
	addServerView(s);
}
void ServerList::addServerView(Server *s)
{
	unsigned int row = m_listeServeurs->addRow();
	CEGUI::ListboxTextItem *item = new CEGUI::ListboxTextItem("", 0);
	item->setSelectionBrushImage("TaharezLook", "MultiListSelectionBrush");
	item->setUserData(s);
	m_listeServeurs->setItem(item, 0, row);

	item = new CEGUI::ListboxTextItem(s->ip, 0);
	item->setSelectionBrushImage("TaharezLook", "MultiListSelectionBrush");
	item->setUserData(s);
	m_listeServeurs->setItem(item, 1, row);

	item = new CEGUI::ListboxTextItem("", 0);
	item->setSelectionBrushImage("TaharezLook", "MultiListSelectionBrush");
	item->setUserData(s);
	m_listeServeurs->setItem(item, 2, row);

	item = new CEGUI::ListboxTextItem("", 0);
	item->setSelectionBrushImage("TaharezLook", "MultiListSelectionBrush");
	item->setUserData(s);
	m_listeServeurs->setItem(item, 3, row);

	item = new CEGUI::ListboxTextItem("", 0);
	item->setSelectionBrushImage("TaharezLook", "MultiListSelectionBrush");
	item->setUserData(s);
	m_listeServeurs->setItem(item, 4, row);
	updateServer(s);
}
void ServerList::updateServer(Server *s)
{
	size_t rows = m_listeServeurs->getRowCount();
	int row = -1;
	for(size_t i=0;i<rows;++i)
	{
		if(m_listeServeurs->getItemAtGridReference(CEGUI::MCLGridRef(i, 0))->getUserData() == s)
		{
			row = i;
			break;
		}
	}
	if(row != -1)
	{
		CEGUI::ListboxTextItem *item;
		item = (CEGUI::ListboxTextItem*)m_listeServeurs->getItemAtGridReference(CEGUI::MCLGridRef(row, 0));
		item->setText(s->nom);

		item = (CEGUI::ListboxTextItem*)m_listeServeurs->getItemAtGridReference(CEGUI::MCLGridRef(row, 1));
		item->setText(s->ip);

		std::string joueurs = boost::lexical_cast<std::string>(s->nombre_joueurs_connectes);
		joueurs += "/";
		joueurs += boost::lexical_cast<std::string>(s->nombre_joueurs_max);
		item = (CEGUI::ListboxTextItem*)m_listeServeurs->getItemAtGridReference(CEGUI::MCLGridRef(row, 2));
		item->setText(joueurs);

		item = (CEGUI::ListboxTextItem*)m_listeServeurs->getItemAtGridReference(CEGUI::MCLGridRef(row, 3));
		item->setText(boost::lexical_cast<std::string>(0));

		item = (CEGUI::ListboxTextItem*)m_listeServeurs->getItemAtGridReference(CEGUI::MCLGridRef(row, 4));
		item->setText((s->passwd) ?"OUI":"NON");
		m_listeServeurs->handleUpdatedItemData();
	}
}
