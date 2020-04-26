#pragma once
#include "APPSYSTEM.h"
#include "COLOR.h"
#include "VECTOR2D.h"

namespace vgui
{
	typedef unsigned long HFont;
	typedef unsigned int VPANEL;
};

struct IntRect
{
	int x0;
	int y0;
	int x1;
	int y1;
};

enum FontDrawType
{
	FONT_DRAW_DEFAULT = 0,
	FONT_DRAW_NONADDITIVE,
	FONT_DRAW_ADDITIVE,
	FONT_DRAW_TYPE_COUNT = 2,
};

struct Vertex_t
{
	Vertex_t() {}
	Vertex_t(const Vector2D& pos, const Vector2D& coord = Vector2D(0, 0))
	{
		m_Position = pos;
		m_TexCoord = coord;
	}
	void Init(const Vector2D& pos, const Vector2D& coord = Vector2D(0, 0))
	{
		m_Position = pos;
		m_TexCoord = coord;
	}

	Vector2D m_Position;
	Vector2D m_TexCoord;
};


class Surface {
public:
	void DrawSetColor(Color col);
	
	void DrawSetColor(int r, int g, int b, int a);


	void DrawFilledRect(int x0, int y0, int x1, int y1);
	

	void DrawOutlinedRect(int x0, int y0, int x1, int y1);


	void DrawLine(int x0, int y0, int x1, int y1);


	void DrawPolyLine(int* x, int* y, int count);


	void DrawSetTextFont(unsigned long font);
	

	void DrawSetTextColor(int r, int g, int b, int a);


	void DrawSetTextColor(Color col);


	void DrawSetTextPos(int x, int y);


	void DrawPrintText(const wchar_t* text, int textLen);


	void DrawSetTexture(int textureID);


	void DrawTexturedRect(int x0, int y0, int x1, int y1);


	bool IsTextureIDValid(int textureID);


	void DrawSetTextureRGBA(int textureID, unsigned char const* colors, int w, int h);


	int CreateNewTextureID(bool procedural);


	void DrawTexturedPolygon(int vtxCount, Vertex_t* vtx, bool bClipVertices = true);


	unsigned long FontCreate();


	void SetFontGlyphSet(unsigned long font, const char* windowsFontName, int tall, int weight, int blur, int scanlines, int flags);


	void GetTextSize(unsigned long font, const wchar_t* text, int& wide, int& tall);


	void DrawOutlinedCircle(int x, int y, int r, int seg);


	void DrawFilledCircle(int x, int y, int r, int seg);

	void UnlockCursor();

	void LockCursor();
};

