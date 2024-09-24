#pragma once

#include "../math/Vector.h"
#include "../math/math.h"

#include <deque>

#include <stdint.h>
#include <string>
#include "../../utils/utils.h"
#include "../../sdk/math/CUtlBuffer.h"

#include "usercmd.pb.hpp"
#include "cs_usercmd.pb.hpp"
#include "network_connection.pb.hpp"
#include "networkbasetypes.pb.hpp"

enum EButton
{
    IN_NONE = 0,
    IN_ALL = -1,
    IN_ATTACK = 1,
    IN_JUMP = 2,
    IN_DUCK = 4,
    IN_FORWARD = 8,
    IN_BACK = 16,
    IN_USE = 32,
    IN_TURNLEFT = 128,
    IN_TURNRIGHT = 256,
    IN_MOVELEFT = 512,
    IN_MOVERIGHT = 1024,
    IN_ATTACK2 = 2048,
    IN_RELOAD = 8192,
    IN_SPEED = 65536,
    IN_JOYAUTOSPRINT = 131072,
    IN_FIRST_MOD_SPECIFIC_BIT = 4294967296,
    IN_USEORRELOAD = 4294967296,
    IN_SCORE = 8589934592,
    IN_ZOOM = 17179869184,
    IN_JUMP_THROW_RELEASE = 34359738368,
};

enum EMoveType : int
{
    MOVETYPE_NONE = 0,
    MOVETYPE_ISOMETRIC,
    MOVETYPE_WALK,
    MOVETYPE_STEP,
    MOVETYPE_FLY,
    MOVETYPE_FLYGRAVITY,
    MOVETYPE_VPHYSICS,
    MOVETYPE_PUSH,
    MOVETYPE_NOCLIP,
    MOVETYPE_LADDER,
    MOVETYPE_OBSERVER,
    MOVETYPE_CUSTOM,
    MOVETYPE_LAST = MOVETYPE_CUSTOM,
    MOVETYPE_MAX_BITS = 4
};

class CCSInputMessage
{
public:
    int32_t frameTickCount; //0x0000
    float frameTickFraction; //0x0004
    int32_t playerTickCount; //0x0008
    float playerTickFraction; //0x000C
    Vector viewAngles; //0x0010
    Vector shootPosition; //0x001C
    int32_t targetEntityIndex; //0x0028
    Vector targetHeadPos; //0x002C
    Vector targetAbsOrigin; //0x0038
    Vector targetAngle; //0x0044
    int32_t svShowHitRegistration; //0x0050
    int32_t entryIndexMax; //0x0054
    int32_t playerIndex; //0x0058
    uint32_t sceneLayer; //0x005C
};

class CButtonState
{
    void* __vfptr;
public:
    uint64_t value;
    uint64_t changed;
    uint64_t scroll;
};

class CUserCmd
{
public:
    CSGOUserCmdPB pb;
    CButtonState buttons;
    char pad__001[0x10];
    bool m_bHasBeenPredicted;
    char pad__002[0x9];
    char pad__003[0x6];

    void SetInputAngles(Vector angles);
};

class CSubtickMoves
{
public:
    float when; //0x0000
    float delta; //0x0004
    uint64_t button; //0x0008
    bool pressed; //0x0010
    char pad0011[7]; //0x0011
}; //Size: 0x0018

class CCSInputMoves
{
public:
    uint64_t m_CurrentBits; //0x0000
    char pad_0008[24]; //0x0008
    float m_flForwardMove; //0x0020
    float m_flSideMove; //0x0024
    char pad_0028[16]; //0x0028
    float m_flFraction; //0x0038
    char pad_003C[4]; //0x003C
    int32_t m_iLastButtons; //0x0040
    char pad_0044[4]; //0x0044
    bool m_bInMove; //0x0048
    char pad_0074[255]; //0x0074
    Vector m_vecViewAngles; //0x0158
    char pad_0164[48]; //0x0164
}; //Size: 0x0194

class CCSGOInput {
public:
    char pad_0000[592]; //0x0000
    CUserCmd m_aCommands[150]; //0x0250
    CUserCmd m_cGlobalCommand; //0x5200
    bool m_bBlockShot; //0x5288
    bool m_bInThirdPerson; //0x5289
    char pad_528A[6]; //0x528A
    Vector m_vecThirdPersonAngles; //0x5290
    char pad_529C[16]; //0x529C
    int32_t m_iSequenceNumber; //0x52AC
    int32_t m_iOldSequenceNumber; //0x52B0
    char pad_52B4[8]; //0x52B4
    float m_fRealTime; //0x52BC
    uint64_t m_ButtonState; //0x52C0
    uint64_t m_ButtonState2; //0x52C8
    uint64_t m_ButtonState3; //0x52D0
    uint64_t m_ButtonState4; //0x52D8
    Vector m_vecMove; //0x52E0
    Vector2D m_vecMouse; //0x52EC
    int32_t m_iSubtickCount; //0x52F4
    CSubtickMoves m_aSubtickMoves[12]; //0x52F8
    Vector m_vecViewAngles; //0x5418
    char pad_5424[148]; //0x5424
    CCSInputMoves* m_pInputMoves; //0x54B8
    int32_t m_iActiveInputMoves; //0x54C0
    char pad_54C4[68]; //0x54C4
    int32_t m_iAttackHistory_1; //0x5508
    int32_t m_iAttackHistory_2; //0x550C
    int32_t m_iAttackHistory_3; //0x5510
    char pad__5514[4]; //0x5514
    int32_t m_iActiveInputs; //0x5518
    char pad__0x551C[4]; //0x551C
    CCSInputMessage* m_pInputMessage; //0x5520
    int32_t m_iInputMessagesCount; //0x5528

    bool PushButton(uint64_t button, bool held, float when = 0.90f) {
        if (m_iSubtickCount >= 12) 
            return false;

        m_aSubtickMoves[m_iSubtickCount++] = CSubtickMoves{ .when = when, .button = button, .pressed = held };
        return true;
    }

    uint8_t PopButton(uint64_t button) {
        uint8_t c = 0;
        for (int i = 0; i < m_iSubtickCount; i++) {
            if (m_aSubtickMoves[i].button == button) {
                memmove(m_aSubtickMoves + i, m_aSubtickMoves + i + 1, (m_iSubtickCount - i - 1) * sizeof(CSubtickMoves));
                m_iSubtickCount--;
                i--;
                c++;
            }
        }
        return c;
    }

    void SetAttackFraction(float ratio)
    {
        auto attackTickFraction = reinterpret_cast<int*>(uintptr_t(this) + 0x553E);

        *attackTickFraction = ratio;
    }

    void SetAttackTickRatio(float tick)
    {
        auto attackTickRatio = reinterpret_cast<int*>(uintptr_t(this) + 0x553D);

        *attackTickRatio = tick;
    }

    void SetAttackTickPostFireRatio(int tick)
    {
        auto attackTickPostFireRatio = reinterpret_cast<int*>(uintptr_t(this) + 0x553C);

        *attackTickPostFireRatio = tick;
    }

    float GetAttackFraction()
    {
        return *reinterpret_cast<float*>(uintptr_t(this) + 0x553F);
    }

    int GetAttackTickRatio()
    {
        return *reinterpret_cast<int*>(uintptr_t(this) + 0x5540);
    }

    int GetAttackTickPostFireRatio()
    {
        return *reinterpret_cast<int*>(uintptr_t(this) + 0x5541);
    }

    CUserCmd* GetUserCmd();

    Vector GetViewAngles();
    void SetViewAngles(Vector&);
};