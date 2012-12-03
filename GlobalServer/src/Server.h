#ifndef SERVER_H
#define SERVER_H
#include <iostream>
#include <map>
#include <string>
#include <boost/serialization/serialization.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/string.hpp>

class Server
{
	public :
		Server(std::string id,std::string ip,std::string nom,std::string m_version,int nombre_joueurs_max,int nombre_joueurs_connectes,bool passwd,std::string carte_jouee,std::string type_partie,float temps_jeu);
        Server();
		std::string get_ip_server() {return m_ip;};
		void set_ip_server(std::string ip) {m_ip = ip;};

		std::string get_id_server() {return m_id;};
		void set_id_server(std::string Id) {m_id = Id;};

		std::string get_nom() {return m_nom;};
        void set_nom(std::string nom) {m_nom = nom;};

		int get_nombre_joueurs_max() {return m_nombre_joueurs_max;};
		void set_nombre_joueurs_max(int nombre_joueurs_max) {m_nombre_joueurs_max = nombre_joueurs_max;};

		int get_nombre_joueurs_connectes() {return m_nombre_joueurs_connectes;};
		void set_nombre_joueurs_connectes(int nombre_joueurs_connectes) {m_nombre_joueurs_connectes = m_nombre_joueurs_connectes;};

		bool get_passwd() {return m_passwd;};
		void set_passwd(bool passwd) {m_passwd = passwd;};

		std::string get_carte_jouee() {return m_carte_jouee;};
		void set_carte_jouee(std::string carte_jouee) {m_carte_jouee = carte_jouee;};

		std::string get_type_partie() {return m_type_partie;};
		void set_type_partie(std::string type_partie) {m_type_partie = type_partie;};

		std::string get_version() {return m_version;};
		void set_version(std::string version) {m_version = version;};

		float get_temps_jeu() {return m_temps_jeu;};
		void set_temps_jeu(float temps_jeu) {m_temps_jeu = temps_jeu;};

	private :
		std::string m_id;
		std::string m_ip;
		std::string m_nom;
		std::string m_version;
		int m_nombre_joueurs_max;
		int m_nombre_joueurs_connectes;
		bool m_passwd;
		std::string m_carte_jouee;
		std::string m_type_partie;
		float m_temps_jeu;
		friend class boost::serialization::access;
        template<class Archive>
        void serialize(Archive& ar, const unsigned int version){
            ar & m_id & m_ip & m_nom & m_version & m_nombre_joueurs_max & m_nombre_joueurs_connectes & m_passwd
             & m_carte_jouee & m_type_partie & m_temps_jeu;
        }

};


#endif // SERVER_H
/*
Server :
Id_Server
Ip_Server*/
