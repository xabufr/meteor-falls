#ifndef ENGINEMESSAGE_H
#define ENGINEMESSAGE_H

#include <vector>
#include <map>
#include <string>
#include "../../Utils/Vector3D.h"
#include "../../Utils/Quaternion.h"
#include "EngineMessageKey.h"
#include "EngineMessageType.h"
#include "../Engine.h"
#include "../../precompiled/serialization.h"
#include "../EngineManager/EngineManager.h"
#include "../NetworkEngine/packet.h"

class EngineMessage
{

    public:
        EngineMessage(EngineManager* p_engine_manager); //à faire
        EngineMessage(EngineManager *p_engine_manager, Packet &packet);
        int message;
        int time;
        std::map<EngineMessageKey, int> ints;
        std::map<EngineMessageKey, double> doubles;
        std::map<EngineMessageKey, std::string> strings;
        std::map<EngineMessageKey, Vector3D> positions;
        std::map<EngineMessageKey, Quaternion> quaternions;
        void setFrom(Engine* p_from);
        void setFromType(EngineType p_from_type); //à faire
        void addTo(Engine* p_to);
        void addToType(EngineType p_to_type); //à faire
        Engine* getFrom();
        EngineType getFromType();
        std::vector<Engine*> getTo();
        std::vector<EngineType> getToType();
        void clearTo();
        Packet toPacket() const;

        static EngineMessage* clone(EngineMessage*);

        void init(EngineManager *p_engine_manager);
        void fromPacket(Packet &packet);
private:
        EngineManager* m_engine_manager;
        Engine* m_from;
        EngineType m_from_type;
        std::vector<Engine*> m_to;
        std::vector<EngineType> m_to_type;

        friend class boost::serialization::access;
        template<class Archive>
        void serialize(Archive& ar, const unsigned int version){
            ar & message & time & m_from_type & m_to_type & ints & doubles & strings & BOOST_SERIALIZATION_NVP(positions) & BOOST_SERIALIZATION_NVP(quaternions);
            if(m_engine_manager!=0)
            {
                if(m_from==0)
                    m_from = m_engine_manager->get(m_from_type);
                if(m_to.empty())
                {
                    for(EngineType t : m_to_type)
                    {
                        m_to.push_back(m_engine_manager->get(t));
                    }
                }
            }
        }
};

#endif // ENGINEMESSAGE_H
