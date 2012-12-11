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
        std::string pseudo;
        std::string passwd;
        std::string cmd;
        template<class Archive>
        void serialize(Archive& ar, const unsigned int version){
            ar & pseudo & passwd & cmd;
        }
};

#endif // ADMIN_H_INCLUDED
