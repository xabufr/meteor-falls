#include "../../meteor-falls-src/src/Utils/Exception/FileNotFound.h"

FileNotFound::~FileNotFound()
{
    //dtor
}
FileNotFound::FileNotFound(const std::string& file):
    m_file(file)
{

}

const char* FileNotFound::what() const throw()
{
    return m_file.c_str();
}
