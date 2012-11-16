#include "Engine/NetworkEngine/NetworkEngine.h"

EngineType NetworkEngine::getType()
{
    return EngineType::NetworkEngine;
}

NetworkEngine::NetworkEngine():
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
