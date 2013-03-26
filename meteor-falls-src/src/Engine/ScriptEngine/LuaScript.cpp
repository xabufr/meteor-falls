#include "LuaScript.h"
#include "../../Lua/LuaInterface.h"
#include <CEGUI/CEGUI.h>
#include <CEGUI/ScriptingModules/LuaScriptModule/CEGUILua.h>

CEGUI::ScriptModule* LuaScriptEngine::m_ceguiScript = nullptr;

LuaScriptEngine::LuaScriptEngine()
{
	lua_State* lua = nullptr;
	if(m_ceguiScript)
	{
		CEGUI::LuaScriptModule *luaScript = dynamic_cast<CEGUI::LuaScriptModule*>(m_ceguiScript);
		lua = luaScript->getLuaState();
	}
	if(lua)
	{
		tolua_LuaInterface_open(lua);
	}
}
void LuaScriptEngine::setCEGUIScriptModule(CEGUI::ScriptModule* m)
{
	m_ceguiScript=m;
}
