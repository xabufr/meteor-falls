#ifndef ENGINEMESSAGE_H
#define ENGINEMESSAGE_H

#include <vector>
#include <map>
#include <string>
#include "../../Utils/Vector3D.h"
#include "EngineMessageKey.h"
#include "EngineMessageType.h"
#include "../Engine.h"
#include "../../precompiled/serialization.h"

class EngineManager;

class EngineMessage{

    public:
        EngineMessage(EngineManager* p_engine_manager); //à faire
        int time, message;
        std::map<EngineMessageKey, int> ints;
        std::map<EngineMessageKey, double> doubles;
        std::map<EngineMessageKey, std::string> strings;
        std::map<EngineMessageKey, Vector3D> positions;
        void setFrom(Engine* p_from);
        void setFromType(EngineType p_from_type); //à faire
        void addTo(Engine* p_to);
        void addToType(EngineType p_to_type); //à faire
        Engine* getFrom();
        EngineType getFromType();
        std::vector<Engine*> getTo();
        std::vector<EngineType> getToType();

    protected:

    private:
        EngineManager* m_engine_manager;
        Engine* m_from;
        EngineType m_from_type;
        std::vector<Engine*> m_to;
        std::vector<EngineType> m_to_type;

        friend class boost::serialization::access;
        template<class Archive>
        void serialize(Archive& ar, const unsigned int version){
            ar & message & time & m_from_type & m_to_type & ints & doubles & strings & positions;
        }
};

#endif // ENGINEMESSAGE_H
