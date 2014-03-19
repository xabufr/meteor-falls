#ifndef ENGINEMESSAGEKEY_H
#define ENGINEMESSAGEKEY_H

namespace mf
{
enum class EngineMessageKey
{
    FILE_NAME       = 0,
    SERVER_NAME     = 1,
    MAX_PLAYERS     = 2,
    PLAYER_NUMBER   = 3,
    MAP_NAME        = 4,
    PASSWORD        = 5,
    SEL             = 6,
    SESSION         = 7,
    PSEUDO          = 8,
    PLAYER_DATA     = 9,
    LEVEL           = 11,
    TEAM_ID         = 12,
    FACTION_ID      = 13,
    TEAM_RANGE      = 14,
    GLOBAL_RANGE    = 15,
    RANGE           = 16,
    MESSAGE         = 17,
    RPG_GAMEPLAY    = 18,
    RTS_GAMEPLAY    = 19,
    NONE_GAMEPLAY   = 20,
    GAMEPLAY_TYPE   = 21,
    RESULT          = 22,
    TIME            = 23,
    OBJECT_ID       = 24,
    OBJECT_HEAL     = 25,
    OBJECT_POSITION = 26,
    OBJECT_TYPE     = 27,
    OBJECT_ROTATION = 28,
    CLASS_ID        = 29,
    AVATAR_ID       = 30,
    AVATAR_NAME     = 31,
    AVATAR_DEFAULT  = 32,
    ERROR_CODE      = 33,
    HERO_AVANCE     = 34,
    HERO_RECULE     = 35,
    HERO_GAUCHE     = 36,
    HERO_DROITE     = 37,
    BUILDER			= 38,
    COUNT			= 39,
};
}
class Packet;
Packet &operator<<(Packet &packet, const mf::EngineMessageKey &key);
Packet &operator>>(Packet &packet, mf::EngineMessageKey &key);
#endif // ENGINEMESSAGEKEY_H
