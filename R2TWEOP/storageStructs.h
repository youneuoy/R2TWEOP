#pragma once

//just offsets, no routines here
struct patchesOffsetsT
{
	//https://www.lua.org/source/5.1/lauxlib.c.html#luaL_loadbuffer
	//useful lua function
	void* luaL_loadbufferOffset = nullptr;
	void* luaLoadSomeOffset = nullptr;



	void initOffsets(void* romeBase);
};

