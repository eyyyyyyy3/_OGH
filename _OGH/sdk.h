#pragma once
#include "imgui.h"
#include "imgui_impl_dx9.h"

//CLASSES

#include "GAMEEVENTMANAGER.h"

#include <d3d9.h>
#include <d3dx9.h>
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
IDirect3DDevice9* d3d9device;

#include "SURFACE.h"
Surface* surf;

#include "INPUTSYSTEM.h"
InputSystem* inputsys;

#include "ENGINE.h"
Engine* eng;

#include "BASEENTITY.h"
BaseEntity* me;

#include "BASECLIENTDLL.h"
BaseClientDLL* clientModeInterface;

#include "CLIENTMODE.h"
ClientMode* clientMode;

#include "USERCMD.h"
Input::UserCmd* cmd;
Input* g_Input;

#include "CLIENTENTITYLIST.h"
ClientEntityList* entlist;

#include "PANEL.h"
Panel* panel;
