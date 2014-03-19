#include "rtsselectedunitscommand.h"
#include "../../Unites/Unite.h"
#include <Engine/EngineMessage/EngineMessage.h>
#include "../RTSState.h"
#include "../../ClientGameEngine.h"
#include <Engine/NetworkEngine/clientnetworkengine.h>

RTSSelectedUnitsCommand::RTSSelectedUnitsCommand(RTSState *rtsState): m_rtsState(rtsState)
{
}

void RTSSelectedUnitsCommand::changeSelection(const std::vector<WorldObject *> &selection)
{
    m_selection = selection;
    m_availableBuilds.clear();
    std::vector<const std::vector<TypeUnite *>*> available;
    for (WorldObject * object : m_selection)
    {
        Unite *unite = dynamic_cast<Unite *>(object);
        if (unite)
        {
            available.push_back(&unite->type()->construit());
        }
        else
        {
            available.clear();
            break;
        }
    }

    for (auto * types : available)
    {
        for (TypeUnite * type : *types)
        {
            bool add = true;
            for (const std::vector<TypeUnite *> *typesToTest : available)
            {
                auto it = std::find(typesToTest->begin(), typesToTest->end(), type);
                if (it == typesToTest->end())
                {
                    add = false;
                    break;
                }
            }
            if (add)
            {
                m_availableBuilds.insert(type);
            }
        }
    }
}

void RTSSelectedUnitsCommand::addBuild(const TypeUnite *type, int count)
{
    if (m_availableBuilds.find(type) != m_availableBuilds.end())
    {
        EngineMessage message(nullptr);
        message.message = mf::EngineMessageType::BUILD;
        message.ints[mf::EngineMessageKey::OBJECT_TYPE] = type->id();
        message.ints[mf::EngineMessageKey::COUNT] = count;
        message.ints[mf::EngineMessageKey::TEAM_ID] = m_rtsState->game()->getCurrentJoueur()->equipe()->id();
        ClientNetworkEngine *network = m_rtsState->game()->clientNetwork();
        for (WorldObject * object : m_selection)
        {
            Unite *unite = dynamic_cast<Unite*>(object);
            message.ints[mf::EngineMessageKey::BUILDER] = unite->id();
            network->sendToServerTcp(message);
        }
    }
}

const std::set<const TypeUnite *> RTSSelectedUnitsCommand::availableBuilds() const
{
    return m_availableBuilds;
}
