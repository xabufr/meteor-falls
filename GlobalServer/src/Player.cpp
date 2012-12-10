#include "Player.h"

Player::Player(std::string Id_Player, std::string pseudo,int exp_rpg,int exp_rts,int level,std::string passwd,std::string email,std::string pays, std::string session)
{
    m_id_player = Id_Player;
    m_pseudo = pseudo;
    m_exp_rpg = exp_rpg;
    m_exp_rts = exp_rts;
    m_level = level;
    m_passwd = passwd;
    m_pays = pays;
    m_email = email;
    m_num_session = session;

}

Player::Player():m_id_player(""),
m_pseudo(""),
m_exp_rpg(0),
m_exp_rts(0),
m_level(0),
m_passwd(""),
m_pays(""),
m_email(""),
m_num_session("")
{

}
