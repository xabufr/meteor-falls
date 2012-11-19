#include "applicationparameters.h"
#include "Application/parameterparserexception.h"
#include "Utils/Exception/BasicException.h"
#include <iostream>

ApplicationParameters::ApplicationParameters(int argc, char** argv)
{
    m_setDefault();
    std::vector<std::string> args;
    for(int i=1;i<argc;++i)
        args.push_back(std::string(argv[i]));
    m_parse(args);
}
ApplicationParameters::ApplicationParameters(std::vector<std::string> args)
{
    m_setDefault();
    m_parse(args);
}

ApplicationParameters::~ApplicationParameters()
{
}
ApplicationParametersKeys & ApplicationParameters::getKeys()
{
    return m_keys;
}

void ApplicationParameters::m_parse(std::vector<std::string> args)
{
    bool settingargument = false;
    std::string argument;
    for(size_t i=0;i<args.size();++i)
    {
        std::string arg = args[i];
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
                    throw ParameterParserException(arg);
                }
            }
            else
            {
                THROW_BASIC_EXCEPTION(arg);
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
