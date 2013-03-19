#include "TeamList.h"
#include "../Factions/Equipe.h"
#include "../Factions/Faction.h"
#include "../Joueur/JoueurRTS.h"
#include <boost/lexical_cast.hpp>
#include "../../NetworkEngine/clientnetworkengine.h"
#include "../../EngineManager/EngineManager.h"
#include "../GameEngine.h"
#include <CEGUI.h>

TeamList::TeamList(StateManager* mgr, GameEngine* engine) : State(mgr),
m_visible(true),
m_game_engine(engine),
m_isSelectingTeam(false)
{
	m_equipe = nullptr;
    CEGUI::WindowManager &m_window_manager = CEGUI::WindowManager::getSingleton();
    m_window = m_window_manager.loadWindowLayout("select_team.layout");
	m_list_team = (CEGUI::MultiColumnList*)m_window->getChildRecursive("fenSelectionTeam/listeEquipes");
	m_commandant = m_window->getChildRecursive("fenSelectionTeam/commandant");
	m_list_joueurs = (CEGUI::MultiColumnList*)m_window->getChildRecursive("fenSelectionTeam/listeJoueurs");
	m_list_team->subscribeEvent(CEGUI::MultiColumnList::EventSelectionChanged,
			CEGUI::Event::Subscriber(&TeamList::m_item_selected, this));
	m_btnJoin = m_window->getChildRecursive("fenSelectionTeam/btnJoindre");
	m_btnJoin->subscribeEvent(CEGUI::PushButton::EventClicked,
			CEGUI::Event::Subscriber(&TeamList::m_join, this));
    CEGUI::System::getSingleton().getGUISheet()->addChildWindow(m_window);
    m_window->hide();
	m_isSelectingTeam = false;
}
TeamList::~TeamList()
{
	CEGUI::WindowManager::getSingleton().destroyWindow(m_window);
}
bool TeamList::isVisible()
{
    return m_window->isVisible();
}
void TeamList::enter()
{
    m_window->show();
}
void TeamList::exit()
{
    m_window->hide();
}
ret_code TeamList::work(unsigned int time)
{
	ClientNetworkEngine *net = (ClientNetworkEngine*)m_game_engine->getManager()->getNetwork();
	for (Equipe* e : m_game_engine->getTeams())
	{
		addEquipe(e);
	}
	if(m_equipe)
	{
		if(m_isSelectingTeam)
		{
			if(m_equipe == m_game_engine->getCurrentJoueur()->equipe())
			{
				m_game_engine->setSousStateType(GameEngine::TypeState::TEAM_STATE);
			}
		}
		for(Joueur *j : m_equipe->joueurs())
			addPlayer(j);
		if(m_equipe->getRTS())
			setCommandant(m_equipe->getRTS()->joueur());
		else
			setCommandant(nullptr);
	}
	m_btnJoin->setEnabled(m_equipe&&!net->isWaitingSelectTeam());
	return CONTINUE;
}
bool TeamList::m_item_selected(const CEGUI::EventArgs&)
{
	ClientNetworkEngine *net = (ClientNetworkEngine*)m_game_engine->getManager()->getNetwork();
    //for (size_t i=0; i<m_list_team->getItemCount(); ++i)
    //    if (m_list_team->getListboxItemFromIndex(i)->isSelected())
    //    {
        //    m_game_engine->addTeam(static_cast<Equipe*>(m_list_team->getListboxItemFromIndex(i)->getUserData()));
	//		m_isSelectingTeam = true;
	//		m_equipe          = static_cast<Equipe*>(m_list_team->getListboxItemFromIndex(i)->getUserData());
	//		net->trySelectTeam(m_equipe->id());
    //    }
	m_equipe = nullptr;
	if(m_list_team->getFirstSelectedItem())
		m_equipe = (Equipe*) m_list_team->getFirstSelectedItem()->getUserData();
	clearPlayers();	
    return true;
}
void TeamList::addEquipe(Equipe *e)
{
	for(Equipe *eq : m_equipes)
	{
		if(eq==e)
			return;
	}
	m_equipes.push_back(e);
	CEGUI::ListboxTextItem *item;

	int row = m_list_team->addRow();
	item = new CEGUI::ListboxTextItem("",0);
	item->setSelectionBrushImage("TaharezLook", "MultiListSelectionBrush");
	item->setUserData(e);
	m_list_team->setItem(item, 0, row);

	item = new CEGUI::ListboxTextItem(e->faction()->nom(),0);
	item->setSelectionBrushImage("TaharezLook", "MultiListSelectionBrush");
	item->setUserData(e);
	m_list_team->setItem(item, 1, row);
}
void TeamList::addPlayer(Joueur *j)
{
	for(Joueur *jj : m_joueurs)
	{
		if(jj=j)
			return;
	}
	m_joueurs.push_back(j);
	int row = m_list_joueurs->addRow();
	CEGUI::ListboxTextItem *item;
	item = new CEGUI::ListboxTextItem(j->getNom(), 0);
	item->setSelectionBrushImage("TaharezLook", "MultiListSelectionBrush");
	item->setUserData(j);
	m_list_joueurs->setItem(item, 0, row);

	item = new CEGUI::ListboxTextItem("0", 0);
	item->setSelectionBrushImage("TaharezLook", "MultiListSelectionBrush");
	item->setUserData(j);
	m_list_joueurs->setItem(item, 1, row);

	item = new CEGUI::ListboxTextItem(boost::lexical_cast<std::string>(j->ping), 0);
	item->setSelectionBrushImage("TaharezLook", "MultiListSelectionBrush");
	item->setUserData(j);
	m_list_joueurs->setItem(item, 2, row);
}
void TeamList::clearPlayers()
{
	m_joueurs.clear();
	m_list_joueurs->resetList();
}
void TeamList::setCommandant(Joueur *j)
{
	if(j)
		m_commandant->setText(j->getNom());
	else 
		m_commandant->setText("");
}
void TeamList::join()
{
	ClientNetworkEngine *net = (ClientNetworkEngine*)m_game_engine->getManager()->getNetwork();
	if(m_equipe&&!net->isWaitingSelectTeam())
	{
		net->trySelectTeam(m_equipe->id());
		m_isSelectingTeam = true;
	}
}
bool TeamList::m_join(const CEGUI::EventArgs&)
{
	join();
}
