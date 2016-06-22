//gcc -llua -fPIC -shared -ldl luaclibtest.c -o luaclibtest.so

#include <lua.h>
#include <lauxlib.h> 
#include <math.h>

static int l_sin(lua_State* L) {

  double d = lua_tonumber(L, 1);
  lua_pushnumber(L, sin(d));
  return 1;
}


static int l_add(lua_State* L) {

  double d1 = lua_tonumber(L, 1);
  double d2 = lua_tonumber(L, 2);
  lua_pushnumber(L, (d1+d2));
  return 1;
}

static const struct luaL_Reg luaclibtestlib[] = {
  {"sin", l_sin},
  {"add", l_add},  
  {NULL, NULL}
};

  
int luaopen_luaclibtest(lua_State* L) {
  //luaL_register(L, "luaclibtestlib", luaclibtestlib);
  lua_newtable(L);
  luaL_setfuncs(L, luaclibtestlib, 0);
  return 1;
} 
