#include "SoundSetting.h"
#include "../../Engine/SoundEngine/Playlist.h"
#include "../../precompiled/_rapidxml.h"
#include "../../precompiled/lexical_cast.h"
#include "Engine/ScriptEngine/XmlDocumentManager.h"
#include "Utils/Exception/FileNotFound.h"
#include "Utils/Configuration/Config.h"
#include <fstream>
#include <rapidxml_print.hpp>

SoundSetting::SoundSetting(StateManager* mgr):State(mgr),
m_state_manager(mgr)
{
    CEGUI::WindowManager &m_window_manager = CEGUI::WindowManager::getSingleton();

    m_activate = (CEGUI::Checkbox*)m_window_manager.createWindow("OgreTray/Checkbox", "CheckBoxActivate");
    m_activate->setSize(CEGUI::UVector2(CEGUI::UDim(0.50, 0), CEGUI::UDim(0.05, 0)));
    m_activate->setPosition(CEGUI::UVector2(CEGUI::UDim(0.05, 0),
                                         CEGUI::UDim(0.05, 0)));
    m_activate->setText("Activer le son");
    m_activate->setSelected((!Playlist::get()->get_Pause() && !Playlist::get()->get_Stop()));
    m_activate->subscribeEvent(CEGUI::Checkbox::EventCheckStateChanged, CEGUI::Event::Subscriber(&SoundSetting::m_checkbox_used, this));
    CEGUI::System::getSingleton().getGUISheet()->getChild("OptionState")->addChildWindow(m_activate);

    m_text_music = (CEGUI::Titlebar*)m_window_manager.createWindow("OgreTray/StaticText", "TextVolMusic");
    m_text_music->setSize(CEGUI::UVector2(CEGUI::UDim(0.50, 0), CEGUI::UDim(0.05, 0)));
    m_text_music->setPosition(CEGUI::UVector2(CEGUI::UDim(0.05, 0),
                                         CEGUI::UDim(0.12, 0)));
    m_text_music->setText("Volume musique:");
    m_text_music->setProperty("FrameEnabled", "false");
    m_text_music->setProperty("BackgroundEnabled", "false");
    m_text_music->setProperty("VertFormatting", "TopAligned");
    CEGUI::System::getSingleton().getGUISheet()->getChild("OptionState")->addChildWindow(m_text_music);

    m_music_volume = (CEGUI::Slider*)m_window_manager.createWindow("OgreTray/Slider", "SliderVolMusic");
    m_music_volume->setSize(CEGUI::UVector2(CEGUI::UDim(0.50, 0), CEGUI::UDim(0.05, 0)));
    m_music_volume->setPosition(CEGUI::UVector2(CEGUI::UDim(0.05, 0),
                                         CEGUI::UDim(0.19, 0)));
    m_music_volume->setMaxValue(100);
    m_music_volume->setCurrentValue(Playlist::get()->get_Volume());
    m_music_volume->setEnabled(m_activate->isSelected());
    m_music_volume->subscribeEvent(CEGUI::Slider::EventValueChanged, CEGUI::Event::Subscriber(&SoundSetting::m_modif_slide, this));
    CEGUI::System::getSingleton().getGUISheet()->getChild("OptionState")->addChildWindow(m_music_volume);

    m_text_ambiant = (CEGUI::Titlebar*)m_window_manager.createWindow("OgreTray/StaticText", "TextVolAmbiant");
    m_text_ambiant->setSize(CEGUI::UVector2(CEGUI::UDim(0.50, 0), CEGUI::UDim(0.05, 0)));
    m_text_ambiant->setPosition(CEGUI::UVector2(CEGUI::UDim(0.05, 0),
                                         CEGUI::UDim(0.26, 0)));
    m_text_ambiant->setText("Volume sons ambiants:");
    m_text_ambiant->setProperty("FrameEnabled", "false");
    m_text_ambiant->setProperty("BackgroundEnabled", "false");
    m_text_ambiant->setProperty("VertFormatting", "TopAligned");
    CEGUI::System::getSingleton().getGUISheet()->getChild("OptionState")->addChildWindow(m_text_ambiant);

    m_ambiant_volume = (CEGUI::Slider*)m_window_manager.createWindow("OgreTray/Slider", "SliderVolAmbiant");
    m_ambiant_volume->setSize(CEGUI::UVector2(CEGUI::UDim(0.50, 0), CEGUI::UDim(0.05, 0)));
    m_ambiant_volume->setPosition(CEGUI::UVector2(CEGUI::UDim(0.05, 0),
                                         CEGUI::UDim(0.33, 0)));
    m_ambiant_volume->setMaxValue(100);
    //m_ambiant_volume->setCurrentValue();
    m_ambiant_volume->setEnabled(m_activate->isSelected());
    m_ambiant_volume->subscribeEvent(CEGUI::Slider::EventValueChanged, CEGUI::Event::Subscriber(&SoundSetting::m_modif_slide, this));
    CEGUI::System::getSingleton().getGUISheet()->getChild("OptionState")->addChildWindow(m_ambiant_volume);

    m_text_effect = (CEGUI::Titlebar*)m_window_manager.createWindow("OgreTray/StaticText", "TextVolEffect");
    m_text_effect->setSize(CEGUI::UVector2(CEGUI::UDim(0.50, 0), CEGUI::UDim(0.05, 0)));
    m_text_effect->setPosition(CEGUI::UVector2(CEGUI::UDim(0.05, 0),
                                         CEGUI::UDim(0.40, 0)));
    m_text_effect->setText("Volume effets:");
    m_text_effect->setProperty("FrameEnabled", "false");
    m_text_effect->setProperty("BackgroundEnabled", "false");
    m_text_effect->setProperty("VertFormatting", "TopAligned");
    CEGUI::System::getSingleton().getGUISheet()->getChild("OptionState")->addChildWindow(m_text_effect);

    m_effect_volume = (CEGUI::Slider*)m_window_manager.createWindow("OgreTray/Slider", "SliderVolEffect");
    m_effect_volume->setSize(CEGUI::UVector2(CEGUI::UDim(0.50, 0), CEGUI::UDim(0.05, 0)));
    m_effect_volume->setPosition(CEGUI::UVector2(CEGUI::UDim(0.05, 0),
                                         CEGUI::UDim(0.47, 0)));
    m_effect_volume->setMaxValue(100);
    //m_effect_volume->setCurrentValue();
    m_effect_volume->setEnabled(m_activate->isSelected());
    m_effect_volume->subscribeEvent(CEGUI::Slider::EventValueChanged, CEGUI::Event::Subscriber(&SoundSetting::m_modif_slide, this));
    CEGUI::System::getSingleton().getGUISheet()->getChild("OptionState")->addChildWindow(m_effect_volume);

    m_text_interface = (CEGUI::Titlebar*)m_window_manager.createWindow("OgreTray/StaticText", "TextVolInterface");
    m_text_interface->setSize(CEGUI::UVector2(CEGUI::UDim(0.50, 0), CEGUI::UDim(0.05, 0)));
    m_text_interface->setPosition(CEGUI::UVector2(CEGUI::UDim(0.05, 0),
                                         CEGUI::UDim(0.54, 0)));
    m_text_interface->setText("Volume sons interface:");
    m_text_interface->setProperty("FrameEnabled", "false");
    m_text_interface->setProperty("BackgroundEnabled", "false");
    m_text_interface->setProperty("VertFormatting", "TopAligned");
    CEGUI::System::getSingleton().getGUISheet()->getChild("OptionState")->addChildWindow(m_text_interface);

    m_interface_volume = (CEGUI::Slider*)m_window_manager.createWindow("OgreTray/Slider", "SliderVolInterface");
    m_interface_volume->setSize(CEGUI::UVector2(CEGUI::UDim(0.50, 0), CEGUI::UDim(0.05, 0)));
    m_interface_volume->setPosition(CEGUI::UVector2(CEGUI::UDim(0.05, 0),
                                         CEGUI::UDim(0.61, 0)));
    m_interface_volume->setMaxValue(100);
    //m_interface_volume->setCurrentValue();
    m_interface_volume->setEnabled(m_activate->isSelected());
    m_interface_volume->subscribeEvent(CEGUI::Slider::EventValueChanged, CEGUI::Event::Subscriber(&SoundSetting::m_modif_slide, this));
    CEGUI::System::getSingleton().getGUISheet()->getChild("OptionState")->addChildWindow(m_interface_volume);

    m_cancel = (CEGUI::PushButton*)m_window_manager.createWindow("OgreTray/Button", "ButtonCancel");
    m_cancel->setSize(CEGUI::UVector2(CEGUI::UDim(0.20, 0), CEGUI::UDim(0.15, 0)));
    m_cancel->setPosition(CEGUI::UVector2(CEGUI::UDim(0.95-m_cancel->getSize().d_x.d_scale, 0),
                                         CEGUI::UDim(0.95-m_cancel->getSize().d_y.d_scale
                                                        , 0)));
    m_cancel->setText("Cancel");
    m_cancel->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&SoundSetting::m_button_pushed, this));
    CEGUI::System::getSingleton().getGUISheet()->getChild("OptionState")->addChildWindow(m_cancel);

    m_accept = (CEGUI::PushButton*)m_window_manager.createWindow("OgreTray/Button", "ButtonOk");
    m_accept->setSize(CEGUI::UVector2(CEGUI::UDim(0.20, 0), CEGUI::UDim(0.15, 0)));
    m_accept->setPosition(CEGUI::UVector2(CEGUI::UDim(0.85-(m_accept->getSize().d_x.d_scale+m_cancel->getSize().d_x.d_scale), 0),
                                         CEGUI::UDim(0.95-m_accept->getSize().d_y.d_scale
                                                        , 0)));
    m_accept->setText("Ok");
    m_accept->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&SoundSetting::m_button_pushed, this));
    CEGUI::System::getSingleton().getGUISheet()->getChild("OptionState")->addChildWindow(m_accept);

    m_activate->hide();
    m_music_volume->hide();
    m_ambiant_volume->hide();
    m_effect_volume->hide();
    m_interface_volume->hide();
    m_cancel->hide();
    m_accept->hide();
    m_text_music->hide();
    m_text_ambiant->hide();
    m_text_effect->hide();
    m_text_interface->hide();

    m_visible = false;
}
SoundSetting::~SoundSetting()
{
    CEGUI::System::getSingleton().getGUISheet()->removeChildWindow(m_activate);
    CEGUI::WindowManager::getSingleton().destroyWindow(m_activate);
    CEGUI::System::getSingleton().getGUISheet()->removeChildWindow(m_music_volume);
    CEGUI::WindowManager::getSingleton().destroyWindow(m_music_volume);
    CEGUI::System::getSingleton().getGUISheet()->removeChildWindow(m_ambiant_volume);
    CEGUI::WindowManager::getSingleton().destroyWindow(m_ambiant_volume);
    CEGUI::System::getSingleton().getGUISheet()->removeChildWindow(m_effect_volume);
    CEGUI::WindowManager::getSingleton().destroyWindow(m_effect_volume);
    CEGUI::System::getSingleton().getGUISheet()->removeChildWindow(m_interface_volume);
    CEGUI::WindowManager::getSingleton().destroyWindow(m_interface_volume);

    CEGUI::System::getSingleton().getGUISheet()->removeChildWindow(m_text_music);
    CEGUI::WindowManager::getSingleton().destroyWindow(m_text_music);
    CEGUI::System::getSingleton().getGUISheet()->removeChildWindow(m_text_ambiant);
    CEGUI::WindowManager::getSingleton().destroyWindow(m_text_ambiant);
    CEGUI::System::getSingleton().getGUISheet()->removeChildWindow(m_text_effect);
    CEGUI::WindowManager::getSingleton().destroyWindow(m_text_effect);
    CEGUI::System::getSingleton().getGUISheet()->removeChildWindow(m_text_interface);
    CEGUI::WindowManager::getSingleton().destroyWindow(m_text_interface);
}

bool SoundSetting::isVisible()
{
    return m_visible;
}

void SoundSetting::enter()
{
    m_visible = true;
    m_activate->show();
    m_music_volume->show();
    m_ambiant_volume->show();
    m_effect_volume->show();
    m_interface_volume->show();
    m_cancel->show();
    m_accept->show();
    m_text_music->show();
    m_text_ambiant->show();
    m_text_effect->show();
    m_text_interface->show();
    CEGUI::System::getSingleton().getGUISheet()->getChild("OptionState")->setSize(CEGUI::UVector2(CEGUI::UDim(0.5,0), CEGUI::UDim(0.5, 0)));
    CEGUI::System::getSingleton().getGUISheet()->getChild("OptionState")->setPosition(CEGUI::UVector2(CEGUI::UDim(0.50-(CEGUI::System::getSingleton().getGUISheet()->getChild("OptionState")->getSize().d_x.d_scale/2), 0),
                                         CEGUI::UDim(0.50-(CEGUI::System::getSingleton().getGUISheet()->getChild("OptionState")->getSize().d_y.d_scale
                                                        /2), 0)));
}

void SoundSetting::exit()
{
    m_visible = false;
    m_activate->hide();
    m_music_volume->hide();
    m_ambiant_volume->hide();
    m_effect_volume->hide();
    m_interface_volume->hide();
    m_cancel->hide();
    m_accept->hide();
    m_text_music->hide();
    m_text_ambiant->hide();
    m_text_effect->hide();
    m_text_interface->hide();
    CEGUI::System::getSingleton().getGUISheet()->getChild("OptionState")->setSize(CEGUI::UVector2(CEGUI::UDim(0.3,0), CEGUI::UDim(0.3, 0)));
    CEGUI::System::getSingleton().getGUISheet()->getChild("OptionState")->setPosition(CEGUI::UVector2(CEGUI::UDim(0.50-(CEGUI::System::getSingleton().getGUISheet()->getChild("OptionState")->getSize().d_x.d_scale/2), 0),
                                         CEGUI::UDim(0.50-(CEGUI::System::getSingleton().getGUISheet()->getChild("OptionState")->getSize().d_y.d_scale
                                                        /2), 0)));
}

ret_code SoundSetting::work(unsigned int)
{
    return CONTINUE;
}

bool SoundSetting::m_button_pushed(const CEGUI::EventArgs&)
{
    if (m_cancel->isPushed())
        m_visible = false;
    else
    {
        Config::get()->getSoundConfig()->saveConfig();
        m_visible = false;
    }

    return true;
}

bool SoundSetting::m_checkbox_used(const CEGUI::EventArgs&)
{
    m_state_manager->setAudio(m_activate->isSelected());
    Playlist::get()->set_Pause(!m_activate->isSelected());
    m_music_volume->setEnabled(m_activate->isSelected());
    m_ambiant_volume->setEnabled(m_activate->isSelected());
    m_effect_volume->setEnabled(m_activate->isSelected());
    m_interface_volume->setEnabled(m_activate->isSelected());
    Config::get()->getSoundConfig()->setActivate(m_activate->isSelected());

    return true;
}

bool SoundSetting::m_modif_slide(const CEGUI::EventArgs&)
{
    if (m_music_volume->getCurrentValue() != Playlist::get()->get_Volume())
    {
        Playlist::get()->set_Volume(m_music_volume->getCurrentValue());
        Config::get()->getSoundConfig()->setMusicVolume(m_music_volume->getCurrentValue());
        Config::get()->getSoundConfig()->setAmbiantVolume(m_ambiant_volume->getCurrentValue());
        Config::get()->getSoundConfig()->setEffectVolume(m_effect_volume->getCurrentValue());
        Config::get()->getSoundConfig()->setInterfaceVolume(m_interface_volume->getCurrentValue());
    }

    return true;
}
