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
	CHAT_MESSAGE    = 8,
	SETSALT         = 9,
	LOGIN_RESULT    = 10,
	LOAD_MAP        = 11,
	GETTEAMLIST = 12,
	ADDTEAM     = 13,
	KICK = 14,
};

#endif // ENGINEMESSAGETYPE_H
