#include "LanLoginState.h"
#include "LoginState.h"
#include "../../Engine/GameEngine/Joueur/JoueurLan.h"
#include <CEGUI/CEGUI.h>
#include <boost/filesystem.hpp>
#include "../../Engine/ScriptEngine/XmlDocumentManager.h"
#include "../../Utils/Exception/FileNotFound.h"
#include <boost/property_tree/xml_parser.hpp>
#include <fstream>

LanLoginState::LanLoginState(StateManager* mng, LoginState* p) : State(mng), m_parentState(p), m_lastSelected(nullptr), m_continue(true)
{
    m_window = CEGUI::WindowManager::getSingleton().loadLayoutFromFile("profiles.layout");
    CEGUI::System::getSingleton().getDefaultGUIContext().getRootWindow()->addChild(m_window);
    m_btn_utiliser = m_window->getChild("jouer");
    m_btn_supp = m_window->getChild("supprimer");
    m_window->subscribeEvent(CEGUI::FrameWindow::EventCloseClicked,
            CEGUI::Event::Subscriber(&LanLoginState::retour, this));
    m_window->getChild("listeProfils")->subscribeEvent(CEGUI::Listbox::EventSelectionChanged,
            CEGUI::Event::Subscriber(&LanLoginState::profilesSelectionChanged, this));
    m_window->getChild("creer")->subscribeEvent(CEGUI::PushButton::EventClicked,
            CEGUI::Event::Subscriber(&LanLoginState::showCreateProfile, this));
    m_window->getChild("supprimer")->subscribeEvent(CEGUI::PushButton::EventClicked,
            CEGUI::Event::Subscriber(&LanLoginState::deleteProfile, this));
    m_window->getChild("jouer")->subscribeEvent(CEGUI::PushButton::EventClicked,
            CEGUI::Event::Subscriber(&LanLoginState::useProfile, this));
    m_window->getChild("listeProfils")->subscribeEvent(CEGUI::Listbox::EventMouseDoubleClick,
            CEGUI::Event::Subscriber(&LanLoginState::useProfile, this));
    m_window->getChild("retour")->subscribeEvent(CEGUI::PushButton::EventClicked,
            CEGUI::Event::Subscriber(&LanLoginState::retour, this));
    m_window->setVisible(false);
    loadProfilesList();
    updateProfileList();
}
LanLoginState::~LanLoginState()
{
    CEGUI::System::getSingleton().getDefaultGUIContext().getRootWindow()->removeChild(m_window);
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
ret_code LanLoginState::work(const TimeDuration &elapsed)
{
    m_btn_utiliser->setEnabled(m_lastSelected);
    m_btn_supp->setEnabled(m_lastSelected);
    return (m_continue) ? ret_code::CONTINUE:ret_code::FINISHED;
}
bool LanLoginState::isVisible()
{
    return true;
}
void LanLoginState::updateProfileList()
{
    CEGUI::Listbox* list = static_cast<CEGUI::Listbox*>(m_window->getChild("listeProfils"));
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
        item->setSelectionBrushImage("TaharezLook/ListboxSelectionBrush");
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
                XmlDocumentManager::Document &doc = XmlDocumentManager::get()->getDocument(profile.string()+".profile");
                JoueurLan *j = new JoueurLan;
                j->setNom(doc.get<std::string>("profile.<xmlattr>.name"));
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
    CEGUI::Listbox* list = static_cast<CEGUI::Listbox*>(m_window->getChild("listeProfils"));
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
    m_windowCreate = CEGUI::WindowManager::getSingleton().loadLayoutFromFile("creer_profil_lan.layout");
    CEGUI::System::getSingleton().getDefaultGUIContext().getRootWindow()->addChild(m_windowCreate);
    m_windowCreate->getChild("creer")->subscribeEvent(CEGUI::PushButton::EventClicked,
            CEGUI::Event::Subscriber(&LanLoginState::createNewProfile, this));
    //TODO faire un vrai annuler ici
    m_windowCreate->getChild("annuler")->subscribeEvent(CEGUI::PushButton::EventClicked,
            CEGUI::Event::Subscriber(&LanLoginState::createNewProfile, this));
    return true;
}
bool LanLoginState::createNewProfile(const CEGUI::EventArgs& e)
{
    const CEGUI::WindowEventArgs *event = static_cast<const CEGUI::WindowEventArgs*>(&e);
    std::string pseudo = m_windowCreate->getChild("pseudo")->getText().c_str();
    if(!profileExists(pseudo))
    {
        boost::filesystem::path pathProfiles("profiles");
        pathProfiles/=pseudo;
        boost::filesystem::create_directory(pathProfiles);
        if(event->window != m_windowCreate->getChild("annuler"))
        {
            XmlDocumentManager::Document doc;
            doc.put("profile.<xmlattr>.pseudo", pseudo);
            pathProfiles/=pseudo;
            boost::property_tree::xml_parser::write_xml(pathProfiles.string()+".profile", doc);
            JoueurLan *j = new JoueurLan;
            j->setNom(pseudo);
            m_profiles.push_back(j);
            updateProfileList();
        }
        CEGUI::System::getSingleton().getDefaultGUIContext().getRootWindow()->removeChild(m_windowCreate);
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
    if(m_lastSelected)
    {
        *m_parentState->joueur() = m_lastSelected;
        m_parentState->exit();
    }
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
bool LanLoginState::retour(const CEGUI::EventArgs& e)
{
    m_continue=false;
    return true;
}
