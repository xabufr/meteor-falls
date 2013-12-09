#include "SoundConfig.h"
#include "../../Engine/ScriptEngine/XmlDocumentManager.h"
#include <boost/property_tree/xml_parser.hpp>
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
		XmlDocumentManager::Document &doc = XmlDocumentManager::get()->getDocument("config.cfg");
		XmlDocumentManager::Document &sound = doc.get_child("configuration.sound");

        m_activate = sound.get<bool>("xmlattr.activate");
        m_music_volume = sound.get<float>("xmlattr.music");
        m_ambiant_volume = sound.get<float>("xmlattr.ambiant");
        m_effect_volume = sound.get<float>("xmlattr.effect");
        m_interface_volume = sound.get<float>("xmlattr.interface");
    }
    catch(...)
    {
        defaultSoundConfig();
    }
}

void SoundConfig::saveConfig()
{
	XmlDocumentManager::Document& document = XmlDocumentManager::get()->getDocument("config.cfg");

	document.put("configuration.sound.xmlattr.activate", m_activate);
	document.put("configuration.sound.music.xmlattr.volume", m_music_volume);
	document.put("configuration.sound.ambiant.xmlattr.volume", m_ambiant_volume);
	document.put("configuration.sound.effect.xmlattr.volume", m_effect_volume);
	document.put("configuration.sound.interface.xmlattr.volume", m_interface_volume);

	boost::property_tree::write_xml("config.cfg", document);
}
