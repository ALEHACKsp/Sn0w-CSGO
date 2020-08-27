#include "Includes.h"


DWORD WINAPI MainThread(HMODULE hModule);
BOOL APIENTRY DllMain(HMODULE hModule, DWORD dwReason, LPVOID lpr);
Hack* pHack;

//Hack Thread's
void THAimbot();
bool InitSigs();
void InitSettings();

bool bExit = false;

BOOL APIENTRY DllMain(HMODULE hModule, DWORD dwReason, LPVOID lpr)
{
	switch (dwReason)
	{
	case DLL_PROCESS_ATTACH:
		HANDLE hThread = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)MainThread, hModule, 0, 0);
		CloseHandle(hThread);
		break;
	}
	return TRUE;
}


DWORD WINAPI MainThread(HMODULE hModule)
{	
	void** ppVtable = D3D::InitD3D();
	if (!ppVtable)
		FreeLibraryAndExitThread(hModule, 1);
	
	//Setup hack obj
	pHack = new Hack();
	pHack->draw = new Draw();

	//Get Module Handle's
	pHack->clientMod = reinterpret_cast<uintptr_t>(GetModuleHandle("client.dll"));
	pHack->engineMod = reinterpret_cast<uintptr_t>(GetModuleHandle("engine.dll"));

	if (!InitSigs())
	{
		FreeLibraryAndExitThread(hModule, 1);
		Patch(reinterpret_cast<BYTE*>(ppVtable[42]), D3D::Hook::EndSceneBytes, 7); //Unhook EndScene
	}
	
	//Create Hack Thread's
	CloseHandle(CreateThread(0, 0, (LPTHREAD_START_ROUTINE)THAimbot, 0, 0, 0));


	while (1)
	{
		if (GetAsyncKeyState(VK_END) & 1)
		{
			pHack->bIsIngame = false;
			bExit = true;
			std::this_thread::sleep_for(std::chrono::milliseconds(500));
			break;
		}

		pHack->CheckKeys();

		LocalPlayer* myPlayer = LocalPlayer::Get();
		if (*LocalPlayer::GetStatuts() == 6)
		{
			if (myPlayer)
				pHack->bIsIngame = true;
			else
				pHack->bIsIngame = false;
		}
		else
		{
			pHack->bIsIngame = false;
		}

		if (pHack->bIsIngame)
		{
			pHack->UpdateMatrix();

			if(!pHack->bChamsInitialized)
				pHack->InitChams();

			//Player Chams
			if (pHack->bChamsInitialized)
				pHack->Chams();

			//Load Settings
		/*	if (GetAsyncKeyState(VK_NUMPAD2) & 1)
				InitSettings();*/

			//FOV Changer
			myPlayer->SetFov();
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(5));
	}

	//Exit
	Patch(reinterpret_cast<BYTE*>(ppVtable[42]), D3D::Hook::EndSceneBytes, 7); //Unhook EndScene
	std::this_thread::sleep_for(std::chrono::milliseconds(500));
	FreeLibraryAndExitThread(hModule, 0);
}


void InitSettings()
{
	std::ifstream ifs;
	ifs.open("kebab.cfg", std::ios::binary);
	if (!ifs.is_open())
		return;

	ifs.read(reinterpret_cast<char*>(pHack), sizeof(Hack));
	Beep(300, 300);
	ifs.close();
}


bool InitSigs()
{
	//LocalPlayer (sig is wrong)
	pHack->sig_LclPlayer = reinterpret_cast<uintptr_t*>(pattern_scan_ida(GetModuleHandle("client.dll"), "8D 34 85 ? ? ? ? 89 15 ? ? ? ? 8B 41 08 8B 48 04 83 F9 FF") + 0x3);
	//Entity List
	pHack->sig_EntList = reinterpret_cast<uintptr_t*>(pattern_scan_ida(GetModuleHandle("client.dll"), "BB ? ? ? ? 83 FF 01 0F 8C ? ? ? ? 3B F8") + 0x1);
	//ClientState
	pHack->sig_ClientState = reinterpret_cast<uintptr_t*>(pattern_scan_ida(GetModuleHandle("engine.dll"), "A1 ? ? ? ? 33 D2 6A 00 6A 00 33 C9 89 B0") + 0x1);

	if (pHack->sig_LclPlayer && pHack->sig_EntList && pHack->sig_ClientState)
		return true;
	else
		return false;
}


void THAimbot()
{
	while (1)
	{
		if (pHack->bAim && pHack->bIsIngame)
			pHack->Aimbot();

		if (bExit)
			break;

		std::this_thread::sleep_for(std::chrono::microseconds(1));
	}
}