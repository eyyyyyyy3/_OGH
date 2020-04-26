#include "InterfaceTools.h"

void* InterfaceTools::GetInterface(char* moudleName, char* interfaceName)
{
	oInterface original = (oInterface)GetProcAddress(GetModuleHandleA(moudleName), "CreateInterface");

	return (void*)original(interfaceName, 0);
}

void* InterfaceTools::GetExport(const char* module_name, const char* export_name)
{
	HMODULE mod;
	while (!((mod = GetModuleHandleA(module_name))))
		Sleep(100);

	return reinterpret_cast<void*>(GetProcAddress(mod, export_name));
}

InterfaceTools* newInterface = new InterfaceTools;