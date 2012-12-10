#ifndef ADMIN_H_INCLUDED
#define ADMIN_H_INCLUDED

#include <string>
#include <boost/serialization/serialization.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/string.hpp>

class Admin
{
    public:
        Admin();
        ~Admin();
        void set_passwd(std::string passwd);
        std::string get_passwd();
        void set_cmd(std::string cmd);
        std::string get_cmd();
        void set_pseudo(std::string pseudo);
        std::string get_pseudo();
    private:
        std::string m_pseudo;
        std::string m_passwd;
        std::string m_cmd;
        friend class boost::serialization::access;
        template<class Archive>
        void serialize(Archive& ar, const unsigned int version){
            ar & m_pseudo & m_passwd & m_cmd;
        }
};

#endif // ADMIN_H_INCLUDED
