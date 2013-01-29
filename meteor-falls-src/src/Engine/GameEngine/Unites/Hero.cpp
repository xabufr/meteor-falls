#include "Hero.h"
#include <assert.h>
Hero::Hero(Ogre::SceneManager* mng, TypeUnite* type, int id)
: Terrestre(mng, type, id)
{
    m_scene_mgr = mng;
    m_timer.reset();
    int m_posx_hero = 0;
    int m_posy_hero = 0;
    int m_posz_hero = 0;
}

void Hero::InsertHero(std::string name_hero, std::string path_hero)
{
    rapidxml::xml_document<> *map_params = XmlDocumentManager::get()->getDocument("data/hero.xml");
    m_rootNode  = map_params->first_node("personnage");
    m_node_faction = m_rootNode->first_node("faction");
    m_node_hero = m_node_faction->first_node("hero");
    m_node_general = m_node_hero->first_node("general");

    m_node_attack1 = m_node_hero->first_node("attack1");
    m_node_attack2 = m_node_hero->first_node("attack2");
    m_node_attack3 = m_node_hero->first_node("attack3");
    m_node_attack_ulti = m_node_hero->first_node("attack_ulti");
    m_node_graphics = m_node_hero->first_node("graphics");

    m_Set_Attack_FromXML();
    m_Set_Global_FromXML();
    m_Set_Graphics_FromXML();

}

void Hero::SetPositionNinja(Vector3D MyPosition)
{



}

bool Hero::m_MOV_IsEnded()
{

}

void Hero::m_Set_Attack_FromXML()
{
    m_attaque1.name   = m_node_attack1->first_node("name")->value();
    m_attaque1.desc   = m_node_attack1->first_node("desc")->value();
    m_attaque1.degats = boost::lexical_cast<int> (m_node_attack1->first_node("damage")->value());

    m_attaque2.name   = m_node_attack2->first_node("name")->value();
    m_attaque2.desc   = m_node_attack2->first_node("desc")->value();
    m_attaque2.degats = boost::lexical_cast<int> (m_node_attack2->first_node("damage")->value());

    m_attaque3.name   = m_node_attack3->first_node("name")->value();
    m_attaque3.desc   = m_node_attack3->first_node("desc")->value();
    m_attaque3.degats = boost::lexical_cast<int> (m_node_attack3->first_node("damage")->value());

    m_attaque_ulti.name   = m_node_attack_ulti->first_node("name")->value();
    m_attaque_ulti.desc   = m_node_attack_ulti->first_node("desc")->value();
    m_attaque_ulti.degats = boost::lexical_cast<int> (m_node_attack_ulti->first_node("damage")->value());
}

void Hero::m_Set_Global_FromXML()
{
    m_carasteristiques.nom     = m_node_general->first_node("nom")->value();
    m_carasteristiques.vie     = boost::lexical_cast<int> (m_node_general->first_node("vie")->value());
    m_carasteristiques.attaque = boost::lexical_cast<int> (m_node_general->first_node("attaque")->value());
    m_carasteristiques.defense = boost::lexical_cast<int> (m_node_general->first_node("defense")->value());
    m_carasteristiques.parry   = boost::lexical_cast<int> (m_node_general->first_node("parry")->value());
}

void Hero::m_Set_Graphics_FromXML()
{
    m_graphics.nom    = m_node_graphics->first_node("nom")->value();
    m_graphics.chemin = m_node_graphics->first_node("chemin")->value();
}

void Hero::m_Set_TypeAD_FromXML()
{
    m_armor_damage_type.id_armorType  = boost::lexical_cast<int> (m_node_general->first_node("armure")->first_attribute("id")->value());
    m_armor_damage_type.id_damageType = boost::lexical_cast<int> (m_node_general->first_node("degat")->first_attribute("id")->value());
}

float Hero::InflictDamage()
{

    // attaque du hero % defense
}


