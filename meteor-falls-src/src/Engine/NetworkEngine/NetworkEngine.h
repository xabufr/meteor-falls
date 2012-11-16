#ifndef H_NETWORKENGINE_H
#define H_NETWORKENGINE_H
#include "Engine/Engine.h"
#include <boost/asio.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/thread.hpp>

class NetworkEngine : public Engine
{
public:
    typedef boost::shared_ptr<boost::asio::io_service> service_ptr;
    typedef unsigned int client_id;
    NetworkEngine();
    ~NetworkEngine();
    virtual void handleMessage(const EngineMessage&) = 0;
    virtual void work() = 0;
    virtual EngineType getType();
protected:
    boost::shared_ptr<boost::asio::io_service> m_service;
    boost::shared_ptr<boost::asio::io_service::work> m_work;
    boost::thread m_thread_service;

private:
    void m_run();
};

#endif // H_NETWORKENGINE_H
