//gcc luamain.c -llua -o luamain.linux

//gcc luamain.c -I../../lua-5.2.3/src -llua -o luamain.linux

#include <stdio.h>
#include <stdlib.h>

#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
#include <lstate.h>

#include <string.h> 


int get_integer_by_index(lua_State* L, int iIndex) {
    double retd;
    lua_pushinteger(L,iIndex);
    lua_gettable(L, -2);
    retd = luaL_checknumber(L, -1);
    lua_pop(L, 1);
    return (int)retd;
}


double get_number_by_index(lua_State* L, int iIndex) {
    double retd;
    lua_pushinteger(L,iIndex);
    lua_gettable(L, -2);
    retd = luaL_checknumber(L, -1);
    lua_pop(L, 1);
    return retd;
}

char* get_c_str_by_index(lua_State* L, int iIndex) {
    static char retchbuf[1024];
    lua_pushinteger(L, iIndex);
    lua_gettable(L, -2);
    strncpy(retchbuf, luaL_checkstring(L, -1), sizeof(retchbuf)-1);
    lua_pop(L, 1);
    return retchbuf;
}

int main(int argc, char* argv[]) {

    lua_State* L = luaL_newstate();
    //luaL_openlibs(L);

    if(luaL_loadfile(L, "config") || lua_pcall(L, 0, 0, 0) ) {
        printf("error %s\n", lua_tostring(L, -1));
    }

    /* lua_getglobal(L, "witdh"); */
    /* printf("width:%d\n", lua_tointeger(L, -1)); */
    /* lua_pop(L, 1); */
    /* printf("lua_typename: %s %s %s\n", lua_typename(L, lua_type(L, -1)), lua_typename(L, lua_type(L, -2)), lua_typename(L, lua_type(L, -3))); */
    /* printf("gettop:%d\n", lua_gettop(L)); */
  
    lua_getglobal(L, "testtablename");
    printf("istable:%d\n", lua_istable(L, -1));
    lua_pushnil(L);
    
    while(lua_next(L, -2)) {
        printf("d: %d\n", get_integer_by_index(L, 1));
        /* printf("f: %f\n", get_number_by_index(L, 1)); */
        printf("s: %s\n", get_c_str_by_index(L, 2));
        printf("s: %s\n", get_c_str_by_index(L, 3));
        lua_pop(L, 1);
    }

    /* printf("%d\n", lua_getfield(L, 1)); */
    /* lua_gettable(L, -1); */

  
    printf("LUA_VERSION_NUM:%d\n", LUA_VERSION_NUM);

    /* if(L) { */
    /*     printf("stacksize:%d\n", L); */
    /* } else { */
    /*     printf("L null\n"); */
    /* } */
  
    printf("lua_check:%d\n", lua_checkstack(L, 10));

    printf("%d", L->stack_last - L->top);  /* stack large enough? */
    
    lua_close(L);
    
    
    return EXIT_SUCCESS;
}
 
