#include "MeshManager.h"
#include "../../Utils/File.h"
#include "XmlDocumentManager.h"
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
		rapidxml::xml_document<>* doc = XmlDocumentManager::get()->getDocument(file);
		rapidxml::xml_node<>* root = doc->first_node("models");
		std::string prefixe;
		if(root->first_attribute("prefix"))
			prefixe = root->first_attribute("prefix")->value();
		for(rapidxml::xml_node<>* model = root->first_node("model");
				model; model=model->next_sibling("model"))
		{
			Mesh* mesh = new Mesh;
			mesh->bullet = model->first_attribute("bullet")->value();
			mesh->ogre   = model->first_attribute("ogre")->value();
			if (fileBullet->loadFile(mesh->bullet.c_str()))
                mesh->shape = fileBullet->getCollisionShapeByName(mesh->bullet.c_str());
			m_meshes.insert(std::pair<std::string, Mesh*>(prefixe + model->first_attribute("name")->value(), mesh));
		}
	}
}
MeshManager::~MeshManager()
{
	for(auto mesh: m_meshes)
		delete mesh.second;
}
