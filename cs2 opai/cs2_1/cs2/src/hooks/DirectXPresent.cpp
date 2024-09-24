#include "hooks.h"

#include "../sdk/entity/entity.h"

#include "../features/menu/menu.h"
#include "../features/features.h"
#include "../render/render.h"

HRESULT Hooks::DirectXPresent::Hook(IDXGISwapChain* pSwapChain, unsigned int uSyncInterval, unsigned int uFlags) {
    IS_UNINITIALIZED(pSwapChain, uSyncInterval, uFlags);

    DirectX::Present::Initialize(pSwapChain);

    DirectX::Present::NewFrame();

    Render::UpdateBackgroundDrawList(ImGui::GetBackgroundDrawList());

    {
        C_CSPlayerPawn* pLocalPlayerPawn = Entity::GetLocalPlayerPawn();
        Visuals::WorldModulation::Skybox();
        Visuals::WorldModulation::Exposure(pLocalPlayerPawn);
        Visuals::ScopeOverlay(pLocalPlayerPawn);
        Visuals::Players::Run();
        Visuals::Weapons::Run();

        Menu::Render();
    }

    DirectX::Present::EndFrame();

    return Original(pSwapChain, uSyncInterval, uFlags);
}