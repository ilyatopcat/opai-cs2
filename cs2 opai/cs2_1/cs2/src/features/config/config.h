#pragma once

#include "../../sdk/math/Color.h"

#include "../../utils/KeyHandle.h"

class DumpedItem_t;

enum ZoomOverlay_t : int {
	ZOOM_OVERLAY_DEFAULT = 0,
	ZOOM_OVERLAY_REMOVE_OVERLAY = 1,
	ZOOM_OVERLAY_REMOVE_ALl = 2
};

enum Removals_t : int {
	REMOVALS_FLASHBANG = 1 << 0,
	REMOVALS_SMOKE = 1 << 1,
	REMOVALS_TORSO = 1 << 2,
	REMOVALS_TEAM_INTRO = 1 << 3
};

enum VisualRecoil_t : int {
	VISUAL_RECOIL_DEFAULT = 0,
	VISUAL_RECOIL_REMOVE_SHAKE = 1,
	VISUAL_RECOIL_REMOVE_ALL = 2
};

enum ChamsType_t : int {
	CHAMS_ENEMY,
	CHAMS_ENEMY_XQZ,
	CHAMS_LOCAL,
	CHAMS_VIEWMODEL,
	CHAMS_WEAPON,
	CHAMS_WEAPON_ENEMY,
	CHAMS_WEAPON_LOCAL,
	CHAMS_RAGDOLLS,
	CHAMS_MAX
};

struct world_modulation_t {
	bool disableFogRendering = true;

	bool bulletracers = true;

	bool custom_prop_color = false;

	ColorRGB worldColor = { 1.f, 1.f, 1.f };
	ColorRGB propColor = { 1.f, 1.f, 1.f };

	ColorRGB skyboxColor = { 0.36f, 0.36f, 0.36f };

	ColorRGBA sunCloundsColor = { 0.37f, 0.84f, 0.98f, 1.f };

	ColorRGB lightingColor = { 0.35f, 0.35f, 0.52f };

	ColorRGB bulletColor = { 0.52f, 0.52f, 0.52f };

	int exposure = 20;
};

struct players_t {
	/*struct enemies_t {

	}; enemies*/

	struct enemies_t {
		
	} enemies;

	struct localplayer_t {
		bool disableOverHeadInfo = true;
	} localplayer;
};

struct movement_t {
	bool bunnyHop = true;

	bool autoStrafe = true;

	int niggerExploit = 50;
	int autostrafeSmooth = 70;
};

struct thirdperson_t
{
	bool enabled = false;
	int distance = 90;

	int thirdperson_keybind, thirdperson_keybind_style = 0;
};

struct OverrideZoom_t {
	int fieldOfView = 0;

	int overlay = 1;

	bool forceSecondZoom = false;

	int line = 30;
	int gap = 5;

	ColorRGBA color = { 1, 1, 1, 1 };
};

struct skins_t {
	struct
	{
		bool enabled = true;
		int selected = 0;
	}agents;

	struct skin_data_t
	{
		int paint_kit = 0;
		int item_def_index = 0;

		int prev_skin = -1;
	}skin_settings[100];

	struct
	{
		bool enabled = true;
		int selected = 0;
	} knifes;

	struct
	{
		bool enabled = true;
		int selected = 0;
	} gloves;

	int selected_weapon = 0;
	DumpedItem_t* selected_item = nullptr;
};

struct esp_t {
	bool bounding_box = true;
	bool health_bar = true;
	bool name = true;
	bool weapon = true;

	ColorRGBA nameColor{ 1.f, 1.f, 1.f, 1.f };
};

struct chams_t {
	bool enable = false;
	int material = 0;
	int overlayMaterial = 0;

	ColorRGBA materialColor{ 1.f, 1.f, 1.f, 1.f };
	ColorRGBA overlayMaterialColor{ 1.f, 1.f, 1.f, 1.f };
};

struct config_t {
	int chamsSelector = 0;

	world_modulation_t world_modulation;
	chams_t chams[CHAMS_MAX];
	players_t players;
	movement_t movement;
	skins_t skins;
	esp_t esp;

	int fieldOfView = 135;

	OverrideZoom_t overrideZoom;

	thirdperson_t thirdperson;

	bool forceCrosshair = true;

	int removals = REMOVALS_FLASHBANG | REMOVALS_SMOKE | REMOVALS_TORSO | REMOVALS_TEAM_INTRO;

	bool radar = true;

	int visualRecoil = 2;
};

extern config_t config;