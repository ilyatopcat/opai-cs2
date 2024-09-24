#pragma once

#include "../../utils/vmt.h"
#include "../../utils/utils.h"

#include "../math/Vector.h"
#include "../math/CStrongHandle.h"

class CGameEvent;
class CCSPlayerController;

class CBuffer
{
public:
    char Pad[0x8];
    const char* name;
};

class CGameEventHelper
{
public:
    CGameEventHelper(CGameEvent* Event) : Event{ std::move(Event) } {};
public:
    CCSPlayerController* GetPlayerController();
    CCSPlayerController* GetAttackerController();
    int GetDamage();
    int GetHealth();

protected:
    CGameEvent* Event;
};

class CGameEvent {
public:
    virtual ~CGameEvent() = 0;
    virtual const char* GetName() const = 0;

    virtual void Unk1() = 0;
    virtual void Unk2() = 0;
    virtual void Unk3() = 0;
    virtual void Unk4() = 0;

    virtual bool GetBool(const char* KeyName = nullptr, bool DefaultValue = false) = 0;
    virtual int GetInt(CBuffer* KeyName = nullptr, bool DefaultValue = false) = 0;
    virtual uint64_t GetUint64(const char* KeyName = nullptr, uint64_t DefaultValue = 0) = 0;
    virtual float GetFloat(const char* KeyName = nullptr, float DefaultValue = 0.f) = 0;
    virtual const char* GetString(const char* KeyName = nullptr, const char* DefaultValue = "") = 0;
    virtual void Unk5() = 0;
    virtual void Unk6() = 0;
    virtual void Unk7() = 0;
    virtual void Unk8() = 0;
    virtual void GetControllerId(int& ControllerId, CBuffer* Buffer = nullptr) = 0;
public:
    CGameEventHelper GetEventHelper()
    {
        CGameEventHelper EventHelper(this);
        return EventHelper;
    }

    int GetInt2(const char* Name, bool Unk);
    float GetFloat2(const char* Name, bool Unk);
};

class IGameEventListener {
public:
    virtual ~IGameEventListener() {}
    virtual void FireGameEvent(CGameEvent* Event) = 0;
};

class CGameEventManager
{
public:
    virtual ~CGameEventManager() = 0;
    virtual int LoadEventsFromFile(const char* Filename) = 0;

    virtual void Reset() = 0;
    virtual bool AddListeners(IGameEventListener* Listener, const char* MName, bool MBServerSide) = 0;

    virtual bool FindListener(IGameEventListener* eventListener, const char* name) = 0;
};