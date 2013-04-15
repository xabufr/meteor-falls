#ifndef H_LUA_FUNCTION_H
#define H_LUA_FUNCTION_H 

#include <lua.hpp>
#include <string>

class LuaFunction
{
public:
	LuaFunction(lua_State* lua, const std::string& name): m_lua(lua), m_funcName(name), m_nbParams(0)
	{
	}
	template<typename... Args>
	void execute(Args... parameters)
	{
		int top = lua_gettop(m_lua);
		lua_getglobal(m_lua, m_funcName.c_str());
		unpack(parameters...);
		lua_call(m_lua, m_nbParams, 0);
		lua_settop(m_lua, top);
	}
	template<class T, class... Args>
	void unpack(T p1, Args... parameters)
	{
		m_nbParams++;
		push(p1);
		unpack(parameters...);
	}
	void unpack() { }
private:
	void push(const char* str)
	{
		lua_pushstring(m_lua, str);
	}
	void push(int val)
	{
		lua_pushinteger(m_lua, val);
	}
	void push(const std::string& str)
	{
		lua_pushstring(m_lua, str.c_str());
	}
	void push(double)
	{
	}
	void push(bool b)
	{
		lua_pushboolean(m_lua, b);
	}
	void push(void* data)
	{
		lua_pushlightuserdata(m_lua, data);
	}
	template<class T>
	void push(T* p)
	{
		push(static_cast<void*>(p));
	}
	lua_State* m_lua;
	std::string m_funcName;
	int m_nbParams;
};

#endif 
