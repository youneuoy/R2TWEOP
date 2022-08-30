#pragma once
#include "headersSTD.h"

#include "storageStructs.h"

#include "programData.h"

//all global things
class dataStorage
{
public:
	static struct globalDataT
	{
		programData globalProgramData;

		patchesOffsetsT patchesOffsets;
	}globalData;
};

