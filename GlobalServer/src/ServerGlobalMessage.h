#ifndef SERVERGLOBALMESSAGE_H_INCLUDED
#define SERVERGLOBALMESSAGE_H_INCLUDED

class ServerGlobalMessage
{
  public:
        enum Type{
            LOGIN,
            LOGOUT,
            SERVER_LIST,
            SERVER_UP,
            SERVER_DEL
        } type;

        std::vector<Server> servers;
        //Player player;
        std::vector<std::string> news, command;
  private:
        friend class boost::serialization::access;
        template<class Archive>
        void serialize(Archive& ar, const unsigned int version){
            ar & type & servers /*& player*/ & news & command;
        }
};

#endif // SERVERGLOBALMESSAGE_H_INCLUDED
