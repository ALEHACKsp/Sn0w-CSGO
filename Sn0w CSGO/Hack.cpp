#include "Includes.h"


extern LPDIRECT3DDEVICE9 pDevice;
extern int ScreenWidth, ScreenHeight;

void Hack::CheckKeys()
{
	LocalPlayer* myPlayer = LocalPlayer::Get();

	if (GetAsyncKeyState(VK_INSERT) & 1)
		bShown = !bShown;

	//Save Settings
	if (GetAsyncKeyState(VK_DELETE) & 1)
		SaveSettings();

	if (bShown)
	{
		//Up and Down Selection
		if (GetAsyncKeyState(VK_UP) & 1)
		{
			if (UpDownIndex > 0)
				UpDownIndex--;

			if (!bEspMenu)
			{
				if (UpDownIndex > 0 && UpDownIndex < 8)
					UpDownIndex = 0;
			}

			if (!bAimbotMenu)
			{
				if (UpDownIndex > 8 && UpDownIndex < 13)
					UpDownIndex = 8;
			}

			if (!bMiscMenu)
			{
				if (UpDownIndex > 13 && UpDownIndex < 16)
					UpDownIndex = 13;
			}
		}
		if (GetAsyncKeyState(VK_DOWN) & 1)
		{
			if (UpDownIndex < 16)
				UpDownIndex++;

			if (!bEspMenu)
			{
				if (UpDownIndex > 0 && UpDownIndex < 8)
					UpDownIndex = 8;
			}

			if (!bAimbotMenu)
			{
				if (UpDownIndex > 8 && UpDownIndex < 13)
					UpDownIndex = 13;
			}

			if (!bMiscMenu)
			{
				if (UpDownIndex > 13 && UpDownIndex < 16)
					UpDownIndex = 13;
			}
		}

		//ESP Start
		switch (UpDownIndex)
		{
		case 0:
		{
			if (GetAsyncKeyState(VK_RIGHT) & 1)
				bEspMenu = true;
			if (GetAsyncKeyState(VK_LEFT) & 1)
				bEspMenu = false;
			break;
		}
		case 1:
			//ESP Target
			if (GetAsyncKeyState(VK_RIGHT) & 1)
			{
				if (index[0] < 3)
				{
					index[0]++;
					//Check what is selected
					switch (index[0])
					{
					case 0:
						bTeam = false;
						bEnemy = false;
						break;
					case 1:
						bTeam = true;
						bEnemy = false;
						break;
					case 2:
						bTeam = false;
						bEnemy = true;
						break;
					case 3:
						bTeam = true;
						bEnemy = true;
						break;
					}
				}
			}
			if (GetAsyncKeyState(VK_LEFT) & 1)
			{
				if (index[0] > 0)
				{
					index[0]--;
					switch (index[0])
					{
					case 0:
						bTeam = false;
						bEnemy = false;
						break;
					case 1:
						bTeam = true;
						bEnemy = false;
						break;
					case 2:
						bTeam = false;
						bEnemy = true;
						break;
					case 3:
						bTeam = true;
						bEnemy = true;
						break;
					}
				}
			}
			break;
		case 2:
			//ESP 2D Box
			if (GetAsyncKeyState(VK_RIGHT) & 1)
					bBox = true;
	
			if (GetAsyncKeyState(VK_LEFT) & 1)
					bBox = false;
	
			break;
		case 3:
			//Snaplines
			if (GetAsyncKeyState(VK_RIGHT) & 1)
					bSnap = true;
	
			if (GetAsyncKeyState(VK_LEFT) & 1)
					bSnap = false;
	
			break;
		case 4:
			//Health
			if (GetAsyncKeyState(VK_RIGHT) & 1)
					bHealth = true;
	
			if (GetAsyncKeyState(VK_LEFT) & 1)
					bHealth = false;

			break;
		case 5:
			//Distance
			if (GetAsyncKeyState(VK_RIGHT) & 1)
					bDist = true;
			
			if (GetAsyncKeyState(VK_LEFT) & 1)
					bDist = false;
	
			break;
		case 6:
			//Head ESP
			if (GetAsyncKeyState(VK_RIGHT) & 1)
					bHead = true;

			if (GetAsyncKeyState(VK_LEFT) & 1)
					bHead = false;
	
			break;
		case 7:
			//Barrel ESP
			if (GetAsyncKeyState(VK_RIGHT) & 1)
					bBarrel = true;
			
			if (GetAsyncKeyState(VK_LEFT) & 1)
					bBarrel = false;
			
			break;

		//Aimbot Start
		case 8:
		{
			if (GetAsyncKeyState(VK_RIGHT) & 1)
				bAimbotMenu = true;
			if (GetAsyncKeyState(VK_LEFT) & 1)
				bAimbotMenu = false;
			break;
		}
		case 9:
			//Auto Aim
			if (GetAsyncKeyState(VK_RIGHT) & 1)
			{
				if (index[1] < 2)
				{
					index[1]++;
					switch (index[1])
					{
					case 0:
						bAim = false;
						bAimOnFire = false;
						break;
					case 1:
						bAim = true;
						bAimOnFire = false;
						break;
					case 2:
						bAim = true;
						bAimOnFire = true;
						break;
					}
				}			
			}
			if (GetAsyncKeyState(VK_LEFT) & 1)
			{
				if (index[1] > 0)
				{
					index[1]--;
					switch (index[1])
					{
					case 0:
						bAim = false;
						bAimOnFire = false;
						break;
					case 1:
						bAim = true;
						bAimOnFire = false;
						break;
					case 2:
						bAim = true;
						bAimOnFire = true;
						break;
					}
				}
			}
		case 10:
			//Aim Smooth
			if (GetAsyncKeyState(VK_RIGHT) & 1)
			{
				if (aimSpeed < 100)
					aimSpeed++;
			}
			if (GetAsyncKeyState(VK_LEFT) & 1)
			{
				if (aimSpeed > 1)
					aimSpeed--;
			}
		case 11:
			//HitBox
			if (GetAsyncKeyState(VK_RIGHT) & 1)
			{
				if (index[2] < 3)
				{
					index[2]++;
					switch (index[2])
					{
					case 0: //Head
						bone = 8;
						break;
					case 1: //Neck
						bone = 7;
						break;
					case 2: //Chest
						bone = 6;
						break;
					case 3: //stomach
						bone = 5;
						break;
					}
				}
			}
			if (GetAsyncKeyState(VK_LEFT) & 1)
			{
				if (index[2] > 0)
				{
					index[2]--;
					switch (index[2])
					{
					case 0: //Head
						bone = 8;
						break;
					case 1: //Neck
						bone = 7;
						break;
					case 2: //Chest
						bone = 6;
						break;
					case 3: //stomach
						bone = 5;
						break;
					}
				}
			}
			break;
		case 12:
			//Aim FOV (Max: 360)
			if (GetAsyncKeyState(VK_RIGHT) & 1)
			{
				if (fov < 360)
					fov++;
			}
			if (GetAsyncKeyState(VK_LEFT) & 1)
			{
				if (fov > 0)
					fov--;
			}
			break;

		//Misc Start
		case 13:
		{
			if (GetAsyncKeyState(VK_RIGHT) & 1)
				bMiscMenu = true;
			if (GetAsyncKeyState(VK_LEFT) & 1)
				bMiscMenu = false;
			break;
		}
		case 14:
			//FOV Changer
			if (GetAsyncKeyState(VK_RIGHT) & 1)
			{
				if (playerFov < 180)
					playerFov++;
			}
			if (GetAsyncKeyState(VK_LEFT) & 1)
			{
				if (playerFov > 1)
					playerFov--;
			}
			break;
		case 15:
			//Recoil Crosshair
			if (GetAsyncKeyState(VK_RIGHT) & 1)
				bCross = true;

			if (GetAsyncKeyState(VK_LEFT) & 1)
				bCross = false;
			break;
		case 16:
			//Player Chams
			if (GetAsyncKeyState(VK_RIGHT) & 1)
			{
				if (index[3] < 3)
				{
					index[3]++;
					switch (index[3])
					{
					case 0: //Off
						bChamsEnemy = false;
						bChamsTeam = false;
						break;
					case 1: //Team On, Enemy Off
						bChamsEnemy = false;
						bChamsTeam = true;
						break;
					case 2: //Team Off, Enemy On
						bChamsEnemy = true;
						bChamsTeam = false;
						break;
					case 3: //All
						bChamsEnemy = true;
						bChamsTeam = true;
						break;
					}
					ResetChams();
				}
			}
			if (GetAsyncKeyState(VK_LEFT) & 1)
			{
				if (index[3] > 0)
				{
					index[3]--;
					switch (index[3])
					{
					case 0: //Off
						bChamsEnemy = false;
						bChamsTeam = false;
						break;
					case 1: //Team On, Enemy Off
						bChamsEnemy = false;
						bChamsTeam = true;
						break;
					case 2: //Team Off, Enemy On
						bChamsEnemy = true;
						bChamsTeam = false;
						break;
					case 3: //All
						bChamsEnemy = true;
						bChamsTeam = true;
						break;
					}
					ResetChams();
				}
			}
		}
	}
}


void Hack::SaveSettings()
{
	std::ofstream ofs;
	ofs.open("kebab.cfg", std::ios::binary);
	if (!ofs.is_open())
		return;

	ofs.write(reinterpret_cast<char*>(this), sizeof(Hack));
	ofs.close();
	Beep(500, 300); //Signal (success)
}

void Hack::DrawMenu()
{
	//D3D Initialize
	if(!d3dWatermark)
		D3DXCreateFontA(pDevice, 19, 0, FW_MEDIUM, 1, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, ANTIALIASED_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Arial Rounded MT", &d3dWatermark);
	if(!d3dESP)
		D3DXCreateFontA(pDevice, 12, 0, FW_NORMAL, 1, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, ANTIALIASED_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Arial", &d3dESP);
	if(!d3dMenu)
		D3DXCreateFontA(pDevice, 17, 0,	FW_MEDIUM, 1, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, ANTIALIASED_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Arial Rounded MT", &d3dMenu);

	//D3D Line
	if (!d3dLine)
		D3DXCreateLine(pDevice, &d3dLine);

	if (!bShown)
	{
		draw->DrawTxt(5, 5, ORANGE(255), d3dWatermark, "[INSERT]");
		return;
	}
	
	//Background Adjustment
	if (bEspMenu && bAimbotMenu && bMiscMenu)
		draw->FillArea(0, 0, 280, 380, BLACK(100));
	else if (!bEspMenu && !bAimbotMenu && !bMiscMenu)
		draw->FillArea(0, 0, 280, 100, BLACK(100));
	else if (bEspMenu && !bAimbotMenu && !bMiscMenu)//
		draw->FillArea(0, 0, 280, 250, BLACK(100));
	else if (bEspMenu && bAimbotMenu && !bMiscMenu)
		draw->FillArea(0, 0, 280, 320, BLACK(100));
	else if (!bEspMenu && bAimbotMenu && !bMiscMenu)
		draw->FillArea(0, 0, 280, 180, BLACK(100));
	else if (!bEspMenu && !bAimbotMenu && bMiscMenu)
		draw->FillArea(0, 0, 280, 160, BLACK(100));
	else if (!bEspMenu && bAimbotMenu && bMiscMenu)
		draw->FillArea(0, 0, 280, 270, BLACK(100));
	else if (bEspMenu && !bAimbotMenu && bMiscMenu)
		draw->FillArea(0, 0, 280, 380, BLACK(100));

	draw->DrawTxt(5, 5, YELLOW(255), d3dWatermark, "KebabHook");

	//ESP Menu
	UpDownIndex == 0 ? draw->DrawTxt(5, 25, YELLOW(255), d3dMenu, "ESP Selection") : draw->DrawTxt(5, 25, WHITE(255), d3dMenu, "ESP Selection");
	bEspMenu ? draw->DrawTxt(250, 25, RED(255), d3dMenu, "[-]") : draw->DrawTxt(250, 25, LAWNGREEN(255), d3dMenu, "[+]");
	if (bEspMenu)
	{
		UpDownIndex == 1 ? draw->DrawTxt(5, 45, YELLOW(255), d3dMenu, "ESP") : draw->DrawTxt(5, 45, WHITE(255), d3dMenu, "ESP");
		UpDownIndex == 2 ? draw->DrawTxt(5, 65, YELLOW(255), d3dMenu, "ESP Box 2D") : draw->DrawTxt(5, 65, WHITE(255), d3dMenu, "ESP Box 2D");
		UpDownIndex == 3 ? draw->DrawTxt(5, 85, YELLOW(255), d3dMenu, "ESP Snaplines") : draw->DrawTxt(5, 85, WHITE(255), d3dMenu, "ESP Snaplines");
		UpDownIndex == 4 ? draw->DrawTxt(5, 105, YELLOW(255), d3dMenu, "ESP Health") : draw->DrawTxt(5, 105, WHITE(255), d3dMenu, "ESP Health");
		UpDownIndex == 5 ? draw->DrawTxt(5, 125, YELLOW(255), d3dMenu, "ESP Distance") : draw->DrawTxt(5, 125, WHITE(255), d3dMenu, "ESP Distance");
		UpDownIndex == 6 ? draw->DrawTxt(5, 145, YELLOW(255), d3dMenu, "ESP Head") : draw->DrawTxt(5, 145, WHITE(255), d3dMenu, "ESP Head");
		UpDownIndex == 7 ? draw->DrawTxt(5, 165, YELLOW(255), d3dMenu, "ESP Barrel") : draw->DrawTxt(5, 165, WHITE(255), d3dMenu, "ESP Barrel");

		switch (index[0])
		{
		case 0:
			draw->DrawTxt(150, 45, RED(255), d3dMenu, "None");
			break;
		case 1:
			draw->DrawTxt(150, 45, BLUE(255), d3dMenu, "Team");
			break;
		case 2:
			draw->DrawTxt(150, 45, ORANGE(255), d3dMenu, "Enemy");
			break;
		case 3:
			draw->DrawTxt(150, 45, GREEN(255), d3dMenu, "All");
			break;
		}

		bBox ? draw->DrawTxt(150, 65, GREEN(255), d3dMenu, "ON") : draw->DrawTxt(150, 65, RED(255), d3dMenu, "OFF");
		bSnap ? draw->DrawTxt(150, 85, GREEN(255), d3dMenu, "ON") : draw->DrawTxt(150, 85, RED(255), d3dMenu, "OFF");
		bHealth ? draw->DrawTxt(150, 105, GREEN(255), d3dMenu, "ON") : draw->DrawTxt(150, 105, RED(255), d3dMenu, "OFF");
		bDist ? draw->DrawTxt(150, 125, GREEN(255), d3dMenu, "ON") : draw->DrawTxt(150, 125, RED(255), d3dMenu, "OFF");
		bHead ? draw->DrawTxt(150, 145, GREEN(255), d3dMenu, "ON") : draw->DrawTxt(150, 145, RED(255), d3dMenu, "OFF");
		bBarrel ? draw->DrawTxt(150, 165, GREEN(255), d3dMenu, "ON") : draw->DrawTxt(150, 165, RED(255), d3dMenu, "OFF");
	}


	//Aimbot Menu
	if (!bEspMenu) //Draw further up
	{
		UpDownIndex == 8 ? draw->DrawTxt(5, 50, YELLOW(255), d3dMenu, "Aimbot Selection") : draw->DrawTxt(5, 50, WHITE(255), d3dMenu, "Aimbot Selection");
		bAimbotMenu ? draw->DrawTxt(250, 50, RED(255), d3dMenu, "[-]") : draw->DrawTxt(250, 50, LAWNGREEN(255), d3dMenu, "[+]");
		if (bAimbotMenu)
		{
			//Aimbot Functions
			UpDownIndex == 9 ? draw->DrawTxt(5, 70, YELLOW(255), d3dMenu, "Auto Aim") : draw->DrawTxt(5, 70, WHITE(255), d3dMenu, "Auto Aim");
			UpDownIndex == 10 ? draw->DrawTxt(5, 90, YELLOW(255), d3dMenu, "Aim Smooth") : draw->DrawTxt(5, 90, WHITE(255), d3dMenu, "Aim Smooth");
			UpDownIndex == 11 ? draw->DrawTxt(5, 110, YELLOW(255), d3dMenu, "HitBox") : draw->DrawTxt(5, 110, WHITE(255), d3dMenu, "HitBox");
			UpDownIndex == 12 ? draw->DrawTxt(5, 130, YELLOW(255), d3dMenu, "Aim FOV") : draw->DrawTxt(5, 130, WHITE(255), d3dMenu, "Aim FOV");

			switch (index[1])
			{
			case 0:
				draw->DrawTxt(150, 70, RED(255), d3dMenu, "OFF");
				break;
			case 1:
				draw->DrawTxt(150, 70, GREEN(255), d3dMenu, "ON");
				break;
			case 2:
				draw->DrawTxt(150, 70, YELLOW(250), d3dMenu, "ON FIRE");
				break;
			}

			std::stringstream sAim;
			sAim << aimSpeed;
			std::string sAimSpeed = sAim.str();
			draw->DrawTxt(150, 90, DARKORANGE(255), d3dMenu, sAimSpeed.c_str());

			std::stringstream sFov;
			sFov << fov;
			std::string strFov = sFov.str();
			draw->DrawTxt(150, 130, YELLOW(255), d3dMenu, strFov.c_str());

			switch (index[2])
			{
			case 0:
				draw->DrawTxt(150, 110, PINK(255), d3dMenu, "Head");
				break;
			case 1:
				draw->DrawTxt(150, 110, YELLOW(255), d3dMenu, "Neck");
				break;
			case 2:
				draw->DrawTxt(150, 110, BLUE(255), d3dMenu, "Chest");
				break;
			case 3:
				draw->DrawTxt(150, 110, DARKORANGE(255), d3dMenu, "Stomach");
				break;
			}
		}	
	}
	else //Start at Y=190
	{
		UpDownIndex == 8 ? draw->DrawTxt(5, 190, YELLOW(255), d3dMenu, "Aimbot Selection") : draw->DrawTxt(5, 190, WHITE(255), d3dMenu, "Aimbot Selection");
		bAimbotMenu ? draw->DrawTxt(250, 190, RED(255), d3dMenu, "[-]") : draw->DrawTxt(250, 190, LAWNGREEN(255), d3dMenu, "[+]");
		if (bAimbotMenu)
		{
			//Aimbot Functions
			UpDownIndex == 9 ? draw->DrawTxt(5, 210, YELLOW(255), d3dMenu, "Auto Aim") : draw->DrawTxt(5, 210, WHITE(255), d3dMenu, "Auto Aim");
			UpDownIndex == 10 ? draw->DrawTxt(5, 230, YELLOW(255), d3dMenu, "Aim Smooth") : draw->DrawTxt(5, 230, WHITE(255), d3dMenu, "Aim Smooth");
			UpDownIndex == 11 ? draw->DrawTxt(5, 250, YELLOW(255), d3dMenu, "HitBox") : draw->DrawTxt(5, 250, WHITE(255), d3dMenu, "HitBox");
			UpDownIndex == 12 ? draw->DrawTxt(5, 270, YELLOW(255), d3dMenu, "Aim FOV") : draw->DrawTxt(5, 270, WHITE(255), d3dMenu, "Aim FOV");

			switch (index[1])
			{
			case 0:
				draw->DrawTxt(150, 210, RED(255), d3dMenu, "OFF");
				break;
			case 1:
				draw->DrawTxt(150, 210, GREEN(255), d3dMenu, "ON");
				break;
			case 2:
				draw->DrawTxt(150, 210, YELLOW(250), d3dMenu, "ON FIRE");
				break;
			}

			switch (index[2])
			{
			case 0:
				draw->DrawTxt(150, 250, PINK(255), d3dMenu, "Head");
				break;
			case 1:
				draw->DrawTxt(150, 250, YELLOW(255), d3dMenu, "Neck");
				break;
			case 2:
				draw->DrawTxt(150, 250, BLUE(255), d3dMenu, "Chest");
				break;
			case 3:
				draw->DrawTxt(150, 250, DARKORANGE(255), d3dMenu, "Stomach");
				break;
			}

			std::stringstream sAim;
			sAim << aimSpeed;
			std::string sAimSpeed = sAim.str();
			draw->DrawTxt(150, 230, DARKORANGE(255), d3dMenu, sAimSpeed.c_str());

			std::stringstream sFov;
			sFov << fov;
			std::string strFov = sFov.str();
			draw->DrawTxt(150, 270, YELLOW(255), d3dMenu, strFov.c_str());
		}
	}


	//Misc Menu
	if (!bEspMenu && !bAimbotMenu)
	{
		UpDownIndex == 13 ? draw->DrawTxt(5, 75, YELLOW(255), d3dMenu, "Misc Selection") : draw->DrawTxt(5, 75, WHITE(255), d3dMenu, "Misc Selection");
		bMiscMenu ? draw->DrawTxt(250, 75, RED(255), d3dMenu, "[-]") : draw->DrawTxt(250, 75, LAWNGREEN(255), d3dMenu, "[+]");
		if (bMiscMenu)
		{
			//FOV
			UpDownIndex == 14 ? draw->DrawTxt(5, 95, YELLOW(255), d3dMenu, "FOV") : draw->DrawTxt(5, 95, WHITE(255), d3dMenu, "FOV");
			std::stringstream ss;
			ss << playerFov;
			draw->DrawTxt(150, 95, CYAN(255), d3dMenu, ss.str().c_str());

			UpDownIndex == 15 ? draw->DrawTxt(5, 115, YELLOW(255), d3dMenu, "Recoil Crosshair") : draw->DrawTxt(5, 115, WHITE(255), d3dMenu, "Recoil Crosshair");
			bCross ? draw->DrawTxt(150, 115, GREEN(255), d3dMenu, "ON") : draw->DrawTxt(150, 115, RED(255), d3dMenu, "OFF");

			UpDownIndex == 16 ? draw->DrawTxt(5, 135, YELLOW(255), d3dMenu, "Player Chams") : draw->DrawTxt(5, 135, WHITE(255), d3dMenu, "Player Chams");
			switch (index[3])
			{
			case 0:
				draw->DrawTxt(150, 135, RED(255), d3dMenu, "OFF");
				break;
			case 1:
				draw->DrawTxt(150, 135, BLUE(255), d3dMenu, "Team");
				break;
			case 2:
				draw->DrawTxt(150, 135, DARKORANGE(255), d3dMenu, "Enemy");
				break;
			case 3:
				draw->DrawTxt(150, 135, LAWNGREEN(255), d3dMenu, "All");
				break;
			}
		}		
	}
	else if (!bEspMenu && bAimbotMenu)
	{
		UpDownIndex == 13 ? draw->DrawTxt(5, 155, YELLOW(255), d3dMenu, "Misc Selection") : draw->DrawTxt(5, 155, WHITE(255), d3dMenu, "Misc Selection");
		bMiscMenu ? draw->DrawTxt(250, 155, RED(255), d3dMenu, "[-]") : draw->DrawTxt(250, 155, LAWNGREEN(255), d3dMenu, "[+]");
		if (bMiscMenu)
		{
			//FOV
			UpDownIndex == 14 ? draw->DrawTxt(5, 175, YELLOW(255), d3dMenu, "FOV") : draw->DrawTxt(5, 175, WHITE(255), d3dMenu, "FOV");
			std::stringstream ss;
			ss << playerFov;
			draw->DrawTxt(150, 175, CYAN(255), d3dMenu, ss.str().c_str());

			UpDownIndex == 15 ? draw->DrawTxt(5, 195, YELLOW(255), d3dMenu, "Recoil Crosshair") : draw->DrawTxt(5, 195, WHITE(255), d3dMenu, "Recoil Crosshair");
			bCross ? draw->DrawTxt(150, 195, GREEN(255), d3dMenu, "ON") : draw->DrawTxt(150, 195, RED(255), d3dMenu, "OFF");

			UpDownIndex == 16 ? draw->DrawTxt(5, 215, YELLOW(255), d3dMenu, "Player Chams") : draw->DrawTxt(5, 215, WHITE(255), d3dMenu, "Player Chams");
			switch (index[3])
			{
			case 0:
				draw->DrawTxt(150, 215, RED(255), d3dMenu, "OFF");
				break;
			case 1:
				draw->DrawTxt(150, 215, BLUE(255), d3dMenu, "Team");
				break;
			case 2:
				draw->DrawTxt(150, 215, DARKORANGE(255), d3dMenu, "Enemy");
				break;
			case 3:
				draw->DrawTxt(150, 215, LAWNGREEN(255), d3dMenu, "All");
				break;
			}
		}
	}
	else if (bEspMenu && !bAimbotMenu)
	{
		UpDownIndex == 13 ? draw->DrawTxt(5, 225, YELLOW(255), d3dMenu, "Misc Selection") : draw->DrawTxt(5, 225, WHITE(255), d3dMenu, "Misc Selection");
		bMiscMenu ? draw->DrawTxt(250, 225, RED(255), d3dMenu, "[-]") : draw->DrawTxt(250, 225, LAWNGREEN(255), d3dMenu, "[+]");
		if (bMiscMenu)
		{
			//FOV
			UpDownIndex == 14 ? draw->DrawTxt(5, 255, YELLOW(255), d3dMenu, "FOV") : draw->DrawTxt(5, 255, WHITE(255), d3dMenu, "FOV");
			std::stringstream ss;
			ss << playerFov;
			draw->DrawTxt(150, 255, CYAN(255), d3dMenu, ss.str().c_str());

			UpDownIndex == 15 ? draw->DrawTxt(5, 275, YELLOW(255), d3dMenu, "Recoil Crosshair") : draw->DrawTxt(5, 275, WHITE(255), d3dMenu, "Recoil Crosshair");
			bCross ? draw->DrawTxt(150, 275, GREEN(255), d3dMenu, "ON") : draw->DrawTxt(150, 275, RED(255), d3dMenu, "OFF");

			UpDownIndex == 16 ? draw->DrawTxt(5, 295, YELLOW(255), d3dMenu, "Player Chams") : draw->DrawTxt(5, 295, WHITE(255), d3dMenu, "Player Chams");
			switch (index[3])
			{
			case 0:
				draw->DrawTxt(150, 295, RED(255), d3dMenu, "OFF");
				break;
			case 1:
				draw->DrawTxt(150, 295, BLUE(255), d3dMenu, "Team");
				break;
			case 2:
				draw->DrawTxt(150, 295, DARKORANGE(255), d3dMenu, "Enemy");
				break;
			case 3:
				draw->DrawTxt(150, 295, LAWNGREEN(255), d3dMenu, "All");
				break;
			}
		}
	}
	else //All Menus opend
 	{
		UpDownIndex == 13 ? draw->DrawTxt(5, 295, YELLOW(255), d3dMenu, "Misc Selection") : draw->DrawTxt(5, 295, WHITE(255), d3dMenu, "Misc Selection");
		bMiscMenu ? draw->DrawTxt(250, 295, RED(255), d3dMenu, "[-]") : draw->DrawTxt(250, 295, LAWNGREEN(255), d3dMenu, "[+]");
		if (bMiscMenu)
		{
			//FOV
			UpDownIndex == 14 ? draw->DrawTxt(5, 315, YELLOW(255), d3dMenu, "FOV") : draw->DrawTxt(5, 315, WHITE(255), d3dMenu, "FOV");
			std::stringstream ss;
			ss << playerFov;
			draw->DrawTxt(150, 315, CYAN(255), d3dMenu, ss.str().c_str());

			UpDownIndex == 15 ? draw->DrawTxt(5, 335, YELLOW(255), d3dMenu, "Recoil Crosshair") : draw->DrawTxt(5, 335, WHITE(255), d3dMenu, "Recoil Crosshair");
			bCross ? draw->DrawTxt(150, 335, GREEN(255), d3dMenu, "ON") : draw->DrawTxt(150, 335, RED(255), d3dMenu, "OFF");

			UpDownIndex == 16 ? draw->DrawTxt(5, 355, YELLOW(255), d3dMenu, "Player Chams") : draw->DrawTxt(5, 355, WHITE(255), d3dMenu, "Player Chams");
			switch (index[3])
			{
			case 0:
				draw->DrawTxt(150, 355, RED(255), d3dMenu, "OFF");
				break;
			case 1:
				draw->DrawTxt(150, 355, BLUE(255), d3dMenu, "Team");
				break;
			case 2:
				draw->DrawTxt(150, 355, DARKORANGE(255), d3dMenu, "Enemy");
				break;
			case 3:
				draw->DrawTxt(150, 355, LAWNGREEN(255), d3dMenu, "All");
				break;
			}	
		}
	}
}


Player* Hack::GetCrosshairEnt()
{
	int closerEntityIndex = -1;
	float closestDistance = 360.f;

	LocalPlayer* myPlayer = LocalPlayer::Get();

	for (int i = 0; i <= *Player::GetMaxEntitys(); i++)
	{
		Player* entAim = Hack::GetEnt(i);
		//ent check
		if (!entAim->EntCheck())
			continue;

		//Team Check
		if (*entAim->GetTeam() == *myPlayer->GetTeam())
			continue;

		Vec3 currentHeadPos3D = *entAim->GetBonePos(8);
		Vec2 currentHeadPos2D = { 0 };

		if (W2S(currentHeadPos3D, currentHeadPos2D))
		{
			//Get closest player to crosshair
			Vec2 entVector = { 0 };
			entVector.x = static_cast<float>(currentHeadPos2D.x - (ScreenWidth / 2));
			entVector.y = static_cast<float>(currentHeadPos2D.y - (ScreenHeight / 2));

			float deltaLen = sqrt(entVector.x * entVector.x + entVector.y * entVector.y);
			if (deltaLen < closestDistance && deltaLen < fov)
			{
				closestDistance = deltaLen;
				closerEntityIndex = i;
			}
		}
	}

	if (closerEntityIndex == -1)
		return nullptr;
	
	return Hack::GetEnt(closerEntityIndex);
}

void Hack::Aimbot()
{
	LocalPlayer* myPlayer = LocalPlayer::Get();
	Player* entAim = GetCrosshairEnt();
	float pitch, yaw;

	if (!entAim)
		return;

	Vec3* viewAngles = (Vec3*)(*(uintptr_t*)(*sig_ClientState) + hazedumper::signatures::dwClientState_ViewAngles);

	Vec3 originPos = *myPlayer->GetOrigin();
	Vec3 viewOffset = *myPlayer->GetViewOffset();

	//Calculate Local Player View Angle Postition
	Vec3 myPos = { originPos.x + viewOffset.x, originPos.y + viewOffset.y, originPos.z + viewOffset.z };

	//Calculate View Angles Vector to Entity Bone Position
	Vec3 entBonePos = *entAim->GetBonePos(bone);
	Vec3 deltaVec = { entBonePos.x - myPos.x, entBonePos.y - myPos.y, entBonePos.z - myPos.z };

	//Calculate Hypotenuse
	float deltaLen = sqrt(deltaVec.x * deltaVec.x + deltaVec.y * deltaVec.y + deltaVec.z * deltaVec.z);

	//Calculate pitch angle and transform it into degrees
	pitch = -asin(deltaVec.z / deltaLen) * (180 / PI); //(-90°,90°), G/H

	//Calculate yaw angle and transform it into degrees
	yaw = atan2(deltaVec.y, deltaVec.x) * (180 / PI); //(-180°, 180°), G/A

	if (bAimOnFire)
	{
		if (!*myPlayer->GetAttack())
			return;
	}

	if (pitch > -89.f && pitch < 89.f && yaw > -180.f && yaw < 180.f)
	{
		if (aimSpeed == 1) //No smooth
		{
			viewAngles->x = pitch;
			viewAngles->y = yaw;
			return;
		}

		//Store current pitch/yaw
		float newPitch = viewAngles->x;
		float newYaw = viewAngles->y;

		//Diff pitch yaw
		float diffPitch = pitch - newPitch;
		float diffYaw = yaw - newYaw;

		//Add smoothed angles
		newPitch += static_cast<float>(diffPitch / aimSpeed);
		newYaw += static_cast<float>(diffYaw / aimSpeed);

		//Set view angles
		viewAngles->x = newPitch;
		viewAngles->y = newYaw;
	}	
}

Player* Hack::GetEnt(int index)
{
	uintptr_t* pEnt = (uintptr_t*)(clientMod + hazedumper::signatures::dwEntityList + (index * 0x10));
	uintptr_t* lclPlayer = reinterpret_cast<uintptr_t*>(LocalPlayer::Get());

	if (!pEnt || !*pEnt)
		return nullptr;

	//Check if ent is our player
	if (pEnt == lclPlayer || *pEnt == *lclPlayer)
		return nullptr;

	return (Player*)pEnt;
}

void Hack::ResetChams()
{
	//Player Chams
	for (int i = 0; i < *Player::GetMaxEntitys(); i++)
	{
		Player* ent = Hack::GetEnt(i);
		LocalPlayer* myPlayer = LocalPlayer::Get();

		if (!ent->EntCheck())
			continue;

		//Get Team
		bool bIsMyTeam = false;
		if (*myPlayer->GetTeam() == *ent->GetTeam())
			bIsMyTeam = true;

		if (!bChamsTeam)
		{
			if (bIsMyTeam)
				ent->DeleteChams(oChamsTeam, oldXoredTeam);
		}

		if (!bChamsEnemy)
		{
			if (!bIsMyTeam)
				ent->DeleteChams(oChamsEnemy, oldXoredEnemy);
		}
	}
}

void Hack::InitChams()
{
	bool bIsInitEnemy = false;
	bool bIsInitTeam = false;

	for (int i = 0; i < *Player::GetMaxEntitys(); i++)
	{
		Player* ent = Hack::GetEnt(i);
		LocalPlayer* myPlayer = LocalPlayer::Get();

		if (!ent->EntCheck())
			continue;

		//Get Team
		bool bIsMyTeam = false;
		if (*myPlayer->GetTeam() == *ent->GetTeam())
			bIsMyTeam = true;

		if (bIsInitEnemy && bIsInitTeam)
		{
			bChamsInitialized = true;
			return;
		}

		//Save old player model data (color & brightness)
		if (!bChamsInitialized)
		{
			if (bIsMyTeam)
			{
				oChamsTeam = *ent->SaveChams(&oldXoredTeam);
				bIsInitTeam = true;
			}
			else
			{
				oChamsEnemy = *ent->SaveChams(&oldXoredEnemy);
				bIsInitEnemy = true;
			}
		}
	}
}


void Hack::Chams()
{
	//Modified Data
	Vec3 chamsTeam = { 0.f, 0.f, 255.f };
	Vec3 chamsEnemy = { 255.f, 0.f, 0.f };

	//Player Chams
	for (int i = 0; i < *Player::GetMaxEntitys(); i++)
	{
		Player* ent = Hack::GetEnt(i);
		LocalPlayer* myPlayer = LocalPlayer::Get();

		if (!ent->EntCheck())
			continue;

		//Get Team
		bool bIsMyTeam = false;
		if (*myPlayer->GetTeam() == *ent->GetTeam())
			bIsMyTeam = true;		

		if (bChamsTeam)
		{
			if(bIsMyTeam)
				ent->SetChams(chamsTeam, 10.f);
		}

		if (bChamsEnemy)
		{
			if(!bIsMyTeam)
				ent->SetChams(chamsEnemy, 10.f);
		}
	}
}

void Hack::ESP()
{
	//Local Player
	LocalPlayer* myPlayer = LocalPlayer::Get();
	Player* ent = NULL;

	for (int i = 0; i < *Player::GetMaxEntitys(); i++)
	{
		ent = Hack::GetEnt(i);
		Vec2 entPos2D = { 0 }, entHead2D = { 0 };

		if (!ent->EntCheck())
			continue;

		if (bTeam && !bEnemy)
		{
			if (*ent->GetTeam() != *myPlayer->GetTeam())
				continue;
		}

		 if(bEnemy && !bTeam)
		{
			 if (*ent->GetTeam() == *myPlayer->GetTeam())
				continue;
		}

		if (W2S(*ent->GetOrigin(), entPos2D) && W2S(*ent->GetBonePos(8), entHead2D))
		{
			bool team = false;
			int height = entPos2D.y - entHead2D.y;
			int width = height / 2;
			int boxPosX = width / 2;
			int sEspWidth = height / 3;

			//Team Check
			if (*ent->GetTeam() == *myPlayer->GetTeam())
				team = true;
			else
				team = false;

			//2D Box
			if (bBox)
			{
				if(team)
					draw->DrawBox(entPos2D.x - boxPosX, entHead2D.y, width, height, DEEPSKYBLUE(255));
				else
					draw->DrawBox(entPos2D.x - boxPosX, entHead2D.y, width, height, PINK(255));
			}

			if (bSnap)
			{
				if (team)
					draw->DrawLine(ScreenWidth / 2, ScreenHeight / 2, entHead2D.x, entHead2D.y, 1.f, DEEPSKYBLUE(255));
				else
					draw->DrawLine(ScreenWidth / 2, ScreenHeight / 2, entHead2D.x, entHead2D.y, 1.f, PINK(255));
			}

			if (bHead)
			{
				if (team)
					draw->DrawCircle(entHead2D.x, entHead2D.y, height / 7, 30, DEEPSKYBLUE(255));
				else
					draw->DrawCircle(entHead2D.x, entHead2D.y, height / 7, 30, PINK(255));
			}

			if (bBarrel)
			{
				//Get Entity ViewAngles
				Vec2 entViewAngles = *ent->GetViewAngles();

				//Angles to Radians		
				entViewAngles.x = static_cast<float>(entViewAngles.x * (PI / 180));
				entViewAngles.y = static_cast<float>(entViewAngles.y * (PI / 180));

				//dir vec
				float sinPitch = sin(entViewAngles.y);
				float cosPitch = cos(entViewAngles.y);
				float sinYaw = sin(entViewAngles.x);
				float cosYaw = cos(entViewAngles.x);

				Vec3 dir = { 0 };
				dir.x = cosYaw * cosPitch;
				dir.y = cosYaw * sinPitch;
				dir.z = -sinYaw;

				Vec3 trailEnd, headPos;
				Vec2 screenTrail, startTrail;

				headPos = *ent->GetBonePos(8);

				const float len = 50.f;
				Vec3 trail{ dir.x * len, dir.y * len, dir.z * len };
				trailEnd = { trail.x + headPos.x , trail.y + headPos.y, +trail.z + headPos.z };

				if (W2S(trailEnd, screenTrail) && W2S(headPos, startTrail))
				{
					if(team)
						draw->DrawLine(startTrail.x, startTrail.y, screenTrail.x, screenTrail.y, 1.f, DEEPSKYBLUE(255));
					else
						draw->DrawLine(startTrail.x, startTrail.y, screenTrail.x, screenTrail.y, 1.f, PINK(255));

					draw->FillRectangle(screenTrail.x, screenTrail.y, 3.f, 3.f, LAWNGREEN(255));
				}
			}

			if (bHealth) 
			{
				int entHealth = *ent->GetHealth();
				float healthPercent = static_cast<float>(entHealth / 100.f);
				float barHeight = (entPos2D.y - entHead2D.y) * healthPercent;

				draw->DrawLine(entPos2D.x + (width / 1.9), entPos2D.y, entPos2D.x + (width / 1.9), (entPos2D.y - barHeight), 3.5f, GREEN(255));
			}

			if (bDist)
			{
				Vec3 diffPos;
				diffPos.x = ent->GetOrigin()->x - myPlayer->GetOrigin()->x;
				diffPos.y = ent->GetOrigin()->y - myPlayer->GetOrigin()->y;
				diffPos.z = ent->GetOrigin()->z - myPlayer->GetOrigin()->z;
				int deltaLen = static_cast<int>(sqrt(diffPos.x * diffPos.x + diffPos.y * diffPos.y + diffPos.z * diffPos.z) * METERS_PER_INCH);

				std::stringstream sDist;
				sDist << deltaLen;
				std::string sDistance = sDist.str();
				sDistance.append("M");
							
				draw->DrawTxt(entPos2D.x - (width / 4.5), entPos2D.y + (width / 5), WHITE(255), d3dESP, (char*)sDistance.c_str());
			}
		}
	}
}


bool Hack::W2S(Vec3 pos, Vec2& screen)
{
	Vec4 clipCords;
	clipCords.x = pos.x * vMatrix[0] + pos.y * vMatrix[1] + pos.z * vMatrix[2] + vMatrix[3];
	clipCords.y = pos.x * vMatrix[4] + pos.y * vMatrix[5] + pos.z * vMatrix[6] + vMatrix[7];
	clipCords.z = pos.x * vMatrix[8] + pos.y * vMatrix[9] + pos.z * vMatrix[10] + vMatrix[11];
	clipCords.w = pos.x * vMatrix[12] + pos.y * vMatrix[13] + pos.z * vMatrix[14] + vMatrix[15];

	if (clipCords.w < 0.1f)
		return false;

	Vec3 NDC;
	NDC.x = clipCords.x / clipCords.w;
	NDC.y = clipCords.y / clipCords.w;
	NDC.z = clipCords.z / clipCords.w;

	screen.x = (ScreenWidth / 2 * NDC.x) + (NDC.x + ScreenWidth / 2);
	screen.y = -(ScreenHeight / 2 * NDC.y) + (NDC.y + ScreenHeight / 2);
	return true;
}


void Hack::UpdateMatrix()
{
	memcpy(&vMatrix, (PBYTE*)(clientMod + hazedumper::signatures::dwViewMatrix), sizeof(vMatrix));
}