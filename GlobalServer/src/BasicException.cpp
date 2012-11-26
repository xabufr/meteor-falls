#include "../../meteor-falls-src/src/Utils/Exception/BasicException.h"
#include <boost/lexical_cast.hpp>

BasicException::~BasicException() throw()
{
    //dtor
}
BasicException::BasicException(std::string description, std::string file, int line):
    m_description(description), m_file(file), m_line(line)
{

}

const char* BasicException::what() const throw()
{
    return ("Erreur: fichier: \""+
            m_file+
            "\" (line "+
            boost::lexical_cast<std::string>(m_line)+
            ") -> "+
            m_description).c_str();
}
