#include "CommandConfig.h"
#include "../../precompiled/lexical_cast.h"
#include "../../Engine/GraphicEngine/Ogre/OgreWindowInputManager.h"
#include "../../Engine/GraphicEngine/Ogre/ogrecontextmanager.h"
#include "../../Engine/GraphicEngine/Ogre/OgreApplication.h"
#include <boost/property_tree/xml_parser.hpp>
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
    //paramètre de la souri
    m_mouse_sensibility = 0.01;
    m_axes_invers = true;

    m_map_key[0] = new KeyAction[KeyGlobal::GLOBAL_COUNT];
    m_map_key[1] = new KeyAction[KeyRPG::RPG_COUNT];
    m_map_key[2] =  new KeyAction[KeyRTS::RTS_COUNT];

    KeyAction current;

    //Global
    current.description = "Chat";
    current.action[0].type = KeyAction::Key::Type::KEYBOARD;
    current.action[0].keyboard = OIS::KeyCode::KC_T;
    current.action[1].type = KeyAction::Key::Type::KEYBOARD;
    m_map_key[0][0] = current;

    current.description = "Carte";
    current.action[0].type = KeyAction::Key::Type::KEYBOARD;
    current.action[0].keyboard = OIS::KeyCode::KC_M;
    current.action[1].type = KeyAction::Key::Type::KEYBOARD;
    m_map_key[0][1] = current;

    //RPG
    current.description = "Avance";
    current.action[0].type = KeyAction::Key::Type::KEYBOARD;
    current.action[0].keyboard = OIS::KeyCode::KC_Z;
    current.action[1].type = KeyAction::Key::Type::KEYBOARD;
    current.action[1].keyboard = OIS::KeyCode::KC_UP;
    m_map_key[1][0] = current;

    current.description = "Reculer";
    current.action[0].type = KeyAction::Key::Type::KEYBOARD;
    current.action[0].keyboard = OIS::KeyCode::KC_S;
    current.action[1].type = KeyAction::Key::Type::KEYBOARD;
    current.action[1].keyboard = OIS::KeyCode::KC_DOWN;
    m_map_key[1][1] = current;

    current.description = "Aller à droite";
    current.action[0].type = KeyAction::Key::Type::KEYBOARD;
    current.action[0].keyboard = OIS::KeyCode::KC_D;
    current.action[1].type = KeyAction::Key::Type::KEYBOARD;
    current.action[1].keyboard = OIS::KeyCode::KC_RIGHT;
    m_map_key[1][2] = current;

    current.description = "Aller à gauche";
    current.action[0].type = KeyAction::Key::Type::KEYBOARD;
    current.action[0].keyboard = OIS::KeyCode::KC_Q;
    current.action[1].type = KeyAction::Key::Type::KEYBOARD;
    current.action[1].keyboard = OIS::KeyCode::KC_LEFT;
    m_map_key[1][3] = current;

    current.description = "Interaction";
    current.action[0].type = KeyAction::Key::Type::KEYBOARD;
    current.action[0].keyboard = OIS::KeyCode::KC_E;
    current.action[1].type = KeyAction::Key::Type::KEYBOARD;
    m_map_key[1][4] = current;

    current.description = "Main gauche";
    current.action[0].type = KeyAction::Key::Type::MOUSE;
    current.action[0].mouse = OIS::MouseButtonID::MB_Left;
    current.action[1].type = KeyAction::Key::Type::KEYBOARD;
    m_map_key[1][5] = current;

    current.description = "Main droite";
    current.action[0].type = KeyAction::Key::Type::MOUSE;
    current.action[0].mouse = OIS::MouseButtonID::MB_Right;
    current.action[1].type = KeyAction::Key::Type::KEYBOARD;
    m_map_key[1][6] = current;

    current.description = "Accroupi";
    current.action[0].type = KeyAction::Key::Type::KEYBOARD;
    current.action[0].keyboard = OIS::KeyCode::KC_C;
    current.action[1].type = KeyAction::Key::Type::KEYBOARD;
    m_map_key[1][7] = current;

    current.description = "Courir";
    current.action[0].type = KeyAction::Key::Type::KEYBOARD;
    current.action[0].keyboard = OIS::KeyCode::KC_LSHIFT;
    current.action[1].type = KeyAction::Key::Type::KEYBOARD;
    m_map_key[1][8] = current;

    current.description = "Marcher";
    current.action[0].type = KeyAction::Key::Type::KEYBOARD;
    current.action[0].keyboard = OIS::KeyCode::KC_W;
    current.action[1].type = KeyAction::Key::Type::KEYBOARD;
    m_map_key[1][9] = current;

    current.description = "Sauter";
    current.action[0].type = KeyAction::Key::Type::KEYBOARD;
    current.action[0].keyboard = OIS::KeyCode::KC_SPACE;
    current.action[1].type = KeyAction::Key::Type::KEYBOARD;
    m_map_key[1][10] = current;

    current.description = "Position";
    current.action[0].type = KeyAction::Key::Type::MOUSE;
    current.action[0].mouse = OIS::MouseButtonID::MB_Middle;
    current.action[1].type = KeyAction::Key::Type::KEYBOARD;
    m_map_key[1][11] = current;

    current.description = "Inventaire";
    current.action[0].type = KeyAction::Key::Type::KEYBOARD;
    current.action[0].keyboard = OIS::KeyCode::KC_I;
    current.action[1].type = KeyAction::Key::Type::KEYBOARD;
    m_map_key[1][12] = current;

    current.description = "Statistique";
    current.action[0].type = KeyAction::Key::Type::KEYBOARD;
    current.action[0].keyboard = OIS::KeyCode::KC_P;
    current.action[1].type = KeyAction::Key::Type::KEYBOARD;
    m_map_key[1][13] = current;

    current.description = "Action 0";
    current.action[0].type = KeyAction::Key::Type::KEYBOARD;
    current.action[0].keyboard = OIS::KeyCode::KC_0;
    current.action[1].type = KeyAction::Key::Type::KEYBOARD;
    m_map_key[1][14] = current;

    current.description = "Action 1";
    current.action[0].type = KeyAction::Key::Type::KEYBOARD;
    current.action[0].keyboard = OIS::KeyCode::KC_1;
    current.action[1].type = KeyAction::Key::Type::KEYBOARD;
    m_map_key[1][15] = current;

    current.description = "Action 2";
    current.action[0].type = KeyAction::Key::Type::KEYBOARD;
    current.action[0].keyboard = OIS::KeyCode::KC_2;
    current.action[1].type = KeyAction::Key::Type::KEYBOARD;
    m_map_key[1][16] = current;

    current.description = "Action 3";
    current.action[0].type = KeyAction::Key::Type::KEYBOARD;
    current.action[0].keyboard = OIS::KeyCode::KC_3;
    current.action[1].type = KeyAction::Key::Type::KEYBOARD;
    m_map_key[1][17] = current;

    current.description = "Action 4";
    current.action[0].type = KeyAction::Key::Type::KEYBOARD;
    current.action[0].keyboard = OIS::KeyCode::KC_4;
    current.action[1].type = KeyAction::Key::Type::KEYBOARD;
    m_map_key[1][18] = current;

    current.description = "Action 5";
    current.action[0].type = KeyAction::Key::Type::KEYBOARD;
    current.action[0].keyboard = OIS::KeyCode::KC_5;
    current.action[1].type = KeyAction::Key::Type::KEYBOARD;
    m_map_key[1][19] = current;

    current.description = "Action 6";
    current.action[0].type = KeyAction::Key::Type::KEYBOARD;
    current.action[0].keyboard = OIS::KeyCode::KC_6;
    current.action[1].type = KeyAction::Key::Type::KEYBOARD;
    m_map_key[1][20] = current;

    current.description = "Action 7";
    current.action[0].type = KeyAction::Key::Type::KEYBOARD;
    current.action[0].keyboard = OIS::KeyCode::KC_7;
    current.action[1].type = KeyAction::Key::Type::KEYBOARD;
    m_map_key[1][21] = current;

    current.description = "Action 8";
    current.action[0].type = KeyAction::Key::Type::KEYBOARD;
    current.action[0].keyboard = OIS::KeyCode::KC_8;
    current.action[1].type = KeyAction::Key::Type::KEYBOARD;
    m_map_key[1][22] = current;

    current.description = "Action 9";
    current.action[0].type = KeyAction::Key::Type::KEYBOARD;
    current.action[0].keyboard = OIS::KeyCode::KC_9;
    current.action[1].type = KeyAction::Key::Type::KEYBOARD;
    m_map_key[1][23] = current;
}
void CommandConfig::loadConfig()
{
    try
    {
		XmlDocumentManager::Document& doc = XmlDocumentManager::get()->getDocument("config.cfg");
		XmlDocumentManager::Document& command = doc.get_child("configuration.command");
        m_map_key[0] = new KeyAction[KeyGlobal::GLOBAL_COUNT];
        m_map_key[1] = new KeyAction[KeyRPG::RPG_COUNT];
        m_map_key[2] =  new KeyAction[KeyRTS::RTS_COUNT];

        int nb=0;

		std::pair<XmlDocumentManager::Document::const_assoc_iterator, XmlDocumentManager::Document::const_assoc_iterator> bounds=command.get_child("global").equal_range("action");
		for(boost::property_tree::ptree::const_assoc_iterator it(bounds.first); it != bounds.second; ++it)
        {
            nb = it->second.get<int>("xmlattr.id");
            addKey(GLOBAL_KEY, nb, it->second);
        }

		bounds = command.get_child("rpg").equal_range("action");
		for(boost::property_tree::ptree::const_assoc_iterator it(bounds.first); it != bounds.second; ++it)
        {
            nb = it->second.get<int>("xmlattr.id");
            addKey(RPG_KEY, nb, it->second);
        }

		bounds = command.get_child("rts").equal_range("action");
		for(boost::property_tree::ptree::const_assoc_iterator it(bounds.first); it != bounds.second; ++it)
        {
            nb = it->second.get<int>("xmlattr.id");
            addKey(RTS_KEY, nb, it->second);
        }
		m_axes_invers = command.get<bool>("mouse.xmlattr.inverse");
		m_mouse_sensibility = command.get<float>("mouse.xmlattr.sensibility");
    }
    catch(...)
    {
        defaultCommandConfig();
    }
}
void CommandConfig::saveConfig()
{
	XmlDocumentManager::Document& document = XmlDocumentManager::get()->getDocument("config.cfg");
    int maxi = 0;

	XmlDocumentManager::Document& command = document.put_child("configuration.command", XmlDocumentManager::Document());
	XmlDocumentManager::Document& global = command.put_child("global", XmlDocumentManager::Document());
	XmlDocumentManager::Document& rpg = command.put_child("rpg", XmlDocumentManager::Document());
	XmlDocumentManager::Document& rts = command.put_child("rts", XmlDocumentManager::Document());
	XmlDocumentManager::Document* current;

    for (int i=0; i<3; ++i)
    {
        KeyAction* keys = m_map_key[i];
        KeyAction* current_key;
        if (i==0)
        {
            maxi = CommandConfig::KeyGlobal::GLOBAL_COUNT;
            current = &global;
        }
        else if (i==1)
        {
            maxi = CommandConfig::KeyRPG::RPG_COUNT;
            current = &rpg;
        }
        else
        {
            maxi = CommandConfig::KeyRTS::RTS_COUNT;
            current = &rpg;
        }
        for (int j=1; j<maxi; ++j)
		{
			current_key = &keys[j-1];
			XmlDocumentManager::Document& action = current->add_child("action", XmlDocumentManager::Document());
			action.put("xmlattr.description", current_key->description);
			action.put("xmlattr.id", j-1); 
			for (int k=0; k<2; ++k)
			{
				std::string num = boost::lexical_cast<std::string>(k+1);
				action.put("type"+num, (int)current_key->action[k].type);
				switch (current_key->action[i].type)
				{
					case KeyAction::Key::Type::KEYBOARD:
						action.put("code"+num, (int)current_key->action[k].keyboard);
						break;
					case KeyAction::Key::Type::MOUSE:
						action.put("code"+num, (int)current_key->action[k].mouse);
						break;
				}
			}
		}
    }
	command.put("mouse.xmlattr.inverse", m_axes_invers);
	command.put("mouse.xmlattr.sensibility", m_mouse_sensibility);

	boost::property_tree::write_xml("config.cfg", document);
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
    }
    return "Unknown";
}
bool CommandConfig::eventExist(OIS::MouseButtonID c, OIS::MouseButtonID old, int rang)
{
    bool res=false;

    if (c == old)
        return false;

    KeyAction *keys = getKeyGlobal();
    for (int i=0; i<KeyGlobal::GLOBAL_COUNT; ++i)
        if (keys[i].action[0].mouse == c || keys[i].action[1].mouse == c)
            res=true;
    switch (rang)
    {
    case 1:
        {
            keys = getKeyRPG();
            for (int i=0; i<KeyRPG::RPG_COUNT; ++i)
                if (keys[i].action[0].mouse == c || keys[i].action[1].mouse == c)
                    res=true;
        }
        break;
    case 2:
        {
            keys = getKeyRTS();
            for (int i=0; i<KeyRTS::RTS_COUNT; ++i)
                if (keys[i].action[0].mouse == c || keys[i].action[1].mouse == c)
                    res=true;
        }
        break;
    }

    return res;
}
bool CommandConfig::eventExist(OIS::KeyCode c, OIS::KeyCode old, int rang)
{
    bool res=false;

    if (c == old)
        return false;

    KeyAction *keys = getKeyGlobal();
    for (int i=0; i<KeyGlobal::GLOBAL_COUNT; ++i)
        if (keys[i].action[0].keyboard == c || keys[i].action[1].keyboard == c)
            res=true;
    switch (rang)
    {
    case 1:
        {
            keys = getKeyRPG();
            for (int i=0; i<KeyRPG::RPG_COUNT; ++i)
                if (keys[i].action[0].keyboard == c || keys[i].action[1].keyboard == c)
                    res=true;
        }
        break;
    case 2:
        {
            keys = getKeyRTS();
            for (int i=0; i<KeyRTS::RTS_COUNT; ++i)
                if (keys[i].action[0].keyboard == c || keys[i].action[1].keyboard == c)
                    res=true;
        }
        break;
    }

    return res;
}
bool CommandConfig::eventActif(int rang, int pos)
{
    OIS::Keyboard *keyboard = OgreContextManager::get()->getInputManager()->getKeyboard();

    if (keyboard->isKeyDown(m_map_key[rang][pos].action[0].keyboard) || keyboard->isKeyDown(m_map_key[rang][pos].action[1].keyboard))
        return true;

    return false;
}
void CommandConfig::addKey(int rang, int pos, const XmlDocumentManager::Document& current)
{
    KeyAction current_key;

    current_key.description = current.get<std::string>("xmlattr.description");
    for (int i=0; i<2; ++i)
    {
        current_key.action[i].type = KeyAction::Key::Type(current.get<int>("xmlattr.type"+boost::lexical_cast<std::string>(i+1)));
        switch (current_key.action[i].type)
        {
            case KeyAction::Key::Type::KEYBOARD:
                current_key.action[i].keyboard = OIS::KeyCode(current.get<int>("xmlattr.code"+boost::lexical_cast<std::string>(i+1)));
                break;
            case KeyAction::Key::Type::MOUSE:
                current_key.action[i].mouse = OIS::MouseButtonID(current.get<int>("xmlattr.code"+boost::lexical_cast<std::string>(i+1)));
                break;
        }
    }
    m_map_key[rang][pos] = current_key;
}
