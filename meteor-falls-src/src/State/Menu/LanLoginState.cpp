#include "LanLoginState.h"
#include "LoginState.h"
#include "../../Engine/GameEngine/Joueur/JoueurLan.h"
#include <CEGUI.h>

LanLoginState::LanLoginState(StateManager* mng, LoginState* p) : State(mng), m_parentState(p), m_lastSelected(nullptr)
{
	m_window = CEGUI::WindowManager::getSingleton().loadWindowLayout("profiles.layout");
	CEGUI::System::getSingleton().getGUISheet()->addChildWindow(m_window);
	m_btn_utiliser = m_window->getChild("fenProfils/jouer");
	m_btn_supp = m_window->getChild("fenProfils/supprimer");
	m_window->getChild("fenProfils/listeProfils")->subscribeEvent(CEGUI::Listbox::EventSelectionChanged,
			CEGUI::Event::Subscriber(&LanLoginState::profilesSelectionChanged, this));
	m_window->getChild("fenProfils/creer")->subscribeEvent(CEGUI::PushButton::EventClicked,
			CEGUI::Event::Subscriber(&LanLoginState::showCreateProfile, this));
	m_window->getChild("fenProfils/supprimer")->subscribeEvent(CEGUI::PushButton::EventClicked,
			CEGUI::Event::Subscriber(&LanLoginState::deleteProfile, this));
	m_window->getChild("fenProfils/jouer")->subscribeEvent(CEGUI::PushButton::EventClicked,
			CEGUI::Event::Subscriber(&LanLoginState::useProfile, this));
	m_window->setVisible(false);
	loadProfilesList();
	updateProfileList();
}
LanLoginState::~LanLoginState()
{
	CEGUI::System::getSingleton().getGUISheet()->removeChildWindow(m_window);
	CEGUI::WindowManager::getSingleton().destroyWindow(m_window);
}
void LanLoginState::enter()
{
	m_window->setVisible(true);
}
void LanLoginState::exit()
{
	m_window->setVisible(false);
}
ret_code LanLoginState::work(unsigned int t)
{
	m_btn_utiliser->setEnabled(m_lastSelected);
	m_btn_supp->setEnabled(m_lastSelected);
	return ret_code::CONTINUE;
}
bool LanLoginState::isVisible()
{
	return true;
}
void LanLoginState::updateProfileList()
{
	CEGUI::Listbox* list = static_cast<CEGUI::Listbox*>(m_window->getChild("fenProfils/listeProfils"));
	list->resetList();
	bool first=true;
	for(JoueurLan *j : m_profiles)
	{
		if(first&&!m_lastSelected)
			m_lastSelected=j;
		CEGUI::ListboxItem *item = new CEGUI::ListboxTextItem(j->getNom());
		list->addItem(item);
		item->setUserData(j);
		item->setSelected(j==m_lastSelected);
		item->setSelectionBrushImage("TaharezLook", "ListboxSelectionBrush");
		first=false;
	}
}
void LanLoginState::loadProfilesList()
{
	JoueurLan* j = new JoueurLan;
	j->setNom("test");
	m_profiles.push_back(j);
	j = new JoueurLan;
	j->setNom("test 1");
	m_profiles.push_back(j);
}
bool LanLoginState::profilesSelectionChanged(const CEGUI::EventArgs&)
{
	CEGUI::Listbox* list = static_cast<CEGUI::Listbox*>(m_window->getChild("fenProfils/listeProfils"));
	CEGUI::ListboxItem* item = list->getFirstSelectedItem();
	if(item)
		m_lastSelected = static_cast<JoueurLan*>(item->getUserData());
	else
		m_lastSelected = nullptr;
	return true;
}
bool LanLoginState::showCreateProfile(const CEGUI::EventArgs&)
{
	m_window->setVisible(false);
	m_windowCreate = CEGUI::WindowManager::getSingleton().loadWindowLayout("creer_profil_lan.layout");
	CEGUI::System::getSingleton().getGUISheet()->addChildWindow(m_windowCreate);
	m_windowCreate->getChild("fenCreerProfils/creer")->subscribeEvent(CEGUI::PushButton::EventClicked,
			CEGUI::Event::Subscriber(&LanLoginState::createNewProfile, this));
	m_windowCreate->getChild("fenCreerProfils/annuler")->subscribeEvent(CEGUI::PushButton::EventClicked,
			CEGUI::Event::Subscriber(&LanLoginState::createNewProfile, this));
}
bool LanLoginState::createNewProfile(const CEGUI::EventArgs& e)
{
	const CEGUI::WindowEventArgs *event = static_cast<const CEGUI::WindowEventArgs*>(&e);
	if(event->window != m_windowCreate->getChild("fenCreerProfils/annuler"))
	{
		std::string pseudo = m_windowCreate->getChild("fenCreerProfils/pseudo")->getText().c_str();
		JoueurLan *j = new JoueurLan;
		j->setNom(pseudo);
		m_profiles.push_back(j);
		updateProfileList();
	}
	CEGUI::System::getSingleton().getGUISheet()->removeChildWindow(m_windowCreate);
	CEGUI::WindowManager::getSingleton().destroyWindow(m_windowCreate);
	m_windowCreate=nullptr;
	m_window->setVisible(true);
}
bool LanLoginState::deleteProfile(const CEGUI::EventArgs& e)
{
	for(auto it=m_profiles.begin();it!=m_profiles.end();++it)
	{
		if(*it==m_lastSelected)
		{
			delete *it;
			m_profiles.erase(it);
			break;
		}
	}
	m_lastSelected=nullptr;
	updateProfileList();
	return true;
}
bool LanLoginState::useProfile(const CEGUI::EventArgs& e)
{
	*m_parentState->joueur() = m_lastSelected;
	m_parentState->exit();
}
