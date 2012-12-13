#include "ServerList.h"
#include "../../Engine/NetworkEngine/NetworkEngine.h"
#include "../../Engine/NetworkEngine/NetworkIpAdressFinder.h"
#include <boost/regex.hpp>

ServerList::ServerList(Type t, StateManager *mgr) : State(mgr),
    m_service(new boost::asio::io_service),
    m_work(new boost::asio::io_service::work(*m_service)),
    m_visible(false)
{
    m_connection = UdpConnection::create(m_service);
    switch (t)
    {
        case LAN:
        {
            //m_connection->socket()->open(80);
            m_connection->socket()->set_option(boost::asio::ip::udp::socket::reuse_address(true));
            m_connection->bind(boost::asio::ip::udp::endpoint(boost::asio::ip::address_v4::any(), 8888));
            m_connection->socket()->set_option(boost::asio::ip::multicast::join_group(boost::asio::ip::address::from_string("225.125.145.155")));
            m_connection->startListen();
        }
        break;
        case WAN:
        {
            //m_connection->bind(boost::asio::ip::udp::endpoint(getAddress(*m_service, "178.32.103.114"),));
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
    if(!m_connection->isConnected())
        return CONTINUE;
    if(m_connection->hasError())
    {
        std::cout << std::endl << m_connection->getError().message() << std::endl;
        return CONTINUE;
    }
    EngineMessage *message;

    if(m_connection->hasData())
    {
        std::cout << "serveur trouvé" << std::endl;
		auto data = m_connection->getData();
		std::cout << data.second << std::endl;
        message = NetworkEngine::deserialize(data.second, 0);
		std::cout << "message extrait" << std::endl;
       /* boost::regex expName("^Server ("+m_connection->getData().first.address().to_string()+")[\w]*$");
        if (boost::regex_match(std::string(m_listServer->findItemWithText("Server ("+m_connection->getData().first.address().to_string()
                                                        +")"+message->strings[EngineMessageKey::SERVER_NAME]
                                                        +" "+message->strings[EngineMessageKey::MAP_NAME]
                                                        +" "+message->strings[EngineMessageKey::PLAYER_NUMBER]
                                                        +"/"+message->strings[EngineMessageKey::MAX_PLAYERS]
                                                        , NULL)->getText().c_str()), expName))
            return CONTINUE;
*/
        m_listServer->addItem(new CEGUI::ListboxTextItem("Server ("+m_connection->getData().first.address().to_string()
                                                        +")"+message->strings[EngineMessageKey::SERVER_NAME]
                                                        +" "+message->strings[EngineMessageKey::MAP_NAME]
                                                        +" "+message->strings[EngineMessageKey::PLAYER_NUMBER]
                                                        +"/"+message->strings[EngineMessageKey::MAX_PLAYERS]
                                                        ));
        delete message;
    }
    return CONTINUE;
}
