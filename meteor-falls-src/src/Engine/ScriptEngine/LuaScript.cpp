#include "LuaScript.h"
#include "../../Lua/LuaInterface.h"
#include <CEGUI/CEGUI.h>
#include <CEGUI/ScriptingModules/LuaScriptModule/CEGUILua.h>
#include <lua.hpp>

#include <fstream>

LuaScriptEngine::LuaScriptEngine(): m_CEGUI(false)
{
	lua_State* L = luaL_newstate();
	luaL_openlibs(L);
	init(L);
}
LuaScriptEngine::LuaScriptEngine(CEGUI::ScriptModule* script): m_CEGUI(true)
{
	init(dynamic_cast<CEGUI::LuaScriptModule*>(script)->getLuaState());
}
LuaScriptEngine::~LuaScriptEngine()
{
	if(!m_CEGUI)
		lua_close(m_lua);
}
void LuaScriptEngine::Create(CEGUI::ScriptModule* module)
{
	Singleton<LuaScriptEngine>::m_instance = new LuaScriptEngine(module);
}
void LuaScriptEngine::init(lua_State* lua)
{
	m_lua = lua;
	tolua_LuaInterface_open(m_lua);
}
void LuaScriptEngine::executeScriptFile(const std::string &path)
{
	std::ifstream file;
	file.open(path);
	file.seekg(0, std::ios_base::end);
	const size_t taille = file.tellg();
	char *buffer        = new char[taille+1];
	buffer[taille]      = 0;
	file.seekg(0, std::ios_base::beg);
	file.read(buffer, taille);
	file.close();
	executeBuffer(buffer, taille, path.c_str());
	delete buffer;
}
void LuaScriptEngine::executeString(const std::string& buffer)
{
	executeBuffer(buffer.c_str(), buffer.size(), buffer.c_str());
}
void LuaScriptEngine::executeBuffer(const char *buffer, size_t taille, const char* name)
{
	int top = lua_gettop(m_lua);
	if(luaL_loadbuffer(m_lua, buffer, taille, name))
	{
		//Throw exception
		lua_settop(m_lua, top);
		return;
	}
	if(lua_pcall(m_lua, 0, 0, 0))
	{
		//Throw
		lua_settop(m_lua, top);
		return;
	}
	lua_settop(m_lua, top);
}
