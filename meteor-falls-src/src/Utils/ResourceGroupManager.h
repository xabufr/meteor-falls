#ifndef RESOURCEGROUPMANAGER_H_INCLUDED
#define RESOURCEGROUPMANAGER_H_INCLUDED

#include "singleton.h"
#include "ResourceGroup.h"
#include <boost/property_tree/ptree.hpp>
#include <fstream>
#include <vector>
#include <string>
#include <map>

class ResourceGroupManager:public Singleton<ResourceGroupManager>
{
    public:
        ResourceGroupManager();
        ~ResourceGroupManager();
        void addResourceLocation(const std::string& nom, const std::string& group);
        void removeResourceLocation(const std::string& nom, const std::string& group);
        void initialiseResourceGroup();
        void loadResourceGroup(const std::string& group);
        void removeResourceGroup(const std::string& group);
        bool loadFromFile(const std::string& nom);
        std::string getFilePath(const std::string& file);
    private:
        std::map<std::string,ResourceGroup*> m_resources;
        boost::property_tree::ptree m_ini;
};

#endif // RESOURCEGROUPMANAGER_H_INCLUDED
