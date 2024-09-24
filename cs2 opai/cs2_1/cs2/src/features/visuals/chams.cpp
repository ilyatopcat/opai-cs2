#include <array>
#include <Windows.h>

#include "../../sdk/classes/KeyValues3.h"
#include "../../utils/fmt.h"
#include "visuals.h"

namespace Visuals::Chams 
{
	static void SetKVType(KeyValues3* kv3, int type, int type2)
	{
		static auto ptr = Utils::OpcodeScan("client.dll", "40 53 48 83 EC 20 48 8B 01 48 8B D9 44");
		using fn = void(__fastcall*)(KeyValues3*, int, int);

		static auto setKV = (fn)ptr;
		setKV(kv3, type, type2);
	}

	static bool LoadKV3(KeyValues3* kv3, std::uintptr_t* string, const char* buffer, const KV3ID_t* kvId, char* unkStr)
	{
		static auto ptr = GetProcAddress(GetModuleHandleA("tier0.dll"), "?LoadKV3@@YA_NPEAVKeyValues3@@PEAVCUtlString@@PEBDAEBUKV3ID_t@@2@Z");
		using fn = bool(__fastcall*)(KeyValues3*, std::uintptr_t*, const char*, const KV3ID_t*, char*);
		
		static auto loadKV = (fn)ptr;
		return loadKV(kv3, string, buffer, kvId, unkStr);
	}

	static CMaterial2* createMaterial(const char* materialShader)
	{
		KeyValues3 kv3{};
		SetKVType(&kv3, KV_BASIC_NULL, KV_BASIC_STRING);

		KV3ID_t kvId{ "generic", 0x469806E97412167C, 0x0E73790B53EE6F2AF };
		if (!LoadKV3(&kv3, nullptr, materialShader, &kvId, nullptr))
			return nullptr;

		static auto ptr = Utils::OpcodeScan("materialsystem2.dll", "48 89 5C 24 08 48 89 6C 24 18 56 57 41 56 48");
		using fn = void(__fastcall*)(std::uintptr_t*, CMaterial2***, const char*, KeyValues3*, int, std::uint8_t);
		static auto createMaterial = (fn)ptr;

		CMaterial2** out{};
		createMaterial(nullptr, &out, "airflow", &kv3, 0, 1);

		return *out;
	}
}

void Visuals::Chams::initMaterials()
{
	materials[MATERIAL_TEXTURED][MATERIAL_PARAM_DEFAULT] = createMaterial(R"#(<!-- kv3 encoding:text:version{e21c7f3c-8a33-41c5-9977-a76d3a32aa0d}
			format:generic:version{7412167c-06e9-4698-aff2-e63eb59037e7} -->
			{
                Shader = "csgo_complex.vfx"
				F_IGNOREZ = 0
				F_DISABLE_Z_WRITE = 0
				F_DISABLE_Z_BUFFERING = 0
				F_RENDER_BACKFACES = 0
				F_TRANSLUCENT = 1
				F_PAINT_VERTEX_COLORS = 1
				g_vColorTint = [1.000000, 1.000000, 1.000000, 1.000000]
				TextureNormal = resource:"materials/default/default_normal.tga"
				g_tAmbientOcclusion = resource:"materials/default/default_ao_tga_559f1ac6.vtex"
				g_tColor = resource:"materials/default/default_color_tga_72dcfbfd.vtex"
				g_tNormal = resource:"materials/default/default_normal_tga_7be61377.vtex"
			} )#");

	materials[MATERIAL_TEXTURED][MATERIAL_PARAM_IGNOREZ] = createMaterial(R"#(<!-- kv3 encoding:text:version{e21c7f3c-8a33-41c5-9977-a76d3a32aa0d}
			format:generic:version{7412167c-06e9-4698-aff2-e63eb59037e7} -->
			{
                Shader = "csgo_complex.vfx"
				F_IGNOREZ = 1
				F_DISABLE_Z_WRITE = 1
				F_DISABLE_Z_BUFFERING = 1
				F_RENDER_BACKFACES = 0
				F_TRANSLUCENT = 1
				F_PAINT_VERTEX_COLORS = 1
				g_vColorTint = [1.000000, 1.000000, 1.000000, 0.300000]
				TextureNormal = resource:"materials/default/default_normal.tga"
				g_tAmbientOcclusion = resource:"materials/default/default_ao_tga_559f1ac6.vtex"
				g_tColor = resource:"materials/default/default_color_tga_72dcfbfd.vtex"
				g_tNormal = resource:"materials/default/default_normal_tga_7be61377.vtex"
			} )#");

	materials[MATERIAL_FLAT][MATERIAL_PARAM_DEFAULT] = createMaterial(R"#(<!-- kv3 encoding:text:version{e21c7f3c-8a33-41c5-9977-a76d3a32aa0d}
			format:generic:version{7412167c-06e9-4698-aff2-e63eb59037e7} -->
			{
				Shader = "csgo_unlitgeneric.vfx"
				F_DISABLE_Z_BUFFERING = 0
				F_BLEND_MODE = 1
				F_TRANSLUCENT = 1
				g_vColorTint = [1.000000, 1.000000, 1.000000, 0.000000]
				g_vGlossinessRange = [0.000000, 1.000000, 0.000000, 0.000000]
				g_vNormalTexCoordScale = [1.000000, 1.000000, 0.000000, 0.000000]
				g_vTexCoordOffset = [0.000000, 0.000000, 0.000000, 0.000000]
				g_vTexCoordScale = [1.000000, 1.000000, 0.000000, 0.000000]
				g_tColor = resource:"materials/dev/primary_white_color_tga_f7b257f6.vtex"
				g_tNormal = resource:"materials/default/default_normal_tga_7652cb.vtex"
				g_tRoughness = resource:"materials/default/default_normal_tga_b3f4ec4c.vtex"
			} )#");

	materials[MATERIAL_FLAT][MATERIAL_PARAM_IGNOREZ] = createMaterial(R"#(<!-- kv3 encoding:text:version{e21c7f3c-8a33-41c5-9977-a76d3a32aa0d}
			format:generic:version{7412167c-06e9-4698-aff2-e63eb59037e7} -->
			{
				Shader = "csgo_unlitgeneric.vfx"
				F_DISABLE_Z_BUFFERING = 1
				F_BLEND_MODE = 1
				F_TRANSLUCENT = 1
				g_vColorTint = [1.000000, 1.000000, 1.000000, 0.000000]
				g_vGlossinessRange = [0.000000, 1.000000, 0.000000, 0.000000]
				g_vNormalTexCoordScale = [1.000000, 1.000000, 0.000000, 0.000000]
				g_vTexCoordOffset = [0.000000, 0.000000, 0.000000, 0.000000]
				g_vTexCoordScale = [1.000000, 1.000000, 0.000000, 0.000000]
				g_tColor = resource:"materials/dev/primary_white_color_tga_f7b257f6.vtex"
				g_tNormal = resource:"materials/default/default_normal_tga_7652cb.vtex"
				g_tRoughness = resource:"materials/default/default_normal_tga_b3f4ec4c.vtex"
			} )#");
}

int Visuals::Chams::GetEnemyType(C_BaseEntity* entity)
{
	auto localPawn = Entity::GetLocalPlayerPawn();

	if (entity->isWeapon())
	{
		auto weapon = entity->As<C_BasePlayerWeapon>();
		CHandle handle(weapon->m_hOwnerEntity().GetEntryIndex());

		auto player = handle.Get<CEntityInstance>();
		if (player && localPawn)
		{
			auto playerPawn = player->As<C_CSPlayerPawn>();
			if (playerPawn == localPawn)
				return CHAMS_WEAPON_LOCAL;
			else if (playerPawn->m_iTeamNum() != localPawn->m_iTeamNum())
				return CHAMS_WEAPON_ENEMY;
		}

		if (weapon->m_hOwnerEntity().GetEntryIndex() <= 0)
			return CHAMS_WEAPON;
	}

	std::string_view name{ entity->GetEntityClassName() };
	if (name.find("C_CSPlayerPawn") != std::string::npos && localPawn)
	{
		auto playerPawn = entity->As<C_CSPlayerPawn>();
		if (playerPawn == localPawn)
			return CHAMS_LOCAL;
		else if (playerPawn->m_iTeamNum() != localPawn->m_iTeamNum())
		{
			if (playerPawn->IsAlive())
				return CHAMS_ENEMY + CHAMS_ENEMY_XQZ;
			else
				return CHAMS_RAGDOLLS;
		}
	}

	return -1;
}
