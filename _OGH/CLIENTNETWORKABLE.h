#pragma once
#include "ENUMS.h"

static class ClientUnknown;
static class ClientClass;
static class bf_read;
class ClientNetworkable
{
public:
	virtual ClientUnknown* GetClientUnknown() = 0;
	virtual void			Release() = 0;
	virtual ClientClass* GetClientClass() = 0;
	virtual void			NotifyShouldTransmit(int state) = 0;
	virtual void			OnPreDataChanged(int updateType) = 0;
	virtual void			OnDataChanged(int updateType) = 0;
	virtual void			PreDataUpdate(int updateType) = 0;
	virtual void			PostDataUpdate(int updateType) = 0;
	virtual void			OnDataUnchangedInPVS() = 0;
	virtual bool			IsDormant() = 0;
	virtual int				EntIndex() const = 0;
	virtual void			ReceiveMessage(int classID, bf_read& msg) = 0;
	virtual void* GetDataTableBasePtr() = 0;
	virtual void			SetDestroyedOnRecreateEntities() = 0;
};