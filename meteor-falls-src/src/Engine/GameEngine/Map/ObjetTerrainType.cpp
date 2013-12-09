#include "ObjetTerrainType.h"
#include <boost/property_tree/ptree.hpp>
#include <boost/exception/all.hpp>
#include "../../ScriptEngine/MeshManager.h"

ObjetTerrainType::ObjetTerrainType(boost::property_tree::ptree const& data)
{
	std::string stype = data.get<std::string>("type");
	if(stype == "DECORS")
		type = Type::DECORS;
	else if(stype=="RESSOURCE")
		type = Type::RESSOURCE;
	else if(stype == "METEOR") 
		type = Type::METEOR;
	else 
		BOOST_THROW_EXCEPTION(ObjetTerrainType::DataExtractionError());
	std::string meshName     = data.get<std::string>("meshName");
	physique     = data.get<bool>("physique", false);
	destructible = data.get<bool>("destructible", false);
	vieMax       = data.get<int> ("vieMax", -1);
	mesh         = MeshManager::get()->fromOgre(meshName);
	if(!mesh)
		BOOST_THROW_EXCEPTION(ObjetTerrainType::DataExtractionError());
}
