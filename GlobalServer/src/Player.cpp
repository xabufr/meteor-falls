#include "Player.h"

Player::Player(std::string Id_Player, std::string pseudo,int exp_rpg,int exp_rts,int level,std::string passwd,std::string email,std::string pays, std::string session)
{
    id_player = Id_Player;
    pseudo = pseudo;
    exp_rpg = exp_rpg;
    exp_rts = exp_rts;
    level = level;
    passwd = passwd;
    pays = pays;
    email = email;
    num_session = session;

}

Player::Player():id_player(""),
pseudo(""),
exp_rpg(0),
exp_rts(0),
level(0),
passwd(""),
pays(""),
email(""),
num_session("")
{

}
