#ifndef H_NETWORKENGINE_H
#define H_NETWORKENGINE_H
#include "../Engine.h"
#include "../../precompiled/asio.h"
#include "../../precompiled/shared_ptr.h"
#include "TcpConnection.h"
#include "UdpConnection.h"
#include "../../Utils/Clock.h"

class NetworkEngine : public Engine
{
public:
    typedef boost::shared_ptr<boost::asio::io_service> service_ptr;
    typedef unsigned int client_id;
    NetworkEngine(EngineManager*);
    virtual ~NetworkEngine();
    virtual void setEngineManager(EngineManager*);
    virtual void handleMessage(EngineMessage&) = 0;
    virtual void work(const TimeDuration &elapsed) = 0;
    virtual EngineType getType();

    static std::string SHA1(const std::string &);

    const Clock& getClock() const;
protected:
    boost::shared_ptr<boost::asio::io_service> m_service;
    boost::shared_ptr<boost::asio::io_service::work> m_work;
    boost::thread m_thread_service;

    UdpConnection::pointer m_udpConnexion;
    Clock m_clock;
private:
    void m_run();
};

#endif // H_NETWORKENGINE_H
