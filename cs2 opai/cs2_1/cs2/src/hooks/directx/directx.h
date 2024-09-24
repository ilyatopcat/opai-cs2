#pragma once

#include <dxgi.h>
#include <d3d11.h>
#include "../../../dependencies/imgui/imgui.h"
#include "../../../dependencies/imgui/imgui_impl_dx11.h"
#include "../../../dependencies/imgui/imgui_impl_win32.h"

namespace DirectX {
    inline void* PresentAddress;
    // inline void* ResizeAddress;

    void Initialize();
    void Uninitialize();

	namespace Present {
        void Initialize(IDXGISwapChain*);

        void NewFrame();
        void EndFrame();
	}

    // void Resize();
}