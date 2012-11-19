#ifndef BASICEXCEPTION_H
#define BASICEXCEPTION_H
#define THROW_BASIC_EXCEPTION(description) throw BasicException(description, __FILE__, __LINE__);

#include <exception>
#include <string>

class BasicException : public std::exception
{
    public:
        BasicException(std::string description, std::string file, int);
        virtual ~BasicException() throw();
        virtual const char* what() const throw();
    protected:
    private:
        std::string m_description, m_file;
        int m_line;
};

#endif // BASICEXCEPTION_H
