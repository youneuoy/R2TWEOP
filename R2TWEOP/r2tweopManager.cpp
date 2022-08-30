#include "pch.h"
#include "r2tweopManager.h"
#include "luaP.h"

#include "dataStorage.h"

#include "gameMainCallbacks.h"
namespace r2tweopManager
{

	struct
	{
		void* romeBase = nullptr;
	}manData;


	//make all code injects, create callbacks, etc
	static bool doPatches()
	{
		patchesWorker& patchesManager = dataStorage::globalData.globalProgramData.patchesManager;


		//to luaL_loadbufferOffset
		{
			codePatchID toluaL_loadbufferOffset = patchesManager.addPatch("toluaL_loadbufferOffset", dataStorage::globalData.patchesOffsets.luaL_loadbufferOffset, codePatchFlag_insertOriginalCodeAtEnd, 5);
			Assembler* a = patchesManager.prepareForCoding(toluaL_loadbufferOffset);


			//code
			{
				a->pushad();
				a->pushf();


				a->mov(edi, dword_ptr(esp, 0x22 + 0x4));//lua_state pointer
				a->mov(edx, dword_ptr(esp, 0x22 + 0x4 + 0x4));//buffer
				a->mov(eax, dword_ptr(esp, 0x22 + 0x4 + 0x4 + 0x4));//buffer size
				a->mov(ebx, dword_ptr(esp, 0x22 + 0x4 + 0x4 + 0x4 + 0x4));//name
				a->push(ebx);
				a->push(eax);
				a->push(edx);
				a->push(edi);

				a->mov(eax, gameMainCallbacks::onluaL_loadbufferOffset);
				a->call(eax);

			//	a->pop(eax);
			//	a->pop(ebx);

				a->popf();
				a->popad();
			}

			patchesManager.createCode(toluaL_loadbufferOffset);
			patchesManager.setPatchedCode(toluaL_loadbufferOffset);
		}
		//to toluaLoadSomeOffset
		{
			codePatchID toluaLoadSomeOffset = patchesManager.addPatch("toluaLoadSomeOffset", dataStorage::globalData.patchesOffsets.luaLoadSomeOffset, codePatchFlag_none, 5);
			Assembler* a = patchesManager.prepareForCoding(toluaLoadSomeOffset);


			//code
			{
				a->pushad();
				a->pushf();


				a->mov(eax, gameMainCallbacks::onluaLoadSome);
				a->call(eax);

			//	a->pop(eax);
			//	a->pop(ebx);

				a->popf();
				a->popad();
			}

			patchesManager.createCode(toluaLoadSomeOffset);
			patchesManager.setPatchedCode(toluaLoadSomeOffset);
		}


		return true;
	}


	void init()
	{
		//MessageBoxA(NULL, "test", "sdsd", MB_APPLMODAL | MB_SETFOREGROUND);
		manData.romeBase = (void*)GetModuleHandleA("Rome2.dll");
		if (manData.romeBase == nullptr)
		{
			MessageBoxA(NULL, "Can`t initialize R2TWEOP", "Warning!", MB_APPLMODAL | MB_SETFOREGROUND);
			return;
		}

		dataStorage::globalData.patchesOffsets.initOffsets(manData.romeBase);

		if (doPatches() == false)
		{
			MessageBoxA(NULL, "Can`t initialize R2TWEOP", "Warning!", MB_APPLMODAL | MB_SETFOREGROUND);
			return;
		}
	}
}