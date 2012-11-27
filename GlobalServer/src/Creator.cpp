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
    int i = 1;
    Player MonPlayer("","",0,0,0,"","","","");

    unsigned int num_champs = 9;
    result = mysql_use_result(m_MYSQL);

    while ((row = mysql_fetch_row(result)))
    {
        unsigned long *lengths;
        lengths = mysql_fetch_lengths(result);

        for(i = 0; i < num_champs; i++)
        {
            //On ecrit toutes les valeurs
            switch (i)
            {
                case 0:
                    MonPlayer.set_id(row[i]);
                    break;
                case 1:
                    MonPlayer.set_pseudo(Nom_Player);
                    break;
                case 2:
                    MonPlayer.set_session(row[i]);
                    break;
                case 3:
                    MonPlayer.set_exp_rpg(atoi(row[i]));
                    break;
                case 4:
                    MonPlayer.set_exp_rts(atoi(row[i]));
                    break;
                case 5:
                    MonPlayer.set_level(atoi(row[i]));
                    break;
                case 6:
                    MonPlayer.set_passwd(row[i]);
                    break;
                case 7:
                    MonPlayer.set_email(row[i]);
                    break;
                case 8:
                    MonPlayer.set_pays(row[i]);
                    break;
            }
        }
        i++;
    }

    return MonPlayer;
    mysql_free_result(result);

}

Server Creator::select_server(std::string ip)
{
    std::string sql_query = "SELECT * FROM Server WHERE ip_server = " + ip;

    mysql_query(m_MYSQL, sql_query.c_str());
    MYSQL_RES *result = NULL;
    MYSQL_ROW row;
    int i = 1;
    Server MonServer("","","","",0,0,0,"","",0);

    unsigned int num_champs = 10;
    result = mysql_use_result(m_MYSQL);

    while ((row = mysql_fetch_row(result)))
    {
        unsigned long *lengths;
        lengths = mysql_fetch_lengths(result);

        for(i = 0; i < num_champs; i++)
        {
            //On ecrit toutes les valeurs
            switch (i)
            {
                case 0:
                    MonServer.set_id_server(row[i]);
                    break;
                case 1:
                    MonServer.set_ip_server(ip);
                    break;
                case 2:
                    MonServer.set_nom(row[i]);
                    break;
                case 3:
                    MonServer.set_version(row[i]);
                    break;
                case 4:
                    MonServer.set_nombre_joueurs_max(atoi(row[i]));
                    break;
                case 5:
                    MonServer.set_nombre_joueurs_connectes(atoi(row[i]));
                    break;
                case 6:
                    MonServer.set_passwd(row[i]);
                    break;
                case 7:
                    MonServer.set_carte_jouee(row[i]);
                    break;
                case 8:
                    MonServer.set_type_partie(row[i]);
                    break;
                case 9:
                    MonServer.set_temps_jeu(atoi(row[i]));
                    break;
            }
        }
        i++;
    }

    return MonServer;
    mysql_free_result(result);

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


void Creator::delete_player(std::string ip)
{
    std::string sql_query;
    sql_query = "DELETE FROM Player WHERE id_player = " +boost::lexical_cast<std::string>(id);
    mysql_query(m_MYSQL, sql_query.c_str());
}


void Creator::delete_server(std::string ip)
{
    std::string sql_query;
    sql_query = "DELETE FROM Server WHERE id_server = " +boost::lexical_cast<std::string>(id);
    mysql_query(m_MYSQL, sql_query.c_str());
}
