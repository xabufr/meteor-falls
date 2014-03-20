#include "Batiment.h"
#include "TypeUnite.h"
#include "../Factions/Equipe.h"
#include "../../../precompiled/lexical_cast.h"
#include "../../ScriptEngine/MeshManager.h"
#include "../GameEngine.h"
#include <bullet/btBulletDynamicsCommon.h>
#include <bullet/btBulletCollisionCommon.h>

Batiment::Batiment(Equipe *equipe, TypeUnite* type, int id)
    : Unite(equipe, type, id)
{
    btCollisionShape *shape = MeshManager::get()->fromOgre(type->meshParameters().at("normal"))->shape;
    btRigidBody::btRigidBodyConstructionInfo BodyCI(0, nullptr, shape);
    m_body = new btRigidBody(BodyCI);
    btTransform tr;
    tr.setIdentity();
    m_body->setCenterOfMassTransform(tr);
    equipe->game()->bulletWorld()->addCollisionObject(m_body);
}

void Batiment::update(const TimeDuration &time)
{
    if(!m_buildTasks.empty())
    {
        TimeDuration &constructionDuration = m_buildTasks.front().first;
        constructionDuration+= time;
        Unite *unite = m_buildTasks.front().second;
        const TypeUnite *type = unite->type();
        if(type->temps_construction() <= constructionDuration.seconds())
        {
            unite->constructionFinished();
            m_buildTasks.pop();
        }
    }
}

void Batiment::addBuildTask(Unite *builded, const TimeDuration& elapsed)
{
    m_buildTasks.push(std::pair<TimeDuration, Unite*>(elapsed, builded));
}

std::queue<std::pair<TimeDuration, Unite *> > Batiment::buildStack() const
{
    return m_buildTasks;
}
