#ifndef SERVER_H
#define SERVER_H
#include <string>
#include <boost/serialization/serialization.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/string.hpp>

class Server
{
	public :
		Server(std::string ip,std::string nom,std::string m_version,int nombre_joueurs_max,int nombre_joueurs_connectes,bool passwd,std::string carte_jouee,std::string type_partie,float temps_jeu);
        Server();
		
		std::string ip;
		std::string nom;
		std::string version;
		int nombre_joueurs_max;
		int nombre_joueurs_connectes;
		bool passwd;
		std::string carte_jouee;
		std::string type_partie;
		float temps_jeu;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int pversion){
            ar & ip & nom & version & nombre_joueurs_max & nombre_joueurs_connectes & passwd
             & carte_jouee & type_partie & temps_jeu;
        }

};


#endif // SERVER_H
/*
Server :
Id_Server
Ip_Server*/
