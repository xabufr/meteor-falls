#ifndef TERRESTRE_H
#define TERRESTRE_H

#include "Mobile.h"

class Equipe;
class btPairCachingGhostObject;
class btCollisionShape;
class Terrestre: public Mobile
{
    public:
        Terrestre(Equipe*, TypeUnite* type, int id);
        virtual ~Terrestre();
        void constructionFinished() override;
        void addPhysics();
        void update(const TimeDuration &time) override;

        void setNodePosition(const Vector3D &p);

private:
        btCollisionShape *m_shape;
};

#endif // TERRESTRE_H
