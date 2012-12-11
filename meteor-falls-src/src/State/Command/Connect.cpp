#include <iostream>
#include <sstream>
#include <string>
#include "Connect.h"
#include "../Console.h"
#include "Engine/NetworkEngine/NetworkIpAdressFinder.h"
#include "precompiled/serialization.h"
#include <boost/bind.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/string.hpp>

Connect::Connect():Command("connect"),
m_service(new boost::asio::io_service),
m_work(new boost::asio::io_service::work(*m_service))
{

}

Connect::~Connect()
{
    m_work.reset();
    m_service->stop();
    m_thread_service.join();
}


std::string Connect::m_serialize(const ServerGlobalMessage *message)
{
    std::ostringstream os;
    boost::archive::text_oarchive archive(os);
    archive << *message;
    return os.str();
}

ServerGlobalMessage* Connect::m_deserialize(const std::string &data)
{
    ServerGlobalMessage *message = new ServerGlobalMessage();
    std::istringstream iss(data);
    boost::archive::text_iarchive archive(iss);
    archive >> *message;
    return message;
}
void Connect::use(std::string s)
{
    int debut = 9;
    std::string adresse = s.substr(debut, (s.substr(debut).find(' ')));
    SslConnection::pointer connexion = SslConnection::create(m_service, SslConnection::Type::CLIENT);
    bool error;
    boost::asio::ip::address adresseIP = getAddress(*m_service, adresse, &error);

    connexion->connect(boost::asio::ip::tcp::endpoint(adresseIP, 6050));
    m_thread_service = boost::thread(&Connect::m_run, this);

    while(1)
    {
        if(connexion->isConnected())
            break;
        if(connexion->hasError())
        {
            std::cout << std::endl << connexion->getError().message() << std::endl;
            return;
        }
        boost::this_thread::sleep(boost::posix_time::milliseconds(150));
    }
    debut += adresse.size()+1;
    std::string login = s.substr(debut, (s.substr(debut).find(' ')));
    debut += login.size()+1;
    std::string motpasse = s.substr(debut);

    ServerGlobalMessage message;
    message.type = ServerGlobalMessageType::ADMIN_LOGIN;
    message.admin.pseudo=login;
    message.admin.passwd=motpasse;
    message.admin.cmd="connexion";

    connexion->send(m_serialize(&message));

    while(1)
    {
        if(connexion->hasData())
            break;
        if(connexion->hasError())
        {
            std::cout << std::endl << connexion->getError().message() << std::endl;
            return;
        }
        boost::this_thread::sleep(boost::posix_time::milliseconds(150));
    }
    std::string data = connexion->getData();
    ServerGlobalMessage *messageAuth = m_deserialize(data);
    Console::get()->setAdmin(messageAuth->make);
    char n = Console::get()->getConsole()->getText().substr(Console::get()->getConsole()->getText().size()-1).c_str()[0];//retoure à la ligne
    if (messageAuth->make)
        Console::get()->getConsole()->setText(Console::get()->getConsole()->getText().substr(0, Console::get()->getConsole()->getText().size()-1)+"=>Connected\n"+n);
    else
        Console::get()->getConsole()->setText(Console::get()->getConsole()->getText().substr(0, Console::get()->getConsole()->getText().size()-1)+"=>Connection error\n"+n);

    delete messageAuth;
}

void Connect::m_run()
{
    m_service->run();
}
