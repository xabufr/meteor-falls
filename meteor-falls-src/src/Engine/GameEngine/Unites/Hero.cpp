#include "Hero.h"

Hero::Hero(std::string name, std::string chemin, Ogre::SceneManager *scene_mgr)
{

    m_name = name;
    m_chemin = chemin;
    m_scene_mgr = scene_mgr;

}

void Hero::m_insert_hero_in_scene()
{
    m_eNinja = m_scene_mgr->createEntity(m_name, m_chemin);
    Ogre::SceneNode *node= m_scene_mgr->getRootSceneNode()->createChildSceneNode("nodeTete", Ogre::Vector3::ZERO, Ogre::Quaternion::IDENTITY);
    node->attachObject(m_eNinja);
}


Hero::~Hero()
{



}
