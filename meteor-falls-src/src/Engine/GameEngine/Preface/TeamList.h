#ifndef TEAMLIST_H_INCLUDED
#define TEAMLIST_H_INCLUDED

#include "../../../State/State.h"
#include "../GameEngine.h"
#include <CEGUI.h>

class Equipe;
class TeamList : public State
{
    public:
        TeamList(StateManager*, GameEngine *);
        ~TeamList();
        virtual bool isVisible();
        virtual void enter();
        virtual void exit();
        virtual ret_code work(unsigned int time);
    private:
        GameEngine *m_game_engine;
        CEGUI::Listbox *m_list_team;
        bool m_visible;
        bool m_item_selected(const CEGUI::EventArgs &);
		bool m_isSelectingTeam;
		Equipe *m_equipe;
};
#endif // TEAMLIST_H_INCLUDED
