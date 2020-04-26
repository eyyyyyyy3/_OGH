#include <iostream>
#include <Windows.h>
#include <string>
#include "utilities.h"
#include "sdk.h"
#include "OFFSETS.h"
#include "InterfaceTools.h"
#include "Memory.h"

using namespace std;

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
extern IMGUI_IMPL_API bool ImGui_ImplWin32_Init(void* hwnd);
extern IMGUI_IMPL_API void ImGui_ImplWin32_NewFrame();

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

typedef HRESULT(__stdcall* EndScene_Hook)(IDirect3DDevice9* pDevice);
EndScene_Hook oEndScene;

typedef long(__stdcall* Reset_Hook)(IDirect3DDevice9* device, D3DPRESENT_PARAMETERS* pp);
Reset_Hook oReset = nullptr;

typedef void(__thiscall* CreateMove_Hook)(BaseClientDLL*, int, float, bool);
CreateMove_Hook oCreateMove;

typedef void(__thiscall* OverrideView_Hook)(void*, ViewSetup* setup);
OverrideView_Hook oOverrideView;

typedef float(__fastcall* GetViewModelFOV_Hook)(void*);
GetViewModelFOV_Hook oGetViewModelFOV;

typedef void(__thiscall* PaintTraverse_Hook)(void*, unsigned int, bool, bool);
PaintTraverse_Hook oPaintTraverse;

typedef void(__fastcall* LockCursor_Hook)(Surface*, void*);
LockCursor_Hook oLockCursor;

typedef void(__stdcall* FrameStageNotify_Hook)(ClientFrameStage_t);
FrameStageNotify_Hook oFrameStageNotify;

typedef bool(__thiscall* FireEventClientSide_Hook)(void*, GameEvent*);
FireEventClientSide_Hook oFireEventClientSide;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam) && GetKeyState(VK_DELETE) == 1)
	{
		return 1l;
	}
	return CallWindowProc(var.oWndProc, hWnd, msg, wParam, lParam);

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

HRESULT __stdcall Hooked_EndScene(IDirect3DDevice9* pDevice) // our hooked endscene
{
	if (!var.pFont)
	{

		D3DDEVICE_CREATION_PARAMETERS d3dcp{ 0 };
		pDevice->GetCreationParameters(&d3dcp);

		ImGuiContext* ctx = ImGui::CreateContext();
		ImGui::SetCurrentContext(ctx);
		ImGuiIO& io = ImGui::GetIO();

		D3DXCreateFontA(pDevice, 12, 0, FW_DONTCARE, 0, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Arial", &var.pFont);
		io.Fonts->AddFontDefault();

		ImGui_ImplWin32_Init(d3dcp.hFocusWindow);
		ImGui_ImplDX9_Init(pDevice);

		{
			ImVec4* colors = ImGui::GetStyle().Colors;
			colors[ImGuiCol_Text] = ImVec4(0.97f, 0.61f, 0.00f, 1.00f);
			colors[ImGuiCol_TextDisabled] = ImVec4(0.06f, 0.05f, 0.00f, 1.00f);
			colors[ImGuiCol_WindowBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.70f);
			colors[ImGuiCol_ChildBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
			colors[ImGuiCol_PopupBg] = ImVec4(0.19f, 0.13f, 0.00f, 0.90f);
			colors[ImGuiCol_Border] = ImVec4(1.00f, 0.94f, 0.23f, 1.00f);
			colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
			colors[ImGuiCol_FrameBg] = ImVec4(0.19f, 0.13f, 0.00f, 0.30f);
			colors[ImGuiCol_FrameBgHovered] = ImVec4(0.47f, 0.31f, 0.00f, 0.40f);
			colors[ImGuiCol_FrameBgActive] = ImVec4(1.00f, 0.94f, 0.23f, 0.45f);
			colors[ImGuiCol_TitleBg] = ImVec4(1.00f, 0.38f, 0.00f, 0.83f);
			colors[ImGuiCol_TitleBgActive] = ImVec4(1.00f, 0.38f, 0.00f, 0.87f);
			colors[ImGuiCol_TitleBgCollapsed] = ImVec4(1.00f, 0.38f, 0.00f, 0.20f);
			colors[ImGuiCol_MenuBarBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
			colors[ImGuiCol_ScrollbarBg] = ImVec4(0.50f, 0.31f, 0.00f, 1.00f);
			colors[ImGuiCol_ScrollbarGrab] = ImVec4(1.00f, 0.38f, 0.00f, 1.00f);
			colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.97f, 0.61f, 0.00f, 1.00f);
			colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(1.00f, 0.97f, 0.21f, 0.71f);
			//colors[ImGuiCol_COUNT] = ImVec4(0.47f, 0.31f, 0.00f, 0.32f);
			colors[ImGuiCol_CheckMark] = ImVec4(0.97f, 0.61f, 0.00f, 1.00f);
			colors[ImGuiCol_SliderGrab] = ImVec4(1.00f, 0.38f, 0.00f, 1.00f);
			colors[ImGuiCol_SliderGrabActive] = ImVec4(0.97f, 0.61f, 0.00f, 1.00f);
			colors[ImGuiCol_Button] = ImVec4(0.47f, 0.31f, 0.00f, 0.60f);
			colors[ImGuiCol_ButtonHovered] = ImVec4(0.97f, 0.61f, 0.00f, 0.60f);
			colors[ImGuiCol_ButtonActive] = ImVec4(1.00f, 0.38f, 0.00f, 0.60f);
			colors[ImGuiCol_Header] = ImVec4(0.47f, 0.31f, 0.00f, 0.60f);
			colors[ImGuiCol_HeaderHovered] = ImVec4(0.97f, 0.61f, 0.00f, 0.60f);
			colors[ImGuiCol_HeaderActive] = ImVec4(1.00f, 0.38f, 0.00f, 0.60f);
			colors[ImGuiCol_Separator] = ImVec4(1.00f, 0.97f, 0.21f, 1.00f);
			colors[ImGuiCol_SeparatorHovered] = ImVec4(1.00f, 0.97f, 0.21f, 1.00f);
			colors[ImGuiCol_SeparatorActive] = ImVec4(1.00f, 0.97f, 0.21f, 1.00f);
			colors[ImGuiCol_ResizeGrip] = ImVec4(1.00f, 0.97f, 0.21f, 0.60f);
			colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.97f, 0.61f, 0.00f, 0.60f);
			colors[ImGuiCol_ResizeGripActive] = ImVec4(1.00f, 0.38f, 0.00f, 0.60f);
			colors[ImGuiCol_PlotLines] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
			colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
			colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
			colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
			colors[ImGuiCol_TextSelectedBg] = ImVec4(1.00f, 0.38f, 0.00f, 0.35f);
			colors[ImGuiCol_ModalWindowDarkening] = ImVec4(0.20f, 0.20f, 0.20f, 0.35f);
			ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 7.0f);
		}
	}
	Updater();
	if (var.Menu)
	{
		ImGui::GetIO().MouseDrawCursor = true;
		ImGui_ImplDX9_NewFrame();
		ImGui_ImplWin32_NewFrame();

		ImGui::NewFrame();

		ImGui::SetNextWindowSize(ImVec2(500, 500));
		ImGui::Begin("_OGH", &var.p_open, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoTitleBar);


		ImGui::Text("_OGH");

		ImGui::End();


		ImGui::EndFrame();
		ImGui::Render();
		ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
	}

	return oEndScene(pDevice);                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                	return oEndScene(pDevice); // call original ensdcene so the game can draw
}

HRESULT __stdcall Hooked_Reset(IDirect3DDevice9* pDevice, D3DPRESENT_PARAMETERS* pPresentationParameters)
{
	ImGui_ImplDX9_InvalidateDeviceObjects();
	ImGui_ImplDX9_CreateDeviceObjects();
	return oReset(pDevice, pPresentationParameters);
}

void __stdcall Hooked_OverrideView(ViewSetup* setup)
{
	//FOV
	oOverrideView(clientMode, setup);

}

float __fastcall Hooked_GetViewModelFOV(void* ecx, void* edx)
{
	//VFOV
	return oGetViewModelFOV(ecx);
}

void __stdcall Hooked_CreateMove(int sequence_number, float input_sample_frametime, bool active, bool& bSendPacket)
{
	oCreateMove(clientModeInterface, sequence_number, input_sample_frametime, active);

	cmd = g_Input->GetUserCmd(sequence_number);

	if (!cmd || !cmd->command_number)
		return;

	Input::VerifiedUserCmd* verified = g_Input->GetVerifiedCmd(sequence_number);

	if (!verified)
		return;

	me = (BaseEntity*)entlist->GetClientEntity(eng->GetLocalPlayer());

	//BHOP
	//TRIGGER
	//EDGE
	//STRAFE


	verified->m_cmd = *cmd;
	verified->m_crc = cmd->GetChecksum();
}

__declspec(naked) void __stdcall Hooked_CreateMovePROXY(int sequence_number, float input_sample_frametime, bool active)
{
	__asm
	{
		push ebp
		mov  ebp, esp
		push ebx
		lea  ecx, [esp]
		push ecx
		push dword ptr[active]
		push dword ptr[input_sample_frametime]
		push dword ptr[sequence_number]
		call Hooked_CreateMove
		pop  ebx
		pop  ebp
		retn 0Ch
	}
}

void __stdcall Hooked_PaintTraverse(int VGUIPanel, bool ForceRepaint, bool AllowForce)
{
	static unsigned int drawPanel;
	if (!drawPanel)
	{
		const char* panelname = panel->GetName(VGUIPanel);
		if (!strcmp(panelname, "MatSystemTopPanel"))
			drawPanel = VGUIPanel;
	}
	else if (drawPanel == VGUIPanel)
	{
		g_pRender->DrawShadowText(var.w - var.w, var.h - var.h, ImColor(0, 255, 255, 255), 31, false, (char*)"_OGH");
		
		//VISUALS
		//SKYCHANGER
	}
	oPaintTraverse(panel, VGUIPanel, ForceRepaint, AllowForce);

}

void __fastcall Hooked_LockCursor(Surface* thisptr, void* edx)
{
	if (GetKeyState(VK_DELETE) == 1)
	{
		if (!var.men1)
		{
			surf->UnlockCursor();
			var.men1 = true;
			var.men2 = true;
			var.Menu = true;
			cout << "666" << endl;
		}
	}

	if (GetKeyState(VK_DELETE) == 0)
	{
		if (var.men2)
		{
			oLockCursor(thisptr, edx);
			var.men1 = false;
			var.men2 = false;
			var.Menu = false;
			cout << "888" << endl;
		}
	}

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

DWORD WINAPI MainThread(LPVOID param) // our main thread
{
	var.oWndProc = (WNDPROC)SetWindowLongPtr(FindWindowA("Valve001", nullptr), GWL_WNDPROC, (LONG)(LONG_PTR)WndProc);
	clientModeInterface = (BaseClientDLL*)newInterface->GetInterface((char*)"client_panorama.dll", (char*)"VClient018");


	d3d9device = **(IDirect3DDevice9***)(memory.FindPattern((char*)"shaderapidx9.dll", "\xA1\x00\x00\x00\x00\x50\x8B\x08\xFF\x51\x0C", "x????xxxxxx") + 0x1);
	surf = (Surface*)newInterface->GetInterface((char*)"vguimatsurface.dll", (char*)"VGUI_Surface031");
	inputsys = (InputSystem*)newInterface->GetInterface((char*)"inputsystem.dll", (char*)"InputSystemVersion001");
	eng = (Engine*)newInterface->GetInterface((char*)"engine.dll", (char*)"VEngineClient014");
	clientMode = **(ClientMode***)((*(uintptr_t**)clientModeInterface)[10] + 0x5);
	panel = (Panel*)newInterface->GetInterface((char*)"vgui2.dll", (char*)"VGUI_Panel009");
	entlist = (ClientEntityList*)newInterface->GetInterface((char*)"client_panorama.dll", (char*)"VClientEntityList003");
	g_Input = *(Input**)(memory.FindPattern((char*)"client_panorama.dll", "\xB9\x00\x00\x00\x00\xF3\x0F\x11\x04\x24\xFF\x50\x10", "x????xxxxxxxx") + 1);

	GetNetVars();

	oEndScene = (EndScene_Hook)memory.VTableFunctionTrampoline((uintptr_t)Hooked_EndScene, (uintptr_t)d3d9device, 42);
	oReset = (Reset_Hook)memory.VTableFunctionTrampoline((uintptr_t)Hooked_Reset, (uintptr_t)d3d9device, 16);
	oOverrideView = (OverrideView_Hook)memory.VTableFunctionTrampoline((uintptr_t)Hooked_OverrideView, (uintptr_t)clientMode, 18);
	oGetViewModelFOV = (GetViewModelFOV_Hook)memory.VTableFunctionTrampoline((uintptr_t)Hooked_GetViewModelFOV, (uintptr_t)clientMode, 35);
	oCreateMove = (CreateMove_Hook)memory.VTableFunctionTrampoline((uintptr_t)Hooked_CreateMovePROXY, (uintptr_t)clientModeInterface, 22);
	oPaintTraverse = (PaintTraverse_Hook)memory.VTableFunctionTrampoline((uintptr_t)Hooked_PaintTraverse, (uintptr_t)panel, 41);
	oLockCursor = (LockCursor_Hook)memory.VTableFunctionTrampoline((uintptr_t)Hooked_LockCursor, (uintptr_t)surf, 67);
	return false;
}


BOOL APIENTRY DllMain(HMODULE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved
)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH: // gets runned when injected
		AllocConsole(); // enables the console
		freopen("CONIN$", "r", stdin); // makes it possible to output to console with cout.
		freopen("CONOUT$", "w", stdout);
		CreateThread(0, 0, MainThread, hModule, 0, 0); // creates our thread 
		break;

	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;

}

