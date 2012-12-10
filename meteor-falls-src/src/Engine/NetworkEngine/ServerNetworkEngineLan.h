//========================================================================
/**@file	/home/thomas/meteor-falls/meteor-falls-src/src/Engine/NetworkEngine/ServerNetworkEngineLan.h
 * @author	thomas
 * @version	703
 * @date
 * 	Created:	lun. 10 déc. 2012 12:06:44 CET \n
 * 	Last Update:	lun. 10 déc. 2012 12:06:44 CET
 */
/*------------------------------------------------------------------------
 * Description:	classe serveur du jeu en mode LAN
 * 
 *------------------------------------------------------------------------
 * History:	
 * TODO:	
 *========================================================================
 */

#ifndef _HOME_THOMAS_METEOR_FALLS_METEOR_FALLS_SRC_SRC_ENGINE_NETWORKENGINE_SERVERNETWORKENGINELAN_H__
#define _HOME_THOMAS_METEOR_FALLS_METEOR_FALLS_SRC_SRC_ENGINE_NETWORKENGINE_SERVERNETWORKENGINELAN_H__
#include "ServerNetworkEngine.h"

class ServerNetworkEngineLan: public ServerNetworkEngine
{
	public:
		ServerNetworkEngineLan(EngineManager*, unsigned short port);
		virtual void announceServer();
		virtual void sendAllUdp(const std::string&);
		virtual ~ServerNetworkEngineLan();

	private:
		boost::asio::deadline_timer *m_timer_seed;

		void m_handleSendLanInfo(const boost::system::error_code&);
};
#endif // _HOME_THOMAS_METEOR_FALLS_METEOR_FALLS_SRC_SRC_ENGINE_NETWORKENGINE_SERVERNETWORKENGINELAN_H__
