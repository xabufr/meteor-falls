#include "Server.h"

Server::Server(std::string pip,std::string pnom,std::string pversion,int pnombre_joueurs_max,int pnombre_joueurs_connectes,bool ppasswd,std::string pcarte_jouee,std::string ptype_partie,float ptemps_jeu)
{
	ip = pip;
	nom = pnom;
	nombre_joueurs_max = pnombre_joueurs_max;
	nombre_joueurs_connectes = pnombre_joueurs_connectes;
	passwd = ppasswd;
	carte_jouee = pcarte_jouee;
	type_partie = ptype_partie;
	temps_jeu = ptemps_jeu;
}

Server::Server()
{
    nombre_joueurs_max = 0;
    nombre_joueurs_connectes = 0;
    passwd = 0;
    temps_jeu = 0;
}

