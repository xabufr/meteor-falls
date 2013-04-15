#include "ResourceGroupManager.h"
#include "Exception/FileNotFound.h"
#include <boost/property_tree/ini_parser.hpp>


void ResourceGroupManager::addResourceLocation(const std::string& nom, const std::string& group)
{
    if (m_resources.find(group) == m_resources.end())
    {
        ResourceGroup *g = new ResourceGroup(group);
        g->addPath(nom);
        m_resources.insert(std::pair<std::string,ResourceGroup*>(group, g));
    }
    else
        m_resources.at(group)->addPath(nom);
}

void ResourceGroupManager::removeResourceLocation(const std::string& nom, const std::string& group)
{
    if (m_resources.find(group) != m_resources.end())
        m_resources.at(group)->removePath(nom);
}

void ResourceGroupManager::initialiseResourceGroup()
{
    for(boost::property_tree::ptree::value_type &v : m_ini)
        loadResourceGroup(v.first.data());
}

void ResourceGroupManager::loadResourceGroup(const std::string& group)
{
    if (m_resources.find(group)==m_resources.end())
        m_resources.insert(std::pair<std::string, ResourceGroup*>(group, new ResourceGroup(group)));

    ResourceGroup *g = m_resources.at(group);
    for(boost::property_tree::ptree::value_type &v : m_ini.get_child(group))
        g->addPath(v.second.data());
}

void ResourceGroupManager::removeResourceGroup(const std::string& group)
{
    if (m_resources.find(group) == m_resources.end())
        return;
    for (auto it=m_resources.begin(); it!=m_resources.end(); ++it)
    {
        if (it->second->getNom() == group)
        {
            delete it->second;
            m_resources.erase(it);
        }
    }
}

bool ResourceGroupManager::loadFromFile(const std::string& nom)
{
    std::ifstream file;
    file.open(nom);
    if (file.bad())
        throw FileNotFound(nom);
    boost::property_tree::ini_parser::read_ini(file, m_ini);
    return true;
}
std::string ResourceGroupManager::getFilePath(const std::string& file)
{
    std::string path;
    for (auto it=m_resources.begin(); it!=m_resources.end(); ++it)
    {
        path = it->second->getFilePath(file);
        if (path != "")
            return path;
    }
}

ResourceGroupManager::ResourceGroupManager()
{

}

ResourceGroupManager::~ResourceGroupManager()
{
    for (auto it=m_resources.begin(); it!=m_resources.end(); ++it)
    {
        delete it->second;
        m_resources.erase(it);
    }
}
