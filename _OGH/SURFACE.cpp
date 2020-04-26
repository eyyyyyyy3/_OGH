#pragma once

#include "SURFACE.h"
#include "Memory.h"

void Surface::DrawSetColor(Color col)
{
	typedef void(__thiscall* oDrawSetColor)(PVOID, Color);
	return memory.GetVTableFunction<oDrawSetColor>((uintptr_t)this, 14)(this, col);
}

void Surface::DrawSetColor(int r, int g, int b, int a)
{
	typedef void(__thiscall* OriginalFn)(PVOID, int, int, int, int);
	memory.GetVTableFunction<OriginalFn>((uintptr_t)this, 15)(this, r, g, b, a);
}

void Surface::DrawFilledRect(int x0, int y0, int x1, int y1)
{
	typedef void(__thiscall* OriginalFn)(PVOID, int, int, int, int);
	memory.GetVTableFunction<OriginalFn>((uintptr_t)this, 16)(this, x0, y0, x1, y1);
}

void Surface::DrawOutlinedRect(int x0, int y0, int x1, int y1)
{
	typedef void(__thiscall* OriginalFn)(PVOID, int, int, int, int);
	memory.GetVTableFunction<OriginalFn>((uintptr_t)this, 18)(this, x0, y0, x1, y1);
}

void Surface::DrawLine(int x0, int y0, int x1, int y1)
{
	typedef void(__thiscall* OriginalFn)(PVOID, int, int, int, int);
	memory.GetVTableFunction<OriginalFn>((uintptr_t)this, 19)(this, x0, y0, x1, y1);
}

void Surface::DrawPolyLine(int* x, int* y, int count)
{
	typedef void(__thiscall* OriginalFn)(PVOID, int*, int*, int);
	memory.GetVTableFunction<OriginalFn>((uintptr_t)this, 19 + 1)(this, x, y, count);
}

void Surface::DrawSetTextFont(unsigned long font)
{
	typedef void(__thiscall* OriginalFn)(PVOID, unsigned long);
	memory.GetVTableFunction<OriginalFn>((uintptr_t)this, 23)(this, font);
}

void Surface::DrawSetTextColor(int r, int g, int b, int a)
{
	typedef void(__thiscall* OriginalFn)(PVOID, int, int, int, int);
	memory.GetVTableFunction<OriginalFn>((uintptr_t)this, 25)(this, r, g, b, a);
}

void Surface::DrawSetTextColor(Color col)
{
	typedef void(__thiscall* oDrawSetTextColor)(PVOID, Color);
	return memory.GetVTableFunction<oDrawSetTextColor>((uintptr_t)this, 24)(this, col);
}

void Surface::DrawSetTextPos(int x, int y)
{
	typedef void(__thiscall* OriginalFn)(PVOID, int, int);
	memory.GetVTableFunction<OriginalFn>((uintptr_t)this, 26)(this, x, y);
}

void Surface::DrawPrintText(const wchar_t* text, int textLen)
{
	typedef void(__thiscall* OriginalFn)(PVOID, const wchar_t*, int, int);
	memory.GetVTableFunction<OriginalFn>((uintptr_t)this, 28)(this, text, textLen, 0);
}

void Surface::DrawSetTexture(int textureID)
{
	typedef void(__thiscall* oDrawSetTextColor)(PVOID, int);
	return memory.GetVTableFunction<oDrawSetTextColor>((uintptr_t)this, 38)(this, textureID);
}

void Surface::DrawTexturedRect(int x0, int y0, int x1, int y1)
{
	typedef void(__thiscall* oDrawSetTextColor)(PVOID, int, int, int, int);
	return memory.GetVTableFunction<oDrawSetTextColor>((uintptr_t)this, 37 + 4)(this, x0, y0, x1, y1);
}

bool Surface::IsTextureIDValid(int textureID)
{
	typedef bool(__thiscall* oDrawSetTextColor)(PVOID, int);
	return memory.GetVTableFunction<oDrawSetTextColor>((uintptr_t)this, 37 + 5)(this, textureID);
}

void Surface::DrawSetTextureRGBA(int textureID, unsigned char const* colors, int w, int h)
{
	typedef void(__thiscall* oDrawSetTextColor)(PVOID, int, unsigned char const*, int, int);
	return memory.GetVTableFunction<oDrawSetTextColor>((uintptr_t)this, 37)(this, textureID, colors, w, h);
}

int Surface::CreateNewTextureID(bool procedural)
{
	typedef int(__thiscall* oDrawSetTextColor)(PVOID, bool);
	return memory.GetVTableFunction<oDrawSetTextColor>((uintptr_t)this, 43)(this, procedural);
}

void Surface::DrawTexturedPolygon(int vtxCount, Vertex_t* vtx, bool bClipVertices)
{
	typedef void(__thiscall* oDrawSetTextColor)(PVOID, int, Vertex_t*, bool);
	return memory.GetVTableFunction<oDrawSetTextColor>((uintptr_t)this, 106)(this, vtxCount, vtx, bClipVertices);
}

unsigned long Surface::FontCreate()
{
	typedef unsigned int(__thiscall* OriginalFn)(PVOID);
	return memory.GetVTableFunction<OriginalFn>((uintptr_t)this, 71)(this);
}

void Surface::SetFontGlyphSet(unsigned long font, const char* windowsFontName, int tall, int weight, int blur, int scanlines, int flags)
{
	typedef void(__thiscall* OriginalFn)(PVOID, unsigned long, const char*, int, int, int, int, int, int, int);
	memory.GetVTableFunction<OriginalFn>((uintptr_t)this, 72)(this, font, windowsFontName, tall, weight, blur, scanlines, flags, 0, 0);
}

void Surface::GetTextSize(unsigned long font, const wchar_t* text, int& wide, int& tall)
{
	typedef void(__thiscall* OriginalFn)(PVOID, unsigned long, const wchar_t*, int&, int&);
	memory.GetVTableFunction< OriginalFn >((uintptr_t)this, 79)(this, font, text, wide, tall);
}

void Surface::DrawOutlinedCircle(int x, int y, int r, int seg)
{
	typedef void(__thiscall* oDrawOutlinedCircle)(PVOID, int, int, int, int);
	return memory.GetVTableFunction<oDrawOutlinedCircle>((uintptr_t)this, 103)(this, x, y, r, seg);
}

void Surface::DrawFilledCircle(int x, int y, int r, int seg)
{
	typedef void(__thiscall* OriginalFn)(PVOID, int, int, int, int);
	return memory.GetVTableFunction<OriginalFn>((uintptr_t)this, 103)(this, x, y, r, seg);
}

void Surface::UnlockCursor()
{
	typedef void(__thiscall* oUnlockCrsor)(PVOID);
	return memory.GetVTableFunction<oUnlockCrsor>((uintptr_t)this, 66)(this);
}

void Surface::LockCursor()
{
	typedef void(__thiscall* oLockCrsor)(PVOID);
	return memory.GetVTableFunction<oLockCrsor>((uintptr_t)this, 67)(this);
}
