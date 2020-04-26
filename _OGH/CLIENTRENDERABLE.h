#pragma once
#include <Windows.h>

#include "VECTOR.h"

typedef float matrix3x4[3][4];
typedef unsigned char uint8;
static class ClientUnknown;
static struct model_t;

class ClientRenderable
{
public:
	virtual ClientUnknown* GetClientUnknown() = 0;

	virtual Vector const& GetRenderOrigin(void) = 0;

	virtual Vector const& GetRenderAngles(void) = 0;

	virtual bool ShouldDraw(void) = 0;

	virtual int GetRenderFlags(void) = 0; // ERENDERFLAGS_xxx
	virtual void Unused(void) const
	{
	}

	virtual HANDLE GetShadowHandle() const = 0;

	virtual HANDLE& RenderHandle() = 0;

	virtual const model_t* GetModel() const = 0;

	virtual int DrawModel(int flags, const int /*RenderableInstance_t*/& instance) = 0;

	virtual int GetBody() = 0;

	virtual void GetColorModulation(float* color) = 0;

	virtual bool LODTest() = 0;

	virtual void SetupWeights(const matrix3x4* pBoneToWorld, int nFlexWeightCount, float* pFlexWeights, float* pFlexDelayedWeights) = 0;

	virtual void DoAnimationEvents(void) = 0;

	virtual void* /*IPVSNotify*/ GetPVSNotifyInterface() = 0;

	virtual void GetRenderBounds(Vector& mins, Vector& maxs) = 0;

	virtual void GetRenderBoundsWorldspace(Vector& mins, Vector& maxs) = 0;

	virtual void GetShadowRenderBounds(Vector& mins, Vector& maxs, int /*ShadowType_t*/ shadowType) = 0;

	virtual bool ShouldReceiveProjectedTextures(int flags) = 0;

	virtual bool GetShadowCastDistance(float* pDist, int /*ShadowType_t*/ shadowType) const = 0;

	virtual bool GetShadowCastDirection(Vector* pDirection, int /*ShadowType_t*/ shadowType) const = 0;

	virtual bool IsShadowDirty() = 0;

	virtual void MarkShadowDirty(bool bDirty) = 0;

	virtual ClientRenderable* GetShadowParent() = 0;

	virtual ClientRenderable* FirstShadowChild() = 0;

	virtual ClientRenderable* NextShadowPeer() = 0;

	virtual int /*ShadowType_t*/ ShadowCastType() = 0;

	virtual void CreateModelInstance() = 0;

	virtual HANDLE GetModelInstance() = 0;

	virtual const matrix3x4& RenderableToWorldTransform() = 0;

	virtual int LookupAttachment(const char* pAttachmentName) = 0;

	virtual bool GetAttachment(int number, Vector& origin, Vector& angles) = 0;

	virtual bool GetAttachment(int number, matrix3x4& matrix) = 0;

	virtual float* GetRenderClipPlane(void) = 0;

	virtual int GetSkin() = 0;

	virtual void OnThreadedDrawSetup() = 0;

	virtual bool UsesFlexDelayedWeights() = 0;

	virtual void RecordToolMessage() = 0;

	virtual bool ShouldDrawForSplitScreenUser(int nSlot) = 0;

	virtual uint8 OverrideAlphaModulation(uint8 nAlpha) = 0;

	virtual uint8 OverrideShadowAlphaModulation(uint8 nAlpha) = 0;
};