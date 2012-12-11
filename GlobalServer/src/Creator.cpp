#include "Player.h"
#include "Server.h"
#include "Creator.h"

Creator::Creator(char* host,char* user,char* password,char* db_name)
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
void Creator::insert(const Player& p)
{
    std::string sql_query;
    sql_query = "INSERT INTO Player (id_player, pseudo_player, num_session_player,exp_rpg_player,exp_rts_player,level_player,password_player,email_player,pays_player) VALUES('"+p.id_player+
    "', '"+p.pseudo+
    "', '"+p.num_session+
    "', '"+boost::lexical_cast<std::string>(p.exp_rpg)+
    "', '"+boost::lexical_cast<std::string>(p.exp_rts)+
    "', '"+boost::lexical_cast<std::string>(p.level)+
    "', '"+p.passwd+
    "', '"+p.email+
    "', '"+p.pays+"')";
    mysql_query(m_MYSQL, sql_query.c_str());

}
void Creator::insertServer(const Server& ser)
{
    std::string sql_query;
    sql_query = std::string("INSERT INTO Server (ip_server, nom_server,version_server,joueurs_max_server,joueurs_connectes_server,password_server,carte_jouee_server,type_partie_server,temps_jeu_server) VALUES(")+
    "'"+ser.ip+
    "', '"+ser.nom+
    "', '"+ser.version+
    "', '"+boost::lexical_cast<std::string>(ser.nombre_joueurs_max)+
    "', '"+boost::lexical_cast<std::string>(ser.nombre_joueurs_connectes)+
    "', '"+boost::lexical_cast<std::string>(ser.passwd)+
    "', '"+ser.carte_jouee+
    "', '"+ser.type_partie+
    "', '"+boost::lexical_cast<std::string>(ser.temps_jeu)+"')";
    mysql_query(m_MYSQL, sql_query.c_str());
}
Player Creator::select_player(std::string Nom_Player)
{
    std::string sql_query = "SELECT * FROM Player WHERE pseudo_player = '" + Nom_Player +"'";

    mysql_query(m_MYSQL, sql_query.c_str());
    MYSQL_RES *result = NULL;
    MYSQL_ROW row;

    Player MonPlayer("","",0,0,0,"","","","");

    result = mysql_use_result(m_MYSQL);

    if (result == NULL)
        return MonPlayer;

    while ((row = mysql_fetch_row(result)))
    {
        MonPlayer.id_player=row[0];
        MonPlayer.pseudo=Nom_Player;
        MonPlayer.num_session=row[2];
        MonPlayer.exp_rpg=atoi(row[3]);
        MonPlayer.exp_rts=atoi(row[4]);
        MonPlayer.level=atoi(row[5]);
        MonPlayer.passwd=row[6];
        MonPlayer.email=row[7];
        MonPlayer.pays=row[8];
    }

    mysql_free_result(result);
    return MonPlayer;
}
Admin Creator::select_admin(std::string pseudo)
{
    Admin admin;
    std::string sql_query = "SELECT * FROM Admin WHERE pseudo = '" + pseudo + "'";

    mysql_query(m_MYSQL, sql_query.c_str());
    MYSQL_RES *result = NULL;
    MYSQL_ROW row;

    result = mysql_use_result(m_MYSQL);

    if (result == NULL)
        return admin;

    while ((row = mysql_fetch_row(result)))
    {
        admin.pseudo = pseudo;
        admin.passwd = row[2];
    }

    mysql_free_result(result);
    return admin;
}
Server Creator::select_server(std::string ip)
{
    std::string sql_query = "SELECT * FROM Server WHERE ip_server = '" + ip +"'";

    mysql_query(m_MYSQL, sql_query.c_str());
    MYSQL_RES *result = NULL;
    MYSQL_ROW row;

    Server MonServer("","","",0,0,0,"","",0);
    result = mysql_use_result(m_MYSQL);

    if (result == NULL)
        return MonServer;

        MonServer.ip=ip;
        MonServer.nom=row[2];
        MonServer.version=row[3];
        MonServer.nombre_joueurs_max=atoi(row[4]);
        MonServer.nombre_joueurs_connectes=atoi(row[5]);
        MonServer.passwd=row[6];
        MonServer.carte_jouee=row[7];
        MonServer.type_partie=row[8];
        MonServer.temps_jeu=atoi(row[9]);

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

    if (result == NULL)
        return list_server;

    while ((row = mysql_fetch_row(result)))
    {
        srv.ip=row[1];
        srv.nom=row[2];
        srv.version=row[3];
        srv.nombre_joueurs_max=atoi(row[4]);
		srv.nombre_joueurs_connectes=atoi(row[5]);
        srv.passwd=row[6];
        srv.carte_jouee=row[7];
        srv.type_partie=row[8];
        srv.temps_jeu=atoi(row[9]);

        list_server.push_back(srv);
    }
    mysql_free_result(result);
    return list_server;
}
void Creator::update(const Player& p)
{
    std::string sql_query;
    sql_query = "UPDATE Player SET pseudo_player = '" +p.pseudo +
    "', num_session_player = '" + p.num_session+
    "', exp_rpg_player = '" + boost::lexical_cast<std::string>(p.exp_rpg)+
    "', exp_rts_player = '" + boost::lexical_cast<std::string>(p.exp_rts)+
    "', level_player = '" + boost::lexical_cast<std::string>(p.level)+
    "', password_player = '" + p.passwd+
    "', email_player = '" + p.email+
    "', pays_player = '" + p.pays+
    "' WHERE id_player = '"+p.id_player+"'";

    mysql_query(m_MYSQL, sql_query.c_str());

}
void Creator::update(const Server& server)
{
	
	Server s = select_server(server.ip);
	if(s.ip.empty())
	{
		insertServer(server);
	}
	else
	{
		std::string sql_query;
    	sql_query = std::string("UPDATE Server SET ") + 
    	"nom_server= '" +server.nom +
   		"', version_server= '" +server.version +
   		"', joueurs_max_server= '" +boost::lexical_cast<std::string>(server.nombre_joueurs_max) +
   		"', joueurs_connectes_servejjj= '" +boost::lexical_cast<std::string>(server.nombre_joueurs_connectes) +
   		"', password_server= '" +boost::lexical_cast<std::string>(server.passwd)+
   		"', carte_jouee_server= '" +server.carte_jouee +
   		"', type_partie_server= '" +server.type_partie +
   		"', temps_jeu_server= '" +boost::lexical_cast<std::string>(server.temps_jeu) + "' "+
		"WHERE ip_server='"+server.ip+"'";
    	mysql_query(m_MYSQL, sql_query.c_str());
	}
}   
void Creator::delete_player(std::string id)
{
    std::string sql_query;
    sql_query = "DELETE FROM Player WHERE id_player = '" + id + "'";
    mysql_query(m_MYSQL, sql_query.c_str());
}
void Creator::delete_server(std::string ip)
{
    std::string sql_query;
    sql_query = "DELETE FROM Server WHERE id_server = '" +boost::lexical_cast<std::string>(ip) +"'";
    mysql_query(m_MYSQL, sql_query.c_str());
}
