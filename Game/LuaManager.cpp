#include "LuaManager.h"
using namespace cell;

LuaManager* LuaManager::_instance = NULL;

LuaManager* LuaManager::GetInst()
{
    if(_instance == NULL)
    {
        _instance = new LuaManager;
    }
    return _instance;
}



LuaManager::LuaManager()
:
_state(lua_open())
{
    luaL_openlibs(_state);
    luabind::open(_state);
}

LuaManager::~LuaManager()
{
    lua_close(_state);

    if(_instance)
    {
        delete _instance;
    }
}

void LuaManager::DoFile(std::string filename)
{
    luaL_dofile(_state, filename.c_str());
}

void LuaManager::DoString(std::string command)
{
    luaL_dostring(_state, command.c_str());
}






