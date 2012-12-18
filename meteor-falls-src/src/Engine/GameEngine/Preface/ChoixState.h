#ifndef CHOIXSTATE_H_INCLUDED
#define CHOIXSTATE_H_INCLUDED

#include "../../../State/State.h"
#include "../../../State/StateManager.h"
#include "../GameEngine.h"
#include <CEGUI.h>

class ChoixState : public State
{
public:
    ChoixState(StateManager*, GameEngine*);
    ~ChoixState();
    virtual bool isVisible();
    virtual void enter();
    virtual void exit();
    virtual ret_code work();
private:
    bool m_visible;
    GameEngine *m_game_engine;
    CEGUI::TabButton *m_window;
    CEGUI::PushButton *m_rts;
    CEGUI::PushButton *m_rpg;
    CEGUI::MultiLineEditbox *m_chat;
    CEGUI::Editbox *m_edit;
};

#endif // CHOIXSTATE_H_INCLUDED
