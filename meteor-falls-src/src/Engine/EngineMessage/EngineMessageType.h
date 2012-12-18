#ifndef ENGINEMESSAGETYPE_H
#define ENGINEMESSAGETYPE_H


enum EngineMessageType
{
    PLAY_SOUND      = 0,
    SERVER_INFO     = 1,
    PING            = 2,
    SYNC_TIME       = 3,
    NEW_PLAYER      = 4,
    PLAYER_POSITION = 5,
    KEEP_ALIVE      = 6,
    DEL_PLAYER      = 7,
    TEAM_MESSAGE    = 8,
    GLOBAL_MESSAGE  = 9,
	SETSALT         = 10,
	LOGIN_RESULT    = 11,
	LOAD_MAP        = 12,
	GETTEAMLIST = 13,
	ADDTEAM     = 14,
};

#endif // ENGINEMESSAGETYPE_H
