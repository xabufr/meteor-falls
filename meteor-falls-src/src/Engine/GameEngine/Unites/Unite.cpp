#include "Unite.h"

Unite::Unite(Ogre::SceneManager* mng, TypeUnite* type, int id): ObjetTerrain(mng)
{
    //ctor
}

TypeUnite* Unite::GetType()
{
    return m_Type;
}

Unite::~Unite()
{
    //dtor
}
