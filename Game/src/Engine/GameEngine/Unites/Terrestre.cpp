#include "Terrestre.h"
#include <btBulletCollisionCommon.h>
#include <btBulletDynamicsCommon.h>
#include "BulletCollision/CollisionDispatch/btGhostObject.h"

Terrestre::Terrestre(Equipe *e, TypeUnite *type, int id) : Mobile(e, type, id), m_shape(nullptr)
{
    m_constructed = false;
}
Terrestre::~Terrestre()
{
    if (m_shape)
    {
        delete m_shape;
    }
}

void Terrestre::constructionFinished()
{
    Mobile::constructionFinished();
    addPhysics();
}

void Terrestre::addPhysics()
{
    m_shape = new btCapsuleShape(1, 1);

    btRigidBody::btRigidBodyConstructionInfo constructionInfos(10, this, m_shape);
    m_body = new btRigidBody(constructionInfos);

    m_body->setCollisionShape(m_shape);
    m_physicalWorld->addRigidBody(m_body);
}

void Terrestre::update(const TimeDuration &time)
{
    Mobile::update(time);
}

void Terrestre::setNodePosition(const Vector3D &p)
{
    m_position = p;
}
