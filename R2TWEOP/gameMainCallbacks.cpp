#include "gameMainCallbacks.h"
#include "dataStorage.h"
void __stdcall gameMainCallbacks::onluaL_loadbufferOffset(lua_State* L, const char* buff, size_t size, const char* name)
{
	dataStorage::globalData.globalProgramData.luaManager.onluaL_loadbufferOffset(L, buff, size, name);
}

lua_State* __stdcall gameMainCallbacks::onluaLoadSome()
{
	return dataStorage::globalData.globalProgramData.luaManager.onlualoadsome();
}
