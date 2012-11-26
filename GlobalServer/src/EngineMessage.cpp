#include "../../meteor-falls-src/src/Engine/EngineMessage/EngineMessage.h"
#include "../../meteor-falls-src/src/Engine/EngineManager/EngineManager.h"

EngineMessage::EngineMessage(EngineManager* p_engine_manager){
    m_engine_manager = p_engine_manager;
}

void EngineMessage::setFrom(Engine* p_from){
    m_from = p_from;
    m_from_type = p_from->getType();
}

void EngineMessage::setFromType(EngineType p_from_type){
    m_from_type = p_from_type;
    m_from = m_engine_manager->get(p_from_type);
}

void EngineMessage::addTo(Engine* p_to){
    for(unsigned int i=0;i<=m_to.size();i++){
        if(p_to == m_to[i]){
            return ;
        }
    }
    m_to.push_back(p_to);
    m_to_type.push_back(p_to->getType());
}

void EngineMessage::addToType(EngineType p_to_type){
    size_t i;
    for(i=0;i<=m_to_type.size();i++){
        if(p_to_type == m_to_type[i]){
            return ;
        }
    }
    m_to_type.push_back(p_to_type);
    m_to.push_back(m_engine_manager->get(p_to_type));
}

Engine* EngineMessage::getFrom(){
    return m_from;
}

EngineType EngineMessage::getFromType(){
    return m_from_type;
}

std::vector<Engine*> EngineMessage::getTo(){
    return m_to;
}

std::vector<EngineType> EngineMessage::getToType(){
    return m_to_type;
}
