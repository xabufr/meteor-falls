#include <iostream>
#include <string>
#include "Engine/NetworkEngine/SslConnection.h"
#include "Engine/NetworkEngine/NetworkIpAdressFinder.h"
#include "../GlobalServer/src/ServerGlobalMessage.h"
#include "../meteor-falls-src/src/precompiled/serialization.h"

using namespace std;
void runNetwork(boost::shared_ptr<boost::asio::io_service> service);
void runCommand(SslConnection::pointer, boost::shared_ptr<boost::asio::io_service>);

std::string serialize(const ServerGlobalMessage *message)
{
    std::ostringstream os;
    boost::archive::text_oarchive archive(os);
    archive << *message;
    return os.str();
}

ServerGlobalMessage* deserialize(const std::string &data)
{
    ServerGlobalMessage *message;
    std::istringstream iss(data);
    boost::archive::text_iarchive archive(iss);
    archive >> *message;
    return message;
}
int main()
{
    std::cout << "Console d'administration" << std::endl;
    std::string adresse;
    std::cout << "Adresse serveur: ";
    std::cin >> adresse;
    std::cout << "Résolution de l'adresse..." << std::endl;
    boost::shared_ptr<boost::asio::io_service> service(new boost::asio::io_service);
    boost::shared_ptr<boost::asio::io_service::work> worker(new boost::asio::io_service::work(*service));

    SslConnection::pointer connexion = SslConnection::create(service, SslConnection::Type::CLIENT);
    bool error;
    boost::asio::ip::address adresseIP = getAddress(*service, adresse, &error);
    if(error)
    {
        std::cout << "Adresse non résolvable" << std::endl;
        return -1;
    }
    std::cout << "Connexion à " << adresseIP<<std::endl;
    connexion->connect(boost::asio::ip::tcp::endpoint(adresseIP, 6050));
    boost::thread network = boost::bind(&runNetwork, service);

    while(1)
    {
        std::cout << ".";
        std::cout.flush();
        if(connexion->isConnected())
            break;
        if(connexion->hasError())
        {
            std::cout << std::endl << connexion->getError().message() << std::endl;
            return 0;
        }
        boost::this_thread::sleep(boost::posix_time::milliseconds(150));
    }
    std::cout << std::endl << "Connexion réussie" << std::endl;

    std::string login, motpasse;

    std::cout << "Login: ";
    std::cin >> login;
    std::cout << "Password: ";
    std::cin >> motpasse;
    std::cout << "Authentification"<<std::endl;

    ServerGlobalMessage message;
    message.type = ServerGlobalMessageType::ADMIN_LOGIN;
    message.admin.set_pseudo(login);
    message.admin.set_pseudo(motpasse);
    message.admin.set_cmd("connexion");

    std::cout<<serialize(&message)<<std::endl;

    connexion->send(serialize(&message));

    boost::thread commandThread(boost::bind(&runCommand, connexion, service));

    boost::this_thread::sleep(boost::posix_time::milliseconds(150));

    while(commandThread.timed_join(boost::posix_time::milliseconds(50)))
    {
        while(connexion->hasError())
        {
            std::cout<<connexion->getError().message()<<std::endl;
        }
        while(connexion->hasData())
        {
            std::string data = connexion->getData();
            std::cout << data;
        }
    }
    worker.reset();
    connexion.reset();
    network.join();

    return 0;
}

void runNetwork(boost::shared_ptr<boost::asio::io_service> service)
{
    service->run();
}
void runCommand(SslConnection::pointer, boost::shared_ptr<boost::asio::io_service>)
{
    std::string command;
    while(1)
    {
        std::cout << ">" << std::endl;
        std::cin>>command;
        if(command=="exit")
            break;
    }
}
