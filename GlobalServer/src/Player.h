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
        Player();

		std::string id_player;
		std::string pseudo;
		std::string num_session;
		int exp_rpg;
		int exp_rts;
		int level;
		std::string passwd;
		std::string email;
		std::string pays;
        template<class Archive>
        void serialize(Archive& ar, const unsigned int version){
            ar & id_player & pseudo & num_session & exp_rpg & exp_rts & level & passwd
             & email & pays;
        }

};

#endif // PLAYER_H
