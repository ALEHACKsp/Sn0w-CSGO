#pragma once

class Player;
class LocalPlayer;

class Hack
{

private:

	//Bools
	bool bAimbotMenu, bEspMenu, bMiscMenu, bShown;

	//Ints
	short UpDownIndex, SelelctionIndex, index[4];
	int oldXoredTeam, oldXoredEnemy;

	//floats
	float vMatrix[16];



public:

	Hack()
	{
		this->UpDownIndex = 0;
		this->SelelctionIndex = 0;
		this->bEspMenu = false;
		this->bAimbotMenu = false;
		this->bMiscMenu = false;
		for (int i = 0; i < 4; i++)
		{
			index[i] = 0;
		}


		this->aimSpeed = 1;
		this->bone = 8;
		this->playerFov = 120;

		this->oChamsTeam = { 0 };
		this->oChamsEnemy = { 0 };
		this->bChamsInitialized = false;
		this->bChamsEnemy = false;
		this->bChamsTeam = false;
	}


	~Hack()
	{
		//D3D
		this->d3dESP->Release();
		this->d3dLine->Release();
		this->d3dMenu->Release();
		this->d3dWatermark->Release();
		delete this;
	}

	//Fonts
	ID3DXLine* d3dLine;
	LPD3DXFONT d3dESP;
	LPD3DXFONT d3dMenu;
	LPD3DXFONT d3dWatermark;

	//Class Instances
	Draw* draw;

	Player* GetEnt(int index);

	uintptr_t* sig_LclPlayer;
	uintptr_t* sig_EntList;
	uintptr_t* sig_ClientState;

	//Hack Functions
	void Aimbot();
	Player* GetCrosshairEnt();
	void ESP();
	void Chams();
	void InitChams();
	void ResetChams();
	void SaveSettings();

	//World2Screen
	bool W2S(Vec3 pos, Vec2& screen);
	void UpdateMatrix();

	//Menu
	void CheckKeys();
	void DrawMenu();

	Vec3 oChamsTeam, oChamsEnemy;
	short espTarget;
	bool bChamsInitialized;
	bool bChamsEnemy, bChamsTeam;

	bool bHead, bBarrel, bBox, bSnap, bHealth, bDist, bTeam, bEnemy;

	//Aimbot
	short bone;
	DWORD key;
	bool bKey;
	int fov; //Max: 360
	bool bAim;
	bool bAimOnFire;
	int aimSpeed; //(1 - 10), currentAngles += diffAngles / aimSpeed

	//Misc
	int playerFov;
	bool bCross;
	//General
	bool bIsIngame;

	//Module
	uintptr_t clientMod;
	uintptr_t engineMod;
};