#include "BASEENTITY.h"
#include "OFFSETS.h"
#include "Memory.h"

typedef void(__thiscall* oRenderBounds)(void*, Vector&, Vector&);
typedef bool(__thiscall* oPlayer)(void*);

void BaseEntity::GetRenderBounds(Vector& min, Vector& max)
{
	void* renderable = (PVOID)(this + 0x4);

	return memory.GetVTableFunction<oRenderBounds>((uintptr_t)this, 20)(renderable, min, max);
}

unsigned char BaseEntity::GetLifeState()
{
	return *(unsigned char*)((uintptr_t)this + off.DT_BasePlayer.m_lifeState);
}

int BaseEntity::GetHealth()
{
	return *(int*)((uintptr_t)this + off.DT_BasePlayer.m_iHealth);
}

bool BaseEntity::IsAlive()
{
	return (GetLifeState() == LIFE_ALIVE && GetHealth() > 0);
}

bool BaseEntity::IsPlayer()
{
	return memory.GetVTableFunction<oPlayer>((uintptr_t)this, 202)(this);
}

bool BaseEntity::IsScoped()
{
	return *(bool*)((uintptr_t)this + off.DT_CSPlayer.m_bIsScoped);
}

bool BaseEntity::SetupBones(matrix3x4_t* pBoneToWorldOut, int nMaxBones, int boneMask, float currentTime)
{
	__asm
	{
		mov edi, this
		lea ecx, DWORD ptr ds : [edi + 0x4]
		mov edx, DWORD ptr ds : [ecx]
		push currentTime
		push boneMask
		push nMaxBones
		push pBoneToWorldOut
		call DWORD ptr ds : [edx + 0x34]
	}
}

char* BaseEntity::GetModelName()
{
	return *(char**)((uintptr_t)this + 0x6C) + BYTE(39);
}

model_t* BaseEntity::GetModel()
{
	return *(model_t**)((uintptr_t)this + 0x6C);
}

Vector BaseEntity::GetBonePosition(int bone)
{
	matrix3x4_t boneMatrixes[128];
	if (this->SetupBones(boneMatrixes, 128, 0x100, 0))
	{
		matrix3x4_t boneMatrix = boneMatrixes[bone];
		return Vector(boneMatrix.m_flMatVal[0][3], boneMatrix.m_flMatVal[1][3], boneMatrix.m_flMatVal[2][3]);
	}
	else return Vector(0, 0, 0);
}

int BaseEntity::GetFlags()
{
	return *(int*)((uintptr_t)this + off.DT_BasePlayer.m_fFlags);
}

int BaseEntity::GetAmmo()
{
	return *(int*)((uintptr_t)this + off.DT_BaseCombatWeapon.m_iClip1);
}

Vector& BaseEntity::GetVecOrigin()
{
	return *(Vector*)((uintptr_t)this + off.DT_BaseEntity.m_vecOrigin);
}

QAngle& BaseEntity::GetAbsAngles()
{
	return *(QAngle*)((uintptr_t)this + 0x4D0C);
}

int BaseEntity::GetTeam()
{
	return *(int*)((uintptr_t)this + off.DT_BaseEntity.m_iTeamNum);
}

int BaseEntity::GetMoney()
{
	return *(int*)((uintptr_t)this + off.DT_CSPlayer.m_iAccount);
}

int BaseEntity::GetArmor()
{
	return *(int*)((uintptr_t)this + 0xB238);
}

int BaseEntity::GetTickBase()
{
	return *(int*)((uintptr_t)this + off.DT_BasePlayer.m_nTickBase);
}

int BaseEntity::InCross()
{
	return *(int*)((uintptr_t)this + 0xB394);
}

int BaseEntity::GetMoveType() 
{
	return *(int*)((uintptr_t)this + off.DT_BaseEntity.m_MoveType);
}

Vector BaseEntity::GetVelocity()
{
	return *(Vector*)((uintptr_t)this + off.DT_BasePlayer.m_vecVelocity);
}

Vector& BaseEntity::GetAbsOrigin()
{
	return *(Vector*)((uintptr_t)this + off.DT_BaseEntity.m_vecOrigin);
}

Vector BaseEntity::GetViewOffset()
{
	static int m_vecViewOffset = off.DT_BasePlayer.m_vecViewOffset;
	return *reinterpret_cast<Vector*>(reinterpret_cast<uintptr_t>(this) + m_vecViewOffset);
}

Vector BaseEntity::GetEyePosition()
{
	return this->GetVecOrigin() + this->GetViewOffset();
}

Vector BaseEntity::GetAimPunchAngle()
{
	return *(Vector*)((uintptr_t)this + 0x301);
}

UINT* BaseEntity::GetMyWeapons()
{
	return (UINT*)((uintptr_t)this + off.DT_BaseCombatCharacter.m_hMyWeapons);
}

int* BaseEntity::GetMyWeapon()
{
	return (int*)((uintptr_t)this + off.DT_BaseCombatCharacter.m_hActiveWeapon);
}

int* BaseEntity::ModelIndex()
{
	return (int*)((uintptr_t)this + off.DT_BaseViewModel.m_nModelIndex);
}

void BaseEntity::SetModelIndex(const int index)
{
	memory.GetVTableFunction<void(__thiscall*)(BaseEntity*, int)>((uintptr_t)this, 75)(this, index);
}

BaseHandle BaseEntity::GetViewModel()
{
	return *(BaseHandle*)((uintptr_t)this + off.DT_BasePlayer.m_hViewModel);
}

int BaseEntity::GetIndex()
{
	return *(int*)((uintptr_t)this + off.DT_BaseEntity.m_bIsAutoaimTarget + 0x4);
}
