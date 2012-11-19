#include "Engine/NetworkEngine/NetworkEngine.h"
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include "Engine/EngineMessage/EngineMessage.h"
#include <iostream>


EngineType NetworkEngine::getType()
{
    return EngineType::NetworkEngine;
}

NetworkEngine::NetworkEngine(EngineManager* manager):
    Engine(manager),
    m_service(new boost::asio::io_service),
    m_work(new boost::asio::io_service::work(*m_service))
{
    m_thread_service = boost::thread(&NetworkEngine::m_run, this);
}
NetworkEngine::~NetworkEngine()
{
    m_work.reset();
    m_service->stop();
    m_thread_service.join();
}

void NetworkEngine::m_run()
{
    m_service->run();
}
std::string NetworkEngine::serialize(const EngineMessage* message)
{
    std::ostringstream os;
    boost::archive::text_oarchive archive(os);
    archive << *message;
    return os.str();
}

EngineMessage* NetworkEngine::deserialize(const std::string& data)
{
    EngineMessage *message = new EngineMessage(m_manager);
    std::istringstream iss(data);
    boost::archive::text_iarchive archive(iss);
    archive >> *message;
    return message;
}
void NetworkEngine::setEngineManager(EngineManager *mng)
{
    m_manager=mng;
}
