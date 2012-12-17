#include "ServerList.h"
#include "../../Engine/NetworkEngine/NetworkEngine.h"
#include "../../Engine/NetworkEngine/NetworkIpAdressFinder.h"
#include "../../../../GlobalServer/src/Server.h"
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/regex.hpp>
#include <sstream>

ServerList::ServerList(Type t, StateManager *mgr) : State(mgr),
    m_service(new boost::asio::io_service),
    m_work(new boost::asio::io_service::work(*m_service)),
    m_visible(false),
    m_type(t)
{
    m_connection_udp = UdpConnection::create(m_service);
    m_connection_ssl = SslConnection::create(m_service, SslConnection::Type::CLIENT);
    switch (m_type)
    {
        case LAN:
        {
            m_connection_udp->socket()->set_option(boost::asio::ip::udp::socket::reuse_address(true));
            m_connection_udp->bind(boost::asio::ip::udp::endpoint(boost::asio::ip::address_v4::any(), 8888));
            m_connection_udp->socket()->set_option(boost::asio::ip::multicast::join_group(boost::asio::ip::address::from_string("225.125.145.155")));
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

    m_listServer = (CEGUI::Listbox*)m_window_mgr.createWindow("OgreTray/Listbox", "ListServerLan");
    m_listServer->setSize(CEGUI::UVector2(CEGUI::UDim(0.80, 0), CEGUI::UDim(0.80, 0)));
    //m_listServer->setPosition(CEGUI::UVector2(CEGUI::UDim(0.50-(m_listServer->getSize().d_x.d_scale/2), 0),
                                         //CEGUI::UDim(0+(m_window->getSize().d_y.d_scale/m_window->getChildCount()), 0)));
    CEGUI::System::getSingleton().getGUISheet()->addChildWindow(m_listServer);
    m_listServer->hide();
}
ServerList::~ServerList()
{
    m_work.reset();
    m_service->stop();
    m_service_thread.join();
    delete m_listServer;
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
    m_listServer->show();
    m_visible = true;
}
void ServerList::exit()
{
    m_listServer->hide();
    m_visible = false;
}
ret_code ServerList::work(unsigned int time)
{
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
            if(!m_connection_udp->hasData())
               return CONTINUE;
            EngineMessage *message;
            auto data = m_connection_udp->getData();
            message = NetworkEngine::deserialize(data.second, 0);
           /* boost::regex expName("^Server ("+m_connection->getData().first.address().to_string()+")[\w]*$");
            if (boost::regex_match(std::string(m_listServer->findItemWithText("Server ("+m_connection->getData().first.address().to_string()
                                                            +")"+message->strings[EngineMessageKey::SERVER_NAME]
                                                            +" "+message->strings[EngineMessageKey::MAP_NAME]
                                                            +" "+message->strings[EngineMessageKey::PLAYER_NUMBER]
                                                            +"/"+message->strings[EngineMessageKey::MAX_PLAYERS]
                                                            , NULL)->getText().c_str()), expName))
                return CONTINUE;
        */
            m_listServer->addItem(new CEGUI::ListboxTextItem("Server ("+data.first.address().to_string()
                                                            +")"+message->strings[EngineMessageKey::SERVER_NAME]
                                                            +" "+message->strings[EngineMessageKey::MAP_NAME]
                                                            +" "+message->strings[EngineMessageKey::PLAYER_NUMBER]
                                                            +"/"+message->strings[EngineMessageKey::MAX_PLAYERS]
                                                            ));
            delete message;
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
            if (m_connection_ssl->hasData())
                return CONTINUE;
            ServerGlobalMessage* message;
            message = m_deserialize(m_connection_ssl->getData());
            for (Server s : message->servers)
            {
                std::ostringstream joueur_connectes;
                joueur_connectes << s.nombre_joueurs_connectes;
                std::ostringstream joueur_max;
                joueur_max << s.nombre_joueurs_max;
                m_listServer->addItem(new CEGUI::ListboxTextItem("Server ("+s.ip
                                                            +")"+s.nom
                                                            +" "+s.carte_jouee
                                                            +" "+joueur_connectes.str()
                                                            +"/"+joueur_max.str()
                                                            ));
            }
            delete message;
        }
        break;
    }
    return CONTINUE;
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
