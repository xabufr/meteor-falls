#ifndef H_OBJET_TERRAIN_TYPE_H
#define H_OBJET_TERRAIN_TYPE_H
#include <boost/property_tree/ptree_fwd.hpp>
#include <boost/exception/exception.hpp>
#include <exception>
#include "../../ScriptEngine/MeshManager.h"
#include "WorldObjectType.h"

struct ObjetTerrainType: public WorldObjectType
{
    class DataExtractionError : public boost::exception, public std::exception
    {
    };
    enum class Type {
        DECORS,
        RESSOURCE,
        METEOR,
    } type;
    bool physique;
    bool destructible;
    int vieMax;
    MeshManager::Mesh* mesh;
    ObjetTerrainType(boost::property_tree::ptree const &);
};
#endif
