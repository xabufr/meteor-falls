#include "LanLoginState.h"
#include "LoginState.h"
#include "../../Engine/GameEngine/Joueur/JoueurLan.h"
#include <CEGUI.h>
#include <boost/filesystem.hpp>
#include "../../Engine/ScriptEngine/XmlDocumentManager.h"
#include "../../Utils/Exception/FileNotFound.h"
#include <rapidxml_print.hpp>
#include <fstream>

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
	boost::filesystem::path pathProfiles("profiles");
	if(!boost::filesystem::exists(pathProfiles))
	{
		boost::filesystem::create_directory("profiles");
		pathProfiles = boost::filesystem::path("profiles");
	}
	for(boost::filesystem::directory_iterator it(pathProfiles);it!=boost::filesystem::directory_iterator();++it)
	{
		if(boost::filesystem::is_directory(it->path()))
		{
			boost::filesystem::path profile = it->path();
			profile/= profile.filename();
			try
			{
				rapidxml::xml_document<> *doc = XmlDocumentManager::get()->getDocument(profile.string()+".profile");
				rapidxml::xml_node<> *root = doc->first_node("profile");
				JoueurLan *j = new JoueurLan;
				j->setNom(root->first_attribute("name")->value());
				m_profiles.push_back(j);
			}
			catch (FileNotFound &e)
			{
				continue;
			}
		}
	}
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
	return true;
}
bool LanLoginState::createNewProfile(const CEGUI::EventArgs& e)
{
	const CEGUI::WindowEventArgs *event = static_cast<const CEGUI::WindowEventArgs*>(&e);
	std::string pseudo = m_windowCreate->getChild("fenCreerProfils/pseudo")->getText().c_str();
	if(!profileExists(pseudo))
	{
		boost::filesystem::path pathProfiles("profiles");
		pathProfiles/=pseudo;
		boost::filesystem::create_directory(pathProfiles);
		if(event->window != m_windowCreate->getChild("fenCreerProfils/annuler"))
		{
			rapidxml::xml_document<> doc;
			rapidxml::xml_node<>* root = doc.allocate_node(rapidxml::node_type::node_element);
			root->name("profile");
			root->append_attribute(doc.allocate_attribute("name", pseudo.c_str()));
			doc.append_node(root);
			pathProfiles/=pseudo;
			std::ofstream f((pathProfiles.string()+".profile").c_str());
			f<<doc;
			f.close();
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
	return true;
}
bool LanLoginState::deleteProfile(const CEGUI::EventArgs& e)
{
	boost::filesystem::remove_all("profiles/"+m_lastSelected->getNom());
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
	return true;
}
bool LanLoginState::profileExists(const std::string& pseudo)
{
	boost::filesystem::path pathProfiles("profiles");
	pathProfiles/=pseudo;
	if(boost::filesystem::exists(pathProfiles))
	{
		pathProfiles/=pseudo+".profile";
		return boost::filesystem::is_regular_file(pathProfiles);
	}
	return false;
}