#include "skins.h"

void SkinChanger::OnInit()
{
	auto item_schema = Interfaces::client->GetEconItemSystem()->GetEconItemSchema();
	if (!item_schema)
		return;

	if (!dumped_items.empty())
		return;

    const auto& vecItems = item_schema->m_SortedItemDefinitionMap;
    const auto& paintKits = item_schema->m_PaintKits;
    const auto& alternateIcons = item_schema->m_AlternateIconsMap;

    for (const auto& it : vecItems)
    {
        CEconItemDefinition* item = it.m_value;
        if (!item)
            continue;

        const bool isWeapon = item->IsWeapon();
        const bool isAgent = item->IsAgent();
        const bool isKnife = item->IsKnife(true);
        const bool isGlove = item->IsGlove(true);

        const char* itemBaseName = item->m_pszItemBaseName;
        if (!itemBaseName || itemBaseName[0] == '\0')
            continue;

        if (isAgent) {
            Agents::dumped_agent_models.emplace_back(item->GetModelName());
            Agents::dumped_agent_name.emplace_back(Interfaces::localize->FindSafe(item->m_pszItemBaseName));
        }

        if (isKnife)
        {
            Knifes::dumped_knife_models.emplace_back(item->GetModelName());
            Knifes::dumped_knife_name.emplace_back(Interfaces::localize->FindSafe(item->m_pszItemBaseName));
        }

        if (isGlove) {
            Gloves::dumped_glove_models.emplace_back(item->GetModelName());
            Gloves::dumped_glove_name.emplace_back(Interfaces::localize->FindSafe(item->m_pszItemBaseName));
            Gloves::glove_idxs.emplace_back(item->m_uDefinitionIndex);
        }

        if (!isWeapon && !isKnife && !isGlove)
            continue;

        DumpedItem_t dumpedItem{};
        dumpedItem.name = Interfaces::localize->FindSafe(itemBaseName);
        dumpedItem.def_index = item->m_uDefinitionIndex;
        dumpedItem.rarity = item->m_nItemRarity;

        if (isKnife || isGlove)
            dumpedItem.unusual_item = true;

        for (const auto& it : paintKits)
        {
            CPaintKit* paint_kit = it.m_value;
            if (!paint_kit || paint_kit->m_nID == 0 || paint_kit->m_nID == 9001)
                continue;

            const uint64_t skin_key = GetAlternateIconKeyForWeaponPaintWearItem(item->m_uDefinitionIndex, paint_kit->m_nID, 0);
            if (alternateIcons.FindByKey(skin_key).has_value())
            {
                DumpedSkins_t dumped_skin;
                dumped_skin.name = Interfaces::localize->FindSafe(paint_kit->m_szDescriptionTag);
                dumped_skin.id = paint_kit->m_nID;
                dumped_skin.rarity = paint_kit->m_nRarity;
                dumpedItem.dumped_skins.emplace_back(dumped_skin);
            }
        }

        if (!dumpedItem.dumped_skins.empty() && isWeapon)
            std::sort(dumpedItem.dumped_skins.begin(), dumpedItem.dumped_skins.end(), [](const DumpedSkins_t& a, const DumpedSkins_t& b) {return a.rarity > b.rarity; });

        dumped_items.emplace_back(dumpedItem);
    }
}

void SkinChanger::Agents::Init(int stage)
{
    auto localPlayerPawn = Entity::GetLocalPlayerPawn();
    if (!localPlayerPawn || !localPlayerPawn->IsAlive() || dumped_agent_models.empty() || stage != 6 || !config.skins.agents.enabled)
        return;

    config.skins.agents.selected = std::clamp<int>(config.skins.agents.selected, 0, dumped_agent_models.size() - 1);

    localPlayerPawn->SetModel(dumped_agent_models.at(config.skins.agents.selected));
}

void InvalidateGloveMaterial(C_BaseViewModel* pViewModel)
{
    MaterialData_t* material_info = reinterpret_cast<MaterialData_t*>(pViewModel + 0xF80);
    for (std::uint32_t i = 0; i < material_info->records_size; i++)
    {
        if (material_info->records[i].magic_number == 0xF143B82A)
        {
            material_info->records[i].type = 0xffffffff;
            break;
        }
    }
}

void SkinChanger::Gloves::Init(C_BaseViewModel* view_model)
{
    auto localPlayerPawn = Entity::GetLocalPlayerPawn();
    if (!localPlayerPawn || !localPlayerPawn->IsAlive() || dumped_glove_models.empty() || !config.skins.gloves.enabled)
        return;
    
    auto econGloves = &localPlayerPawn->m_EconGloves();
    auto currentModel = Gloves::glove_idxs[config.skins.gloves.selected];
    auto modelSkin = config.skins.skin_settings[config.skins.selected_weapon].paint_kit;

    static int updateFrames{ -1 };
    static int lastSkin{ -1 };
    static float lastSpawnTime{ -1.f };
    
    if (econGloves->m_iItemDefinitionIndex() != currentModel || localPlayerPawn->m_flLastSpawnTimeIndex() != lastSpawnTime)
    {
        econGloves->m_iItemDefinitionIndex() = currentModel;

        lastSpawnTime   = localPlayerPawn->m_flLastSpawnTimeIndex();
        updateFrames    = 3;
    }

    if (modelSkin != lastSkin && modelSkin > 0)
    {
        using fnCreateNewPaintKit = CPaintKit * (__fastcall*)(C_EconItemView*);
        static fnCreateNewPaintKit oCreateNewPaintKit = reinterpret_cast<fnCreateNewPaintKit>(Utils::OpcodeScan("client.dll", "48 89 5C 24 10 56 48 83 EC 20 48 8B 01 FF 50 10 48 8B 1D ? ? ? ?"));

        auto paintKit = oCreateNewPaintKit(econGloves);
        if (paintKit && paintKit->m_szName)
        {
            lastSkin = modelSkin;

            auto curPaint = Interfaces::client->GetEconItemSystem()->GetEconItemSchema()->m_PaintKits.FindByKey(modelSkin);
            if (curPaint.has_value())
                paintKit->m_szName = curPaint.value()->m_szName;
        }
    }

    if (updateFrames)
    {
        InvalidateGloveMaterial(view_model);

        econGloves->m_bInitialized() = true;
        localPlayerPawn->m_bNeedToReApplyGloves() = true;
        --updateFrames;
    }
}

void SkinChanger::Knifes::Init(int stage)
{
    auto localPlayerPawn = Entity::GetLocalPlayerPawn();
    if (!localPlayerPawn || !localPlayerPawn->IsAlive() || dumped_knife_models.empty() || !config.skins.knifes.enabled)
        return;

    auto weaponService = localPlayerPawn->m_pWeaponServices();
    if (!weaponService)
        return;

    auto viewModelService = localPlayerPawn->m_pViewModelServices();
    if (!viewModelService)
        return;

    auto viewModel = reinterpret_cast<C_BaseViewModel*>(viewModelService->m_hViewModel().Get());
    if (!viewModel)
        return;

    if (stage == FRAME_NET_UPDATE_POST_DATA_UPDATE_END)
        SkinChanger::Gloves::Init(viewModel);

    auto& my_weapons = weaponService->m_hMyWeapons();

    for (auto i = 0; i < my_weapons.m_nSize; i++)
    {
        auto weapon = my_weapons.m_pElements[i].Get<C_EconEntity>();
        if (!weapon)
            continue;

        auto attributeManager = weapon->m_AttributeManager();
        if (!attributeManager)
            continue;

        auto item = attributeManager->m_Item();
        if (!item)
            continue;

        auto itemDefinition = item->GetStaticData();
        if (!itemDefinition)
            continue;

        auto bodyComponent = viewModel->m_CBodyComponent();
        if (!bodyComponent)
            continue;

        auto weaponScene = weapon->m_pGameSceneNode();
        if (!weaponScene)
            continue;

        auto viewModelScene = viewModel->m_pGameSceneNode();
        if (!viewModelScene)
            continue;

        bool isKnife = itemDefinition->IsKnife(false);

        // TO-DO: detect updated knife @opai
        int curWeapon = GetSkinConfig(item->m_iItemDefinitionIndex());
        if (!isKnife && curWeapon == CONFIG_UNKNOWN)
            continue;

        auto curSkin = &config.skins.skin_settings[curWeapon];

        if (curSkin->paint_kit > 0)
        {
            auto paintkit = Interfaces::client->GetEconItemSystem()->GetEconItemSchema()->m_PaintKits.FindByKey(curSkin->paint_kit);
            bool useOldModel = paintkit.has_value() && *reinterpret_cast<bool*>(reinterpret_cast<uintptr_t>(paintkit.value()) + 0xB2);

            uint64_t meshMask = 1 + static_cast<uint64_t>(useOldModel);

            weapon->m_nFallbackStatTrak() = 1337;
            weapon->m_nFallbackPaintKit() = curSkin->paint_kit;

            item->m_iItemIDHigh() = -1;

            weaponScene->SetMeshGroupMask(meshMask);
            viewModelScene->SetMeshGroupMask(meshMask);
        }

        if (stage == FRAME_NET_UPDATE_POST_DATA_UPDATE_END && isKnife)
        {
            int selectedKnife = config.skins.knifes.selected;
                
            weapon->SetModel(dumped_knife_models.at(selectedKnife));
            item->m_iItemDefinitionIndex() = knife_idxs.at(selectedKnife);

            if (viewModel->m_hWeapon() == weapon->GetRefEHandle())
                viewModel->SetModel(dumped_knife_models.at(selectedKnife));

            weapon->UpdateSubclass();
        }

        if (curSkin->prev_skin != curSkin->paint_kit)
        {
            auto weaponBase = weapon->As<C_CSWeaponBase>();
            if (!weaponBase)
                continue;

            // @shialex put force update here (@opai)

            curSkin->prev_skin = curSkin->paint_kit;
        }
    }
}