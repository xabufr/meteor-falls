#ifndef WORLDOBJECTTYPE_H
#define WORLDOBJECTTYPE_H

#include <string>
#include <OgreQuaternion.h>
#include "../../../Utils/Vector3D.h"

namespace{ class Ogre::Entity; }
struct WorldObjectType
{
    WorldObjectType(const std::string &mesh);
    const std::string mesh_name;
    Ogre::Quaternion quaternion;
    Vector3D offset;
    bool follow_normals, static_mesh;
    float scale;
    Ogre::Entity *entity;
};

#endif // WORLDOBJECTTYPE_H
