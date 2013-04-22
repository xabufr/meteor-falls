#include "MeshManager.h"
#include "../../Utils/File.h"
#include "XmlDocumentManager.h"
#include "../../Utils/Xml.h"
#include "../../Utils/btBulletWorldImporter.h"

MeshManager::Mesh* MeshManager::fromName(const std::string& name) const
{
	cmesh_iterator it = m_meshes.find(name);
	if(it != m_meshes.end())
		return it->second;
	return nullptr;
}
MeshManager::Mesh* MeshManager::fromBullet(const std::string& bulletName) const
{
	for(cmesh_iterator it = m_meshes.begin();it!=m_meshes.end();++it)
	{
		if(it->second->bullet==bulletName)
			return it->second;
	}
	return nullptr;
}
MeshManager::Mesh* MeshManager::fromOgre(const std::string& ogreName) const
{
	for(cmesh_iterator it = m_meshes.begin();it!=m_meshes.end();++it)
	{
		if(it->second->ogre==ogreName)
			return it->second;
	}
	return nullptr;
}
MeshManager::MeshManager(const std::string& path)
{
    btBulletWorldImporter* fileBullet = new btBulletWorldImporter();
	std::list<std::string> liste(FileUtils::getFiles(path, ".models"));
	for(std::string& file: liste)
	{
		XmlDocumentManager::Document& doc = XmlDocumentManager::get()->getDocument(file);
		std::string prefixe = doc.get("models.<xmlattr>.prefix", "");

		auto bounds = doc.get_child("models").equal_range("model");
		for(auto it=bounds.first;it!=bounds.second;++it)
		{
			Mesh* mesh = new Mesh;
			mesh->bullet = it->second.get<std::string>("<xmlattr>.bullet");
			mesh->ogre   = it->second.get<std::string>("<xmlattr>.ogre");
			mesh->offset = XmlUtils::getPosition(it->second.get_child("<xmlattr>"));
			if (fileBullet->loadFile(mesh->bullet.c_str()))
                mesh->shape = fileBullet->getCollisionShapeByName(mesh->bullet.c_str());
			m_meshes.insert(std::pair<std::string, Mesh*>(prefixe + it->second.get<std::string>("<xmlattr>.name"), mesh));
		}
	}
}
MeshManager::~MeshManager()
{
	for(auto mesh: m_meshes)
		delete mesh.second;
}
