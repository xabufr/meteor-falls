#ifndef H_LUA_SCRIPT_H
#define H_LUA_SCRIPT_H
#include "../../Utils/singleton.h"

namespace CEGUI {
	class ScriptModule;
} // namespace CEGUI
class LuaScriptEngine : public Singleton<LuaScriptEngine>
{
	friend class Singleton<LuaScriptEngine>;
protected:
	LuaScriptEngine();
public:
	static void setCEGUIScriptModule(CEGUI::ScriptModule*);
private:
	static CEGUI::ScriptModule* m_ceguiScript;
};

#endif 
