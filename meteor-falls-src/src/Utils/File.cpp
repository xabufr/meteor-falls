#include "File.h"
#include <boost/filesystem.hpp>
#include <boost/algorithm/string/predicate.hpp>

namespace FileUtils
{
using namespace boost;
std::list<std::string> getRecurse(const std::string& path, const std::string& pattern)
{
    std::list<std::string> ret;
    getFiles(path, pattern, true, ret);
    return ret;
}
std::list<std::string> getRecurse(const std::string& path, const std::list<std::string>& pattern)
{
    std::list<std::string> ret;
    getFiles(path, pattern, true, ret);
    return ret;
}
std::list<std::string> getFiles(const std::string& path, const std::string& pattern)
{
    std::list<std::string> ret;
    getFiles(path, pattern, false, ret);
    return ret;
}

std::list<std::string> getFiles(const std::string& path, const std::list<std::string>& pattern)
{
    std::list<std::string> ret;
    getFiles(path, pattern, false, ret);
    return ret;
}

void getFiles(const std::string& path, const std::string& pattern, bool recurse, std::list<std::string>& liste)
{
    std::list<std::string> patterns;
    patterns.push_back(pattern);
    getFiles(path, patterns, recurse, liste);
}
void getFiles(const std::string& path, const std::list<std::string> pattern, bool recurse, std::list<std::string>& liste)
{
    filesystem::path dir(path);
    if(exists(dir)&&is_directory(dir))
    {
        for(filesystem::directory_iterator it(dir); it!=filesystem::directory_iterator(); ++it)
        {
            const filesystem::path& current = it->path();
            if(filesystem::is_directory(current))
            {
                getFiles(current.string(), pattern, recurse, liste);
            }
            else
            {
                for(std::string s : pattern)
                {
                    if(ends_with(current.string(), s))
                        liste.push_back(current.string());
                }
            }
        }
    }
}
}
