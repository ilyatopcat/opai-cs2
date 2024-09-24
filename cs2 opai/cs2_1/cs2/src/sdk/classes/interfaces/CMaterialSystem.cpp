#include "../../../utils/vmt.h"

#include "CMaterialSystem.h"

CMaterial2*** CMaterialSystem::FindMaterial(CMaterial2*** pMaterial, const char* materialName) {
	return CALL_VIRTUAL(this, CMaterial2***, 14, pMaterial, materialName);
}

CMaterial2** CMaterialSystem::CreateMaterial(CMaterial2*** pMaterial, const char* materialName, void* pData) {
	return CALL_VIRTUAL(this, CMaterial2**, 29, pMaterial, materialName, pData, 0, 0, 0, 0, 0, 1);
}

void CMaterialSystem::SetCreateDataByMaterial(void* pData, CMaterial2*** pMaterial) {
	CALL_VIRTUAL(this, void, 37, pData, pMaterial);
}