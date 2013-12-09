#ifndef COMMANDCONFIG_H_INCLUDED
#define COMMANDCONFIG_H_INCLUDED

#include "../../Engine/ScriptEngine/XmlDocumentManager.h"
#include <OIS/OIS.h>
#include <vector>

class CommandConfig
{
public:
    enum KeyRPG{
        RPG_FORWARD=0,
        RPG_BACKWARD,
        RPG_LEFT,
        RPG_RIGHT,
        RPG_INTERACTION,
        RPG_HAND_R,
        RPG_HAND_L,
        RPG_SQUAT,
        RPG_RUN,
        RPG_WALK,
        RPG_JUMP,
        RPG_COMMUNICATE_POSITION,
        RPG_MENU_INVENTORY,
        RPG_MENU_STATE,
        RPG_ACTION_0,
        RPG_ACTION_1,
        RPG_ACTION_2,
        RPG_ACTION_3,
        RPG_ACTION_4,
        RPG_ACTION_5,
        RPG_ACTION_6,
        RPG_ACTION_7,
        RPG_ACTION_8,
        RPG_ACTION_9,
        RPG_COUNT
    };
    enum KeyRTS{
        RTS_COUNT=0
    };
    enum KeyGlobal{
        GLOBAL_CHAT=0,
        GLOBAL_MAP,
        GLOBAL_COUNT
    };
    struct KeyAction{
        std::string description;
        struct Key{
            enum Type{
                KEYBOARD=0,
                MOUSE
            }type;
            OIS::KeyCode keyboard;
            OIS::MouseButtonID mouse;
        }action[2];
        const KeyAction& operator=(const KeyAction& o)
        {
            description = o.description;
            action[0].type = o.action[0].type;
            action[1].type = o.action[1].type;
            action[0] = o.action[0];
            action[1] = o.action[1];

            return *this;
        }
    };
	enum KeyType{
		GLOBAL_KEY = 0,
		RPG_KEY = 1,
		RTS_KEY = 2,
	};
    CommandConfig();
    ~CommandConfig();
    void defaultCommandConfig();
    void loadConfig();
    void saveConfig();
    void setMouseSensibility(float value){m_mouse_sensibility = value;}
    void setAxesInvers(bool value){m_axes_invers = value;}
    static std::string toString(OIS::MouseButtonID);
    bool eventExist(OIS::MouseButtonID, OIS::MouseButtonID, int);
    bool eventExist(OIS::KeyCode, OIS::KeyCode, int);
    bool eventActif(int, int);
    const bool axesInvers(){return m_axes_invers;}
    void addKey(int, int, const XmlDocumentManager::Document&);
    KeyAction** getKeyMap(){return m_map_key;}
    KeyAction* getKeyGlobal(){return m_map_key[0];}
    KeyAction* getKeyRTS(){return m_map_key[2];}
    KeyAction* getKeyRPG(){return m_map_key[1];}
    const float getMouseSensibility(){return m_mouse_sensibility;}
private:
    KeyAction* m_map_key[3];
    float m_mouse_sensibility;
    bool m_axes_invers;

};
#endif // COMMANDCONFIG_H_INCLUDED
