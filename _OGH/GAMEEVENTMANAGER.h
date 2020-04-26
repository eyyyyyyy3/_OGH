#pragma once
#include <stdint.h>

static class bf_write;
static class bf_read;
static struct KeyValues;

class GameEvent
{
public:
	virtual					~GameEvent() {};
	virtual const char*		GetName() const = 0;

	virtual bool			IsReliable() const = 0;
	virtual bool			IsLocal() const = 0;
	virtual bool			IsEmpty(const char* keyname = nullptr) = 0;

	virtual bool			GetBool(const char* keyname = nullptr, bool default_value = false) = 0;
	virtual int				GetInt(const char* keyname = nullptr, int default_value = 0) = 0;
	virtual uint64_t		GetUint64(const char* keyname = nullptr, uint64_t default_value = 0) = 0;
	virtual float			GetFloat(const char* keyname = nullptr, float default_value = 0.0f) = 0;
	virtual const char*		GetString(const char* keyname = nullptr, const char* default_value = "") = 0;
	virtual const wchar_t*  GetWString(const char* keyname = nullptr, const wchar_t* default_value = L"") = 0;
	virtual const void*		GetPtr(const char* keyname = nullptr, const void* default_values = nullptr) = 0;

	virtual void			SetBool(const char* keyname, bool value) = 0;
	virtual void			SetInt(const char* keyname, int value) = 0;
	virtual void			SetUint64(const char* keyname, uint64_t value) = 0;
	virtual void			SetFloat(const char* keyname, float value) = 0;
	virtual void			SetString(const char* keyname, const char* value) = 0;
	virtual void			SetWString(const char* keyname, const wchar_t* value) = 0;
	virtual void			SetPtr(const char* keyname, const void* value) = 0;
};

class GameEventListener2
{
public:
	virtual					~GameEventListener2() {};
	virtual void			FireGameEvent(GameEvent* event) = 0;
	virtual int				GetEventDebugID() = 0;
};

class GameEventManager2
{
public:
	virtual					~GameEventManager2() {};
	virtual int				LoadEventsFromFile(const char* filename) = 0;
	virtual void			Reset() = 0;
	virtual bool			AddListener(GameEventListener2* listener, const char* name, bool serverside) = 0;
	virtual bool			FindListener(GameEventListener2* listener, const char* name) = 0;
	virtual void			RemoveListener(GameEventListener2* listener) = 0;
	virtual void			AddListenerGlobal(GameEventListener2* listener, bool serverside) = 0;
	virtual GameEvent*		CreateEvent(const char* name, bool force = false, int* cookie = nullptr) = 0;
	virtual bool			FireEvent(GameEvent* event, bool bDontBroadcast = false) = 0;
	virtual bool			FireEventClientSide(GameEvent* event) = 0;
	virtual GameEvent*		DuplicateEvent(GameEvent* event) = 0;
	virtual void			FreeEvent(GameEvent* event) = 0;
	virtual bool			SerializeEvent(GameEvent* event, bf_write* buffer) = 0;
	virtual GameEvent*		UnserializeEvent(bf_read* buffer) = 0;
	virtual KeyValues*		GetEventDataTypes(GameEvent* event) = 0;
};