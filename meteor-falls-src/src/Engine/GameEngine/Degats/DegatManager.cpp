#include "DegatManager.h"
#include "../../ScriptEngine/XmlDocumentManager.h"
#include "Degat.h"
#include "Armure.h"

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
	XmlDocumentManager::Document& document = XmlDocumentManager::get()->getDocument("data/degats.xml");

    Degat *deg;
	auto bounds = document.get_child("root.degats").equal_range("degat");
	for(auto it=bounds.first;it!=bounds.second;++it)
    {
        DegatId id;
        std::string nom;

        id = it->second.get<DegatId>("<xmlattr>.id");
        nom = it->second.get<std::string>("<xmlattr>.nom");

        deg = new Degat(id,nom);
        m_degats[id]=deg;
    }

    Armure *armure;
	bounds = document.get_child("root.armures").equal_range("armure");
	for(auto it=bounds.first;it!=bounds.second;++it)
    {
        ArmureId id;
        std::string nom;

        id = it->second.get<DegatId>("<xmlattr>.id");
        nom = it->second.get<std::string>("<xmlattr>.nom");

        armure = new Armure(id,nom);
        m_armures[id]=armure;

        //Paramètres de l'armure
		auto boundsDef = it->second.get_child("defenses").equal_range("degat");
		for(auto def=boundsDef.first;def!=boundsDef.second;++def)
        {
            deg=getDegat(def->second.get<DegatId>("<xmlattr>.id"));
            if(deg)
            {
                armure->addDegat(deg, def->second.get<int>("<xmlattr>.valeur"));
            }
        }
    }
}

DegatManager::~DegatManager()
{
    for(auto it : m_armures)
    {
        delete it.second;
    }
    for(auto it : m_degats)
    {
        delete it.second;
    }
}
