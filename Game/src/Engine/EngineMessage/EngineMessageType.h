#ifndef ENGINEMESSAGETYPE_H
#define ENGINEMESSAGETYPE_H

namespace mf {
enum class EngineMessageType
{
    PLAY_SOUND      = 0,
    SERVER_INFO     = 1,
    PING            = 2,
    SYNC_TIME       = 3,
    NEW_PLAYER      = 4,
    PLAYER_POSITION = 5,
    KEEP_ALIVE      = 6,
    DEL_PLAYER      = 7,
    CHAT_MESSAGE    = 8,
    SETSALT         = 9,
    LOGIN_RESULT    = 10,
    LOAD_MAP        = 11,
    GETTEAMLIST     = 12,
    ADDTEAM         = 13,
    KICK            = 14,
    SELECT_TEAM     = 15,
    SELECT_GAMEPLAY = 16,
    SET_PING 		= 17,
    GETOBJECTSLIST  = 18,
    ADDOBJECT       = 19,
    SPAWN           = 20,
    KILL            = 21,
    SUBIR_DEGATS    = 22,
    RTS_SELECTION   = 23,
};
}


#endif // ENGINEMESSAGETYPE_H
