#ifndef _LUA_MANAGER_H__
#define _LUA_MANAGER_H__

//#include "luabridge.hpp"
#include "luabind.hpp"  // the important file ( na if i feel like it some day i may write a binding lib but that stack is a pain in the ass

#include <stdio.h>
#include <string>
extern "C"	{
	#include "lua.h"
	#include "lualib.h"
	#include "lauxlib.h"
}
#include <iostream>


#undef SFML_DYNAMIC


namespace cell
{
class  LuaManager
{
    private:
        static LuaManager* _instance;
        LuaManager();

    public:
        static LuaManager* GetInst();
        ~LuaManager();

        //wrapper to luaL_dofile
        void DoFile(std::string filename);

        //wrapper to luaL_dostring
        void DoString(std::string command);

        lua_State* GetState()           { return _state;    }

    private:
        lua_State*          _state;
};
}

#endif
