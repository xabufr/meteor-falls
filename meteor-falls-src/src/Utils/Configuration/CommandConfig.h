#ifndef COMMANDCONFIG_H_INCLUDED
#define COMMANDCONFIG_H_INCLUDED

#include <OIS/OIS.h>
#include <vector>

class CommandConfig
{
public:
    enum KeyRPG{
        RPG_INTERACTION=0,
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
        GLOBAL_QUIT,
        GLOBAL_COUNT
    };
    struct KeyAction{
        std::string description;
        struct Key{
            enum Type{
                KEYBOARD,
                MOUSE
            }type;
            OIS::KeyCode keyboard;
            OIS::MouseButtonID mouse;
        }action[2];
        const KeyAction& operator=(const KeyAction& o)
        {
            description = o.description;
            action[0] = o.action[0];
            action[1] = o.action[1];

            return *this;
        }
    };
    CommandConfig();
    ~CommandConfig();
    void defaultCommandConfig();
    void loadConfig();
    void saveConfig();
    std::string toString(OIS::MouseButtonID) const;
    KeyAction** getKeyMap(){return m_map_key;}
    KeyAction* getKeyGlobal(){return m_map_key[0];}
    KeyAction* getKeyRTS(){return m_map_key[1];}
    KeyAction* getKeyRPG(){return m_map_key[2];}
private:
    KeyAction* m_map_key[3];

};
#endif // COMMANDCONFIG_H_INCLUDED
