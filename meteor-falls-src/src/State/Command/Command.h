#ifndef COMMAND_H_INCLUDED
#define COMMAND_H_INCLUDED

#include <string>
#include <vector>

class Command
{
    public:
        Command(std::string);
        ~Command();
        std::string getName();
        void setName(std::string);
        std::string getUsedPropertie();
        void setUsedPropertie(std::string);
        std::vector<std::string> getProperties();
        void setProperties(std::vector<std::string>);
        virtual void use(std::string);
    protected:
        std::string m_used_propertie;
        std::string m_name;
        std::vector<std::string> m_properties;
};

#endif // COMMAND_H_INCLUDED
