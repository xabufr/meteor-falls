#include "LoadingScreen.h"
#include <iostream>
#include "OgreApplication.h"
#include "ogrecontextmanager.h"

LoadingScreen::LoadingScreen(int sum):m_count(0), m_sum(sum)
{
	m_window = CEGUI::WindowManager::getSingleton().loadLayoutFromFile("loading_screen.layout");
//    m_window = CEGUI::WindowManager::getSingleton().createWindow("OgreTray/TabButtonPane", "Loading");

//    m_loadingText = CEGUI::WindowManager::getSingleton().createWindow("OgreTray/StaticText", "StaticTextLoadingText");
//    m_loadingText->setText("Loading...");
//    m_loadingText->setSize(CEGUI::UVector2(CEGUI::UDim(0.80, 0), CEGUI::UDim(0.10, 0)));
//    m_loadingText->setProperty("FrameEnabled", "false");
//    m_loadingText->setProperty("BackgroundEnabled", "false");
//    m_loadingText->setProperty("VertFormatting", "TopAligned");
//    m_window->addChildWindow(m_loadingText);

//    m_progress_bar = (CEGUI::ProgressBar*)CEGUI::WindowManager::getSingleton().createWindow("OgreTray/ProgressBar", "ProgressBarRess");
    //m_progress_bar->setStepSize((float)(100/m_sum));
//    m_progress_bar->setSize(CEGUI::UVector2(CEGUI::UDim(0.80, 0), CEGUI::UDim(0.05, 0)));
//    m_progress_bar->setPosition(CEGUI::UVector2(CEGUI::UDim(0.50-(m_progress_bar->getSize().d_x.d_scale/2), 0),
//                                         CEGUI::UDim(m_progress_bar->getPosition().d_y.d_scale+(m_window->getSize().d_y.d_scale*0.5/m_window->getChildCount()), 0)));
//    m_window->addChildWindow(m_progress_bar);

//    m_loadingCurrent = CEGUI::WindowManager::getSingleton().createWindow("OgreTray/StaticText", "StaticTextLoadingCurrent");
//    m_loadingCurrent->setText("Loading...");
//    m_loadingCurrent->setSize(CEGUI::UVector2(CEGUI::UDim(0.80, 0), CEGUI::UDim(0.10, 0)));
//    m_loadingCurrent->setProperty("FrameEnabled", "false");
//    m_loadingCurrent->setProperty("BackgroundEnabled", "false");
//    m_loadingCurrent->setProperty("VertFormatting", "TopAligned");
//    m_window->addChildWindow(m_loadingCurrent);

//    m_loadingText->setPosition(CEGUI::UVector2(CEGUI::UDim(0.50-(m_loadingText->getSize().d_x.d_scale/2), 0),
//                                         CEGUI::UDim(0+(m_window->getSize().d_y.d_scale*0.5/m_window->getChildCount()), 0)));
//    m_loadingCurrent->setPosition(CEGUI::UVector2(CEGUI::UDim(0.50-(m_loadingCurrent->getSize().d_x.d_scale/2), 0),
//                                         CEGUI::UDim(m_loadingText->getPosition().d_y.d_scale+(m_window->getSize().d_y.d_scale*0.5/m_window->getChildCount()), 0)));
	m_progress_bar   = (CEGUI::ProgressBar*)m_window->getChild("fenChargement/progression");
	m_loadingCurrent = m_window->getChild("fenChargement/texteCurrRessource");
	m_logger         = (CEGUI::MultiLineEditbox*)m_window->getChild("fenChargement/chargementLogger");
    m_window->show();
}
LoadingScreen::~LoadingScreen()
{
	//CEGUI::System::getSingleton().getGUISheet()->removeChildWindow(m_window);
	CEGUI::WindowManager::getSingleton().destroyWindow(m_window);
	CEGUI::System::getSingleton().getDefaultGUIContext().setRootWindow(m_ancWindow);
}
void LoadingScreen::update(std::string s)
{
	static std::string last;
	if(last != s)
	{
		m_loadingCurrent->setText(s);
		m_logger->appendText("Chargement de '"+s+"'\n");
		m_logger->getVertScrollbar()->setScrollPosition(9999.f);
	}
	last=s;
	m_progress_bar->setProgress(float(m_count)/float(m_sum));
    OgreContextManager::get()->getOgreApplication()->RenderOneFrame();
}
void LoadingScreen::setGroup(std::string s)
{
    update(s);
    ++m_count;
}
void LoadingScreen::show()
{
	m_ancWindow = CEGUI::System::getSingleton().getDefaultGUIContext().getRootWindow();
    CEGUI::System::getSingleton().getDefaultGUIContext().setRootWindow(m_window);
    OgreContextManager::get()->getOgreApplication()->RenderOneFrame();
}
