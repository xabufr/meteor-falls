#include "Batiment.h"
#include "TypeUnite.h"
#include <OgreSceneManager.h>
#include <OgreEntity.h>
#include "../Factions/Equipe.h"
#include "../../../precompiled/lexical_cast.h"

Batiment::Batiment(Ogre::SceneManager* mng, Equipe *equipe, TypeUnite* type, int id)
    : Unite(mng, equipe, type, id)
{
    m_timer.reset();
    m_isconstructed = false;
	if(m_sceneNode != nullptr)
	{
		m_entite = mng->createEntity("bat#" + boost::lexical_cast<std::string>(equipe->id())
					+ "#" + boost::lexical_cast<std::string>(id), type->meshParameters().at("normal"));
		m_sceneNode->attachObject(m_entite);	
	}
}
bool Batiment::Is_Constructed()
{
    return m_isconstructed;
}
