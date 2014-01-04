#ifndef CHOIXSTATE_H_INCLUDED
#define CHOIXSTATE_H_INCLUDED

#include "../../../State/State.h"
#include "../../../State/StateManager.h"
#include <vector>
#include <OIS/OIS.h>

class JoueurRPG;
class ClientGameEngine;
namespace CEGUI {
    class PushButton;
    class Listbox;
    class Editbox;
    class TabButton;
    class String;
    class EventArgs;
}
class TeamState : public State
{
public:
    TeamState(StateManager*, ClientGameEngine*);
    ~TeamState();
    virtual bool isVisible();
    virtual void enter();
    virtual void exit();
    virtual ret_code work(const TimeDuration &elapsed);
private:
    bool m_choix_mode(const CEGUI::EventArgs &);
    bool m_visible;
    OIS::Keyboard *m_keyboard;
    ClientGameEngine *m_game_engine;
    CEGUI::TabButton *m_window;
    CEGUI::PushButton *m_rts;
    CEGUI::PushButton *m_rpg;
};

#endif // CHOIXSTATE_H_INCLUDED
