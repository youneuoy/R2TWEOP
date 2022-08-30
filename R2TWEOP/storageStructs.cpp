#include "storageStructs.h"

void patchesOffsetsT::initOffsets(void* romeBase)
{
	luaL_loadbufferOffset= (void*)((int)romeBase+0x149e610);
	luaLoadSomeOffset = (void*)((int)romeBase+0x10fde19);
}
