#pragma once
class LocalPlayer
{
public:

	LocalPlayer() {}

	static LocalPlayer* Get();
	int* GetHealth();
	int* GetTeam();
	static int* GetStatuts();
	static int* GetStatutsPlayer();
	int* GetFlag();
	int* GetFov();
	void SetFov();
	int* GetAttack();
	Vec3* GetBonePos(int bone);
	Vec3* GetOrigin();
	Vec3* GetViewOffset();
	Vec3* GetPunchAngle();
};

