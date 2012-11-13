#ifndef APPLICATIONPARAMETERS_H
#define APPLICATIONPARAMETERS_H

#include <unordered_map>
#include <string>

typedef std::unordered_map<std::string, std::string> ApplicationParametersKeys;
class ApplicationParameters
{
    public:
        ApplicationParameters(int argc, char **argv);
        virtual ~ApplicationParameters();
        const ApplicationParametersKeys & getKeys() const;

    private:
        ApplicationParametersKeys m_keys;
        void m_parse(int argc, char **argv);
        void m_setDefault();
};

#endif // APPLICATIONPARAMETERS_H
