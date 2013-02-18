#include "CommandConfig.h"
#include "../../precompiled/lexical_cast.h"
#include "Utils/Exception/FileNotFound.h"
#include <rapidxml_print.hpp>
#include <fstream>

CommandConfig::CommandConfig()
{
    loadConfig();
}

CommandConfig::~CommandConfig()
{

}

void CommandConfig::defaultCommandConfig()
{
    m_map_key[0] = new KeyAction[KeyGlobal::GLOBAL_COUNT];
    m_map_key[1] = new KeyAction[KeyRPG::RPG_COUNT];
    m_map_key[2] =  new KeyAction[KeyRTS::RTS_COUNT];

    KeyAction current;

    //Global
    current.description = "Chat";
    current.action[0].type = 0;
    current.action[0].keyboard = 20;
    current.action[0].mouse = 0;
    current.action[1].type = 0;
    current.action[1].keyboard = 999;
    current.action[1].mouse = 0;
    m_map_key[0][0] = current;

    current.description = "Carte";
    current.action[0].type = 0;
    current.action[0].keyboard = 50;
    current.action[0].mouse = 0;
    current.action[1].type = 0;
    current.action[1].keyboard = 999;
    current.action[1].mouse = 0;
    m_map_key[0][1] = current;

    //RPG
    current.description = "Avance";
    current.action[0].type = 0;
    current.action[0].keyboard = 44;
    current.action[0].mouse = 0;
    current.action[1].type = 0;
    current.action[1].keyboard = 200;
    current.action[1].mouse = 0;
    m_map_key[1][0] = current;

    current.description = "Reculer";
    current.action[0].type = 0;
    current.action[0].keyboard = 31;
    current.action[0].mouse = 0;
    current.action[1].type = 0;
    current.action[1].keyboard = 999;
    current.action[1].mouse = 0;
    m_map_key[1][1] = current;

    current.description = "Aller à droite";
    current.action[0].type = 0;
    current.action[0].keyboard = 32;
    current.action[0].mouse = 0;
    current.action[1].type = 0;
    current.action[1].keyboard = 205;
    current.action[1].mouse = 0;
    m_map_key[1][2] = current;

    current.description = "Aller à gauche";
    current.action[0].type = 0;
    current.action[0].keyboard = 16;
    current.action[0].mouse = 0;
    current.action[1].type = 0;
    current.action[1].keyboard = 203;
    current.action[1].mouse = 0;
    m_map_key[1][3] = current;

    current.description = "Interface";
    current.action[0].type = 0;
    current.action[0].keyboard = 18;
    current.action[0].mouse = 0;
    current.action[1].type = 0;
    current.action[1].keyboard = 999;
    current.action[1].mouse = 0;
    m_map_key[1][4] = current;

    current.description = "Main gauche";
    current.action[0].type = 1;
    current.action[0].keyboard = 0;
    current.action[0].mouse = 0;
    current.action[1].type = 0;
    current.action[1].keyboard = 999;
    current.action[1].mouse = 0;
    m_map_key[1][5] = current;

    current.description = "Main droite";
    current.action[0].type = 1;
    current.action[0].keyboard = 0;
    current.action[0].mouse = 1;
    current.action[1].type = 0;
    current.action[1].keyboard = 999;
    current.action[1].mouse = 0;
    m_map_key[1][6] = current;

    current.description = "Accroupi";
    current.action[0].type = 0;
    current.action[0].keyboard = 46;
    current.action[0].mouse = 0;
    current.action[1].type = 0;
    current.action[1].keyboard = 999;
    current.action[1].mouse = 0;
    m_map_key[1][7] = current;

    current.description = "Courir";
    current.action[0].type = 0;
    current.action[0].keyboard = 42;
    current.action[0].mouse = 0;
    current.action[1].type = 0;
    current.action[1].keyboard = 999;
    current.action[1].mouse = 0;
    m_map_key[1][8] = current;

    current.description = "Marcher";
    current.action[0].type = 0;
    current.action[0].keyboard = 17;
    current.action[0].mouse = 0;
    current.action[1].type = 0;
    current.action[1].keyboard = 999;
    current.action[1].mouse = 0;
    m_map_key[1][9] = current;

    current.description = "Sauter";
    current.action[0].type = 0;
    current.action[0].keyboard = 57;
    current.action[0].mouse = 0;
    current.action[1].type = 0;
    current.action[1].keyboard = 999;
    current.action[1].mouse = 0;
    m_map_key[1][10] = current;

    current.description = "Position";
    current.action[0].type = 1;
    current.action[0].keyboard = 0;
    current.action[0].mouse = 3;
    current.action[1].type = 0;
    current.action[1].keyboard = 999;
    current.action[1].mouse = 0;
    m_map_key[1][11] = current;

    current.description = "Inventaire";
    current.action[0].type = 0;
    current.action[0].keyboard = 23;
    current.action[0].mouse = 0;
    current.action[1].type = 0;
    current.action[1].keyboard = 999;
    current.action[1].mouse = 0;
    m_map_key[1][12] = current;

    current.description = "Statistique";
    current.action[0].type = 0;
    current.action[0].keyboard = 25;
    current.action[0].mouse = 0;
    current.action[1].type = 0;
    current.action[1].keyboard = 999;
    current.action[1].mouse = 0;
    m_map_key[1][13] = current;

    current.description = "Action 0";
    current.action[0].type = 0;
    current.action[0].keyboard = 11;
    current.action[0].mouse = 0;
    current.action[1].type = 0;
    current.action[1].keyboard = 999;
    current.action[1].mouse = 0;
    m_map_key[1][14] = current;

    current.description = "Action 1";
    current.action[0].type = 0;
    current.action[0].keyboard = 2;
    current.action[0].mouse = 0;
    current.action[1].type = 0;
    current.action[1].keyboard = 999;
    current.action[1].mouse = 0;
    m_map_key[1][15] = current;

    current.description = "Action 2";
    current.action[0].type = 0;
    current.action[0].keyboard = 3;
    current.action[0].mouse = 0;
    current.action[1].type = 0;
    current.action[1].keyboard = 999;
    current.action[1].mouse = 0;
    m_map_key[1][16] = current;

    current.description = "Action 3";
    current.action[0].type = 0;
    current.action[0].keyboard = 4;
    current.action[0].mouse = 0;
    current.action[1].type = 0;
    current.action[1].keyboard = 999;
    current.action[1].mouse = 0;
    m_map_key[1][17] = current;

    current.description = "Action 4";
    current.action[0].type = 0;
    current.action[0].keyboard = 5;
    current.action[0].mouse = 0;
    current.action[1].type = 0;
    current.action[1].keyboard = 999;
    current.action[1].mouse = 0;
    m_map_key[1][18] = current;

    current.description = "Action 5";
    current.action[0].type = 0;
    current.action[0].keyboard = 6;
    current.action[0].mouse = 0;
    current.action[1].type = 0;
    current.action[1].keyboard = 999;
    current.action[1].mouse = 0;
    m_map_key[1][19] = current;

    current.description = "Action 6";
    current.action[0].type = 0;
    current.action[0].keyboard = 7;
    current.action[0].mouse = 0;
    current.action[1].type = 0;
    current.action[1].keyboard = 999;
    current.action[1].mouse = 0;
    m_map_key[1][17] = current;

    current.description = "Action 7";
    current.action[0].type = 0;
    current.action[0].keyboard = 8;
    current.action[0].mouse = 0;
    current.action[1].type = 0;
    current.action[1].keyboard = 999;
    current.action[1].mouse = 0;
    m_map_key[1][18] = current;

    current.description = "Action 8";
    current.action[0].type = 0;
    current.action[0].keyboard = 9;
    current.action[0].mouse = 0;
    current.action[1].type = 0;
    current.action[1].keyboard = 999;
    current.action[1].mouse = 0;
    m_map_key[1][19] = current;
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

        int nb=0;

        for (current = command->first_node("global")->first_node("action");current;current=current->next_sibling("action"))
        {
            nb = boost::lexical_cast<int>(current->first_attribute("id")->value());
            addKey(0, nb, current);
        }

        for (current = command->first_node("rpg")->first_node("action");current;current=current->next_sibling("action"))
        {
            nb = boost::lexical_cast<int>(current->first_attribute("id")->value());
            addKey(1, nb, current);
        }

        for (current = command->first_node("rts")->first_node("action");current;current=current->next_sibling("action"))
        {
            nb = boost::lexical_cast<int>(current->first_attribute("id")->value());
            addKey(2, nb, current);
        }
    }
    catch(FileNotFound &e)
    {
        defaultCommandConfig();
    }
}

void CommandConfig::saveConfig()
{
    rapidxml::xml_document<>* document = XmlDocumentManager::get()->getDocument("config.cfg");
    rapidxml::xml_node<>* root;
    rapidxml::xml_node<>* command;
    rapidxml::xml_node<>* global;
    rapidxml::xml_node<>* rpg;
    rapidxml::xml_node<>* rts;
    rapidxml::xml_node<>* current;
    rapidxml::xml_node<>* action;
    int maxi = 0;

    if (!document->first_node("configuration"))
    {
        root = document->allocate_node(rapidxml::node_type::node_element, "configuration");
        document->append_node(root);
    }
    else
        root = document->first_node("configuration");

    if (!root->first_node("command"))
    {
        command = document->allocate_node(rapidxml::node_type::node_element, "command");
        root->append_node(command);
    }
    else
        command = root->first_node("command");

    if (!command->first_node("global"))
    {
        global = document->allocate_node(rapidxml::node_type::node_element, "global");
        command->append_node(global);
    }
    else
        global = command->first_node("global");

    if (!command->first_node("rpg"))
    {
        rpg = document->allocate_node(rapidxml::node_type::node_element, "rpg");
        command->append_node(rpg);
    }
    else
        rpg = command->first_node("rpg");

    if (!command->first_node("rts"))
    {
        rts = document->allocate_node(rapidxml::node_type::node_element, "rts");
        command->append_node(rts);
    }
    else
        rts = command->first_node("rts");

    for (int i=0; i<3; ++i)
    {
        KeyAction* keys = m_map_key[i];
        KeyAction* current_key;
        if (i==0)
        {
            maxi = CommandConfig::KeyGlobal::GLOBAL_COUNT;
            current = global;
        }
        else if (i==1)
        {
            maxi = CommandConfig::KeyRPG::RPG_COUNT;
            current = rpg;
        }
        else
        {
            maxi = CommandConfig::KeyRTS::RTS_COUNT;
            current = rpg;
        }
        for (int j=1; j<maxi; ++j)
        {
            current_key = &keys[j-1];
            for (action = current->first_node("action");action;action=action->next_sibling("action"))
            {
                if (boost::lexical_cast<std::string>(action->first_attribute("description")->value()) == current_key->description)
                {
                    for (int k=0; k<2; ++k)
                    {
                        action->first_attribute(
                            ("type"+boost::lexical_cast<std::string>(k+1)).c_str())->value(
                                document->allocate_string(boost::lexical_cast<std::string>(current_key->action[k].type).c_str()));
                        switch (current_key->action[i].type)
                        {
                            case KeyAction::Key::Type::KEYBOARD:
                                action->first_attribute(
                                    ("code"+boost::lexical_cast<std::string>(k+1)).c_str())->value(
                                    document->allocate_string(boost::lexical_cast<std::string>(current_key->action[k].keyboard).c_str()));
                            break;
                            case KeyAction::Key::Type::MOUSE:
                                action->first_attribute(
                                    ("code"+boost::lexical_cast<std::string>(k+1)).c_str())->value(
                                    document->allocate_string(boost::lexical_cast<std::string>(current_key->action[k].mouse).c_str()));
                                break;
                        }
                    }
                }
            }
        }
    }

    std::ofstream file;
    file.open("config.cfg");
    if (file.bad())
        throw FileNotFound("config.cfg");
    file << *document;
    file.close();
}

std::string CommandConfig::toString(OIS::MouseButtonID c)
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
        case 999:
            return "";
        break;
    }
    return "Unknown";
}
bool CommandConfig::eventExist(OIS::MouseButtonID c)
{
    KeyAction *keys = getKeyRPG();
    for (int i=0; i<KeyRPG::RPG_COUNT; ++i)
        if (keys[i].action[0].mouse == c || keys[i].action[1].mouse == c)
            return true;

    keys = getKeyRTS();
    for (int i=0; i<KeyRTS::RTS_COUNT; ++i)
        if (keys[i].action[0].mouse == c || keys[i].action[1].mouse == c)
            return true;

    keys = getKeyGlobal();
    for (int i=0; i<KeyGlobal::GLOBAL_COUNT; ++i)
        if (keys[i].action[0].mouse == c || keys[i].action[1].mouse == c)
            return true;

    return false;
}

bool CommandConfig::eventExist(OIS::KeyCode c)
{
    KeyAction* keys = getKeyRPG();
    for (int i=0; i<KeyRPG::RPG_COUNT; ++i)
        if (keys[i].action[0].keyboard == c || keys[i].action[1].keyboard == c)
            return true;

    keys = getKeyRTS();
    for (int i=0; i<KeyRTS::RTS_COUNT; ++i)
        if (keys[i].action[0].keyboard == c || keys[i].action[1].keyboard == c)
            return true;

    keys = getKeyGlobal();
    for (int i=0; i<KeyGlobal::GLOBAL_COUNT; ++i)
        if (keys[i].action[0].keyboard == c || keys[i].action[1].keyboard == c)
            return true;

    return false;
}

void CommandConfig::addKey(int rang, int pos, rapidxml::xml_node<>* current)
{
    KeyAction current_key;

    current_key.description = std::string(current->first_attribute("description")->value());
    for (int i=0; i<2; ++i)
    {
        current_key.action[i].type = KeyAction::Key::Type(boost::lexical_cast<int>(current->first_attribute(("type"+boost::lexical_cast<std::string>(i+1)).c_str())->value()));
        switch (current_key.action[i].type)
        {
            case KeyAction::Key::Type::KEYBOARD:
                current_key.action[i].keyboard = OIS::KeyCode(boost::lexical_cast<int>(current->first_attribute(("code"+boost::lexical_cast<std::string>(i+1)).c_str())->value()));
                break;
            case KeyAction::Key::Type::MOUSE:
                current_key.action[i].mouse = OIS::MouseButtonID(boost::lexical_cast<int>(current->first_attribute(("code"+boost::lexical_cast<std::string>(i+1)).c_str())->value()));
                break;
        }
    }
    m_map_key[rang][pos] = current_key;
}
