#ifndef CREATOR_H
#define CREATOR_H
#include <iostream>
#include <map>
#include <string>
#include <boost/lexical_cast.hpp>
#include<sstream>
#include <mysql.h>
#include <my_global.h>
#include <my_sys.h>

class Player;
class Server;

class Creator
{
	public :
		Creator(char* host,char* password,char* user,char* db_name);
		void connect_mysql();
        Player create_player_item(std::string Id_Player, std::string pseudo, std::string session,int exp_rpg,int exp_rts,int level,std::string passwsd,std::string email,std::string pays);
        Server create_server_item(std::string id,std::string ip,std::string nom,std::string version,int nombre_joueurs_max,int nombre_joueurs_connectes,bool passwd,std::string carte_jouee,std::string type_partie,float temps_jeu);

        void update(std::string id,std::string ip,std::string nom,std::string version,int nombre_joueurs_max,int nombre_joueurs_connectes,bool passwd,std::string carte_jouee,std::string type_partie,float temps_jeu);
        void update(std::string Id_Player, std::string pseudo,std::string session,int exp_rpg,int exp_rts,int level,std::string passwsd,std::string email,std::string pays);

        void insert(std::string Id_Player, std::string pseudo,std::string session,int exp_rpg,int exp_rts,int level,std::string passwsd,std::string email,std::string pays);
        void insert(std::string id,std::string ip,std::string nom,std::string version,int nombre_joueurs_max,int nombre_joueurs_connectes,bool passwd,std::string carte_jouee,std::string type_partie,float temps_jeu);

        Player select_player(std::string Nom_Player);
        Server select_server(std::string ip);

        void delete_player(std::string ip);
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
