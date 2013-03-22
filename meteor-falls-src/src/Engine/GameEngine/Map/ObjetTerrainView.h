#ifndef H_OBJET_TERRAIN_VIEW_H
#define H_OBJET_TERRAIN_VIEW_H

namespace Ogre {
	class SceneManager;
	class SceneNode;
} // namespace 
class ObjetTerrain;
class ObjetTerrainView
{
protected:
	Ogre::SceneManager *m_manager;
	Ogre::SceneNode *m_node;
	ObjetTerrain *m_model;
};
#endif 
