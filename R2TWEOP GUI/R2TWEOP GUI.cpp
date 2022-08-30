// R2TWEOP GUI.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include <string>
#include <vector>
#include <windows.h>

#include <fstream>
#include <shlwapi.h>

#pragma comment(lib, "user32.lib")
using namespace std;
#include <iostream>

int main()
{
	string libP = "R2TWEOPLibrary.dll";

	HANDLE hRTW2;

	DWORD ProcessId = 0;

	HWND hWnd = 0;
	UINT32 stop = 0;
	do {
		stop++;
		Sleep(100);
		hWnd = FindWindowA(0, ("Total War: Rome 2"));
		if (stop == 500)
			exit(0);
	} while (hWnd == 0);
	GetWindowThreadProcessId(hWnd, &ProcessId);

	hRTW2 = OpenProcess(PROCESS_CREATE_THREAD | PROCESS_QUERY_INFORMATION |
		PROCESS_QUERY_LIMITED_INFORMATION | PROCESS_VM_OPERATION |
		PROCESS_VM_WRITE | PROCESS_VM_READ
		, 0, ProcessId);

	size_t SizePatch = libP.size();
	LPVOID pDllPath = VirtualAllocEx(hRTW2, NULL, SizePatch, MEM_COMMIT, PAGE_READWRITE);
	if (!pDllPath)return 0;

	SIZE_T numW = 0;
	WriteProcessMemory(hRTW2, pDllPath, (LPVOID)libP.c_str(), SizePatch, &numW);
	if (!numW)return 0;
	HMODULE kernel = GetModuleHandleA("Kernel32.dll");
	if (!kernel)return 0;
	DWORD Adr = (DWORD)GetProcAddress(kernel, "LoadLibraryA");
	if (!Adr)return 0;
	HANDLE hThread = CreateRemoteThread(hRTW2, 0, 0, (LPTHREAD_START_ROUTINE)Adr, pDllPath, 0, 0);
	if (!hThread)return 0;
	WaitForSingleObject(hThread, INFINITE);
	CloseHandle(hThread);
	VirtualFreeEx(hRTW2, pDllPath, 0, MEM_RELEASE);

	CloseHandle(hRTW2);
	return 0;
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
