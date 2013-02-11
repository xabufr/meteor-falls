#include "CommandConfig.h"
#include "../../Engine/ScriptEngine/XmlDocumentManager.h"
#include "../../precompiled/lexical_cast.h"
#include "Utils/Exception/FileNotFound.h"
#include <rapidxml_print.hpp>


CommandConfig::CommandConfig()
{
    loadConfig();
}

CommandConfig::~CommandConfig()
{

}

void CommandConfig::defaultCommandConfig()
{

}

void CommandConfig::loadConfig()
{
    try
    {
        rapidxml::xml_document<>* doc = XmlDocumentManager::get()->getDocument("config.cfg");
        rapidxml::xml_node<>* root = doc->first_node("configuration");
        rapidxml::xml_node<>* command = root->first_node("command");
        rapidxml::xml_node<>* current;
        m_map_key[0] = new KeyAction[KeyGlobal::GLOBAL_COUNT];
        m_map_key[1] = new KeyAction[KeyRPG::RPG_COUNT];
        m_map_key[2] =  new KeyAction[KeyRTS::RTS_COUNT];

        KeyAction current_key;
        int nb=0;
        for (current = command->first_node("rpg")->first_node("action");current;current=current->next_sibling("action"))
        {
            current_key.description = std::string(current->first_attribute("description")->value());
            for (int i=0; i<2;++i)
            {
                std::string itos = boost::lexical_cast<std::string>(i);
                current_key.action[i].type = KeyAction::Key::Type(boost::lexical_cast<int>(current->first_attribute("type")->value()));
                switch (current_key.action[i].type)
                {
                    case 0:
                        current_key.action[i].keyboard = OIS::KeyCode(boost::lexical_cast<int>(current->first_attribute("code")->value()));
                        break;
                    case 1:
                        current_key.action[i].mouse = OIS::MouseButtonID(boost::lexical_cast<int>(current->first_attribute("code")->value()));
                        break;
                }
            }
            m_map_key[1][nb] = current_key;
            ++nb;
        }
    }
    catch(FileNotFound &e)
    {
        defaultCommandConfig();
    }
}

void CommandConfig::saveConfig()
{

}

std::string CommandConfig::toString(OIS::MouseButtonID c) const
{
    switch (c)
    {
        case OIS::MouseButtonID::MB_Left:
            return "Clic gauche";
        break;
        case OIS::MouseButtonID::MB_Right:
            return "Clic droit";
        break;
        case OIS::MouseButtonID::MB_Middle:
            return "Clic milieu";
        break;
        case OIS::MouseButtonID::MB_Button3:
            return "Bouton 1";
        break;
        case OIS::MouseButtonID::MB_Button4:
            return "Bouton 2";
        break;
        case OIS::MouseButtonID::MB_Button5:
            return "Bouton 3";
        break;
        case OIS::MouseButtonID::MB_Button6:
            return "Bouton 4";
        break;
        case OIS::MouseButtonID::MB_Button7:
            return "Bouton 5";
        break;
    }
}
