#include "WorldObjectType.h"
#include <boost/property_tree/ptree.hpp>


WorldObjectType::WorldObjectType()
{
    m_selectedMaterialName = "Selection/Circle";
}

WorldObjectType::WorldObjectType(const boost::property_tree::ptree & data)
{
    m_selectedMaterialName = data.get<std::string>("selectedMaterial", "Selection/Circle");
}

const std::string &WorldObjectType::selectedMaterialName() const
{
    return m_selectedMaterialName;
}
