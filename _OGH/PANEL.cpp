#include "PANEL.h"
#include "Memory.h"

const char* Panel::GetName(unsigned int Panel)
{
	typedef const char* (__thiscall* OriginalFn)(void*, unsigned int);
	return memory.GetVTableFunction<OriginalFn>((uintptr_t)this, 36)(this, Panel);
}
