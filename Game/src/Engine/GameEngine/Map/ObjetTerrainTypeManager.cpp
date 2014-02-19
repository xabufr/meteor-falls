#include "ObjetTerrainTypeManager.h"
#include "../../../Utils/File.h"
#include "../../../Utils/ResourceGroupManager.h"
#include "../../ScriptEngine/XmlDocumentManager.h"
#include "ObjetTerrainType.h"
#include <boost/exception/diagnostic_information.hpp>

ObjetTerrainTypeManager::ObjetTerrainTypeManager()
{
	std::list<std::string> files(ResourceGroupManager::get()->getFilesFromType(".mfo", "MapObjects"));
	ObjetTerrainType *type;
	for(std::string& file : files)
	{
		try {
			XmlDocumentManager::Document& doc = XmlDocumentManager::get(file);
			auto bounds = doc.equal_range("object");
			for(auto it=bounds.first;it!=bounds.second;++it)
			{
				try {
					type = new ObjetTerrainType(it->second);
				} catch (ObjetTerrainType::DataExtractionError& e) {
					std::cout << "Error for object " << boost::diagnostic_information(e) << std::endl;
				}
			}
		} catch (...) {
			std::cout << "Can't read file " << file << std::endl;
		}
	}
}
ObjetTerrainTypeManager::~ObjetTerrainTypeManager()
{
	for(std::pair<const std::string, ObjetTerrainType*> &t: m_types)
		delete t.second;
}
ObjetTerrainType* ObjetTerrainTypeManager::get(const std::string& name) const 
{
	auto it = m_types.find(name);
	if(it!=m_types.end())
		return it->second;
	return nullptr;
}
