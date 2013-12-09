/*
** Lua binding: LuaInterface
** Generated automatically by tolua++-1.0.92 on Sun Mar 17 17:52:41 2013.
*/

#ifndef __cplusplus
#include "stdlib.h"
#endif
#include "string.h"

#include "tolua++.h"

/* Exported function */
TOLUA_API int  tolua_LuaInterface_open (lua_State* tolua_S);

#include "../State/Menu/ServerList.h"
#include "../Application/application.h"
#include "../State/StateManager.h"
#include "../State/State.h"
#include "../State/Menu/MenuState.h"

/* function to register type */
static void tolua_reg_types (lua_State* tolua_S)
{
 tolua_usertype(tolua_S,"State");
 tolua_usertype(tolua_S,"MenuState");
 tolua_usertype(tolua_S,"StateManager");
 tolua_usertype(tolua_S,"Application");
 tolua_usertype(tolua_S,"ServerList");
}

/* method: updateFiltre of class  ServerList */
#ifndef TOLUA_DISABLE_tolua_LuaInterface_ServerList_updateFiltre00
static int tolua_LuaInterface_ServerList_updateFiltre00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ServerList",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ServerList* self = (ServerList*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'updateFiltre'", NULL);
#endif
  {
   self->updateFiltre();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'updateFiltre'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: instance of class  Application */
#ifndef TOLUA_DISABLE_tolua_LuaInterface_Application_instance00
static int tolua_LuaInterface_Application_instance00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Application",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   Application* tolua_ret = (Application*)  Application::instance();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Application");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'instance'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: currentState of class  Application */
#ifndef TOLUA_DISABLE_tolua_LuaInterface_Application_currentState00
static int tolua_LuaInterface_Application_currentState00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Application",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Application* self = (const Application*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'currentState'", NULL);
#endif
  {
   State* tolua_ret = (State*)  self->currentState();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"State");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'currentState'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: menuState of class  Application */
#ifndef TOLUA_DISABLE_tolua_LuaInterface_Application_menuState00
static int tolua_LuaInterface_Application_menuState00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Application",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Application* self = (const Application*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'menuState'", NULL);
#endif
  {
   MenuState* tolua_ret = (MenuState*)  self->menuState();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"MenuState");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'menuState'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: manager of class  Application */
#ifndef TOLUA_DISABLE_tolua_LuaInterface_Application_manager00
static int tolua_LuaInterface_Application_manager00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Application",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Application* self = (const Application*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'manager'", NULL);
#endif
  {
   StateManager* tolua_ret = (StateManager*)  self->manager();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"StateManager");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'manager'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: sousState of class  MenuState */
#ifndef TOLUA_DISABLE_tolua_LuaInterface_MenuState_sousState00
static int tolua_LuaInterface_MenuState_sousState00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const MenuState",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const MenuState* self = (const MenuState*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'sousState'", NULL);
#endif
  {
   State* tolua_ret = (State*)  self->sousState();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"State");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'sousState'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* Open function */
TOLUA_API int tolua_LuaInterface_open (lua_State* tolua_S)
{
 tolua_open(tolua_S);
 tolua_reg_types(tolua_S);
 tolua_module(tolua_S,NULL,0);
 tolua_beginmodule(tolua_S,NULL);
  tolua_cclass(tolua_S,"ServerList","ServerList","State",NULL);
  tolua_beginmodule(tolua_S,"ServerList");
   tolua_function(tolua_S,"updateFiltre",tolua_LuaInterface_ServerList_updateFiltre00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"Application","Application","",NULL);
  tolua_beginmodule(tolua_S,"Application");
   tolua_function(tolua_S,"instance",tolua_LuaInterface_Application_instance00);
   tolua_function(tolua_S,"currentState",tolua_LuaInterface_Application_currentState00);
   tolua_function(tolua_S,"menuState",tolua_LuaInterface_Application_menuState00);
   tolua_function(tolua_S,"manager",tolua_LuaInterface_Application_manager00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"StateManager","StateManager","",NULL);
  tolua_beginmodule(tolua_S,"StateManager");
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"State","State","",NULL);
  tolua_beginmodule(tolua_S,"State");
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"MenuState","MenuState","State",NULL);
  tolua_beginmodule(tolua_S,"MenuState");
   tolua_function(tolua_S,"sousState",tolua_LuaInterface_MenuState_sousState00);
  tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
 TOLUA_API int luaopen_LuaInterface (lua_State* tolua_S) {
 return tolua_LuaInterface_open(tolua_S);
};
#endif

