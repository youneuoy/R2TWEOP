#pragma once
#include "headersSTD.h"
#include "patchesWorker.h"

#include "luaP.h"
//here we store all program things
//no pointers to game stuff, etc
class programData
{
public:
	luaP luaManager;
	patchesWorker patchesManager;
};

