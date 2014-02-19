#ifndef PARAMETERPARSEREXCEPTION_H
#define PARAMETERPARSEREXCEPTION_H

#include <exception>
#include <string>

class ParameterParserException : public std::exception
{
    public:
        ParameterParserException(std::string arg);
        virtual ~ParameterParserException() throw();
        std::string getArgument() const;
    protected:
    private:
        std::string m_arg;
};

#endif // PARAMETERPARSEREXCEPTION_H
