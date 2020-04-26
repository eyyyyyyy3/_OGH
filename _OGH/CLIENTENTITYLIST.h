#pragma once
#include "CLIENTUNKNOWN.h"
#include "CLIENTRENDERABLE.h"
#include "CLIENTNETWORKABLE.h"
#include "CLIENTHINKABLE.h"	

static class BaseEntity;

struct ClientEntityList
{
	virtual ClientNetworkable* GetClientNetworkable(int entnum) = 0;
	virtual void* vtablepad0x1(void) = 0;
	virtual void* vtablepad0x2(void) = 0;
	virtual BaseEntity* GetClientEntity(int entNum) = 0;
	virtual BaseEntity* GetClientEntityFromHandle(BaseHandle hEnt) = 0;
	virtual int                   NumberOfEntities(bool bIncludeNonNetworkable) = 0;
	virtual int                   GetHighestEntityIndex(void) = 0;
	virtual void                  SetMaxEntities(int maxEnts) = 0;
	virtual int                   GetMaxEntities() = 0;
};

class ClientEntity : public ClientUnknown, public ClientRenderable, public ClientNetworkable, public ClientThinkable
{
public:
	virtual ~ClientEntity() {};
};
