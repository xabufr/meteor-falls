#ifndef SERVERGLOBALMESSAGE_H_INCLUDED
#define SERVERGLOBALMESSAGE_H_INCLUDED

#include "Player.h"
#include "Admin.h"
#include "Server.h"
#include <boost/serialization/serialization.hpp>
#include <boost/serialization/map.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/string.hpp>

namespace ServerGlobalMessageType{
    const int LOGIN = 0,
    ADMIN_LOGIN = 1,
    ADMIN_CMD = 2,
    LOGOUT = 3,
    SERVER_LIST = 4,
    SERVER_UP = 5,
    SERVER_DEL = 6;
}
class ServerGlobalMessage
{
  public:

        int type;

        std::vector<Server> servers;
        Player player;
        Admin admin;
        std::vector<std::string> news, command;
        bool make;
        ServerGlobalMessage()
        {
            make=false;
            type=ServerGlobalMessageType::ADMIN_LOGIN;
        }
  private:
        friend class boost::serialization::access;
        template<class Archive>
        void serialize(Archive& ar, const unsigned int version){
            ar & type & servers & player & news & command & admin & make;
        }
};

#endif // SERVERGLOBALMESSAGE_H_INCLUDED
