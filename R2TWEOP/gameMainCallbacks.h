#pragma once
//most important callbacks here
#include <sol.hpp>
class gameMainCallbacks
{
public:
	static void __stdcall onluaL_loadbufferOffset(lua_State* L, const char* buff, size_t size, const char* name);
	static lua_State* __stdcall onluaLoadSome();
};

