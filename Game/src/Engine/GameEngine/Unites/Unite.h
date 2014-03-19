#ifndef UNITE_H
#define UNITE_H
#include "../Map/WorldObject.h"
#include "TypeUnite.h"

class GameEngine;
class Equipe;
class btDynamicsWorld;
class Unite : public WorldObject
{
public:
    Unite(Equipe* ,TypeUnite* type, int id);
    virtual ~Unite();
    const TypeUnite *type() const;
    virtual void update(const TimeDuration &time);
    void subirDegats(int);
    int vie() const;
    void tuer();
    bool estVivant() const;
    Equipe *equipe() const;
    virtual bool destroyNeeded() const;
    bool isConstructed() const;
    virtual void constructionFinished();

protected:
    int m_vie;
    bool m_constructed;
    Equipe *m_equipe;
    btDynamicsWorld *m_physicalWorld;
};

#endif // UNITE_H
