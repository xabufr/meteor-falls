#ifndef ENGINEMESSAGE_H
#define ENGINEMESSAGE_H

#include <vector>
#include <map>
#include <string>
#include "../../Utils/Vector3D.h"
#include "EngineMessageKey.h"
#include "EngineMessageType.h"
#include "../Engine.h"

class EngineMessage{

    public:
        int time;
        std::map<EngineMessageKey, int> ints;
        std::map<EngineMessageKey, double> doubles;
        std::map<EngineMessageKey, std::string> strings;
        std::map<EngineMessageKey, Vector3D> positions;
        void setFrom(Engine* p_from);
        void addTo(Engine* p_to);
        Engine* getFrom();
        EngineType getFromType();
        std::vector<Engine*> getTo();
        std::vector<EngineType> getToType();

    protected:

    private:
        Engine* m_from;
        EngineType m_from_type;
        std::vector<Engine*> m_to;
        std::vector<EngineType> m_to_type;

};

#endif // ENGINEMESSAGE_H
