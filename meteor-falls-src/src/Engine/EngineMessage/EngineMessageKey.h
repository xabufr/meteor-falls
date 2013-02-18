#ifndef ENGINEMESSAGEKEY_H
#define ENGINEMESSAGEKEY_H


enum EngineMessageKey
{
    FILE_NAME    	= 0,
    SERVER_NAME  	= 1,
    MAX_PLAYERS  	= 2,
    PLAYER_NUMBER	= 3,
    MAP_NAME     	= 4,
    PASSWORD     	= 5,
    SEL          	= 6,
    SESSION      	= 7,
    PSEUDO       	= 8,
	PLAYER_DATA  	= 9,
	LEVEL        	= 11,
	TEAM_ID      	= 12,
	FACTION_ID   	= 13,
	TEAM_RANGE   	= 14,
	GLOBAL_RANGE 	= 15,
	RANGE        	= 16,
	MESSAGE      	= 17,
	RPG_GAMEPLAY 	= 18,
	RTS_GAMEPLAY 	= 19,
	NONE_GAMEPLAY	= 20,
	GAMEPLAY_TYPE	= 21,
	RESULT       	= 22,
	TIME          	= 23,
	OBJECT_ID       = 24,
	OBJECT_HEAL     = 25,
	OBJECT_POSITION = 26,
	OBJECT_TYPE     = 27,
	CLASS_ID  		= 28,
	AVATAR_ID 		= 29,
	ERROR_CODE 		= 30,
};

#endif // ENGINEMESSAGEKEY_H
