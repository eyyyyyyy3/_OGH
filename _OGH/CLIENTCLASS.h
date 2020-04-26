#pragma once
#include "RECV.h"
#include "ENUMS.h"

static class ClientClass;
static class ClientNetworkable;

typedef ClientNetworkable* (*CreateClientClassFn)(int entnum, int serialNum);
typedef ClientNetworkable* (*CreateEventFn)();

class ClientClass
{
public:
	CreateClientClassFn      m_pCreateFn;
	CreateEventFn            m_pCreateEventFn;
	char* m_pNetworkName;
	RecvTable* m_pRecvTable;
	ClientClass* m_pNext;
	ClassId                  m_ClassID;
};