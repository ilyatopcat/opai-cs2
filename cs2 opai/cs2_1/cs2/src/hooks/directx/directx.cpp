#include <stdint.h>

#include "../hooks.h"

#include "../../utils/vmt.h"
#include "../../utils/utils.h"

HWND window;
WNDPROC windowProcOriginal = NULL;

IDXGISwapChain* g_pSwapChain;
ID3D11Device* g_pDevice;
ID3D11DeviceContext* g_pDeviceContext;
ID3D11RenderTargetView* g_pRenderTarget;

IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

LRESULT WindowProcHook(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam);

    if (uMsg == WM_KEYUP && wParam == VK_INSERT)
        Menu::isOpen = !Menu::isOpen;

    Hooks::EnableCursor::Original(Interfaces::inputSystem, Menu::isOpen ? false : Hooks::EnableCursorLastActive);

    return CallWindowProc(windowProcOriginal, hWnd, uMsg, wParam, lParam);
}

void DirectX::Initialize() {
    uint8_t* ptr = Utils::OpcodeScanRelative("rendersystemdx11.dll", "66 0F 7F 0D ?? ?? ?? ?? 66 0F 7F 05 ?? ?? ?? ?? 0F 1F 40 00", 0x0, 0x4, 0x8); // xref: "Display GPU memory usage." (https://i.imgur.com/ChGjXtn.png)
    if (ptr == nullptr)
        return;

    uint8_t* next_ptr = **reinterpret_cast<uint8_t***>(ptr);
    if (next_ptr == nullptr)
        return;

    g_pSwapChain = *reinterpret_cast<IDXGISwapChain**>(next_ptr + 0x170);
    if (g_pSwapChain == nullptr)
        return;

    PresentAddress = vmt::GetVMethod(g_pSwapChain, 8);
    // ResizeAddress = vmt::GetVMethod(g_pSwapChain, 13);
}

void DirectX::Uninitialize() {
    if (!windowProcOriginal)
        return;

    SetWindowLongPtr(window, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(windowProcOriginal));
}

/*
void DirectX::Resize() {
    if (g_pRenderTarget) {
        g_pRenderTarget->Release();
        g_pRenderTarget = nullptr;
    }

    if (g_pDeviceContext) {
        g_pDeviceContext->Release();
        g_pDeviceContext = nullptr;
    }

    if (g_pDevice) {
        g_pDevice->Release();
        g_pDevice = nullptr;
    }

    ImGui_ImplWin32_Shutdown();
    ImGui_ImplDX11_Shutdown();
    ImGui::DestroyContext();
}
*/

void DirectX::Present::Initialize(IDXGISwapChain* pSwapChain) {
    if (g_pDevice)
        return;

    if (!SUCCEEDED(pSwapChain->GetDevice(__uuidof(ID3D11Device), (void**)&g_pDevice)))
        return;

    g_pDevice->GetImmediateContext(&g_pDeviceContext);

    DXGI_SWAP_CHAIN_DESC sd;
    pSwapChain->GetDesc(&sd);
    window = sd.OutputWindow;

    ID3D11Texture2D* pBackBuffer;
    pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);

    g_pDevice->CreateRenderTargetView(pBackBuffer, NULL, &g_pRenderTarget);

    pBackBuffer->Release();

    ImGui::CreateContext();

    ImGuiIO io = ImGui::GetIO();
    io.ConfigFlags = ImGuiConfigFlags_NoMouseCursorChange;

    ImGui_ImplWin32_Init(window);
    ImGui_ImplDX11_Init(g_pDevice, g_pDeviceContext);

    Render::Initialize();

    windowProcOriginal = reinterpret_cast<WNDPROC>(SetWindowLongPtr(window, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(WindowProcHook)));
}

void DirectX::Present::NewFrame() {
    ImGuiIO io = ImGui::GetIO();

    Render::UpdateScreenSize(io);

    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();
}

void DirectX::Present::EndFrame() {
    ImGui::Render();

    g_pDeviceContext->OMSetRenderTargets(1, &g_pRenderTarget, nullptr);

    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}