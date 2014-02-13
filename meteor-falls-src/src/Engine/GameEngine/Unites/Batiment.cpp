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
    m_isconstructed = false;
    btCollisionShape *shape = MeshManager::get()->fromOgre(type->meshParameters().at("normal"))->shape;
    btRigidBody::btRigidBodyConstructionInfo BodyCI(0, nullptr, shape);
    m_body = new btRigidBody(BodyCI);
    btTransform tr;
    tr.setIdentity();
    m_body->setCenterOfMassTransform(tr);
    equipe->game()->bulletWorld()->addCollisionObject(m_body);
}
bool Batiment::isConstructed()
{
    return m_isconstructed;
}
