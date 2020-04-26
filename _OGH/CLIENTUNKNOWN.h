#pragma once
#include <Windows.h>
#include "OFFSETS.h"

static class Collideable;
static class ClientNetworkable;
static class ClientRenderable;
static class BaseEntity;
static class ClientThinkable;
using BaseHandle = unsigned long;

class HandleEntity
{
public:
	virtual ~HandleEntity() {}
	virtual void SetRefEHandle(const BaseHandle& handle) = 0;
	virtual const BaseHandle& GetRefEHandle() const = 0;
};

class ClientUnknown : public HandleEntity
{
public:
	virtual Collideable* GetCollideable() = 0;
	virtual ClientNetworkable* GetClientNetworkable() = 0;
	virtual ClientRenderable* GetClientRenderable() = 0;
	virtual BaseEntity* GetIClientEntity() = 0;
	virtual BaseEntity* GetBaseEntity() = 0;
	virtual ClientThinkable* GetClientThinkable() = 0;
};