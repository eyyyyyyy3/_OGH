#pragma once
#include "ENUMS.h"

class InputSystem
{
public:

	void EnableInput(bool bEnable);


	bool IsButtonDown(ButtonCode_t code);


	int GetAnalogValue(AnalogCode_t code);


	void ResetInputState();


	const char* ButtonCodeToString(ButtonCode_t code);


	ButtonCode_t VirtualKeyToButtonCode(int nVirtualKey);
	

	int ButtonCodeToVirtualKey(ButtonCode_t code);

	void GetCursorPosition(int* m_pX, int* m_pY);

};