#include "SpawnState.h"
#include "../ClientGameEngine.h"
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
#include "../Heros/Avatar.h"
#include "../Camera/CameraManager.h"
#include <OgreCamera.h>
#include "../../EngineManager/EngineManager.h"
#include "../../NetworkEngine/clientnetworkengine.h"

SpawnState::SpawnState(StateManager *mng, ClientGameEngine* game): State(mng), m_game(game)
{
	CEGUI::WindowManager &windowManager = CEGUI::WindowManager::getSingleton();
	m_window = windowManager.createWindow("TaharezLook/FrameWindow","spawn_screen");
	m_window->setSize(CEGUI::USize(CEGUI::UDim(0.8, 0.f), CEGUI::UDim(0.8, 0.f)));
	m_window->setPosition(CEGUI::UVector2(CEGUI::UDim(0.5-(m_window->getSize().d_width.d_scale*0.5), 0), 
							CEGUI::UDim(0.5-(m_window->getSize().d_height.d_scale*0.5), 0)));
	CEGUI::FrameWindow* frame = (CEGUI::FrameWindow*)m_window;
	frame->setCloseButtonEnabled(false);
	frame->setRollupEnabled(false);
	frame->setDragMovingEnabled(false);
	frame->setSizingEnabled(false);
	m_buttonSpawn = (CEGUI::PushButton*) windowManager.createWindow("TaharezLook/Button", "btn_spawn");
	m_buttonSpawn->setText((CEGUI::utf8*)"Apparaître");
	m_buttonSpawn->setSize(CEGUI::USize(CEGUI::UDim(0.15,0), CEGUI::UDim(0.10,0)));
	m_buttonSpawn->setPosition(CEGUI::UVector2(CEGUI::UDim(0.8250,0), CEGUI::UDim(0.875, 0)));
	m_buttonSpawn->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&SpawnState::trySpawn, this));

	m_spawns = (CEGUI::Listbox*) windowManager.createWindow("TaharezLook/Listbox", "spawns_list");
	m_spawns->setSize(CEGUI::USize(CEGUI::UDim(0.4625, 0), CEGUI::UDim(0.4, 0)));
	m_spawns->setPosition(CEGUI::UVector2(CEGUI::UDim(0.025, 0), CEGUI::UDim(0.025, 0)));

	m_groupCarte = (CEGUI::GroupBox*)windowManager.createWindow("TaharezLook/GroupBox", "groupe_spawn_carte");
	m_groupCarte->setSize(CEGUI::USize(CEGUI::UDim(0.4625, 0), CEGUI::UDim(0.4,0)));
	m_groupCarte->setPosition(CEGUI::UVector2(CEGUI::UDim(0.5125, 0), CEGUI::UDim(0.025, 0)));
	m_groupCarte->setText("Carte");

	m_infosSpawn = windowManager.createWindow("TaharezLook/StaticText", "infos_spawn");
	m_infosSpawn->setSize(CEGUI::USize(CEGUI::UDim(0.8, 0), CEGUI::UDim(0.8,0)));
	m_infosSpawn->setPosition(CEGUI::UVector2(CEGUI::UDim(0.1, 0), CEGUI::UDim(0.1, 0)));
	m_infosSpawn->setText("infos spawn");

	m_tabClasses = (CEGUI::TabControl*) windowManager.createWindow("TaharezLook/TabControl", "tab_classes");
	m_tabClasses->setSize(CEGUI::USize(CEGUI::UDim(0.95, 0), CEGUI::UDim(0.4, 0)));
	m_tabClasses->setPosition(CEGUI::UVector2(CEGUI::UDim(0.025, 0), CEGUI::UDim(0.45, 0)));
	m_tabClasses->subscribeEvent(CEGUI::TabControl::EventSelectionChanged, CEGUI::Event::Subscriber(&SpawnState::classChanged, this));

	m_groupCarte->addChild(m_infosSpawn);
	m_window->addChild(m_groupCarte);
	m_window->addChild(m_buttonSpawn);
	m_window->addChild(m_spawns);
	m_window->addChild(m_tabClasses);
	CEGUI::System::getSingleton().getDefaultGUIContext().getRootWindow()->addChild(m_window);
	m_last_selected_u = nullptr;
	m_avatar = nullptr;
	updateSpawns();
	m_loadClasses();
	m_waitingResponse = false;
}
SpawnState::~SpawnState()
{
	CEGUI::System::getSingleton().getDefaultGUIContext().getRootWindow()->removeChild(m_window);
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
	m_buttonSpawn->setEnabled(m_avatar!=nullptr && !m_waitingResponse);
	return ret_code::CONTINUE;
}
void SpawnState::updateSpawns()
{
	m_spawns->resetList();
	Joueur *curr = m_game->getCurrentJoueur();
	Equipe *equi = curr->equipe();
	for(Unite *e : equi->unites())
	{
		if(e->type() && e->type()->spawn())
		{
			CEGUI::ListboxTextItem *item = new CEGUI::ListboxTextItem(e->type()->nom());
			item->setUserData((void*)e);
			item->setSelectionColours(CEGUI::Colour(255,0,0), CEGUI::Colour(255,0,0), CEGUI::Colour(255,0,0), CEGUI::Colour(255,0,0));
			item->setSelectionBrushImage("TaharezLook/ListboxSelectionBrush");
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
	infos = "x: " + boost::lexical_cast<std::string>(m_last_selected_u->position().x);
	infos += " y: " + boost::lexical_cast<std::string>(m_last_selected_u->position().y);
	infos += " z: " + boost::lexical_cast<std::string>(m_last_selected_u->position().z);
	infos += " id: " + boost::lexical_cast<std::string>(m_last_selected_u->id());
	m_infosSpawn->setText(infos);

	Ogre::Camera *cam = m_game->cameraManager()->camera();
	cam->setPosition(m_last_selected_u->position().convert<Ogre::Vector3>()+Ogre::Vector3(1, 100, 1));
	cam->lookAt(m_last_selected_u->position());

	return true;
}
void SpawnState::m_loadClasses()
{
	Faction *fac = m_game->getCurrentJoueur()->equipe()->faction();
	const ClasseHeroManager& classesMng = fac->getClassesManager(); 
	for(ClasseHero *classe : classesMng.classes())
	{
		CEGUI::Window* tab = CEGUI::WindowManager::getSingleton().createWindow("TaharezLook/TabButtonPane", "tab_classe_"+classe->nom());
		tab->setText(classe->nom());
		m_tabClasses->addTab(tab);
		tab->setUserData(classe);

		CEGUI::ScrollablePane* scroll = (CEGUI::ScrollablePane*)CEGUI::WindowManager::getSingleton().createWindow("TaharezLook/ScrollablePane");
		int i=0;
		for(Avatar* ava : m_game->getCurrentJoueur()->avatars())
		{
			CEGUI::PushButton *btn = m_loadClasse(classe, ava);
			if(!btn)
				continue;
			scroll->addChild(btn);
			btn->setPosition(CEGUI::UVector2(CEGUI::UDim(0.2*i, 0), CEGUI::UDim(0.1, 0)));
			++i;
		}
		for(Avatar* ava : m_game->getCurrentJoueur()->equipe()->faction()->defaultAvatars())
		{
			CEGUI::PushButton *btn = m_loadClasse(classe, ava);
			if(!btn)
				continue;
			scroll->addChild(btn);
			btn->setPosition(CEGUI::UVector2(CEGUI::UDim(0.2*i, 0), CEGUI::UDim(0.1, 0)));
			++i;
		}
		scroll->setSize(CEGUI::USize(CEGUI::UDim(1.00, 0), CEGUI::UDim(1.0, 0)));
		scroll->setPosition(CEGUI::UVector2(CEGUI::UDim(0.0, 0), CEGUI::UDim(0.0, 0)));
		tab->addChild(scroll);
	}
}
CEGUI::PushButton* SpawnState::m_loadClasse(ClasseHero* classe, Avatar* ava)
{
	if(ava->classe() == classe)
	{
		CEGUI::PushButton* btn = (CEGUI::PushButton*)CEGUI::WindowManager::getSingleton().createWindow("TaharezLook/Button");
		btn->setText(ava->nom());
		btn->setSize(CEGUI::USize(CEGUI::UDim(0.2, 0), CEGUI::UDim(0.8, 0)));
		btn->setUserData(ava);
		btn->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&SpawnState::classSelected, this));
		return btn;
	}
	return nullptr;
}
bool SpawnState::classSelected(const CEGUI::EventArgs& arg)
{
	CEGUI::Window* win = ((CEGUI::WindowEventArgs&)arg).window;
	m_avatar = (Avatar*) win->getUserData();
	m_selectionsAvatar[m_avatar->classe()] = m_avatar;
	m_resetCurrentClasses();
	win->setEnabled(false);
	return true;
}
bool SpawnState::classChanged(const CEGUI::EventArgs&)
{
	m_avatar = nullptr;	
	m_resetCurrentClasses();
	return true;
}
void SpawnState::m_resetCurrentClasses()
{
	CEGUI::Window *currT = m_tabClasses->getTabContentsAtIndex(m_tabClasses->getSelectedTabIndex());
	if(currT->getChildCount() == 0 || currT->getChildAtIdx(0)->getChildCount()==0)
		return;
	CEGUI::Window *currentTab = currT->getChildAtIdx(0)->getChildAtIdx(0);
	size_t number = currentTab->getChildCount();
	for(size_t i(0);i<number;++i)
	{
		auto it = m_selectionsAvatar.find(((Avatar*)currentTab->getChildAtIdx(i)->getUserData())->classe());
		if(it!=m_selectionsAvatar.end()&&it->second==currentTab->getChildAtIdx(i)->getUserData())
		{
			currentTab->getChildAtIdx(i)->setEnabled(false);
			m_avatar = it->second;
		}
		else
			currentTab->getChildAtIdx(i)->setEnabled(true);
	}
}
bool SpawnState::trySpawn(const CEGUI::EventArgs&)
{
	m_waitingResponse = true;
	ClientNetworkEngine* net = (ClientNetworkEngine*)m_game->getManager()->getNetwork();
	net->trySpawn(m_last_selected_u, m_avatar);
	return true;	
}
void SpawnState::notifySpawnError(ErrorMessages error)
{
	m_waitingResponse = false;
}
