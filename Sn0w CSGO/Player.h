#pragma once
class Player
{
public:
	Player() {}

	static int* GetMaxEntitys();
	//Player* Get(int index);
	bool EntCheck();

	//Get Entity Data
	int* GetHealth();
	int* GetTeam();
	int* GetDormant();
	void SetChams(Vec3 col, float brightness);
	void DeleteChams(Vec3 col, int xored);
	Vec3* SaveChams(int *xorval);
	Vec3* GetBonePos(int bone);
	Vec3* GetOrigin();
	Vec3* GetView();
	Vec2* GetViewAngles();
};
