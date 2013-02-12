#include "SpawnState.h"
#include "../GameEngine.h"
#include "../Joueur/Joueur.h"
#include "../Factions/Equipe.h"
#include "../Factions/Faction.h"
#include "../Unites/Unite.h"
#include "../Unites/TypeUnite.h"
#include <CEGUI.h>
#include <string>
#include "../../../precompiled/lexical_cast.h"
#include "../Heros/ClasseHeroManager.h"
#include "../Heros/ClasseHero.h"

SpawnState::SpawnState(StateManager *mng, GameEngine* game): State(mng), m_game(game)
{
	CEGUI::WindowManager &windowManager = CEGUI::WindowManager::getSingleton();
	m_window = windowManager.createWindow("OgreTray/TabButtonPane","spawn_screen");
	m_window->setSize(CEGUI::UVector2(CEGUI::UDim(0.8, 0.f), CEGUI::UDim(0.8, 0.f)));
	m_window->setPosition(CEGUI::UVector2(CEGUI::UDim(0.5-(m_window->getSize().d_x.d_scale*0.5), 0), 
							CEGUI::UDim(0.5-(m_window->getSize().d_y.d_scale*0.5), 0)));
	m_buttonSpawn = (CEGUI::PushButton*) windowManager.createWindow("OgreTray/Button", "btn_spawn");
	m_buttonSpawn->setText((CEGUI::utf8*)"Apparaître");
	m_buttonSpawn->setSize(CEGUI::UVector2(CEGUI::UDim(0.15,0), CEGUI::UDim(0.10,0)));
	m_buttonSpawn->setPosition(CEGUI::UVector2(CEGUI::UDim(0.8250,0), CEGUI::UDim(0.875, 0)));
	m_spawns = (CEGUI::Listbox*) windowManager.createWindow("OgreTray/Listbox", "spawns_list");
	m_spawns->setSize(CEGUI::UVector2(CEGUI::UDim(0.4625, 0), CEGUI::UDim(0.4, 0)));
	m_spawns->setPosition(CEGUI::UVector2(CEGUI::UDim(0.025, 0), CEGUI::UDim(0.025, 0)));
	m_groupCarte = (CEGUI::GroupBox*)windowManager.createWindow("OgreTray/Group", "groupe_spawn_carte");
	m_groupCarte->setSize(CEGUI::UVector2(CEGUI::UDim(0.4625, 0), CEGUI::UDim(0.4,0)));
	m_groupCarte->setPosition(CEGUI::UVector2(CEGUI::UDim(0.5125, 0), CEGUI::UDim(0.025, 0)));
	m_groupCarte->setText("Carte");
	m_infosSpawn = windowManager.createWindow("OgreTray/StaticText", "infos_spawn");
	m_infosSpawn->setSize(CEGUI::UVector2(CEGUI::UDim(0.8, 0), CEGUI::UDim(0.8,0)));
	m_infosSpawn->setPosition(CEGUI::UVector2(CEGUI::UDim(0.1, 0), CEGUI::UDim(0.1, 0)));
	m_infosSpawn->setText("infos spawn");

	m_tabClasses = (CEGUI::TabControl*) windowManager.createWindow("OgreTray/TabControl", "tab_classes");
	m_tabClasses->setSize(CEGUI::UVector2(CEGUI::UDim(0.95, 0), CEGUI::UDim(0.4, 0)));
	m_tabClasses->setPosition(CEGUI::UVector2(CEGUI::UDim(0.025, 0), CEGUI::UDim(0.45, 0)));

	m_groupCarte->addChildWindow(m_infosSpawn);
	m_window->addChildWindow(m_groupCarte);
	m_window->addChildWindow(m_buttonSpawn);
	m_window->addChildWindow(m_spawns);
	m_window->addChildWindow(m_tabClasses);
	CEGUI::System::getSingleton().getGUISheet()->addChildWindow(m_window);
	m_last_selected_u = nullptr;
	updateSpawns();
	m_loadClasses();
}
SpawnState::~SpawnState()
{
	CEGUI::System::getSingleton().getGUISheet()->removeChildWindow(m_window);
	CEGUI::WindowManager::getSingleton().destroyWindow(m_window);
	CEGUI::WindowManager::getSingleton().destroyWindow(m_spawns);
	CEGUI::WindowManager::getSingleton().destroyWindow(m_groupCarte);
	CEGUI::WindowManager::getSingleton().destroyWindow(m_infosSpawn);
}
bool SpawnState::isVisible()
{
	return true;
}
void SpawnState::enter()
{
	m_window->show();	
}
void SpawnState::exit()
{
	m_window->hide();
}
ret_code SpawnState::work(unsigned int time)
{
	return ret_code::CONTINUE;
}
void SpawnState::updateSpawns()
{
	m_spawns->resetList();
	Joueur *curr = m_game->getCurrentJoueur();
	Equipe *equi = curr->equipe();
	for(Unite *e : equi->unites())
	{
		if(e->type()->spawn())
		{
			CEGUI::ListboxTextItem *item = new CEGUI::ListboxTextItem(e->type()->nom());
			item->setUserData((void*)e);
			item->setSelectionColours(CEGUI::colour(255,0,0), CEGUI::colour(255,0,0), CEGUI::colour(255,0,0), CEGUI::colour(255,0,0));
			m_spawns->addItem(item);
			if(e==m_last_selected_u)
				item->setSelected(true);
		}
	}
	if(m_spawns->getItemCount() > 0 && m_last_selected_u==nullptr)
	{
		m_spawns->getListboxItemFromIndex(0)->setSelected(true);
		spawnSelected(CEGUI::EventArgs());
	}
	m_spawns->subscribeEvent(CEGUI::Listbox::EventSelectionChanged, CEGUI::Event::Subscriber(&SpawnState::spawnSelected, this));
}
bool SpawnState::spawnSelected(const CEGUI::EventArgs& a)
{
	if(m_spawns->getSelectedCount()==0)
			return true;
	m_last_selected_u = (Unite*) m_spawns->getFirstSelectedItem()->getUserData();
	std::string infos;
	infos = "x: " + boost::lexical_cast<std::string>(m_last_selected_u->getPosition().x);
	infos += " y: " + boost::lexical_cast<std::string>(m_last_selected_u->getPosition().y);
	infos += " z: " + boost::lexical_cast<std::string>(m_last_selected_u->getPosition().z);
	m_infosSpawn->setText(infos);

	return true;
}
void SpawnState::m_loadClasses()
{
	Faction *fac = m_game->getCurrentJoueur()->equipe()->faction();
	const ClasseHeroManager& classesMng = fac->getClassesManager(); 
	for(ClasseHero *classe : classesMng.classes())
	{
		CEGUI::Window* tab = CEGUI::WindowManager::getSingleton().createWindow("OgreTray/TabButtonPane", "tab_classe_"+classe->nom());
		tab->setText(classe->nom());
		m_tabClasses->addTab(tab);
		tab->setUserData(classe);
	}
}
