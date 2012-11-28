#include "Server.h"

Server::Server(std::string id,std::string ip,std::string nom,std::string m_version,int nombre_joueurs_max,int nombre_joueurs_connectes,bool passwd,std::string carte_jouee,std::string type_partie,float temps_jeu)
{
	m_id = id;
	m_ip = ip;
	m_nom = nom;
	m_nombre_joueurs_max = nombre_joueurs_max;
	m_nombre_joueurs_connectes = nombre_joueurs_connectes;
	m_passwd = passwd;
	m_carte_jouee = carte_jouee;
	m_type_partie = type_partie;
	m_temps_jeu = temps_jeu;
}

 Server::Server()
{

}

