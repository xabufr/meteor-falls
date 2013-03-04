#include "MessageDialog.h"


MessageDialog::MessageDialog():m_visible(false)
{
    CEGUI::WindowManager &m_window_manager = CEGUI::WindowManager::getSingleton();

    m_window = m_window_manager.createWindow("OgreTray/TabButtonPane", "MessageDialog");
    m_window->setSize(CEGUI::UVector2(CEGUI::UDim(0.40, 0), CEGUI::UDim(0.30, 0)));
    m_window->setPosition(CEGUI::UVector2(CEGUI::UDim(0.3, 0), CEGUI::UDim(0.35, 0)));
    m_window->setAlwaysOnTop(true);
    CEGUI::System::getSingleton().getGUISheet()->addChildWindow(m_window);

    m_text = m_window_manager.createWindow("OgreTray/StaticText", "TextDialog");
    m_text->setSize(CEGUI::UVector2(CEGUI::UDim(0.92, 0), CEGUI::UDim(0.79, 0)));
    m_text->setPosition(CEGUI::UVector2(CEGUI::UDim(0.03, 0),
                                     CEGUI::UDim(0.03, 0)));
    m_text->setText("");
    m_text->setProperty("FrameEnabled", "false");
    m_text->setProperty("BackgroundEnabled", "false");
    m_text->setProperty("HorzFormatting", "WordWrapCentred");
    m_window->addChildWindow(m_text);

    m_accept = (CEGUI::PushButton*)m_window_manager.createWindow("OgreTray/Button", "BouttonOkDialog");
    m_accept->setSize(CEGUI::UVector2(CEGUI::UDim(0.20, 0), CEGUI::UDim(0.15, 0)));
    m_accept->setPosition(CEGUI::UVector2(CEGUI::UDim(0.40, 0),
                                         CEGUI::UDim(0.82, 0)));
    m_accept->setText("Ok");
    m_accept->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&MessageDialog::m_button_pushed, this));
    m_window->addChildWindow(m_accept);
    m_window->hide();
}

MessageDialog::~MessageDialog()
{
    CEGUI::System::getSingleton().getGUISheet()->removeChildWindow(m_window);
    CEGUI::WindowManager::getSingleton().destroyWindow(m_window);
    CEGUI::System::getSingleton().getGUISheet()->removeChildWindow(m_text);
    CEGUI::WindowManager::getSingleton().destroyWindow(m_text);
    CEGUI::System::getSingleton().getGUISheet()->removeChildWindow(m_accept);
    CEGUI::WindowManager::getSingleton().destroyWindow(m_accept);
}

void MessageDialog::show()
{
    m_visible = true;
    m_window->show();
}

void MessageDialog::hide()
{
    m_visible = false;
    m_window->hide();
}


bool MessageDialog::m_button_pushed(const CEGUI::EventArgs&)
{
    hide();
}
