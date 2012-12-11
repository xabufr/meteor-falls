//========================================================================
/**@file	/home/thomas/meteor-falls/meteor-falls-src/src/State/ServerState/ServerState.h
 * @author	thomas
 * @version	703
 * @date
 * 	Created:	lun. 10 déc. 2012 15:59:58 CET \n
 * 	Last Update:	lun. 10 déc. 2012 15:59:58 CET
 */
/*------------------------------------------------------------------------
 * Description:	
 *
 * 
 *------------------------------------------------------------------------
 *========================================================================
 */

#ifndef _HOME_THOMAS_METEOR_FALLS_METEOR_FALLS_SRC_SRC_STATE_SERVERSTATE_SERVERSTATE_H__
#define _HOME_THOMAS_METEOR_FALLS_METEOR_FALLS_SRC_SRC_STATE_SERVERSTATE_SERVERSTATE_H__
#include "../State.h"
#include "../../Engine/EngineManager/EngineManager.h"

class Parameters;
class ServerState : public State
{
	public:
		ServerState(StateManager*, Parameters*);
		void enter();
		bool isVisible(){
				return true;
		}
		void exit();
        ret_code work(unsigned int time);
	private:
		EngineManager *m_eManager;
		Parameters *m_param;
};

#endif // _HOME_THOMAS_METEOR_FALLS_METEOR_FALLS_SRC_SRC_STATE_SERVERSTATE_SERVERSTATE_H__
