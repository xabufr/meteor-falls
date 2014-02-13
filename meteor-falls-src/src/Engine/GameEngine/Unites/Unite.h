#ifndef UNITE_H
#define UNITE_H
#include "../Map/WorldObject.h"
#include "TypeUnite.h"

class GameEngine;
class Equipe;
class Unite : public WorldObject
{
public:
    Unite(Equipe* ,TypeUnite* type, int id);
    virtual ~Unite();
    int id() const;
    const TypeUnite *type() const;
    virtual void update(float time);
    void subirDegats(int);
    int vie() const;
    void tuer();
    bool estVivant() const;
    Equipe *equipe() const;
    virtual bool destroyNeeded() const;
protected:
    int m_id;
    int m_vie;
    Equipe *m_equipe;
};

#endif // UNITE_H
