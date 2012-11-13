#include "applicationparameters.h"
#include "Application/parameterparserexception.h"
#include <iostream>

ApplicationParameters::ApplicationParameters(int argc, char** argv)
{
    m_setDefault();
    m_parse(argc, argv);
}

ApplicationParameters::~ApplicationParameters()
{
}
ApplicationParametersKeys & ApplicationParameters::getKeys()
{
    return m_keys;
}

void ApplicationParameters::m_parse(int argc, char** argv)
{
    bool settingargument = false;
    std::string argument;
    for(int i=1;i<argc;++i)
    {
        std::string arg = argv[i];
        if(!settingargument)
        {
            if(arg.size()>2)
            {
                if(arg.substr(0, 2)=="--")
                {
                    if(m_keys.find(arg.substr(2))==m_keys.cend())
                        throw ParameterParserException(arg);
                    if(arg.substr(2)=="help")
                    {
                        m_keys["help"]="y";
                        settingargument=!settingargument;
                    }
                    else
                        argument = arg.substr(2);
                }
                else
                {
                    throw std::exception();
                }
            }
        }
        else
        {
            m_keys[argument] = arg;
        }
        settingargument=!settingargument;
    }
}
void ApplicationParameters::m_setDefault()
{
    m_keys["gui"]="y";
    m_keys["netconsole"]="n";
    m_keys["help"]="n";
}
