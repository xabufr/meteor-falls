#ifndef H_WORLD_OBJECT_TYPE_H
#define H_WORLD_OBJECT_TYPE_H

#include <string>
#include <boost/property_tree/ptree_fwd.hpp>

class WorldObjectType
{
public:
    WorldObjectType();
    WorldObjectType(const boost::property_tree::ptree &data);
    const std::string& selectedMaterialName() const;
private:
    std::string m_selectedMaterialName;
};
#endif
