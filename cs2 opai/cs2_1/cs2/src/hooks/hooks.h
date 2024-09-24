#pragma once

#include "directx/directx.h"

#include "../features/features.h"
#include "../render/render.h"

#include "../sdk/entity/entity.h"
#include "../sdk/interfaces/interfaces.h"

#include "../sdk/classes/CCSGOInput.h"
#include "../sdk/classes/entity/CEntityInstance.h"
#include "../sdk/classes/entity/C_CSPlayerPawn.h"
#include "../sdk/classes/CGlowProperty.h"
#include "../sdk/classes/entity/C_CSWeaponBaseGun.h"
#include "../sdk/classes/CPlayer_CameraServices.h"
#include "../sdk/classes/C_PostProcessingVolume.h"
#include "../sdk/classes/CLightBinnerGPU.h"
#include "../sdk/classes/CSceneLightObject.h"
#include "../sdk/classes/CAnimatableSceneObjectDesc.h"
#include "../sdk/classes/CBaseSceneData.h"
#include "../sdk/classes/CMaterial2.h"
#include "../sdk/classes/CSceneView.h"
#include "../sdk/classes/CSceneLayer.h"
#include "../sdk/classes/CRenderContextDx11.h"
#include "../sdk/classes/entity/C_EnvSky.h"
#include "../sdk/classes/CViewRender.h"
#include "../sdk/classes/CViewSetup.h"
#include "../sdk/classes/CAggregateSceneObject.h"

#define IS_UNINITIALIZED(...)           \
    if (IsUninitialized)				\
        return Original(__VA_ARGS__);   \

#define SDK_HOOK(hook) &hook
#define SDK_HOOK_ORIGINAL(hook) reinterpret_cast<void**>(&hook)

#define CREATE_HOOK(hook, address)																									  \
	if (MH_CreateHook(address, SDK_HOOK(Hooks::hook::Hook), SDK_HOOK_ORIGINAL(Hooks::hook::Original)) != MH_OK) {	            	  \
		Hooks::Uninitialize();																										  \
																																	  \
        printf("[Hooks] Failed to hook: %s \n", #hook);																				  \
																																	  \
		return false;							            																		  \
	}

#define CREATE_HOOK_NAMESPACE(hook, returnType, ...)					\
	namespace hook {													\
		inline returnType (__fastcall* Original)(__VA_ARGS__);			\
																		\
		returnType __fastcall Hook(__VA_ARGS__);						\
																		\
		void UnHook();													\
	}

//#define ENABLE_TEST_HOOK
//#define ENABLE_TEST2_HOOK

namespace Hooks {
	inline bool IsUninitialized;

	bool Initialize();
	void Uninitialize();

	CREATE_HOOK_NAMESPACE(DirectXPresent, HRESULT, IDXGISwapChain*, unsigned int, unsigned int);

	/*
	namespace DirectXResize {
		inline HRESULT(__stdcall* Original)(IDXGISwapChain*, UINT, UINT, UINT, DXGI_FORMAT, UINT);
		inline HRESULT Hook(IDXGISwapChain*, UINT, UINT, UINT, DXGI_FORMAT, UINT);
	};
	*/

	CREATE_HOOK_NAMESPACE(CreateMove, void, CCSGOInput*, int, int);

	CREATE_HOOK_NAMESPACE(FrameStageNotify, void, void*, int);

	CREATE_HOOK_NAMESPACE(ValidateInput, void, CCSGOInput*, int);

	CREATE_HOOK_NAMESPACE(MouseInput, bool, CCSGOInput*);

	CREATE_HOOK_NAMESPACE(EnableCursor, void*, void*, bool);
	inline bool EnableCursorLastActive;

	CREATE_HOOK_NAMESPACE(UpdateInPVS, bool, CEntityInstance*);

#ifdef ENABLE_TEST_HOOK
	CREATE_HOOK_NAMESPACE(test, byte*, float*, float*, void*, void*, void*, void*, void*, void*)
#endif // ENABLE_TEST_Hook

#ifdef ENABLE_TEST2_HOOK
	CREATE_HOOK_NAMESPACE(test2, void*, void*)
	CREATE_HOOK_NAMESPACE(test3, Vector, float*, unsigned __int64, __int64, float*, float*)
#endif // ENABLE_TEST2_Hook

	CREATE_HOOK_NAMESPACE(UpdatePostProcessing, void*, C_PostProcessingVolume*, int);

	CREATE_HOOK_NAMESPACE(DrawLightSceneObject, void*, CLightBinnerGPU*, CSceneLightObject*, __int64);

	CREATE_HOOK_NAMESPACE(DrawAnimatableSceneObject, void, CAnimatableSceneObjectDesc*, CRenderContextDx11*, CSceneData*, int, CSceneView*, CSceneLayer*, void*, void*);

	CREATE_HOOK_NAMESPACE(UpdateSkybox, void*, C_EnvSky*);

	CREATE_HOOK_NAMESPACE(DrawOverHeadInfo, bool, C_CSPlayerPawn*);

	CREATE_HOOK_NAMESPACE(DrawCrosshair, bool, C_CSWeaponBaseGun*);

	CREATE_HOOK_NAMESPACE(DrawScopeOverlay, void, void*, void*);

	CREATE_HOOK_NAMESPACE(GetFieldOfView, float, void*);

	CREATE_HOOK_NAMESPACE(DrawFlashbang, void*, C_CSPlayerPawn*);

	CREATE_HOOK_NAMESPACE(DrawSmokeVolume, void, void*, __int64, __int64, unsigned int, __int64, unsigned int*);

	CREATE_HOOK_NAMESPACE(DrawTorso, bool, C_CSPlayerPawn*);

	CREATE_HOOK_NAMESPACE(DrawTeamIntro, void, void*, void*, byte*);

	CREATE_HOOK_NAMESPACE(DrawRadarEntities, void, void*);

	CREATE_HOOK_NAMESPACE(ViewPunch, void*, CPlayer_CameraServices*, float*, float*, float*);

	CREATE_HOOK_NAMESPACE(OverrideView, void*, CViewRender*, CViewSetup*, void*, void*, void*, void*);

	CREATE_HOOK_NAMESPACE(UpdateAggregateSceneObject, void*, CAggregateSceneObject*, void*);

	CREATE_HOOK_NAMESPACE(LevelInit, void*, void*, const char*);
	CREATE_HOOK_NAMESPACE(LevelShutdown, void*, void*);

	CREATE_HOOK_NAMESPACE(OnAddEntity, void*, void*, CEntityInstance*, int);
	CREATE_HOOK_NAMESPACE(OnRemoveEntity, void*, void*, CEntityInstance*, int);

	CREATE_HOOK_NAMESPACE(DrawGlow, void*, CGlowProperty*);

	CREATE_HOOK_NAMESPACE(ShouldUpdateKnifeSequences, void*, void*, void*, void*);
	CREATE_HOOK_NAMESPACE(DrawAggregateSceneObject, void, void*, void*, CBaseSceneData*, int, int, void*, void*, void*);
}