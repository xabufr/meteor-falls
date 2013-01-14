#include "LoadingScreen.h"
#include <iostream>
#include "OgreApplication.h"
#include "ogrecontextmanager.h"

LoadingScreen::LoadingScreen()
{
    m_window = CEGUI::WindowManager::getSingleton().createWindow("OgreTray/TabButtonPane", "Loading");
    //m_window->setSize(CEGUI::UVector2(CEGUI::UDim(0.30, 0), CEGUI::UDim(0.50, 0)));
    //m_window->setPosition(CEGUI::UVector2(CEGUI::UDim(0.50-(m_window->getSize().d_x.d_scale/2), 0), CEGUI::UDim(0.30, 0)));


    //m_window->setText("loadingbbvrevervr");
    //m_window->setProperty("FrameEnabled", "false");
    //m_window->setProperty("Alpha", "1.0");
    //m_window->setProperty("VertFormatting", "TopAligned");
    //m_window->setProperty("TextColours", "0.5,0.5,0.5,0.5");
    m_loadingText = CEGUI::WindowManager::getSingleton().createWindow("OgreTray/StaticText", "StaticTextLoadingText");
    m_loadingText->setText("Loading...");
    m_loadingText->setSize(CEGUI::UVector2(CEGUI::UDim(0.80, 0), CEGUI::UDim(0.10, 0)));
    m_loadingText->setProperty("FrameEnabled", "false");
    m_loadingText->setProperty("BackgroundEnabled", "false");
    m_loadingText->setProperty("VertFormatting", "TopAligned");
    m_window->addChildWindow(m_loadingText);

    m_loadingCurrent = CEGUI::WindowManager::getSingleton().createWindow("OgreTray/StaticText", "StaticTextLoadingCurrent");
    m_loadingCurrent->setText("Loading...");
    m_loadingCurrent->setSize(CEGUI::UVector2(CEGUI::UDim(0.80, 0), CEGUI::UDim(0.10, 0)));
    m_loadingCurrent->setProperty("FrameEnabled", "false");
    m_loadingCurrent->setProperty("BackgroundEnabled", "false");
    m_loadingCurrent->setProperty("VertFormatting", "TopAligned");
    m_window->addChildWindow(m_loadingCurrent);

    m_loadingText->setPosition(CEGUI::UVector2(CEGUI::UDim(0.50-(m_loadingText->getSize().d_x.d_scale/2), 0),
                                         CEGUI::UDim(0+(m_window->getSize().d_y.d_scale*0.5/m_window->getChildCount()), 0)));
    m_loadingCurrent->setPosition(CEGUI::UVector2(CEGUI::UDim(0.50-(m_loadingCurrent->getSize().d_x.d_scale/2), 0),
                                         CEGUI::UDim(m_loadingText->getPosition().d_y.d_scale+(m_window->getSize().d_y.d_scale*0.5/m_window->getChildCount()), 0)));


    m_window->show();
}

LoadingScreen::~LoadingScreen()
{
    //dtor
}
void LoadingScreen::update(std::string s)
{
    m_loadingCurrent->setText(s);
    OgreContextManager::get()->getOgreApplication()->RenderOneFrame();
}
void LoadingScreen::show()
{
    CEGUI::System::getSingleton().setGUISheet(m_window);
    OgreContextManager::get()->getOgreApplication()->RenderOneFrame();
}
