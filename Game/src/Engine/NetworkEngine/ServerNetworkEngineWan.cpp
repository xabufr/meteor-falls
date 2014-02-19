#include "ServerNetworkEngineWan.h"
#include "../../../../GlobalServer/src/Server.h"
#include "../../../../GlobalServer/src/ServerGlobalMessage.h"
#include <boost/archive/text_oarchive.hpp>
#include "NetworkIpAdressFinder.h"
#include "../../Utils/Exception/BasicException.h"
#include "../EngineMessage/EngineMessage.h"
#include "../GameEngine/Joueur/Joueur.h"

ServerNetworkEngineWan::ServerNetworkEngineWan(EngineManager* mng, unsigned short port):
ServerNetworkEngine(mng, port)
{
    m_connexionServerG = SslConnection::create(m_service, SslConnection::CLIENT);
    m_udpConnexion = UdpConnection::create(m_service);
    bool error;
    boost::asio::ip::address adr = getAddress(*m_service, "178.32.103.114", &error);
    if(error)
    {
        THROW_BASIC_EXCEPTION("Adresse non résolvable");
    }
    m_connexionServerG->connect(boost::asio::ip::tcp::endpoint(adr, 80));
}
ServerNetworkEngineWan::~ServerNetworkEngineWan()
{
}
void ServerNetworkEngineWan::sendAllUdp(const std::string& data)
{
}
void ServerNetworkEngineWan::announceServer()
{
    m_timer_seed->expires_from_now(boost::posix_time::seconds(5));
    m_timer_seed->async_wait(boost::bind(&ServerNetworkEngineWan::m_handleSendWanInfo, this, _1));
}
void ServerNetworkEngineWan::m_handleSendWanInfo(const boost::system::error_code&)
{
    m_timer_seed->expires_from_now(boost::posix_time::seconds(5));
    m_timer_seed->async_wait(boost::bind(&ServerNetworkEngineWan::m_handleSendWanInfo, this, _1));

    ServerGlobalMessage message;
    message.type = ServerGlobalMessageType::SERVER_UP;
    Server server;
    server.passwd=false;
    server.nom=m_server_name;
    server.nombre_joueurs_connectes=m_clients.size();
    server.nombre_joueurs_max=m_max_clients;
    server.carte_jouee=m_map_name;
    message.servers.push_back(server);

    std::ostringstream os;
    boost::archive::text_oarchive ar(os);
    ar << message;
    m_connexionServerG->send(os.str());
    std::cout << "Envoi données"<<std::endl;
}
void ServerNetworkEngineWan::work(const TimeDuration &elapsed)
{
    if(!m_hasSendtoG&&m_connexionServerG->isConnected())
    {
        std::cout << "Connexion réussie"<<std::endl;
        announceServer();
        m_hasSendtoG=true;
    }
    if(m_connexionServerG->hasError())
    {
        THROW_BASIC_EXCEPTION(m_connexionServerG->getError().message());
    }
    while (m_connexionServerG->hasData())
    {
        std::string data = m_connexionServerG->getData();
        ServerGlobalMessage message;
        std::istringstream iss(data);
        boost::archive::text_iarchive ar(iss);
        ar>>message;
        if (message.type==ServerGlobalMessageType::GET_IP_SESSION)
        {
            boost::mutex::scoped_lock(m_mutex_clients);
            ServerClient *cli = nullptr;
            for(ServerClient &c : m_clients)
            {
                if(c.data->session==message.player.num_session)
                {
                    cli=&c;
                    break;
                }
            }
            if(cli==nullptr)
                continue;
            if(cli->tcp()->socket().remote_endpoint().address().to_string()==message.player.ip)
            {
                //On peut ajouter le client
                cli->data->isConnected=true;
                cli->joueur = new Joueur;
                cli->joueur->setNom(message.player.pseudo);
                EngineMessage messageLogin(m_manager);
                messageLogin.message = EngineMessageType::NEW_PLAYER;
                messageLogin.ints[EngineMessageKey::PLAYER_NUMBER] = cli->id();
                messageLogin.strings[EngineMessageKey::PSEUDO] = cli->joueur->getNom();
                sendToAllTcp(&messageLogin);
            }
            else //Le client n'est pas qui il prétend
            {
                EngineMessage messageQuit(m_manager);
                messageQuit.message = EngineMessageType::KICK;
                sendToTcp(*cli, &messageQuit);
            }
        }
    }
    ServerNetworkEngine::work(elapsed);
}
void ServerNetworkEngineWan::m_addNewPlayer(client_id id, EngineMessage* message)
{
    std::string password = message->strings[EngineMessageKey::PASSWORD];
    std::string session = message->strings[EngineMessageKey::SESSION];
    boost::mutex::scoped_lock(m_mutex_clients);
    ServerClient* client=nullptr;
    for(ServerClient &c : m_clients)
    {
        if(c.id()==id)
        {
            client=&c;
        }
    }
    if(client==nullptr)
        return;
    if(password == SHA1(password+client->data->sel))
    {
        client->data->session = session;
        m_recupererSession(client);
    }
    else
    {
        EngineMessage message(m_manager);
        message.message = EngineMessageType::LOGIN_RESULT;
        message.ints[EngineMessageKey::PLAYER_NUMBER] = -1;
        client->tcp()->sendPacket(message.toPacket());
    }
}
void ServerNetworkEngineWan::m_recupererSession(ServerClient* sc)
{
    ServerGlobalMessage message;
    message.type               = ServerGlobalMessageType::GET_IP_SESSION;
    message.player.num_session = sc->data->session;
    std::ostringstream os;
    boost::archive::text_oarchive ar(os);
    ar << message;
    m_connexionServerG->send(os.str());
}
