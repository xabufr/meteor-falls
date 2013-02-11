#include "UniteFactory.h"
#include "../Factions/Equipe.h"
#include "../Factions/Faction.h"
#include "TypeUnite.h"
#include "Batiment.h"

UniteFactory::UniteFactory(Equipe* e): m_equipe(e)
{
	m_last_id = 0;
}
UniteFactory::~UniteFactory()
{
}
Unite* UniteFactory::create(Ogre::SceneManager* scene, UnitId idType, UnitId id)
{
	if(id==0)
		id = m_last_id++;

    TypeUnite *type = m_equipe->faction()->getType(idType);
	Unite *unit = nullptr;		

    if(type==0)
        return unit;
    switch(type->type())
    {
    case TypeUnite::BATIMENT:
		{
			Batiment *bat = new Batiment(scene, m_equipe, type, id);
			unit          = static_cast<Unite*>(bat);
		}
        break;
    case TypeUnite::AERIEN:
        break;
    case TypeUnite::TERRESTE:
        break;
    }
	if(unit!=nullptr)
	{

	}
    return unit;
}
