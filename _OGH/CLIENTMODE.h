#pragma once
#include "VECTOR.h"
#include "QANGLE.h"
#include "PANEL.h"
#include "BaseEntity.h"

struct ViewSetup
{
	char _0x0000[16];
	__int32 x;
	__int32 x_old;
	__int32 y;
	__int32 y_old;
	__int32 width;
	__int32    width_old;
	__int32 height;
	__int32    height_old;
	char _0x0030[128];
	float fov;
	float fovViewmodel;
	Vector origin;
	QAngle angles;
	float zNear;
	float zFar;
	float zNearViewmodel;
	float zFarViewmodel;
	float m_flAspectRatio;
	float m_flNearBlurDepth;
	float m_flNearFocusDepth;
	float m_flFarFocusDepth;
	float m_flFarBlurDepth;
	float m_flNearBlurRadius;
	float m_flFarBlurRadius;
	float m_nDoFQuality;
	__int32 m_nMotionBlurMode;
	char _0x0104[68];
	__int32 m_EdgeBlur;
};

struct ClientMode
{
	virtual             ~ClientMode() {}
	virtual int         ClientModeCSNormal(void*) = 0;
	virtual void        Init() = 0;
	virtual void        InitViewport() = 0;
	virtual void        Shutdown() = 0;
	virtual void        Enable() = 0;
	virtual void        Disable() = 0;
	virtual void        Layout() = 0;
	virtual Panel* GetViewport() = 0;
	virtual void* GetViewportAnimationController() = 0;
	virtual void        ProcessInput(bool bActive) = 0;
	virtual bool        ShouldDrawDetailObjects() = 0;
	virtual bool        ShouldDrawEntity(BaseEntity* pEnt) = 0;
	virtual bool        ShouldDrawLocalPlayer(BaseEntity* pPlayer) = 0;
	virtual bool        ShouldDrawParticles() = 0;
	virtual bool        ShouldDrawFog(void) = 0;
	virtual void        OverrideView(ViewSetup* pSetup) = 0;
	virtual int         KeyInput(int down, int keynum, const char* pszCurrentBinding) = 0;
	virtual void        StartMessageMode(int iMessageModeType) = 0;
	virtual Panel* GetMessagePanel() = 0;
	virtual void        OverrideMouseInput(float* x, float* y) = 0;
	virtual bool        CreateMove(float flInputSampleTime, void* usercmd) = 0;
	virtual void        LevelInit(const char* newmap) = 0;
	virtual void        LevelShutdown(void) = 0;
};

