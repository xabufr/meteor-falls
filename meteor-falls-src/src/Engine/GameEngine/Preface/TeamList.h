#ifndef TEAMLIST_H_INCLUDED
#define TEAMLIST_H_INCLUDED

#include "../../../State/State.h"
#include <vector>

class ClientGameEngine;
class Equipe;
class Joueur;
namespace CEGUI {
    class Window;
    class MultiColumnList;
    class EventArgs;
}
class TeamList : public State
{
    public:
        TeamList(StateManager*, ClientGameEngine *);
        ~TeamList();
        virtual bool isVisible();
        virtual void enter();
        virtual void exit();
        virtual ret_code work(const TimeDuration &elapsed);

        void addEquipe(Equipe*);
        void addPlayer(Joueur*);
        void clearPlayers();
        void setCommandant(Joueur*);
        void join();
    private:
        ClientGameEngine *m_game_engine;
        CEGUI::Window *m_window, *m_commandant;
        CEGUI::MultiColumnList *m_list_team, *m_list_joueurs;
        CEGUI::Window *m_btnJoin;

        bool m_visible;
        bool m_item_selected(const CEGUI::EventArgs &);
        bool m_join(const CEGUI::EventArgs&);
        bool m_isSelectingTeam;
        Equipe *m_equipe;
        std::vector<Equipe*> m_equipes;
        std::vector<Joueur*> m_joueurs;
};
#endif // TEAMLIST_H_INCLUDED
