#include "C_CSWeaponBase.h"

CCSWeaponBaseVData* C_CSWeaponBase::GetWeaponBaseData() {
	return *reinterpret_cast<CCSWeaponBaseVData**>(reinterpret_cast<unsigned __int64>(this) + 0x360);
}