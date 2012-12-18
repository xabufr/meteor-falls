#include "TeamList.h"
#include "../Factions/Equipe.h"

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
    m_list_team->show();
}

TeamList::~TeamList()
{
    delete m_list_team;
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
            CEGUI::ListboxTextItem *item = new CEGUI::ListboxTextItem("Team"+e->id());
                item->setSelected(false);
                m_list_team->addItem(item);
				item->setUserData(e);
        }
    }
    return CONTINUE;
}

bool TeamList::m_item_selected(const CEGUI::EventArgs&)
{
    for (size_t i=0; i<m_list_team->getItemCount(); ++i)
        if (m_list_team->getListboxItemFromIndex(i)->isSelected())
           std::cout << m_list_team->getListboxItemFromIndex(i)->getText() << std::endl;

    return true;
}
