#ifndef H_NETWORKENGINE_H
#define H_NETWORKENGINE_H
#include "../Engine.h"
#include "precompiled/asio.h"
#include "precompiled/shared_ptr.h"


class NetworkEngine : public Engine
{
public:
    typedef boost::shared_ptr<boost::asio::io_service> service_ptr;
    typedef unsigned int client_id;
    NetworkEngine(EngineManager*);
    ~NetworkEngine();
    virtual void setEngineManager(EngineManager*);
    virtual void handleMessage(const EngineMessage&) = 0;
    virtual void work() = 0;
    virtual EngineType getType();

    static std::string serialize(const EngineMessage*);
    EngineMessage* deserialize(const std::string &);
protected:
    boost::shared_ptr<boost::asio::io_service> m_service;
    boost::shared_ptr<boost::asio::io_service::work> m_work;
    boost::thread m_thread_service;

private:
    void m_run();
};

#endif // H_NETWORKENGINE_H
