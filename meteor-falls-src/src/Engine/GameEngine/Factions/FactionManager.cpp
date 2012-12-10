#include "FactionManager.h"
#include "Faction.h"
#include "Engine/ScriptEngine/XmlDocumentManager.h"
#include "precompiled/lexical_cast.h"


FactionManager::FactionManager()
{
    rapidxml::xml_document<>* document = XmlDocumentManager::get()->getDocument("data/factions.xml");
    rapidxml::xml_node<>* factions_node = document->first_node("factions"),
                            *faction_node;

    Faction *faction;

    for(faction_node=factions_node->first_node("faction");
        faction_node;faction_node=faction_node->next_sibling("faction"))
    {
        FactionId id = boost::lexical_cast<FactionId>(faction_node->first_attribute("id")->value());
        std::string nom = faction_node->first_attribute("nom")->value();
        bool jouable = boost::lexical_cast<bool>(faction_node->first_attribute("jouable")->value());

        faction = new Faction(jouable, id, nom);
        m_factions.push_back(faction);
        rapidxml::xml_node<>* fileNode;
        for(fileNode=faction_node->first_node("fichier");
            fileNode;fileNode=fileNode->next_sibling("fichier"))
        {
            std::string path = fileNode->value();
            faction->addConfigFile(path);
        }
        faction->load();
    }
}

FactionManager::~FactionManager()
{
    for(Faction* fac : m_factions)
    {
        delete fac;
    }
}
Faction* FactionManager::getFaction(FactionId id)
{
    for(Faction* fac : m_factions)
    {
        if(fac->id()==id)
            return fac;
    }
    return 0;
}
