#include "C_BasePlayerWeapon.h"
#include "../../../utils/utils.h"

CCSWeaponBaseVData* C_BasePlayerWeapon::GetWeaponData()
{
    return *reinterpret_cast<CCSWeaponBaseVData**>(reinterpret_cast<uintptr_t>(this) + 0x360);
}