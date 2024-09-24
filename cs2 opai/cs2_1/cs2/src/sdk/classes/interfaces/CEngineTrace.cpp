#include "CEngineTrace.h"

#include "../entity/C_CSPlayerPawn.h"

SurfaceData_t* GameTrace_t::GetSurfaceData()
{
	using fnGetSurfaceData = std::uint64_t(__fastcall*)(void*);
	static fnGetSurfaceData oGetSurfaceData = reinterpret_cast<fnGetSurfaceData>(Utils::OpcodeScanAbsolute("client.dll", "E8 ? ? ? ? 48 85 C0 74 ? 44 38 60", 0x1));

	return reinterpret_cast<SurfaceData_t*>(oGetSurfaceData(m_pSurface));
}

int GameTrace_t::GetHitboxId()
{
	if (m_pHitboxData)
		return m_pHitboxData->m_nHitboxId;
	return 0;
}

int GameTrace_t::GetHitgroup()
{
	if (m_pHitboxData)
		return m_pHitboxData->m_nHitGroup;
	return 0;
}

bool GameTrace_t::IsVisible() const
{
	return (m_flFraction > 0.97f);
}

TraceFilter_t::TraceFilter_t(std::uint64_t uMask, C_CSPlayerPawn* pSkip1, C_CSPlayerPawn* pSkip2, int nLayer)
{
	m_uTraceMask = uMask;
	m_v1[0] = m_v1[1] = 0;
	m_v2 = 7;
	m_v3 = nLayer;
	m_v4 = 0x49;
	m_v5 = 0;

	if (pSkip1 != nullptr)
	{
		m_arrSkipHandles[0] = pSkip1->GetRefEHandle().GetEntryIndex();
		m_arrSkipHandles[2] = pSkip1->GetOwnerHandleIndex();
		m_arrCollisions[0] = pSkip1->m_pCollision()->CollisionMask();
	}

	if (pSkip2 != nullptr)
	{
		m_arrSkipHandles[0] = pSkip2->GetRefEHandle().GetEntryIndex();
		m_arrSkipHandles[2] = pSkip2->GetOwnerHandleIndex();
		m_arrCollisions[0] = pSkip2->m_pCollision()->CollisionMask();
	}
}