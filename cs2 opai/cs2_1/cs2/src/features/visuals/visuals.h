#pragma once

#include "../config/config.h"

#include "../../render/render.h"

#include "../../sdk/interfaces/interfaces.h"

#include "../../sdk/entity/entity.h"

#include "../../sdk/classes/C_PostProcessingVolume.h"
#include "../../sdk/classes/CSceneLightObject.h"

#include "../../sdk/classes/entity/C_CSPlayerPawn.h"
#include "../../sdk/classes/entity/C_EnvSky.h"
#include "../../sdk/classes/entity/C_Inferno.h"
#include "../../sdk/classes/entity/C_SmokeGrenadeProjectile.h"

#include <mutex>
#include <format>

constexpr float BAR_WIDTH = 2.f;

enum MaterialType_t : int {
	MATERIAL_TEXTURED,
	MATERIAL_FLAT,
	MATERIAL_METALLIC,
	MATERIAL_BUBBLE,
	MATERIAL_WIREFRAME,
	MATERIAL_GLOW,
	MATERIAL_MAX,
};

enum MaterialParam_t : int {
	MATERIAL_PARAM_DEFAULT,
	MATERIAL_PARAM_IGNOREZ,
	MATERIAL_PARAM_MAX
};

class CClassTracerInfo
{
public:
	unsigned int effectIndex = -1;
	Vector* positions = nullptr;
	float* times = nullptr;
	CStrongHandle<CParticleSnapshot> handleSnapshotParticle{};
	CParticleData particleData_;
};

class CHitData
{
public:
	float time;
	CSceneHitboxData hitbox_data;
	CSceneHitboxPosition hitbox_position;
	ColorRGBA clr;
};

namespace Visuals {
	namespace WorldModulation {
		void Skybox();
		void Modulate();
		void ProcessTracers(Vector start, Vector end, ColorRGB color);
		void Skybox(C_EnvSky*);

		void Lighting(CSceneLightObject*);

		void Exposure(C_CSPlayerPawn*);
		void Exposure(C_PostProcessingVolume*);

		inline std::vector<CClassTracerInfo> bullets{};
	}

	void ScopeOverlay(C_CSPlayerPawn*);
	
	struct Box
	{
		bool found = false;

		float x;
		float y;
		float w;
		float h;
	};

	namespace Players {
		struct PlayerInfo
		{
			bool valid = false;

			int handle;
			int health;
			int ammo;
			int maxAmmo;

			Box box;

			std::string name;
			std::string weaponName;
		};

		inline std::mutex playerMutex;
		inline std::unordered_map<int, PlayerInfo> playerMap;

		Box GetBox(C_CSPlayerPawn* entity);

		void RenderBBox(Box& box);
		void RenderHealth(PlayerInfo& info);
		void RenderName(PlayerInfo& info);
		void RenderWeapon(PlayerInfo& info);

		void Store();
		void Run();
	}

	namespace Weapons {
		constexpr float MAX_DISTANCE = 450.f;
		constexpr float MAX_NADE_DISTANCE = 650.f;
		constexpr float NADE_TIMER_WIDTH = 25.f;

		struct WeaponInfo
		{
			bool valid = false;
			bool isMolotov = false;
			bool isSmoke = false;

			int handle;
			int ammo;
			int maxAmmo;

			float expireTime;
			float lifeTime;
			float fireRange;
			float alpha;

			Box box;

			std::string name;

			std::vector<ImVec2> infernoPos;
		};

		inline std::vector<C_BaseEntity*> weaponEntities;

		inline std::mutex weaponMutex;
		inline std::unordered_map<int, WeaponInfo> weaponMap;

		void RenderBBox(WeaponInfo& info);
		void RenderNameAndAmmo(WeaponInfo& info);
		void RenderRadius(WeaponInfo& info);
		Box GetBox(C_BaseEntity* entity);

		void Store();
		void Run();
	}

	namespace Chams {
		inline CMaterial2* materials[MATERIAL_MAX][MATERIAL_PARAM_MAX]{};

		void initMaterials();
		int GetEnemyType(C_BaseEntity* entity);
	}

	inline int lastCountBullet = 0;
	void ThirdPerson();
	void ProcessBulletImpactsOnClient();
}