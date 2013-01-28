#include "WorldObjectManager.h"
#include "../../ScriptEngine/XmlDocumentManager.h"
#include "WorldObjectType.h"
#include "../../../precompiled/lexical_cast.h"

WorldObjectManager::WorldObjectManager()
{
    rapidxml::xml_document<>* document = XmlDocumentManager::get()->getDocument("data/objects.xml");
    rapidxml::xml_node<> *objectsNode = document->first_node("objects"),
                         *objectNode;
    for(objectNode=objectsNode->first_node("object");objectNode;objectNode=objectNode->next_sibling("object"))
    {
        WorldObjectType *type;
        std::string mesh;
        WorldObjectTypeId id;
        id = boost::lexical_cast<WorldObjectTypeId>(objectNode->first_attribute("id")->value());
        mesh = objectNode->first_attribute("mesh")->value();
        type = new WorldObjectType(mesh);
        m_types[id]=type;
        if(objectNode->first_node("rotation"))
        {
            rapidxml::xml_node<> *nodeRotation = objectNode->first_node("rotation");
            type->quaternion.x = boost::lexical_cast<float>(nodeRotation->first_attribute("x")->value());
            type->quaternion.y = boost::lexical_cast<float>(nodeRotation->first_attribute("y")->value());
            type->quaternion.z = boost::lexical_cast<float>(nodeRotation->first_attribute("z")->value());
            type->quaternion.w = boost::lexical_cast<float>(nodeRotation->first_attribute("w")->value());
        }
        if(objectNode->first_node("offset"))
        {
            rapidxml::xml_node<> *nodeOffset = objectNode->first_node("offset");
            type->offset.x = boost::lexical_cast<float>(nodeOffset->first_attribute("x")->value());
            type->offset.y = boost::lexical_cast<float>(nodeOffset->first_attribute("y")->value());
            type->offset.z = boost::lexical_cast<float>(nodeOffset->first_attribute("z")->value());
        }
        if(objectNode->first_attribute("follow_normals"))
        {
            type->follow_normals = boost::lexical_cast<bool>(objectNode->first_attribute("follow_normals")->value());
        }
        if(objectNode->first_attribute("static"))
        {
            type->static_mesh = boost::lexical_cast<bool>(objectNode->first_attribute("static")->value());
        }
        if(objectNode->first_attribute("scale"))
        {
            type->scale = boost::lexical_cast<float>(objectNode->first_attribute("scale")->value());
        }
    }
}

WorldObjectManager::~WorldObjectManager()
{
    //dtor
}
WorldObjectType* WorldObjectManager::getType(WorldObjectTypeId id) const
{
    auto it = m_types.find(id);
    if(it!=m_types.end())
        return it->second;
    return nullptr;
}
