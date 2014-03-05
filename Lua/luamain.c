//gcc luamain.c -llua -o luamain.linux

#include <stdio.h>
#include <stdlib.h>

#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>

int main(int argc, char* argv[]) {

  lua_State* L = luaL_newstate();
  //luaL_openlibs(L);

  if(luaL_loadfile(L, "config") || lua_pcall(L, 0, 0, 0) ) {
    printf("error %s\n", lua_tostring(L, -1));
  }

  lua_getglobal(L, "witdh");
  printf("width:%d\n", lua_tointeger(L, -1));

  printf("lua_check:%d", lua_checkstack(L, 10));
  lua_close(L);


  
  
  return EXIT_SUCCESS;
}
 
