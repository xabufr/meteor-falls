#ifndef FILE_H_INCLUDED
#define FILE_H_INCLUDED
#include <list>
#include <string>

namespace FileUtils{
    std::list<std::string> getRecurse(const std::string& path, const std::string& pattern);
    std::list<std::string> getRecurse(const std::string& path, const std::list<std::string>& pattern);
    std::list<std::string> getFiles(const std::string& path, const std::string &pattern);
    std::list<std::string> getFiles(const std::string& path, const std::list<std::string>& pattern);

    void getFiles(const std::string& path, const std::string& pattern, bool recurse, std::list<std::string>& liste);
    void getFiles(const std::string& path, const std::list<std::string> &pattern, bool recurse, std::list<std::string>& liste);
}

#endif // FILE_H_INCLUDED
