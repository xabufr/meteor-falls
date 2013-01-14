#ifndef CREATOR_H
#define CREATOR_H
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <boost/lexical_cast.hpp>
#include<sstream>
#include <mysql/mysql.h>
#include <mysql/my_global.h>
#include <mysql/my_sys.h>
#include "Admin.h"

class Player;
class Server;

class Creator
{
	public :
		Creator(char* host,char* password,char* user,char* db_name);
		void connect_mysql();

        void update(const Player&);
        void update(const Server&);

        void insert(const Player&);
        void insertServer(const Server&);

        Player select_player(std::string Nom_Player);
        Admin select_admin(std::string);
        Server select_server(std::string ip);
        std::vector<Server> select_all_server();

        void delete_player(std::string id);
        void delete_server(std::string ip);

	private :
		char* m_host;
		char* m_password;
		char* m_user;
		char* m_db_name;

        MYSQL *m_MYSQL;
        MYSQL_STMT *m_STMT;

};
#endif // CREATOR_H
