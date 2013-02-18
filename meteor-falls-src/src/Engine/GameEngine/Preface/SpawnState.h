#ifndef _HOME_THOMAS_METEOR_FALLS_SRC_ENGINE_GAMEENGINE_PREFACE_SPAWNSTATE_H__
#define _HOME_THOMAS_METEOR_FALLS_SRC_ENGINE_GAMEENGINE_PREFACE_SPAWNSTATE_H__

#include "../../../State/State.h"
#include "../../../State/StateManager.h"
#include <unordered_map>

class Unite;
class GameEngine;
namespace CEGUI {
	class Window;
	class PushButton;
	class Listbox;
	class EventArgs;
	class GroupBox;
	class TabControl;
} // namespace CEGUI
class Avatar;
class ClasseHero;
class SpawnState: public State
{
public:
	SpawnState(StateManager*, GameEngine*);
	~SpawnState();
	virtual bool isVisible();
    virtual void enter();
    virtual void exit();
    virtual ret_code work(unsigned int time);
	void updateSpawns();
	bool spawnSelected(const CEGUI::EventArgs&);
	bool classSelected(const CEGUI::EventArgs&);
	bool classChanged(const CEGUI::EventArgs&);
	bool trySpawn(const CEGUI::EventArgs&);
private:
	GameEngine* m_game;
	CEGUI::Window *m_window;
	CEGUI::PushButton *m_buttonSpawn;
	CEGUI::Listbox *m_spawns;
	CEGUI::GroupBox *m_groupCarte;
	CEGUI::Window *m_infosSpawn;
	CEGUI::TabControl *m_tabClasses;
	Unite* m_last_selected_u;
	void m_loadClasses();
	Avatar *m_avatar;
	std::unordered_map<ClasseHero*, Avatar*> m_selectionsAvatar;
	void m_resetCurrentClasses();
};

#endif 
