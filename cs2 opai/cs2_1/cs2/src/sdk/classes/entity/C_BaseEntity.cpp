#include "C_BaseEntity.h"
#include "../../../utils/vmt.h"

/*
CSkeletonInstance* C_BaseEntity::GetSkeletonInstance() {
	return *reinterpret_cast<CSkeletonInstance**>((unsigned __int64)this + 0x318);
}
*/

bool C_BaseEntity::isWeapon()
{
	return vmt::CallVirtual<bool>(this, 156);
}

void C_BaseEntity::UpdateSubclass()
{
	using fnUpdateSubclass = void(__fastcall*)(void*);
	static fnUpdateSubclass onSubclassChange = reinterpret_cast<fnUpdateSubclass>(Utils::OpcodeScan("client.dll", "40 53 48 83 EC 30 48 8B 41 10 48 8B D9 8B 50 30"));

	onSubclassChange(this);
}