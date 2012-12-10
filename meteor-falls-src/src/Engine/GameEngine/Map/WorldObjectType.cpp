#include "WorldObjectType.h"


WorldObjectType::WorldObjectType(const std::string& mesh) : mesh_name(mesh)
{
    follow_normals=false;
    static_mesh=false;
    scale=1.f;
    entity=nullptr;
}
