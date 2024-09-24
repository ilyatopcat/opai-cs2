#include "C_CSPlayerPawn.h"

#include "../../../utils/utils.h"
#include "../../../utils/vmt.h"
#include "../../interfaces/interfaces.h"

Vector C_CSPlayerPawn::GetEyePosition() {
	return GetOriginPosition() + m_vecViewOffset();
}

Vector C_CSPlayerPawn::GetOriginPosition() {
	return m_pGameSceneNode()->m_vecOrigin();
}

Vector C_CSPlayerPawn::GetBonePosition(int index) {
	using GetBonePosition_t = int(__fastcall*)(void*, int, Vector&, Vector&);
	static GetBonePosition_t GetBonePosition = reinterpret_cast<GetBonePosition_t>(Utils::OpcodeScan("client.dll", "48 89 6C 24 ? 48 89 74 24 ? 48 89 7C 24 ? 41 56 48 83 EC ? 4D 8B F1 49 8B E8"));

	Vector position;
	Vector rotation;

	GetBonePosition(this, index, position, rotation);

	return position;
}

bool C_CSPlayerPawn::IsVisible(C_CSPlayerPawn* pPawn, Vector vecPoint)
{
	if (!this || !pPawn)
		return false;

	TraceFilter_t filter(0x1C3003, this, nullptr, 4);
	Ray_t ray = Ray_t();
	GameTrace_t trace = GameTrace_t();

	Vector vecSource = this->GetEyePosition();
	Interfaces::engineTrace->TraceShape(&ray, vecSource, vecPoint, &filter, &trace);

	if ((trace.IsVisible() || (trace.m_pHitEntity && trace.m_pHitEntity->GetRefEHandle().GetEntryIndex() == pPawn->GetRefEHandle().GetEntryIndex())))
		return true;

	return false;
}

CHitboxsets* C_CSPlayerPawn::GetHitboxSets(unsigned int hitboxSetIndex)
{
	using GetHitboxSets_t = std::int64_t(__fastcall*) (void*, unsigned int);
	static GetHitboxSets_t GetHitboxSets = reinterpret_cast<GetHitboxSets_t>(Utils::OpcodeScan("client.dll", "48 89 5C 24 ? 48 89 74 24 ? 57 48 81 EC ? ? ? ? 8B DA 48 8B F9 E8 ? ? ? ? 48 8B F0 48 85 C0 0F 84"));

	return (CHitboxsets*)GetHitboxSets(this, hitboxSetIndex);
}

C_BasePlayerWeapon* C_CSPlayerPawn::GetActiveWeapon()
{
	auto weaponServices = this->m_pWeaponServices();
	if (weaponServices)
	{
		auto activeWeapon = weaponServices->m_hActiveWeapon().Get<C_BasePlayerWeapon>();
		if (activeWeapon && activeWeapon->isWeapon())
			return activeWeapon;
	}

	return nullptr;
}

void CGameSceneNode::SetMeshGroupMask(uint64_t mask)
{
	using fnSetMeshGroupMask = void(__thiscall*) (void*, uint64_t);
	static fnSetMeshGroupMask oSetMeshGroupMaks = reinterpret_cast<fnSetMeshGroupMask>(Utils::OpcodeScanAbsolute("client.dll", "E8 ? ? ? ? 48 8B 5C 24 ? 4C 8B 7C 24 ? 4C 8B 74 24 ?", 0x1));

	return oSetMeshGroupMaks(this, mask);
}

CSkeletonInstance* CGameSceneNode::GetSkeletonInstance()
{
	return CALL_VIRTUAL(this, CSkeletonInstance*, 8);
}

bool C_CSPlayerPawn::IsAlive() {
	return m_iHealth() > 0;
}

int C_CSPlayerPawn::GetBoneIndex(const char* name)
{
	using GetBoneIndex_t = int(__fastcall*)(void*, const char*);
	static GetBoneIndex_t GetBoneIndex = reinterpret_cast<GetBoneIndex_t>(Utils::OpcodeScanAbsolute("client.dll", "E8 ?? ?? ?? ?? 33 DB 89 47 08", 0x1));

	return GetBoneIndex(this, name);
}