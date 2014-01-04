#ifndef _HOME_THOMAS_METEOR_FALLS_METEOR_FALLS_SRC_SRC_STATE_MENU_LANLOGINSTATE_HPP__
#define _HOME_THOMAS_METEOR_FALLS_METEOR_FALLS_SRC_SRC_STATE_MENU_LANLOGINSTATE_HPP__

#include "../State.h"
#include <string>

class StateManager;
class LoginState;
class JoueurLan;
namespace CEGUI {
    class Window;
    class EventArgs;
} // namespace CEGUI
class LanLoginState: public State
{
public:
    LanLoginState(StateManager*, LoginState*);
    virtual ~LanLoginState();
    virtual void enter();
    virtual void exit();
    virtual ret_code work(const TimeDuration &elapsed);
    virtual bool isVisible();
private:
    CEGUI::Window* m_window;
    CEGUI::Window* m_windowCreate;
    LoginState* m_parentState;
    std::vector<JoueurLan*> m_profiles;
    JoueurLan* m_lastSelected;
    CEGUI::Window *m_btn_utiliser, *m_btn_supp;
    bool m_continue;

    bool profilesSelectionChanged(const CEGUI::EventArgs&);
    bool createNewProfile(const CEGUI::EventArgs&);
    bool showCreateProfile(const CEGUI::EventArgs&);
    bool deleteProfile(const CEGUI::EventArgs&);
    void updateProfileList();
    void loadProfilesList();
    bool useProfile(const CEGUI::EventArgs&);
    bool profileExists(const std::string&);
    bool retour(const CEGUI::EventArgs&);
};

#endif
