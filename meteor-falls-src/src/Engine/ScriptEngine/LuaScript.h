#ifndef H_LUA_SCRIPT_H
#define H_LUA_SCRIPT_H
#include "../../Utils/singleton.h"

#include <string>
namespace CEGUI {
	class ScriptModule;
} // namespace CEGUI
struct lua_State;
class LuaScriptEngine : public Singleton<LuaScriptEngine>
{
	friend class Singleton<LuaScriptEngine>;
protected:
	LuaScriptEngine();
	LuaScriptEngine(CEGUI::ScriptModule*);
	~LuaScriptEngine();
public:
	static void Create(CEGUI::ScriptModule*);
	void executeScriptFile(const std::string& file);
	void executeString(const std::string& str);
	void executeBuffer(const char* buffer, size_t s, const char* name);
	template<class ...Args>
	void executeFunction(const std::string& funcName, Args... parameters);
	
private:
	void init(lua_State* lua);
	lua_State* m_lua;
	bool m_CEGUI;
};

#include "LuaFunction.h"
template<class ...Args>
void LuaScriptEngine::executeFunction(const std::string& funcName, Args... parameters)
{
	LuaFunction func(m_lua, funcName);
	func.execute(parameters...);
}

#endif 
