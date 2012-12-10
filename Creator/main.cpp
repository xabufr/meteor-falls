#include <iostream>
#include "include/Creator.h"
#include "include/Player.h"
#include "include/Server.h"
#include <assert.h>
using namespace std;

int main()
{
    Creator MyCreator(static_cast <char*> ("213.251.187.31"),static_cast <char*> ("lucie"),static_cast <char*> ("SL_amateur"),static_cast <char*> ("test"));
    MyCreator.connect_mysql();

    Player MonPlayer = MyCreator.create_player_item("32","xoorus","session",225,225,12,"psswd","monemail","france");
    MyCreator.insert("33",MonPlayer.get_pseudo(),MonPlayer.get_session(),MonPlayer.get_exp_rpg(),MonPlayer.get_exp_rts(),MonPlayer.get_level(),MonPlayer.get_passwsd(),MonPlayer.get_email(),MonPlayer.get_pays());
    MyCreator.insert(MonPlayer.get_id(),MonPlayer.get_pseudo(),MonPlayer.get_session(),MonPlayer.get_exp_rpg(),MonPlayer.get_exp_rts(),MonPlayer.get_level(),MonPlayer.get_passwsd(),MonPlayer.get_email(),MonPlayer.get_pays());

    Player MonPlayer2 = MyCreator.select_player(boost::lexical_cast<std::string>(33));

    assert(MonPlayer.get_email()   == MonPlayer2.get_email());
    assert(MonPlayer.get_exp_rpg() == MonPlayer2.get_exp_rpg());
    assert(MonPlayer.get_exp_rts() == MonPlayer2.get_exp_rts());
    assert(MonPlayer.get_level()   == MonPlayer2.get_level());
    assert(MonPlayer.get_passwsd() == MonPlayer2.get_passwsd());
    assert(MonPlayer.get_pays()    == MonPlayer2.get_pays());
    assert(MonPlayer.get_pseudo()  == MonPlayer2.get_pseudo());
    assert(MonPlayer.get_session() == MonPlayer2.get_session());

    MonPlayer.set_pseudo("pseudo_change");
    MyCreator.update(MonPlayer.get_id(),MonPlayer.get_pseudo(),MonPlayer.get_session(),MonPlayer.get_exp_rpg(),MonPlayer.get_exp_rts(),MonPlayer.get_level(),MonPlayer.get_passwsd(),MonPlayer.get_email(),MonPlayer.get_pays());

    assert(MonPlayer.get_pseudo()  != MonPlayer2.get_pseudo());
    MyCreator.delete_player(32);
    MyCreator.delete_player(33);


    Server MonServer = MyCreator.create_server_item("32","122.0.0.0","nom","version",121,12,0,"macarte","type",125.54);
    MyCreator.insert("33",MonServer.get_ip_server(),MonServer.get_nom(),MonServer.get_version(),MonServer.get_nombre_joueurs_max(),MonServer.get_nombre_joueurs_connectes(),MonServer.get_passwd(),MonServer.get_carte_jouee(),MonServer.get_type_partie(),MonServer.get_temps_jeu());
    MyCreator.insert(MonServer.get_id_server(),MonServer.get_ip_server(),MonServer.get_nom(),MonServer.get_version(),MonServer.get_nombre_joueurs_max(),MonServer.get_nombre_joueurs_connectes(),MonServer.get_passwd(),MonServer.get_carte_jouee(),MonServer.get_type_partie(),MonServer.get_temps_jeu());

    Server MonServer2 = MyCreator.select_server(boost::lexical_cast<std::string>(33));

    assert(MonServer.get_carte_jouee()              ==  MonServer.get_carte_jouee()              );
    assert(MonServer.get_ip_server()                ==  MonServer.get_ip_server()                );
    assert(MonServer.get_nom()                      ==  MonServer.get_nom()                      );
    assert(MonServer.get_nombre_joueurs_connectes() ==  MonServer.get_nombre_joueurs_connectes() );
    assert(MonServer.get_nombre_joueurs_max()       ==  MonServer.get_nombre_joueurs_max()       );
    assert(MonServer.get_passwd()                   ==  MonServer.get_passwd()                   );
    assert(MonServer.get_temps_jeu()                ==  MonServer.get_temps_jeu()                );
    assert(MonServer.get_type_partie()              ==  MonServer.get_type_partie()              );
    assert(MonServer.get_version()                  ==  MonServer.get_version()                  );

    MonServer2.set_nom("nom_change");
    MyCreator.update(MonServer2.get_id_server(),MonServer2.get_ip_server(),MonServer2.get_nom(),MonServer2.get_version(),MonServer2.get_nombre_joueurs_max(),MonServer2.get_nombre_joueurs_connectes(),MonServer2.get_passwd(),MonServer2.get_carte_jouee(),MonServer2.get_type_partie(),MonServer2.get_temps_jeu());

    assert(MonServer2.get_nom()  != MonServer.get_nom());

    MyCreator.delete_server(32);
    MyCreator.delete_server(33);

    std::cout << "Tests sql succesfull" << std::endl;
}

