#include "CCSGOInput.h"
#include "../math/math.h"

CUserCmd* CCSGOInput::GetUserCmd() {
    return &m_aCommands[m_iSequenceNumber % 150];
}

Vector CCSGOInput::GetViewAngles() {
    using GetViewAngles_t = void* (__thiscall*)(CCSGOInput*, int);
    static GetViewAngles_t GetViewAngles = reinterpret_cast<GetViewAngles_t>(Utils::OpcodeScan("client.dll", "4C 8B C1 85 D2 74 08 48 8D 05 ? ? ? ? C3"));

    return *reinterpret_cast<Vector*>(GetViewAngles(this, 0));
}

void CCSGOInput::SetViewAngles(Vector& viewAngles) {
    using SetViewAngles_t = void(__fastcall*)(CCSGOInput*, int, Vector&);
    static SetViewAngles_t SetViewAngle = reinterpret_cast<SetViewAngles_t>(Utils::OpcodeScan("client.dll", "85 D2 75 3F 48"));

    SetViewAngle(this, 0, viewAngles);
}

void CUserCmd::SetInputAngles(Vector angles) {

    for (auto i = 0; i < pb.input_history_size(); i++) {
        auto tick = pb.mutable_input_history(i);
        if (!tick)
            continue;

        auto view_angles = tick->mutable_view_angles();
        if (!view_angles)
			continue;

        view_angles->set_x(angles.x);
		view_angles->set_y(angles.y);
		view_angles->set_z(angles.z);
    }
}