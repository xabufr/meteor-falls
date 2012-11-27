#include "DegatManager.h"
#include "Engine/ScriptEngine/XmlDocumentManager.h"
#include "Degat.h"
#include "Armure.h"
#include <boost/lexical_cast.hpp>

Armure* DegatManager::getArmure(ArmureId armure)
{
    auto it = m_armures.find(armure);
    if(it!=m_armures.end())
        return it->second;
    return 0;
}

Degat* DegatManager::getDegat(DegatId degat)
{
    auto it = m_degats.find(degat);
    if(it!=m_degats.end())
        return it->second;
    return 0;
}

DegatManager::DegatManager()
{
    rapidxml::xml_document<>* document = XmlDocumentManager::get()->getDocument("data/degats.xml");
    rapidxml::xml_node<> *nodeDegats = document->first_node("root")->first_node("degats");
    rapidxml::xml_node<> *nodeArmures = document->first_node("root")->first_node("armures");
    rapidxml::xml_node<> *currentNode;

    Degat *deg;
    for(currentNode=nodeDegats->first_node("degat");currentNode;currentNode=currentNode->next_sibling("degat"))
    {
        DegatId id;
        std::string nom;

        id = boost::lexical_cast<DegatId>(currentNode->first_attribute("id")->value());
        nom = currentNode->first_attribute("nom")->value();

        deg = new Degat(id,nom);
        m_degats[id]=deg;
    }

    Armure *armure;
    for(currentNode=nodeArmures->first_node("armure");currentNode;currentNode=currentNode->next_sibling("armure"))
    {
        ArmureId id;
        std::string nom;

        id = boost::lexical_cast<ArmureId>(currentNode->first_attribute("id")->value());
        nom = currentNode->first_attribute("nom")->value();

        armure = new Armure(id,nom);
        m_armures[id]=armure;
    }
}

DegatManager::~DegatManager()
{

}
