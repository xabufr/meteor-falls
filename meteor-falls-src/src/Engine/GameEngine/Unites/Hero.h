#ifndef HERO_H
#define HERO_H

#include "Terrestre.h"
#include "Engine/GameEngine/Degats/Armure.h"
#include "Engine/GameEngine/Degats/Degat.h"
#include <OgreSceneManager.h>
#include <string>
#include <iostream>
#include <vector>
#include "../../../Utils/Vector3D.h"
#include "Engine/ScriptEngine/XmlDocumentManager.h"
#include <boost/lexical_cast.hpp>

using namespace rapidxml;

struct animation
{
    std::string name,path;
};
struct attaque
{
    std::string name,desc;
    int degats;
};
struct carasteristiques
{
    std::string nom;
    int vie,attaque,defense,parry;
};
struct graphics
{
    std::string nom,chemin;
};
struct armor_damage_type
{
    int id_armorType, id_damageType;
};


class Hero : public Terrestre
{
    public:
        Hero(Ogre::SceneManager* mng, TypeUnite* type, int id);
        void InsertHero(std::string name, std::string path);
        void SetPositionNinja(Vector3D MyPosition);
        float InflictDamage();

    private:
        bool m_MOV_IsEnded();
        void m_Set_Attack_FromXML();
        void m_Set_Global_FromXML();
        void m_Set_Graphics_FromXML();
        void m_Set_TypeAD_FromXML();

        Ogre::SceneManager *m_scene_mgr;
        Ogre::Light *light;
        Ogre::Timer m_timer;
        Ogre::Entity *m_Entity_ninja;
        Ogre::SceneNode *m_SNode_hero;
        Ogre::AnimationState *mAnimationState;
        rapidxml::xml_node<>* m_rootNode;
        rapidxml::xml_node<>* m_node_faction;
        rapidxml::xml_node<>* m_node_hero;
        rapidxml::xml_node<>* m_node_general;
        rapidxml::xml_node<>* m_node_attack1;
        rapidxml::xml_node<>* m_node_attack2;
        rapidxml::xml_node<>* m_node_attack3;
        rapidxml::xml_node<>* m_node_attack_ulti;
        rapidxml::xml_node<>* m_node_graphics;
        int m_posx_hero,m_posy_hero,m_posz_hero;
        std::string m_name;
        attaque m_attaque1;
        attaque m_attaque2;
        attaque m_attaque3;
        attaque m_attaque_ulti;
        carasteristiques m_carasteristiques;
        armor_damage_type m_armor_damage_type;
        graphics m_graphics;

};
/*

    voir pour les animations.
    Il faut absolument permettre la double animation.

    3 choix
    LUA ou LISP
    Polymorphisme si actions bien différentes
    Scripts pour parametrer tout ça

*/
#endif // HERO_H
