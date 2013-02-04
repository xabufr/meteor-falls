#include "NetworkEngine.h"
#include "../../precompiled/serialization.h"
#include "../EngineMessage/EngineMessage.h"
#include <iostream>
#include <boost/uuid/sha1.hpp>

EngineType NetworkEngine::getType()
{
    return EngineType::NetworkEngineType;
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
    return deserialize(data, m_manager);
}
EngineMessage* NetworkEngine::deserialize(const std::string& data, EngineManager* mng)
{
    EngineMessage *message = new EngineMessage(mng);
    std::istringstream iss(data);
    boost::archive::text_iarchive archive(iss);
    archive >> *message;
    return message;
}
void NetworkEngine::setEngineManager(EngineManager *mng)
{
    m_manager=mng;
}
std::string NetworkEngine::SHA1(const std::string& chaine)
{
	boost::uuids::detail::sha1 sha1; 
	sha1.process_bytes(chaine.c_str(), chaine.length());
	unsigned int hash[5];
	sha1.get_digest(hash);
	std::ostringstream os;
	os << std::hex << std::setfill('0') << std::setw(sizeof(int)*2);
	for(int i=0; i<5;++i)
		os << hash[i];
	return os.str();
}
const Clock& NetworkEngine::getClock() const
{
	return m_clock;
}
