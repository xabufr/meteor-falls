#include "Player.h"
#include "Server.h"
#include "Creator.h"

Creator::Creator(char* host,char* password,char* user,char* db_name)
{
     m_host = host;
     m_password = password;
     m_user = user;
     m_db_name = db_name;
}

void Creator::connect_mysql()
{

    m_MYSQL = mysql_init(NULL);
    /* Connect to database */
    if (!mysql_real_connect(m_MYSQL, m_host, m_user, m_password, m_db_name, 0, NULL, 0))
    {
        fprintf(stderr, "%s\n", mysql_error(m_MYSQL));
        exit(1);
    }

    mysql_options(m_MYSQL,MYSQL_READ_DEFAULT_GROUP,"option");
}

Player Creator::create_player_item(std::string Id_Player, std::string pseudo, std::string session ,int exp_rpg,int exp_rts,int level,std::string passwsd,std::string email,std::string pays)
{
    Player MyPlayer(Id_Player,pseudo,exp_rpg,exp_rts,level,passwsd,email,pays,session);
    return MyPlayer;

}

Server Creator::create_server_item(std::string id,std::string ip,std::string nom,std::string version,int nombre_joueurs_max,int nombre_joueurs_connectes,bool passwd,std::string carte_jouee,std::string type_partie,float temps_jeu)
{
    Server MyServer(id,ip,nom,version,nombre_joueurs_max,nombre_joueurs_connectes,passwd,carte_jouee,type_partie,temps_jeu);
    return MyServer;

}

void Creator::insert(std::string Id_Player, std::string pseudo,std::string session,int exp_rpg,int exp_rts,int level,std::string passwd,std::string email,std::string pays)
{
    std::string sql_query;
    sql_query = "INSERT INTO Player (id_player, pseudo_player, num_session_player,exp_rpg_player,exp_rts_player,level_player,password_player,email_player,pays_player) VALUES('"+Id_Player+
    "', '"+pseudo+
    "', '"+session+
    "', '"+boost::lexical_cast<std::string>(exp_rpg)+
    "', '"+boost::lexical_cast<std::string>(exp_rts)+
    "', '"+boost::lexical_cast<std::string>(level)+
    "', '"+passwd+
    "', '"+email+
    "', '"+pays+"')";
    mysql_query(m_MYSQL, sql_query.c_str());

}

void Creator::insert(std::string id,std::string ip,std::string nom,std::string version,int nombre_joueurs_max,int nombre_joueurs_connectes,bool passwd,std::string carte_jouee,std::string type_partie,float temps_jeu)
{
    std::string sql_query;
    sql_query = "INSERT INTO Server (id_server, ip_server, nom_server,version_server,joueurs_max_server,joueurs_connectes_server,password_server,carte_jouee_server,type_partie_server,temps_jeu_server) VALUES('"+id+
    "', '"+ip+
    "', '"+nom+
    "', '"+version+
    "', '"+boost::lexical_cast<std::string>(nombre_joueurs_max)+
    "', '"+boost::lexical_cast<std::string>(nombre_joueurs_connectes)+
    "', '"+boost::lexical_cast<std::string>(passwd)+
    "', '"+carte_jouee+
    "', '"+type_partie+
    "', '"+boost::lexical_cast<std::string>(temps_jeu)+"')";
    mysql_query(m_MYSQL, sql_query.c_str());
}

Player Creator::select_player(std::string Nom_Player)
{
    std::string sql_query = "SELECT * FROM Player WHERE pseudo_player = " + Nom_Player;

    mysql_query(m_MYSQL, sql_query.c_str());
    MYSQL_RES *result = NULL;
    MYSQL_ROW row;

    Player MonPlayer("","",0,0,0,"","","","");

    result = mysql_use_result(m_MYSQL);

    while ((row = mysql_fetch_row(result)))
    {
        MonPlayer.set_id(row[0]);
        MonPlayer.set_pseudo(Nom_Player);
        MonPlayer.set_session(row[2]);
        MonPlayer.set_exp_rpg(atoi(row[3]));
        MonPlayer.set_exp_rts(atoi(row[4]));
        MonPlayer.set_level(atoi(row[5]));
        MonPlayer.set_passwd(row[6]);
        MonPlayer.set_email(row[7]);
        MonPlayer.set_pays(row[8]);
    }

    mysql_free_result(result);
    return MonPlayer;
}

Admin Creator::select_admin(std::string pseudo)
{
    Admin admin;
    std::string sql_query = "SELECT * FROM Admin WHERE pseudo = " + pseudo;

    mysql_query(m_MYSQL, sql_query.c_str());
    MYSQL_RES *result = NULL;
    MYSQL_ROW row;

    result = mysql_use_result(m_MYSQL);

    if(result==0)
        return admin;

    while ((row = mysql_fetch_row(result)))
    {
        admin.set_pseudo(pseudo);
        admin.set_passwd(row[2]);
    }

    mysql_free_result(result);
    return admin;
}



Server Creator::select_server(std::string ip)
{
    std::string sql_query = "SELECT * FROM Server WHERE ip_server = " + ip;

    mysql_query(m_MYSQL, sql_query.c_str());
    MYSQL_RES *result = NULL;
    MYSQL_ROW row;

    Server MonServer("","","","",0,0,0,"","",0);
    result = mysql_use_result(m_MYSQL);

    while ((row = mysql_fetch_row(result)))
    {
        MonServer.set_id_server(row[0]);
        MonServer.set_ip_server(ip);
        MonServer.set_nom(row[2]);
        MonServer.set_version(row[3]);
        MonServer.set_nombre_joueurs_max(atoi(row[4]));
        MonServer.set_nombre_joueurs_connectes(atoi(row[5]));
        MonServer.set_passwd(row[6]);
        MonServer.set_carte_jouee(row[7]);
        MonServer.set_type_partie(row[8]);
        MonServer.set_temps_jeu(atoi(row[9]));
    }

    mysql_free_result(result);
    return MonServer;
}

std::vector<Server> Creator::select_all_server()
{
    std::vector<Server> list_server;
    std::string sql_query = "SELECT * FROM Server";

    mysql_query(m_MYSQL, sql_query.c_str());
    MYSQL_RES *result = NULL;
    MYSQL_ROW row;

    result = mysql_use_result(m_MYSQL);
    Server srv;

    while ((row = mysql_fetch_row(result)))
    {
        srv.set_id_server(row[0]);
        srv.set_ip_server(row[1]);
        srv.set_nom(row[2]);
        srv.set_version(row[3]);
        srv.set_nombre_joueurs_max(atoi(row[4]));
        srv.set_nombre_joueurs_connectes(atoi(row[5]));
        srv.set_passwd(row[6]);
        srv.set_carte_jouee(row[7]);
        srv.set_type_partie(row[8]);
        srv.set_temps_jeu(atoi(row[9]));

        list_server.push_back(srv);
    }
    mysql_free_result(result);
    return list_server;
}



void Creator::update(std::string Id_Player, std::string pseudo,std::string session,int exp_rpg,int exp_rts,int level,std::string passwsd,std::string email,std::string pays)
{

    std::string sql_query;
    sql_query = "UPDATE Player SET pseudo_player = '" +pseudo +
    "', num_session_player = '" + session+
    "', exp_rpg_player = '" + boost::lexical_cast<std::string>(exp_rpg)+
    "', exp_rts_player = '" + boost::lexical_cast<std::string>(exp_rts)+
    "', level_player = '" + boost::lexical_cast<std::string>(level)+
    "', password_player = '" + passwsd+
    "', email_player = '" + email+
    "', pays_player = '" + pays+
    "' WHERE id_player = '"+Id_Player+"'";

    mysql_query(m_MYSQL, sql_query.c_str());

}


void Creator::update(std::string id,std::string ip,std::string nom,std::string version,int nombre_joueurs_max,int nombre_joueurs_connectes,bool passwd,std::string carte_jouee,std::string type_partie,float temps_jeu)
{
    std::string sql_query;
    sql_query = "UPDATE Server SET ip_server = '" +ip +
    "', nom_server= '" +nom +
    "', version_server= '" +version +
    "', joueurs_max_server= '" +boost::lexical_cast<std::string>(nombre_joueurs_max) +
    "', joueurs_connectes_server= '" +boost::lexical_cast<std::string>(nombre_joueurs_connectes) +
    "', password_server= '" +boost::lexical_cast<std::string>(passwd)+
    "', carte_jouee_server= '" +carte_jouee +
    "', type_partie_server= '" +type_partie +
    "', temps_jeu_server= '" +boost::lexical_cast<std::string>(temps_jeu) + "')";
    mysql_query(m_MYSQL, sql_query.c_str());
}


void Creator::delete_player(std::string nom)
{
    std::string sql_query;
    sql_query = "DELETE FROM Player WHERE id_player = " +nom;
    mysql_query(m_MYSQL, sql_query.c_str());
}


void Creator::delete_server(std::string ip)
{
    std::string sql_query;
    sql_query = "DELETE FROM Server WHERE id_server = " +boost::lexical_cast<std::string>(ip);
    mysql_query(m_MYSQL, sql_query.c_str());
}
