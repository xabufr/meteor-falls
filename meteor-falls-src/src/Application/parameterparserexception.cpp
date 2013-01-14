#include "parameterparserexception.h"

ParameterParserException::ParameterParserException(std::string arg) : m_arg(arg)
{
}

std::string ParameterParserException::getArgument() const
{
    return m_arg;
}

ParameterParserException::~ParameterParserException() throw()
{
    //dtor
}
