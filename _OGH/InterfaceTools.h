#pragma once
#include <Windows.h>

typedef void* (*oInterface)(char*, int);

struct InterfaceTools
{
public:
	void* GetInterface(char* moudleName, char* interfaceName);

	void* GetExport(const char* module_name, const char* export_name);
};
 extern InterfaceTools* newInterface;