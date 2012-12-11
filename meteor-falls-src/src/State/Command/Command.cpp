#include "Command.h"

Command::Command(std::string name):
m_name(name)
{

}

void Command::setProperties(std::vector<std::string> properties)
{
    m_properties = properties;
}

std::vector<std::string> Command::getProperties()
{
    return m_properties;
}

void Command::use(std::string s)
{

}

void Command::setName(std::string name)
{
    m_name = name;
}

std::string Command::getName()
{
    return m_name;
}

 Command::~Command()
{

}

void Command::setUsedPropertie(std::string propertie)
{
    m_used_propertie = propertie;
}

std::string Command::getUsedPropertie()
{
    return m_used_propertie;
}

