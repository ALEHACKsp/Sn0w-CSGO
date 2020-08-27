#include "Includes.h"

extern Hack* pHack;
extern LPDIRECT3DDEVICE9 pDevice;

//Draw Functions
void Draw::FillArea(float x, float y, float width, float height, D3DCOLOR color)
{
	D3DXVECTOR2 vectorLine[2];
	pHack->d3dLine->SetWidth(width);

	vectorLine[0].x = x + width / 2;
	vectorLine[0].y = y;
	vectorLine[1].x = x + width / 2;
	vectorLine[1].y = y + height;

	pHack->d3dLine->Draw(vectorLine, 2, color);
}

void Draw::FillRectangle(double x, double y, double w, double h, D3DCOLOR color)
{
	struct Vertex
	{
		float x, y, z, h;
		D3DCOLOR color;
	};

	Vertex vertices[4] =
	{
		x,  y, 0.0f, 1.0f, color,
		x + w, y, 0.0f, 1.0f, color,

		x + w, y + h, 0.0f, 1.0f, color,
		x,  y + h, 0.0f, 1.0f, color,
	};

	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	pDevice->SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE);
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, vertices, sizeof(Vertex));
}

void Draw::DrawBox(float x, float y, float width, float height, D3DCOLOR color)
{
	D3DXVECTOR2 points[5];
	points[0] = D3DXVECTOR2(x, y); //bottom left
	points[1] = D3DXVECTOR2(x + width, y); //bottom right
	points[2] = D3DXVECTOR2(x + width, y + height); //top right
	points[3] = D3DXVECTOR2(x, y + height); //top left
	points[4] = D3DXVECTOR2(x, y); //connection between top left and bottom left
	pHack->d3dLine->SetWidth(1);
	pHack->d3dLine->Draw(points, 5, color);
}

void Draw::DrawLine(float x1, float y1, float x2, float y2, FLOAT width, DWORD color)
{
	D3DXVECTOR2 points[2];
	points[0] = D3DXVECTOR2(x1, y1);
	points[1] = D3DXVECTOR2(x2, y2);
	pHack->d3dLine->SetWidth(width);
	pHack->d3dLine->Draw(points, 2, color);
}


void Draw::DrawTxt(int x, int y, DWORD color, LPD3DXFONT g_pFont, const char* fmt, ...)
{
	char buf[1024] = { 0 };
	va_list va_alist;
	RECT FontPos = { x, y, x + 120, y + 16 };
	va_start(va_alist, fmt);
	vsprintf_s(buf, fmt, va_alist);
	va_end(va_alist);
	g_pFont->DrawTextA(NULL, buf, -1, &FontPos, DT_NOCLIP, color);
}

void Draw::DrawCircle(int X, int Y, int radius, int numSides, DWORD color)
{
	D3DXVECTOR2 Line[128];
	if (numSides <= 0)
		numSides = 1;
	float Step = PI * 2.0 / numSides;
	int Count = 0;
	for (float a = 0; a < PI * 2.0; a += Step)
	{
		float X1 = radius * cos(a) + X;
		float Y1 = radius * sin(a) + Y;
		float X2 = radius * cos(a + Step) + X;
		float Y2 = radius * sin(a + Step) + Y;
		Line[Count].x = X1;
		Line[Count].y = Y1;
		Line[Count + 1].x = X2;
		Line[Count + 1].y = Y2;
		Count += 2;
	}
	pHack->d3dLine->SetWidth(1);
	pHack->d3dLine->Draw(Line, Count, color);
}
