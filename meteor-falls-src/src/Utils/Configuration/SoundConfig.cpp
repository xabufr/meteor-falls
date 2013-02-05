#include "SoundConfig.h"
#include "../../Engine/ScriptEngine/XmlDocumentManager.h"
#include "../../precompiled/lexical_cast.h"
#include "Utils/Exception/FileNotFound.h"
#include <rapidxml_print.hpp>
#include <iostream>
#include <CEGUI.h>

SoundConfig::SoundConfig()
{
    loadConfig();
}

void SoundConfig::defaultSoundConfig()
{
    m_activate = true;
    m_music_volume = 100;
    m_ambiant_volume = 100;
    m_effect_volume = 100;
    m_interface_volume = 100;
}

void SoundConfig::loadConfig()
{
    try
    {
        rapidxml::xml_document<>* doc = XmlDocumentManager::get()->getDocument("config.cfg");
        rapidxml::xml_node<>* root = doc->first_node("configuration");
        rapidxml::xml_node<>* sound = root->first_node("sound");

        m_activate = boost::lexical_cast<bool>(sound->first_attribute("activate")->value());
        m_music_volume = boost::lexical_cast<float>(sound->first_node("music")->first_attribute("volume")->value());
        m_ambiant_volume = boost::lexical_cast<float>(sound->first_node("ambiant")->first_attribute("volume")->value());
        m_effect_volume = boost::lexical_cast<float>(sound->first_node("effect")->first_attribute("volume")->value());
        m_interface_volume = boost::lexical_cast<float>(sound->first_node("interface")->first_attribute("volume")->value());
    }
    catch(FileNotFound &e)
    {
        m_activate = true;
        m_music_volume = 100;
        m_ambiant_volume = 100;
        m_effect_volume = 100;
        m_interface_volume = 100;
    }
}

void SoundConfig::saveConfig()
{
    rapidxml::xml_document<>* document = XmlDocumentManager::get()->writeDocument("config.cfg");
    rapidxml::xml_node<>* root;
    rapidxml::xml_node<>* sound;
    rapidxml::xml_node<>* music;
    rapidxml::xml_node<>* ambiant;
    rapidxml::xml_node<>* effect;
    rapidxml::xml_node<>* interface;

    CEGUI::Checkbox *activate = (CEGUI::Checkbox*)CEGUI::System::getSingleton().getGUISheet()->getChild("OptionState")->getChild("CheckBoxActivate");
    CEGUI::Slider *music_volume = (CEGUI::Slider*)CEGUI::System::getSingleton().getGUISheet()->getChild("OptionState")->getChild("SliderVolMusic");
    CEGUI::Slider *ambiant_volume = (CEGUI::Slider*)CEGUI::System::getSingleton().getGUISheet()->getChild("OptionState")->getChild("SliderVolAmbiant");
    CEGUI::Slider *effect_volume = (CEGUI::Slider*)CEGUI::System::getSingleton().getGUISheet()->getChild("OptionState")->getChild("SliderVolEffect");
    CEGUI::Slider *interface_volume = (CEGUI::Slider*)CEGUI::System::getSingleton().getGUISheet()->getChild("OptionState")->getChild("SliderVolInterface");

    if (!document->first_node("configuration"))
    {
        root = document->allocate_node(rapidxml::node_type::node_element, "configuration");
        document->append_node(root);
    }
    else
        root = document->first_node("configuration");

    if (!root->first_node("sound"))
    {
        sound = document->allocate_node(rapidxml::node_type::node_element, "sound");
        sound->append_attribute(document->allocate_attribute("activate", document->allocate_string(boost::lexical_cast<std::string>(!activate->isSelected()).c_str())));
        root->append_node(sound);
    }
    else
    {
        sound = document->first_node("sound");
        sound->first_attribute("activate")->value(document->allocate_string(boost::lexical_cast<std::string>(!activate->isSelected()).c_str()));
    }

    if (!sound->first_node("music"))
    {
        music = document->allocate_node(rapidxml::node_type::node_element, "music");
        music->append_attribute(document->allocate_attribute("volume", document->allocate_string(boost::lexical_cast<std::string>(music_volume->getCurrentValue()).c_str())));
        sound->append_node(music);
    }
    else
    {
        music = sound->first_node("music");
        music->first_attribute("volume")->value(document->allocate_string(boost::lexical_cast<std::string>(music_volume->getCurrentValue()).c_str()));
    }

    if (!sound->first_node("ambiant"))
    {
        ambiant = document->allocate_node(rapidxml::node_type::node_element, "ambiant");
        ambiant->append_attribute(document->allocate_attribute("volume", document->allocate_string(boost::lexical_cast<std::string>(ambiant_volume->getCurrentValue()).c_str())));
        sound->append_node(ambiant);
    }
    else
    {
        ambiant = sound->first_node("ambiant");
        ambiant->first_attribute("volume")->value(document->allocate_string(boost::lexical_cast<std::string>(ambiant_volume->getCurrentValue()).c_str()));
    }

    if (!sound->first_node("effect"))
    {
        effect = document->allocate_node(rapidxml::node_type::node_element, "effect");
        effect->append_attribute(document->allocate_attribute("volume", document->allocate_string(boost::lexical_cast<std::string>(effect_volume->getCurrentValue()).c_str())));
        sound->append_node(effect);
    }
    else
    {
        effect = sound->first_node("effect");
        effect->first_attribute("volume")->value(document->allocate_string(boost::lexical_cast<std::string>(effect_volume->getCurrentValue()).c_str()));
    }

    if (!sound->first_node("interface"))
    {
        interface = document->allocate_node(rapidxml::node_type::node_element, "interface");
        interface->append_attribute(document->allocate_attribute("volume", document->allocate_string(boost::lexical_cast<std::string>(interface_volume->getCurrentValue()).c_str())));
        sound->append_node(interface);
    }
    else
    {
        interface = sound->first_node("interface");
        interface->first_attribute("volume")->value(document->allocate_string(boost::lexical_cast<std::string>(interface_volume->getCurrentValue()).c_str()));
    }

    std::ofstream file;
    file.open("config.cfg");
    if (file.bad())
        throw FileNotFound("config.cfg");
    file << *document;
    file.close();
    loadConfig();
}
