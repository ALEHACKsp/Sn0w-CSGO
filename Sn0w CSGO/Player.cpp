#include "Includes.h"

extern Hack* pHack;

int* Player::GetMaxEntitys()
{
	return (int*)(*(uintptr_t*)(*pHack->sig_ClientState) + hazedumper::signatures::dwClientState_MaxPlayer);
}


int* Player::GetDormant()
{
	return (int*)(*(uintptr_t*)this + hazedumper::signatures::m_bDormant);
}


void Player::SetChams(Vec3 col, float brightness)
{
	//Set Model Color
	*(BYTE*)(*(uintptr_t*)this + 0x70) = col.x;
	*(BYTE*)(*(uintptr_t*)this + 0x71) = col.y;
	*(BYTE*)(*(uintptr_t*)this + 0x72) = col.z;

	//Set Model brightness
	uintptr_t ptr1 = (uintptr_t)(pHack->engineMod + hazedumper::signatures::model_ambient_min - 0x2C);
	int xored = *(int*)&brightness ^ ptr1;
	*(int*)(pHack->engineMod + hazedumper::signatures::model_ambient_min) = xored;
}

void Player::DeleteChams(Vec3 col, int xored)
{
	//Set Model Color
	*(BYTE*)(*(uintptr_t*)this + 0x70) = col.x;
	*(BYTE*)(*(uintptr_t*)this + 0x71) = col.y;
	*(BYTE*)(*(uintptr_t*)this + 0x72) = col.z;

	//Set Model brightness
	*(int*)(pHack->engineMod + hazedumper::signatures::model_ambient_min) = xored;
}

Vec3* Player::SaveChams(int *xorval)
{
	Vec3 oldChams = { 0 };

	//Save old Color
	oldChams.x = (float)*(BYTE*)(*(uintptr_t*)this + 0x70);
	oldChams.y = (float)*(BYTE*)(*(uintptr_t*)this + 0x71);
	oldChams.z = (float)*(BYTE*)(*(uintptr_t*)this + 0x72);

	//Save old brightness
	uintptr_t ptr1 = (uintptr_t)(pHack->engineMod + hazedumper::signatures::model_ambient_min - 0x2C);
	*xorval = *(int*)(pHack->engineMod + hazedumper::signatures::model_ambient_min);

	return &oldChams;
}

Vec2* Player::GetViewAngles()
{
	Vec2 entView = { 0 };
	entView.x = *(float*)(*(uintptr_t*)this + hazedumper::netvars::m_angEyeAnglesX);
	entView.y = *(float*)(*(uintptr_t*)this + hazedumper::netvars::m_angEyeAnglesY);
	return &entView;
}

//Get Entity Data
int* Player::GetHealth()
{
	return (int*)(*(uintptr_t*)this + hazedumper::netvars::m_iHealth);
}

int* Player::GetTeam()
{
	return (int*)(*(uintptr_t*)this + hazedumper::netvars::m_iTeamNum);
}


bool Player::EntCheck()
{
	//Entity Ptr Check
	if (!this)
		return false;
	//Dormant Check
	if (*GetDormant())
		return false;
	//Health Check
	if (*GetHealth() <= 0)
		return false;

	return true; //Entity is valid
}


Vec3* Player::GetBonePos(int bone)
{
	uintptr_t boneMatrix = *(uintptr_t*)(*(uintptr_t*)this + hazedumper::netvars::m_dwBoneMatrix);
	Vec3 bonePos;
	bonePos.x = *(float*)(boneMatrix + 0x30 * bone + 0x0C);
	bonePos.y = *(float*)(boneMatrix + 0x30 * bone + 0x1C);
	bonePos.z = *(float*)(boneMatrix + 0x30 * bone + 0x2C);
	return &bonePos;
}

Vec3* Player::GetOrigin()
{
	return (Vec3*)(*(uintptr_t*)this + hazedumper::netvars::m_vecOrigin);
}

Vec3* Player::GetView()
{
	return (Vec3*)(*(uintptr_t*)this + hazedumper::netvars::m_vecViewOffset);
}