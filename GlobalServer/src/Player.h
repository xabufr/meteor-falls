#ifndef PLAYER_H
#define PLAYER_H
#include <iostream>
#include <map>
#include <string>
#include <boost/serialization/serialization.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/string.hpp>

class Player
{
	public :
		Player(std::string Id_Player, std::string pseudo,int exp_rpg,int exp_rts,int level,std::string passwsd,std::string email,std::string pays,std::string session);
        Player(){
        m_exp_rpg=0;
		m_exp_rts=0;
        m_level=0;
		}
		std::string get_pseudo() {return m_pseudo;};
		void set_pseudo(std::string pseudo) {m_pseudo = pseudo;};

		std::string get_id() {return m_id_player;};
		void set_id(std::string id_player) {m_id_player = id_player;};

		int get_exp_rpg() {return m_exp_rpg;};
		void set_exp_rpg(int exp_rpg) {m_exp_rpg = exp_rpg;};

		int get_exp_rts() {return m_exp_rts;};
		void set_exp_rts(int exp_rts) {m_exp_rts = exp_rts;};

		int get_level() {return m_level;};
		void set_level(int level) {m_level = level;};

		std::string get_passwd() {return m_passwd;};
		void set_passwd(std::string passwd) {m_passwd = passwd;};

		std::string get_email() {return m_email;};
		void set_email(std::string email) {m_email = email;};

		std::string get_pays() {return m_pays;};
		void set_pays(std::string pays) {m_pays = pays;};

		std::string get_session() {return m_num_session;};
		void set_session(std::string session) {m_num_session = session;};

	private :
		std::string m_id_player;
		std::string m_pseudo;
		std::string m_num_session;
		int m_exp_rpg;
		int m_exp_rts;
		int m_level;
		std::string m_passwd;
		std::string m_email;
		std::string m_pays;
		friend class boost::serialization::access;
        template<class Archive>
        void serialize(Archive& ar, const unsigned int version){
            ar & m_id_player & m_pseudo & m_num_session & m_exp_rpg & m_exp_rts & m_level & m_passwd
             & m_email & m_pays;
        }

};

#endif // PLAYER_H
/*
Player :
Id_Player
Pseudo_Player*/
