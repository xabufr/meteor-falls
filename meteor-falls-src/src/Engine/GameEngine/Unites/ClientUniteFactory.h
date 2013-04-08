#ifndef H_CLIENT_UNITE_FACTORY_H
#define H_CLIENT_UNITE_FACTORY_H 
#include "UniteFactory.h"

namespace Ogre {
	class SceneManager;
} // namespace Ogre
class ClientUniteFactory: public UniteFactory
{
public:
	ClientUniteFactory(Equipe* e, Ogre::SceneManager* mng): UniteFactory(e), m_sceneManager(mng) {}
protected:
	virtual Unite* create_impl(UniteBuilder*, Joueur*, Avatar*, TypeUnite*, UnitId);
private:
	Ogre::SceneManager *m_sceneManager;
};

#endif 
