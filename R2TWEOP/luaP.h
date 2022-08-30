#pragma once
#pragma comment(lib,"lua.lib")
#include "headersSTD.h"


#include <sol.hpp>


//all lua things
class luaP
{
public:
	void onluaL_loadbufferOffset(lua_State* L, const char* buff, size_t size, const char* name);
	lua_State* onlualoadsome();
private:
	void updateCampaignState(lua_State* L);
	//std::vector< std::shared_ptr<>
};

