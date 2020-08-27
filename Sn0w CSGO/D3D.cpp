#include "Includes.h"

extern Hack* pHack;
int ScreenWidth, ScreenHeight;
LPDIRECT3DDEVICE9 pDevice;

void** D3D::InitD3D()
{
	
	auto deviceAddr = pattern_scan_ida(GetModuleHandle("shaderapidx9.dll"), "A1 ? ? ? ? 50 8B 08 FF 51 0C") + 0x1;
	if (!deviceAddr)
		return nullptr;

	while (!pDevice)
		pDevice = **reinterpret_cast<LPDIRECT3DDEVICE9**>(deviceAddr);

	//Get Viewport
	D3DVIEWPORT9 viewPort = { 0 };
	pDevice->GetViewport(&viewPort);
	ScreenWidth = viewPort.Width;
	ScreenHeight = viewPort.Height;

	//Hook
	void** ppVtable = *reinterpret_cast<void***>(pDevice);
	memcpy(D3D::Hook::EndSceneBytes, reinterpret_cast<BYTE*>(ppVtable[42]), 7);
	D3D::Hook::oEndScene = reinterpret_cast<tEndScene>(TrampHook(reinterpret_cast<char*>(ppVtable[42]), reinterpret_cast<char*>(D3D::Hook::HookFunc), 7));

	return ppVtable;
}


void APIENTRY D3D::Hook::HookFunc(LPDIRECT3DDEVICE9 o_pDevice)
{
	if (pHack->bIsIngame && pHack->bAim)
		pHack->draw->DrawCircle(ScreenWidth / 2, ScreenHeight / 2, pHack->fov, 50, WHITE(255));

	if (pHack->bIsIngame && pHack->bCross)
	{
		//Corsshair
		Vec3 punchAngle = { 0 };
		LocalPlayer* myPlayer = LocalPlayer::Get();
		punchAngle = *myPlayer->GetPunchAngle();
		pHack->draw->FillRectangle(ScreenWidth / 2 - (ScreenWidth / 90 * punchAngle.y), ScreenHeight / 2 + (ScreenHeight / 90 * punchAngle.x), 4, 4, WHITE(255));
	}

	pHack->DrawMenu();

	if (pHack->bIsIngame)
	{
		if (pHack->bTeam || pHack->bEnemy)
			pHack->ESP();
	}

	//Return to Gateway
	D3D::Hook::oEndScene(pDevice);
}