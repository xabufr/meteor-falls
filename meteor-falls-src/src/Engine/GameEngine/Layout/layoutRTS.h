#ifndef LAYOUTRTS_H
#define LAYOUTRTS_H
#include <CEGUI.h>
#include "Engine/GameEngine/Factions/Faction.h"
#include "State/StateManager.h"
#include "State/State.h"
#include <iostream>

class LayoutRTS : public State
{
    public:
        LayoutRTS(StateManager*);
        ~LayoutRTS();
        virtual bool isVisible();
        virtual void enter();
        virtual void exit();
        virtual ret_code work(unsigned int);

    private:
        StateManager *m_state_manager;
        bool m_visible;
        Faction* m_faction;
        CEGUI::Window *m_info_ressources, * m_grille_batiments, * m_position_map, *m_infos_unite;
};

#endif
