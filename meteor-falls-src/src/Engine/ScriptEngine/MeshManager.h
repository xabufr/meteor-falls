#ifndef H_MESH_MANAGER_H
#define H_MESH_MANAGER_H
#include "../../Utils/singleton.h"
#include <bullet/BulletCollision/btBulletCollisionCommon.h>
#include <map>
#include <string>

class MeshManager: public Singleton<MeshManager>
{
	friend class Singleton<MeshManager>;
public:
	struct Mesh{
		std::string ogre, bullet;
		btCollisionShape* shape;
	};
	Mesh* fromName(const std::string&) const;
	Mesh* fromOgre(const std::string&) const;
	Mesh* fromBullet(const std::string&) const;
protected:
	MeshManager(const std::string& path="data/models/");
	~MeshManager();
private:
	std::map<std::string, Mesh*> m_meshes;
	typedef std::map<std::string, Mesh*>::iterator mesh_iterator;
	typedef std::map<std::string, Mesh*>::const_iterator cmesh_iterator;
};


#endif
