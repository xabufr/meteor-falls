#include "ResourceGroup.h"
#include "boost/filesystem.hpp"
#include "File.h"

ResourceGroup::ResourceGroup(const std::string& nom):m_nom(nom)
{

}
ResourceGroup::~ResourceGroup()
{

}
void ResourceGroup::addPath(const std::string& path)
{
    bool exist=false;
    for (std::string s:m_path)
        exist = (s == path);

    if (!exist)
        m_path.push_back(path);
}
void ResourceGroup::removePath(const std::string& path)
{
    for (auto it=m_path.begin();it!=m_path.end();++it)
        if (*it == path)
            m_path.erase(it);
}
std::string ResourceGroup::getFilePath(const std::string& file)
{
    for (std::string s : m_path)
        if (boost::filesystem::exists(s+"/"+file) && !boost::filesystem::is_directory(s+"/"+file))
            return s+"/"+file;

    return "";
}
std::list<std::string> ResourceGroup::getFilesFromType(const std::string& type) const 
{
	std::list<std::string> liste;
	for(std::string path : m_path)
	{
		liste.splice(liste.end(), FileUtils::getFiles(path, type));
	}
	return liste;
}
