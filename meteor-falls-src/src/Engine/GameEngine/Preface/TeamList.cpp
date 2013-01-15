#include "TeamList.h"
#include "../Factions/Equipe.h"
#include <boost/lexical_cast.hpp>
#include "../../NetworkEngine/clientnetworkengine.h"

TeamList::TeamList(StateManager* mgr, GameEngine* engine) : State(mgr),
m_visible(true),
m_game_engine(engine)
{
    CEGUI::WindowManager &m_window_manager = CEGUI::WindowManager::getSingleton();
    m_list_team = (CEGUI::Listbox*)m_window_manager.createWindow("OgreTray/Listbox", "ListTeam");
    m_list_team->setSize(CEGUI::UVector2(CEGUI::UDim(0.50, 0), CEGUI::UDim(0.60, 0)));
    m_list_team->setPosition(CEGUI::UVector2(CEGUI::UDim(0.50-(m_list_team->getSize().d_x.d_scale/2), 0),
                                         CEGUI::UDim((m_list_team->getSize().d_y.d_scale
                                                        /2), 0)));
    m_list_team->setMultiselectEnabled(false);
    m_list_team->subscribeEvent(CEGUI::Listbox::EventSelectionChanged, CEGUI::Event::Subscriber(&TeamList::m_item_selected, this));
    CEGUI::System::getSingleton().getGUISheet()->addChildWindow(m_list_team);
    m_list_team->hide();
}
TeamList::~TeamList()
{
	CEGUI::System::getSingleton().getGUISheet()->removeChildWindow(m_list_team);
	CEGUI::WindowManager::getSingleton().destroyWindow(m_list_team);
}
bool TeamList::isVisible()
{
    return m_visible;
}
void TeamList::enter()
{
    m_list_team->show();
    m_visible = true;
}
void TeamList::exit()
{
    m_list_team->hide();
    m_visible = false;
}
ret_code TeamList::work(unsigned int time)
{
    if (!m_game_engine->getTeams().empty())
    {
        m_list_team->resetList();
        for (Equipe* e : m_game_engine->getTeams())
        {
            CEGUI::ListboxTextItem *item = new CEGUI::ListboxTextItem("Team "+boost::lexical_cast<std::string>((int)e->id()));
            item->setSelected(false);
            m_list_team->addItem(item);
            item->setUserData(e);
        }
    }
	if(m_isSelectingTeam)
	{
		ClientNetworkEngine *net = (ClientNetworkEngine*)m_game_engine->getManager()->getNetwork();
		if(m_equipe->id() == net->teamId())
		{
    		m_game_engine->setSousStateType(GameEngine::TypeState::TEAM_STATE);
		}
	}
    return CONTINUE;
}
bool TeamList::m_item_selected(const CEGUI::EventArgs&)
{
	ClientNetworkEngine *net = (ClientNetworkEngine*)m_game_engine->getManager()->getNetwork();
    for (size_t i=0; i<m_list_team->getItemCount(); ++i)
        if (m_list_team->getListboxItemFromIndex(i)->isSelected())
        {
            m_game_engine->addTeam(static_cast<Equipe*>(m_list_team->getListboxItemFromIndex(i)->getUserData()));
			m_isSelectingTeam = true;
			m_equipe          = static_cast<Equipe*>(m_list_team->getListboxItemFromIndex(i)->getUserData());
			net->trySelectTeam(m_equipe->id());
        }

    return true;
}
