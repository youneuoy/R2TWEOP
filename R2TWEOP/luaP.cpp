#include "pch.h"
#include "luaP.h"

void luaP::onluaL_loadbufferOffset(lua_State* L, const char* buff, size_t size, const char* name)
{
	return;
	if (strstr(name, "campaigns") == 0) {
		return;
	}


	updateCampaignState(L);
}
lua_State* luaP::onlualoadsome()
{
	return luaL_newstate();
}
static void tesfad()
{
	int i = 0;
	int t = i;
}

void luaP::updateCampaignState(lua_State* L)
{
	//void* ud;

	//lua_getallocf(L, &ud);
	///lua_State* L2 = luaL_newstate();
	//luaL_openlibs(L2);

	luaL_checkstack(L, 3, "not enough stack slots available");
	const char* err = lua_tostring(L, -1);
	sol::state_view lua(L);


	lua.set_function("tesft", tesfad);

}
