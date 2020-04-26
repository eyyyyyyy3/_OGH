#pragma once
#include <Windows.h>
#include "VECTOR.h"
#include "VMATRIX.h"
#include "QANGLE.h"
#include "CLIENTENTITYLIST.h"


static struct model_t;

class BaseEntity : public ClientEntity
{
public:

	void GetRenderBounds(Vector& min, Vector& max);

	unsigned char GetLifeState();

	int GetHealth();

	bool IsAlive();

	bool IsPlayer();

	bool IsScoped();

	bool SetupBones(matrix3x4_t* pBoneToWorldOut, int nMaxBones, int boneMask, float currentTime);
	
	char* GetModelName();

	model_t* GetModel();

	Vector GetBonePosition(int bone);

	int GetFlags();

	int GetAmmo();

	Vector& GetVecOrigin();

	QAngle& GetAbsAngles();

	int GetTeam();

	int GetMoney();

	int GetArmor();

	int GetTickBase();

	int InCross();

	int GetMoveType();

	Vector GetVelocity();

	/*	Vector GetBonePos(int bone)
	{
	matrix3x4_t boneMatrix[MAXSTUDIOBONES];
	if(var.ClientRenderable->SetupBones(boneMatrix, MAXSTUDIOBONES, BONE_USED_BY_ANYTHING, 0.0f)) {
	return boneMatrix[bone].at(3);
	}
	return Vector{};
	}*/

	Vector& GetAbsOrigin();

	Vector GetViewOffset();

	Vector GetEyePosition();

	Vector GetAimPunchAngle();

	UINT* GetMyWeapons();

	int* GetMyWeapon();

	int* ModelIndex();

	void SetModelIndex(const int index);

	BaseHandle GetViewModel();

	int GetIndex();

};

