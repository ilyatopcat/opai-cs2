#pragma once

#include "../features.h"

class CRecord
{
public:
	Vector m_vecOrigin;
	float m_flSimulationTime = 0.0f;
	int m_iFlags = 0;
	bool m_bValid = false;

	CRecord() {}

	inline CRecord(C_CSPlayerPawn* pawn)
	{
		this->Store(pawn);
	}

	inline void Store(C_CSPlayerPawn* pawn)
	{
		m_vecOrigin = pawn->m_pGameSceneNode()->m_vecOrigin();
		m_flSimulationTime = pawn->m_fSimulationTime();
		m_iFlags = pawn->m_fFlags();

		m_bValid = true;
	}
};

namespace Lagcompensation
{
	inline std::unordered_map<int, std::deque<CRecord>> m_mPlayerRecords{};

	void Run();
}