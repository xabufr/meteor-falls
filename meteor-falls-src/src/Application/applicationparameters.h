#ifndef APPLICATIONPARAMETERS_H
#define APPLICATIONPARAMETERS_H

#include <unordered_map>
#include <string>
#include <vector>

typedef std::unordered_map<std::string, std::string> ApplicationParametersKeys;
class ApplicationParameters
{
    public:
        ApplicationParameters(int argc, char **argv);
        ApplicationParameters(std::vector<std::string> args);
        virtual ~ApplicationParameters();
        ApplicationParametersKeys & getKeys();

    private:
        ApplicationParametersKeys m_keys;
        void m_parse(std::vector<std::string> args);
        void m_setDefault();
};

#endif // APPLICATIONPARAMETERS_H
