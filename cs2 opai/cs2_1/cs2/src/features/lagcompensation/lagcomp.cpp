#include "lagcomp.h"

void Lagcompensation::Run() {
	auto localPlayer = Entity::GetLocalPlayerPawn();
	if (!localPlayer)
		return;

	static auto sv_maxunlag = Interfaces::cvar->GetByName("sv_maxunlag");
	const int max_ticks = TIME_TO_TICKS(sv_maxunlag->GetFloat());

	const auto entities = Entity::Get("CCSPlayerController");
	for (auto entity : entities)
	{
		auto controller = entity->As<CCSPlayerController>();
		if (!controller)
			continue;

		auto playerPawn = controller->m_hPawn().Get<C_CSPlayerPawn>();
		if (!playerPawn)
			continue;

		int handle = Entity::GetEntityHandle(playerPawn);

		if (!playerPawn->IsAlive())
		{
			auto playerIterator = m_mPlayerRecords.find(handle);
			if (playerIterator != m_mPlayerRecords.end())
				m_mPlayerRecords.erase(playerIterator);
		}

		if (playerPawn->m_iTeamNum() == localPlayer->m_iTeamNum())
			continue;

		if (playerPawn == localPlayer)
			continue;
		
		if (m_mPlayerRecords.find(handle) == m_mPlayerRecords.end()) {
			m_mPlayerRecords.insert_or_assign(handle, std::deque<CRecord>{});

			continue;
		}

		auto& records = m_mPlayerRecords[handle];

		if (records.size() != max_ticks) {
			records.clear();
			records.resize(max_ticks);
		}

		auto& record = records.emplace_front(playerPawn);
		if (records.size() > max_ticks - 1)
			records.erase(records.end() - 1);
	}
}