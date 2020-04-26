#include "INPUTSYSTEM.h"
#include "Memory.h"
void InputSystem::EnableInput(bool bEnable)
{
	typedef void(__thiscall* oEnableInput)(void*, bool);
	return memory.GetVTableFunction<oEnableInput>((uintptr_t)this, 11)(this, bEnable);
}

bool InputSystem::IsButtonDown(ButtonCode_t code)
{
	typedef bool(__thiscall* oIsButtonDown)(void*, ButtonCode_t);
	return memory.GetVTableFunction<oIsButtonDown>((uintptr_t)this, 15)(this, code);
}

int InputSystem::GetAnalogValue(AnalogCode_t code)
{
	typedef int(__thiscall* oGetAnalogValue)(void*, AnalogCode_t);
	return memory.GetVTableFunction<oGetAnalogValue>((uintptr_t)this, 18)(this, code);
}

void InputSystem::ResetInputState()
{
	typedef void(__thiscall* oResetInputState)(void*);
	return memory.GetVTableFunction<oResetInputState>((uintptr_t)this, 39)(this);
}

const char* InputSystem::ButtonCodeToString(ButtonCode_t code)
{
	typedef const char* (__thiscall* oButtonCodeToString)(void*, ButtonCode_t);
	return memory.GetVTableFunction<oButtonCodeToString>((uintptr_t)this, 40)(this, code);
}

ButtonCode_t InputSystem::VirtualKeyToButtonCode(int nVirtualKey)
{
	typedef ButtonCode_t(__thiscall* oVirtualKeyToButtonCode)(void*, int);
	return memory.GetVTableFunction<oVirtualKeyToButtonCode>((uintptr_t)this, 45)(this, nVirtualKey);
}

int InputSystem::ButtonCodeToVirtualKey(ButtonCode_t code)
{
	typedef ButtonCode_t(__thiscall* oVirtualKeyToButtonCode)(void*, ButtonCode_t);
	return memory.GetVTableFunction<oVirtualKeyToButtonCode>((uintptr_t)this, 46)(this, code);
}

void InputSystem::GetCursorPosition(int* m_pX, int* m_pY)
{
	typedef void(__thiscall* oGetCursorPosition)(void*, int*, int*);
	return memory.GetVTableFunction<oGetCursorPosition>((uintptr_t)this, 56)(this, m_pX, m_pY);
}