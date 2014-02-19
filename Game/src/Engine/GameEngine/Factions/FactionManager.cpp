#include "FactionManager.h"
#include "Faction.h"
#include "../../ScriptEngine/XmlDocumentManager.h"


FactionManager::FactionManager()
{
	XmlDocumentManager::Document& document = XmlDocumentManager::get()->getDocument("data/factions.xml");
    Faction *faction;
	auto bounds = document.get_child("factions").equal_range("faction");
	for(auto it=bounds.first;it!=bounds.second;++it)
	{
        FactionId id = it->second.get<FactionId>("<xmlattr>.id");
        std::string nom = it->second.get<std::string>("<xmlattr>.nom");
        bool jouable = it->second.get<bool>("<xmlattr>.jouable");

        faction = new Faction(jouable, id, nom);
        m_factions.push_back(faction);
		auto boudsFiles = it->second.equal_range("fichier");
		for(auto itFile=boudsFiles.first;itFile!=boudsFiles.second;++itFile)
		{
			faction->addConfigFile(itFile->second.get_value<std::string>());
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
        if(int(fac->id())==(int) id)
            return fac;
    }
    return 0;
}
