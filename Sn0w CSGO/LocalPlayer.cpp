#include "Includes.h"

extern Hack* pHack;

//Get Ptr to the LocalPlayer Object
LocalPlayer* LocalPlayer::Get() //Works
{
	static uintptr_t* pLclPlayer = reinterpret_cast<uintptr_t*>(pHack->clientMod + hazedumper::signatures::dwLocalPlayer);
	if (!pLclPlayer || !*pLclPlayer)
		return nullptr;

	return (LocalPlayer*)pLclPlayer;
}
//Get Data of LocalPlayer
int* LocalPlayer::GetHealth()
{
	return (int*)(*(uintptr_t*)this + hazedumper::netvars::m_iHealth);
}

int* LocalPlayer::GetAttack()
{
	return (int*)(*(uintptr_t*)this + hazedumper::netvars::m_iShotsFired);
}

int* LocalPlayer::GetTeam()
{
	return (int*)(*(uintptr_t*)this + hazedumper::netvars::m_iTeamNum);
}

int* LocalPlayer::GetFlag()
{
	return (int*)(*(uintptr_t*)this + hazedumper::netvars::m_fFlags);
}


int* LocalPlayer::GetFov()
{
	return (int*)(*(uintptr_t*)this + hazedumper::netvars::m_iFOV);
}

void LocalPlayer::SetFov()
{
	//Check if zoomed
	int* bZoom = (int*)(*(uintptr_t*)this + hazedumper::netvars::m_bIsScoped);
	if (!*bZoom)
		*(int*)(*(uintptr_t*)this + hazedumper::netvars::m_iFOV) = pHack->playerFov;
}

int* LocalPlayer::GetStatuts()
{
	return (int*)(*(uintptr_t*)*pHack->sig_ClientState + hazedumper::signatures::dwClientState_State);
}

int* LocalPlayer::GetStatutsPlayer()
{
	return (int*)(*(uintptr_t*)*pHack->sig_ClientState + hazedumper::signatures::dwClientState_GetLocalPlayer);
}

Vec3* LocalPlayer::GetBonePos(int bone)
{
	uintptr_t boneMatrix = *(uintptr_t*)(*(uintptr_t*)this + hazedumper::netvars::m_dwBoneMatrix);
	Vec3 bonePos;
	bonePos.x = *(float*)(boneMatrix + 0x30 * bone + 0x0C);
	bonePos.y = *(float*)(boneMatrix + 0x30 * bone + 0x1C);
	bonePos.z = *(float*)(boneMatrix + 0x30 * bone + 0x2C);
	return &bonePos;
}

Vec3* LocalPlayer::GetViewOffset()
{
	return (Vec3*)(*(uintptr_t*)this + hazedumper::netvars::m_vecViewOffset);
}

Vec3* LocalPlayer::GetPunchAngle()
{
	return (Vec3*)(*(uintptr_t*)this + hazedumper::netvars::m_aimPunchAngle);
}


Vec3* LocalPlayer::GetOrigin()
{
	return (Vec3*)(*(uintptr_t*)this + hazedumper::netvars::m_vecOrigin);
}