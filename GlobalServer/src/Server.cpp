#include "Server.h"

Server::Server(std::string ip,std::string nom,std::string m_version,int nombre_joueurs_max,int nombre_joueurs_connectes,bool passwd,std::string carte_jouee,std::string type_partie,float temps_jeu)
{
	ip = ip;
	nom = nom;
	nombre_joueurs_max = nombre_joueurs_max;
	nombre_joueurs_connectes = nombre_joueurs_connectes;
	passwd = passwd;
	carte_jouee = carte_jouee;
	type_partie = type_partie;
	temps_jeu = temps_jeu;
}

 Server::Server()
{
    nombre_joueurs_max = 0;
    nombre_joueurs_connectes = 0;
    passwd = 0;
    temps_jeu = 0;
}

