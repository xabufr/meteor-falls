#ifndef FILENOTFOUND_H
#define FILENOTFOUND_H

#include <exception>
#include <string>

class FileNotFound
{
    public:
        FileNotFound(const std::string&);
        virtual ~FileNotFound();
        virtual const char* what() const throw();
    protected:
    private:
        std::string m_file;
};

#endif // FILENOTFOUND_H
