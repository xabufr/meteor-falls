#ifndef SERVERGLOBALMESSAGE_H_INCLUDED
#define SERVERGLOBALMESSAGE_H_INCLUDED

#include "Player.h"
#include "Admin.h"
#include "Server.h"
#include <boost/serialization/serialization.hpp>
#include <boost/serialization/map.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/string.hpp>

class ServerGlobalMessage
{
  public:
        enum Type{
            LOGIN,
            ADMIN_LOGIN,
            ADMIN_CMD,
            LOGOUT,
            SERVER_LIST,
            SERVER_UP,
            SERVER_DEL
        } type;

        std::vector<Server> servers;
        Player player;
        Admin admin;
        std::vector<std::string> news, command;
        bool make;
        ServerGlobalMessage();
  private:
        friend class boost::serialization::access;
        template<class Archive>
        void serialize(Archive& ar, const unsigned int version){
            ar & type & servers & player & news & command;
        }
};

#endif // SERVERGLOBALMESSAGE_H_INCLUDED
