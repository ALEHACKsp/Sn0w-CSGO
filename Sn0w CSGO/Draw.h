#pragma once
#define PI	3.14159265358979323846264338327950288419716939937510
#define ABS(x) ((x < 0) ? (-x) : (x))
#define METERS_PER_INCH 0.0254f

class Draw
{
public:

	Draw(){}
	~Draw(){delete this;}

	//Draw Functions
	void FillArea(float x, float y, float width, float height, D3DCOLOR color);
	void FillRectangle(double x, double y, double w, double h, D3DCOLOR color);
	void DrawBox(float x, float y, float width, float height, D3DCOLOR color);
	void DrawLine(float x1, float y1, float x2, float y2, FLOAT width, DWORD color);
	void DrawTxt(int x, int y, DWORD color, LPD3DXFONT g_pFont, const char* fmt, ...);
	void DrawCircle(int X, int Y, int radius, int numSides, DWORD color);
};


#define WHITE(alpha)         D3DCOLOR_ARGB(alpha, 255, 255, 255)
#define BLACK(alpha)         D3DCOLOR_ARGB(alpha, 0, 0, 0)
#define RED(alpha)           D3DCOLOR_ARGB(alpha, 255, 0, 0)
#define GREEN(alpha)         D3DCOLOR_ARGB(alpha, 0, 128, 0)
#define LAWNGREEN(alpha)     D3DCOLOR_ARGB(alpha, 124, 252, 0)
#define BLUE(alpha)          D3DCOLOR_ARGB(alpha, 0, 200, 255)
#define DEEPSKYBLUE(alpha)   D3DCOLOR_ARGB(alpha, 0, 191, 255)
#define SKYBLUE(alpha)       D3DCOLOR_ARGB(alpha, 0, 122, 204)
#define YELLOW(alpha)        D3DCOLOR_ARGB(alpha, 255, 255, 0)
#define ORANGE(alpha)        D3DCOLOR_ARGB(alpha, 255, 165, 0)
#define DARKORANGE(alpha)    D3DCOLOR_ARGB(alpha, 255, 140, 0)
#define PURPLE(alpha)        D3DCOLOR_ARGB(alpha, 125, 0, 255)
#define CYAN(alpha)          D3DCOLOR_ARGB(alpha, 0, 255, 255)
#define PINK(alpha)          D3DCOLOR_ARGB(alpha, 255, 20, 147)
#define GRAY(alpha)          D3DCOLOR_ARGB(alpha, 128, 128, 128)
#define DARKGRAY(alpha)      D3DCOLOR_ARGB(alpha, 73, 73, 73)
#define DARKERGRAY(alpha)    D3DCOLOR_ARGB(alpha, 31, 31, 31)