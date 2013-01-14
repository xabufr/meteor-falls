#ifndef CHOIXSTATE_H_INCLUDED
#define CHOIXSTATE_H_INCLUDED

#include "../../../State/State.h"
#include "../../../State/StateManager.h"
#include "../GameEngine.h"
#include <vector>
#include <CEGUI.h>

class JoueurRPG;

class TeamState : public State
{
public:
    TeamState(StateManager*, GameEngine*);
    ~TeamState();
    virtual bool isVisible();
    virtual void enter();
    virtual void exit();
    virtual ret_code work(unsigned int);
private:
    bool m_visible;
    GameEngine *m_game_engine;
    CEGUI::TabButton *m_window;
    CEGUI::PushButton *m_rts;
    CEGUI::PushButton *m_rpg;
    //CEGUI::MultiLineEditbox *m_chat;
    //CEGUI::Editbox *m_edit;
};

#endif // CHOIXSTATE_H_INCLUDED
