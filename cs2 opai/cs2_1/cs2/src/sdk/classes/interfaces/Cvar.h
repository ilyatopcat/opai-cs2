#pragma once

enum CvarFlags : int
{
	FCVAR_NONE = 0,
	FCVAR_UNREGISTERED = (1 << 0),
	FCVAR_DEVELOPMENTONLY = (1 << 1),
	FCVAR_GAMEDLL = (1 << 2),
	FCVAR_CLIENTDLL = (1 << 3),
	FCVAR_HIDDEN = (1 << 4),
	FCVAR_PROTECTED = (1 << 5),
	FCVAR_SPONLY = (1 << 6),
	FCVAR_ARCHIVE = (1 << 7),
	FCVAR_NOTIFY = (1 << 8),
	FCVAR_USERINFO = (1 << 9),
	FCVAR_CHEAT = (1 << 14),
	FCVAR_PRINTABLEONLY = (1 << 10),
	FCVAR_UNLOGGED = (1 << 11),
	FCVAR_NEVER_AS_STRING = (1 << 12),
	FCVAR_REPLICATED = (1 << 13),
	// TODO: (1 << 14) used somehow
	FCVAR_DEMO = (1 << 16),
	FCVAR_DONTRECORD = (1 << 17),
	FCVAR_RELOAD_MATERIALS = (1 << 20),
	FCVAR_RELOAD_TEXTURES = (1 << 21),
	FCVAR_NOT_CONNECTED = (1 << 22),
	FCVAR_MATERIAL_SYSTEM_THREAD = (1 << 23),
	FCVAR_ARCHIVE_XBOX = (1 << 24),
	FCVAR_ACCESSIBLE_FROM_THREADS = (1 << 25),
	FCVAR_SERVER_CAN_EXECUTE = (1 << 28),
	FCVAR_SERVER_CANNOT_QUERY = (1 << 29),
	FCVAR_CLIENTCMD_CAN_EXECUTE = (1 << 30),
	FCVAR_MATERIAL_THREAD_MASK = (FCVAR_RELOAD_MATERIALS | FCVAR_RELOAD_TEXTURES | FCVAR_MATERIAL_SYSTEM_THREAD)
};

union CConvarValue
{
	bool i1;
	short i16;
	unsigned short u16;
	int i32;
	unsigned int u32;
	long long i64;
	unsigned long long u64;
	float fl;
	double db;
	const char* sz;
};

class ConVar {
public:
	const char* name;
	ConVar* next;
	char pad_0008[0x10];
	const char* description;
	unsigned int type;
	unsigned int registered;
	unsigned int flags;
	char padding_2[0x8]; // 0x34
	CConvarValue value; // 0x40

	bool GetBool() { return value.i1; }
	int GetInt() { return value.i32; }
	float GetFloat() { return value.fl; }
};

using CVarIterator_t = unsigned long long;

class Cvar {
public:
	CVarIterator_t GetFirstCvarIterator();
	CVarIterator_t GetNextCvarIterator(CVarIterator_t);

	ConVar* GetByIndex(CVarIterator_t);
	ConVar* GetByName(const char*);

	void UnlockHidden();
};