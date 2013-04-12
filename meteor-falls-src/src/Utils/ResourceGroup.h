#ifndef RESOURCE_H_INCLUDED
#define RESOURCE_H_INCLUDED

#include <string>
#include <list>

class ResourceGroup
{
public:
    ResourceGroup(const std::string& nom);
    ~ResourceGroup();
    const std::string& getNom(){return m_nom;}
    void addPath(const std::string& path);
    void removePath(const std::string& path);
private:
    std::string m_nom;
    std::list<std::string> m_path;
};

#endif // RESOURCE_H_INCLUDED
