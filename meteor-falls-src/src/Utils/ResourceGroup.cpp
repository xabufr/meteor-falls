#include "ResourceGroup.h"
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
