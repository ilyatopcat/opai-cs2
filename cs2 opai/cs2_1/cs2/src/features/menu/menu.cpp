#include <string>

#include "../../../dependencies/imgui/imgui.h"

#include "../config/config.h"

#include "../../render/render.h"

#include "../skins/skins.h"

#include "menu.h"

#define WM_KEYUP 0x0101

#define VK_INSERT 0x2D

void Menu::Render() {
    if (!isOpen)
        return;

    /*
    ImGuiIO& io = ImGui::GetIO();
    ImGuiStyle& style = ImGui::GetStyle();
    */

    ImGui::SetNextWindowSize(ImVec2(750, 550));

    ImGui::Begin("Menu", nullptr, ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoTitleBar);
    
    ImGui::BeginTabBar("Tabs");

    ImVec2 mousePos = ImGui::GetMousePos();
    ImVec2 windowPos = ImGui::GetWindowPos();
    ImVec2 windowSize = ImGui::GetWindowSize();

    isCursorInMenu = (mousePos.x >= windowPos.x && mousePos.x <= windowPos.x + windowSize.x && mousePos.y >= windowPos.y && mousePos.y <= windowPos.y + windowSize.y);

    if (ImGui::BeginTabItem("Aimbot")) {
        ImGui::EndTabItem();
    }

    if (ImGui::BeginTabItem("ESP")) {
        ImGui::Checkbox("Disable Over Head Information", &config.players.localplayer.disableOverHeadInfo);
        ImGui::Text("Esp");
        ImGui::Separator();
        {
            ImGui::Checkbox("Bounding Box", &config.esp.bounding_box);
            ImGui::Checkbox("Health bar", &config.esp.health_bar);
            ImGui::Checkbox("Name", &config.esp.name);
            ImGui::ColorEdit3("Name Color", reinterpret_cast<float*>(&config.esp.nameColor), ImGuiColorEditFlags_NoInputs);
            ImGui::Checkbox("Weapon name", &config.esp.weapon);
        };

        ImGui::Text("Chams");
        ImGui::Separator();
        {
            static const char* chamsType[] = { "Enemy", "Enemy XQZ", "Local", "Viewmodel", "Weapon", "Enemy Weapon", "Local Weapon", "Ragdolls" };

            ImGui::Combo("Type", &config.chamsSelector, chamsType, IM_ARRAYSIZE(chamsType));

            auto& chamsConfig = config.chams[config.chamsSelector];
            {
                ImGui::Checkbox("Enable", &chamsConfig.enable);

                static const char* chamsMaterial[] = { "None", "Textured", "Flat", "Metalic", "Bubble", "Wireframe", "Glow" };

                ImGui::Combo("Material", &chamsConfig.material, chamsMaterial, IM_ARRAYSIZE(chamsMaterial));
                if (chamsConfig.material > 0)
                    ImGui::ColorEdit4("Material Color", reinterpret_cast<float*>(&chamsConfig.materialColor), ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaBar);

                ImGui::Combo("Overlay Material", &chamsConfig.overlayMaterial, chamsMaterial, IM_ARRAYSIZE(chamsMaterial));
                if (chamsConfig.overlayMaterial > 0)
                    ImGui::ColorEdit4("Overlay Material Color", reinterpret_cast<float*>(&chamsConfig.overlayMaterialColor), ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaBar);
            }
        }

        ImGui::EndTabItem();
    }

    if (ImGui::BeginTabItem("Visuals")) {
        ImGui::Checkbox("Disable Fog Rendering", &config.world_modulation.disableFogRendering);

        ImGui::ColorEdit3("World Color", reinterpret_cast<float*>(&config.world_modulation.worldColor), ImGuiColorEditFlags_NoInputs);
        ImGui::Checkbox("Custom prop color", &config.world_modulation.custom_prop_color);
        if (config.world_modulation.custom_prop_color)
            ImGui::ColorEdit3("Prop Color", reinterpret_cast<float*>(&config.world_modulation.propColor), ImGuiColorEditFlags_NoInputs);

        ImGui::ColorEdit3("Skybox Color", reinterpret_cast<float*>(&config.world_modulation.skyboxColor), ImGuiColorEditFlags_NoInputs);

        ImGui::ColorEdit4("Sun & Clounds Color", reinterpret_cast<float*>(&config.world_modulation.sunCloundsColor), ImGuiColorEditFlags_NoInputs);

        ImGui::ColorEdit3("Lighting Color", reinterpret_cast<float*>(&config.world_modulation.lightingColor), ImGuiColorEditFlags_NoInputs);

        ImGui::Checkbox("Enable Bullet tracers", &config.world_modulation.bulletracers);

        if (config.world_modulation.bulletracers)
            ImGui::ColorEdit3("Bullet Colors", reinterpret_cast<float*>(&config.world_modulation.bulletColor), ImGuiColorEditFlags_NoInputs);

        ImGui::SliderInt("Exposure", reinterpret_cast<int*>(&config.world_modulation.exposure), 1, 100);

        static const char* removalsItems[] = { "Flashbang", "Smoke", "Torso", "Team Intro"};

        ImGui::Selectable("Removals", &config.removals, removalsItems, IM_ARRAYSIZE(removalsItems));

        ImGui::Checkbox("Radar", &config.radar);

        static const char* visualRecoilItems[] = { "Default", "Remove Shake", "Remove All" };

        ImGui::Combo("Visual Recoil", &config.visualRecoil, visualRecoilItems, IM_ARRAYSIZE(visualRecoilItems));

        ImGui::EndTabItem();
    }

    if (ImGui::BeginTabItem("Skins")) {
        static std::vector<const char*> weaponNames{};

        if (weaponNames.size() < SkinChanger::dumped_items.size())
        {
            for (auto& item : SkinChanger::dumped_items)
                weaponNames.emplace_back(item.name);
        }

        ImGui::Combo("Weapons", &config.skins.selected_weapon, weaponNames.data(), weaponNames.size());
        auto& selectedEntry = config.skins.skin_settings[config.skins.selected_weapon];

        if (ImGui::BeginListBox("##skins"))
        {
            auto& selectedWeaponCfg = SkinChanger::dumped_items[config.skins.selected_weapon];

            for (auto& skin : selectedWeaponCfg.dumped_skins)
            {
                ImGui::PushID(&skin);
                if (ImGui::Selectable(skin.name, selectedWeaponCfg.selected_skin == &skin))
                {
                    if (selectedWeaponCfg.selected_skin == &skin)
                        selectedWeaponCfg.selected_skin = nullptr;
                    else
                    {
                        selectedWeaponCfg.selected_skin = &skin;
                        selectedEntry.paint_kit = skin.id;
                    }
                }
                ImGui::PopID();
            }
            ImGui::EndListBox();
        }

        ImGui::Checkbox("Enable agent changer", &config.skins.agents.enabled);
        if (config.skins.agents.enabled)
            ImGui::ListBox("##agents", &config.skins.agents.selected, SkinChanger::Agents::dumped_agent_name.data(), SkinChanger::Agents::dumped_agent_name.size());

        ImGui::Checkbox("Enable knife changer", &config.skins.knifes.enabled);
        if (config.skins.knifes.enabled)
            ImGui::ListBox("##knifes", &config.skins.knifes.selected, SkinChanger::Knifes::dumped_knife_name.data(), SkinChanger::Knifes::dumped_knife_name.size());
        
        ImGui::Checkbox("Enable glove changer", &config.skins.gloves.enabled);
        if (config.skins.gloves.enabled)
            ImGui::ListBox("##gloves", &config.skins.gloves.selected, SkinChanger::Gloves::dumped_glove_name.data(), SkinChanger::Gloves::dumped_glove_name.size());

        ImGui::EndTabItem();
    }

    if (ImGui::BeginTabItem("Misc")) {
        ImGui::SliderInt("Field of View", &config.fieldOfView, 40, 135);

        ImGui::SliderInt("Override Zoom", &config.overrideZoom.fieldOfView, 0, 100);

        static const char* ScopeOverlayItems[] = { "Default", "Remove Overlay", "Remove All" };

        ImGui::Combo("Scope Overlay", &config.overrideZoom.overlay, ScopeOverlayItems, IM_ARRAYSIZE(ScopeOverlayItems));

        ImGui::Checkbox("Force Second Zoom", &config.overrideZoom.forceSecondZoom);

        ImGui::Checkbox("Enable Third person", &config.thirdperson.enabled);
        if (config.thirdperson.enabled) {
            ImGui::SliderInt("Third person distance", &config.thirdperson.distance, 0, 200);
            ImGui::Keybind("Third person keybind", &config.thirdperson.thirdperson_keybind, &config.thirdperson.thirdperson_keybind_style);
        }

        if (config.overrideZoom.overlay == ZOOM_OVERLAY_REMOVE_OVERLAY) {
            ImGui::SliderInt("Line", &config.overrideZoom.line, 0, 100);
            ImGui::SliderInt("Gap", &config.overrideZoom.gap, 0, 100);

            ImGui::ColorEdit4("Lines Color", reinterpret_cast<float*>(&config.overrideZoom.color), ImGuiColorEditFlags_NoInputs);
        }

        ImGui::Checkbox("Force Crosshair", &config.forceCrosshair);

        ImGui::Checkbox("Bunny Hop", &config.movement.bunnyHop);

        ImGui::Checkbox("Auto Strafe", &config.movement.autoStrafe);
        ImGui::SliderInt("Auto Strafe Smooth", &config.movement.autostrafeSmooth, 0, 100);

        ImGui::EndTabItem();
    }

    if (ImGui::BeginTabItem("Settings")) {
        ImGui::EndTabItem();
    }

    ImGui::EndTabBar();

    ImGui::End();
}

void Menu::CreateMove(CUserCmd* pUserCmd) {
    if (!isOpen)
        return;

    pUserCmd->buttons.value &= ~(IN_ATTACK | IN_ATTACK2);
    pUserCmd->buttons.scroll &= ~(IN_ATTACK | IN_ATTACK2);
    pUserCmd->buttons.changed &= ~(IN_ATTACK | IN_ATTACK2);
}