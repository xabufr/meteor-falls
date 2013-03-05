#ifndef LAYOUTRTS_H
#define LAYOUTRTS_H
#include <CEGUI.h>
#include "Engine/GameEngine/Factions/Faction.h"
#include "State/StateManager.h"
#include "State/State.h"
#include "Engine/GameEngine/Joueur/Joueur.h"
#include <iostream>

class LayoutRTS : public State
{
    public:
        LayoutRTS(StateManager*, Joueur*);
        ~LayoutRTS();
        virtual bool isVisible();
        virtual void enter();
        virtual void exit();
        virtual ret_code work(unsigned int);

    private:
        StateManager *m_state_manager;
        bool m_visible;
        bool m_choix_grille(const CEGUI::EventArgs&);
        Faction* m_faction;
        Joueur* m_joueur;
        CEGUI::Window *m_info_ressources,* m_position_map, *m_infos_unite,*m_grille_batiments;
        CEGUI::PushButton *m_grille_batimentsA,*m_grille_batimentsZ,*m_grille_batimentsE,*m_grille_batimentsQ,*m_grille_batimentsS,*m_grille_batimentsD,*m_grille_batimentsW,*m_grille_batimentsX,*m_grille_batimentsC;
};

#endif
