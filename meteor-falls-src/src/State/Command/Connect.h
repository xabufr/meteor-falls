#ifndef CONNECT_H_INCLUDED
#define CONNECT_H_INCLUDED

#include "Command.h"
#include "Engine/NetworkEngine/SslConnection.h"
#include "../../GlobalServer/src/ServerGlobalMessage.h"
#include <boost/asio.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/thread.hpp>

class Connect : public Command
{
    public:
        Connect();
        ~Connect();
        virtual void use(std::string s);
    protected:
        boost::shared_ptr<boost::asio::io_service> m_service;
        boost::shared_ptr<boost::asio::io_service::work> m_work;
        boost::thread m_thread_service;
    private:
        void m_runNetwork(boost::shared_ptr<boost::asio::io_service> service);
        void m_runCommand(SslConnection::pointer, boost::shared_ptr<boost::asio::io_service>, std::string login, std::string pass);
        void m_run();
        std::string m_serialize(const ServerGlobalMessage *message);
        ServerGlobalMessage* m_deserialize(const std::string &data);
};


#endif // CONNECT_H_INCLUDED
