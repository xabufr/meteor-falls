#include "MessageEngine.h"
#include "Engine.h"

EngineMessage::EngineMessage()
{
    //ctor
}

EngineMessage::~EngineMessage()
{
    //dtor
}

void EngineMessage::setFrom(Engine p_from){
    m_from = p_from;
    m_from_type = p_from->getType();
}

void EngineMessage::addTo(Engine* p_to){
    int i;
    for(i=0;i<=m_to.size();i++){
        if(p_to == m_to[i]){
            return ;
        }
    }
    m_to.push_back(p_to);
    m_toType.push_back(p_to->getType());
}

Engine* EngineMessage::getFrom(){
    return m_from;
}

EngineType EngineMessage::getFromType(){
    return m_from_type;
}

vector<Engine*> EngineMessage::getTo(){
    return m_to;
}

vector<EngineType> EngineMessage::getToType(){
    return m_to_type;
}
