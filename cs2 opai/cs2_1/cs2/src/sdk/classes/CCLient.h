#pragma once

#include <stdint.h>
#include <string>

#include "../../utils/utils.h"
#include "../../sdk/math/CUtlBuffer.h"
#include "../../sdk/classes/CUtlVector.h"

#include "../math/Vector.h"

#include "CDebugOverlaySystem.h"
#include "../../utils/vmt.h"

#include "../math/CUtlMap.h"
#include "../../hash/hash.h"

enum frame_stages
{
	FRAME_UNDEFINED = -1,
	FRAME_START,
	FRAME_SIMULATE_START,
	FRAME_NET_UPDATE_START,
	FRAME_NET_UPDATE_PREPROCESS,
	FRAME_NET_FULL_FRAME_UPDATE_ON_REMOVE,
	FRAME_NET_UPDATE_POST_DATA_UPDATE_START,
	FRAME_NET_UPDATE_POST_DATA_UPDATE_END,
	FRAME_NET_UPDATE_END,
	FRAME_NET_CREATION,
	FRAME_SIMULATE_END,
};

class CEconItemDefinition
{
public:
	bool IsWeapon()
	{
		// Every gun supports at least 4 stickers.
		return GetStickersSupportedCount() >= 4;
	}

	bool IsAgent()
	{
		static auto Type_CustomPlayer = HASH("#Type_CustomPlayer");
		if (HASH(m_pszItemTypeName) != Type_CustomPlayer)
			return false;

		return GetStickersSupportedCount() >= 1;//proper chek na defolt modelki XD
	}


	bool IsKnife(bool bExcludeDefault)
	{
		static auto CSGO_Type_Knife = HASH("#CSGO_Type_Knife");
		if (HASH(m_pszItemTypeName) != CSGO_Type_Knife)
			return false;

		return bExcludeDefault ? m_uDefinitionIndex >= 500 : true;
	}

	bool IsGlove(bool bExcludeDefault)
	{
		static auto Type_Hands = HASH("#Type_Hands");
		if (HASH(m_pszItemTypeName) != Type_Hands)
			return false;

		const bool bDefaultGlove = m_uDefinitionIndex == 5028 || m_uDefinitionIndex == 5029;
		return bExcludeDefault ? !bDefaultGlove : true;
	}

	bool IsWeaponCase()
	{
		static auto Type_WeaponCase = HASH("#CSGO_Type_WeaponCase");
		return HASH(m_pszItemTypeName) == Type_WeaponCase;
	}

	bool IsKey()
	{
		static auto Tool_WeaponCase_KeyTag = HASH("#CSGO_Tool_WeaponCase_KeyTag");
		return HASH(m_pszItemTypeName) == Tool_WeaponCase_KeyTag;
	}

	const char* GetModelName()
	{
		return *reinterpret_cast<const char**>((uintptr_t)(this) + 0xD8);
	}

	int GetStickersSupportedCount()
	{
		return *reinterpret_cast<int*>((uintptr_t)(this) + 0x100);
	}

	const char* GetSimpleWeaponName()
	{
		return *reinterpret_cast<const char**>((uintptr_t)(this) + 0x1F0);
	}

	int GetLoadoutSlot()
	{
		return *reinterpret_cast<int*>((uintptr_t)(this) + 0x2E8);
	}
public:
	char pad_001[0x8];  // vtable
	void* m_pKVItem; // 0x8
	std::uint16_t m_uDefinitionIndex; // 0x10
	char pad_002[0x1e];
	bool m_bEnabled; // 0x30
	char pad_003[0xf];
	std::uint8_t m_unMinItemLevel; // 0x40
	std::uint8_t m_unMaxItemLevel; // 0x41
	std::uint8_t m_nItemRarity; // 0x42
	std::uint8_t m_nItemQuality; // 0x43
	std::uint8_t m_nForcedItemQuality; // 0x44
	std::uint8_t m_nDefaultDropItemQuality; // 0x45
	std::uint8_t m_nDefaultDropQuantity; // 0x46
	char pad_004[0x19];
	std::uint8_t m_nPopularitySeed; // 0x60
	char pad_005[0x7];
	void* m_pPortraitsKV; // 0x68
	char* m_pszItemBaseName; // 0x70
	bool m_bProperName; // 0x78
	char pad_006[0x7];
	char* m_pszItemTypeName; // 0x80
	char pad_007[0x8];
	char* m_pszItemDesc; // 0x90
	std::uint32_t m_iExpirationTimeStamp; // 0x98
	std::uint32_t m_iCreationTimeStamp; // 0x9c
	char* m_pszInventoryModel; // 0xa0
	char* m_pszInventoryImage; // 0xa8
	char pad_008[0x18];
	int m_iInventoryImagePosition[2]; // 0xc8
	int m_iInventoryImageSize[2]; // 0xd0
	char* m_pszBaseDisplayModel; // 0xd8
	bool m_bLoadOnDemand; // 0xe0
	char pad_009[0x1];
	bool m_bHideBodyGroupsDeployedOnly; // 0xe2
	char pad_010[0x5];
	char* m_pszWorldDisplayModel; // 0xe8
	char* m_pszHolsteredModel; // 0xf0
	char* m_pszWorldExtraWearableModel; // 0xf8
	std::uint32_t m_iStickerSlots; // 0x100
	char pad_011[0x4];
	char* m_pszIconDefaultImage; // 0x108
	bool m_bAttachToHands; // 0x110
	bool m_bAttachToHandsVMOnly; // 0x111
	bool m_bFlipViewModel; // 0x112
	bool m_bActAsWearable; // 0x113
	char pad_012[0x24];
	std::uint32_t m_iItemType; // 0x138
	char pad_013[0x4];
	char* m_pszBrassModelOverride; // 0x140
	char* m_pszZoomInSoundPath; // 0x148
	char* m_pszZoomOutSoundPath; // 0x150
	char pad_014[0x18];
	std::uint32_t m_nSoundMaterialID; // 0x170
	bool m_bDisableStyleSelection; // 0x174
	char pad_015[0x13];
	char* m_pszParticleFile; // 0x188
	char* m_pszParticleSnapshotFile; // 0x190
	char pad_016[0x40];
	char* m_pszItemClassname; // 0x1d8
	char* m_pszItemLogClassname; // 0x1e0
	char* m_pszItemIconClassname; // 0x1e8
	char* m_pszDefinitionName; // 0x1f0
	bool m_bHidden; // 0x1f8
	bool m_bShouldShowInArmory; // 0x1f9
	bool m_bBaseItem; // 0x1fa
	bool m_bFlexibleLoadoutDefault; // 0x1fb
	bool m_bImported; // 0x1fc
	bool m_bOnePerAccountCDKEY; // 0x1fd
	char pad_017[0xa];
	char* m_pszArmoryDesc; // 0x208
	char pad_018[0x8];
	char* m_pszArmoryRemap; // 0x218
	char* m_pszStoreRemap; // 0x220
	char* m_pszClassToken; // 0x228
	char* m_pszSlotToken; // 0x230
	std::uint32_t m_iDropType; // 0x238
	char pad_019[0x4];
	char* m_pszHolidayRestriction; // 0x240
	std::uint32_t m_iSubType; // 0x248
	char pad_020[0xc];
	std::uint32_t m_unEquipRegionMask; // 0x258
	std::uint32_t m_unEquipRegionConflictMask; // 0x25c
	char pad_021[0x50];
	bool m_bPublicItem; // 0x2b0
	bool m_bIgnoreInCollectionView; // 0x2b1
	char pad_022[0x36];
	int m_iLoadoutSlot; // 0x2e8
	char pad_023[0x94];
}; // Size: 0x380

struct AlternateIconData_t
{
	const char* m_szSimpleName;
	const char* m_szLargeSimpleName;
	char pad_001[0x10];
};

struct CPaintKit
{
	std::uint64_t m_nID; // 0x0
	const char* m_szName; // 0x8
	const char* m_szDescriptionString; // 0x10
	const char* m_szDescriptionTag; // 0x18
	char pad_001[0x8];
	const char* m_szPattern; // 0x28
	const char* m_szNormal; // 0x30
	const char* m_szLogoMaterial; // 0x38
	char pad_002[0x4];
	std::uint32_t m_nRarity; // 0x44
	std::uint32_t m_nStyle; // 0x48
	float m_rgbaColor[4][4]; // 0x4c
	float m_rgbaLogoColor[4][4]; // 0x5c
	float m_flWearDefault; // 0x6c
	float m_flWearRemapMin; // 0x70
	float m_flWearRemapMax; // 0x74
	std::uint8_t m_nFixedSeed; // 0x78
	std::uint8_t m_uchPhongExponent; // 0x79
	std::uint8_t m_uchPhongAlbedoBoost; // 0x7a
	std::uint8_t m_uchPhongIntensity; // 0x7b
	float m_flPatternScale; // 0x7c
	float m_flPatternOffsetXStart; // 0x80
	float m_flPatternOffsetXEnd; // 0x84
	float m_flPatternOffsetYStart; // 0x88
	float m_flPatternOffsetYEnd; // 0x8c
	float m_flPatternRotateStart; // 0x90
	float m_flPatternRotateEnd; // 0x94
	float m_flLogoScale; // 0x98
	float m_flLogoOffsetX; // 0x9c
	float m_flLogoOffsetY; // 0xa0
	float m_flLogoRotation; // 0xa4
	bool m_bIgnoreWeaponSizeScale; // 0xa8
	char pad_003[0x3];
	std::uint32_t m_nViewModelExponentOverrideSize; // 0xac
	bool m_bOnlyFirstMaterial; // 0xb0
	bool m_bUseNormalModel; // 0xb1
	bool m_bUseLegacyModel; // 0xb2
	char pad_004[0x1];
	float m_flPearlesent; // 0xb4
	const char* m_szVmtPath; // 0xb8
	char pad_005[0x8];
	const char* m_szCompositeMaterialPath; // 0xc8
	void* m_pkvVmtOverrides; // 0xd0
	char pad_006[0x8];
}; // Size: 0xe0

class CStickerKit
{
public:
	int m_nID;
	int m_nRarity;
	const char* m_szName;
	const char* m_szDescription;
	const char* m_szItemName;
	const char* m_szMaterialPath;
	const char* m_szMaterialPathNoDrips;
	const char* m_szInventoryImage;
	int m_nTournamentID;
	int m_nTournamentTeamID;
	int m_nTournamentPlayerID;
	bool m_bMaterialPathIsAbsolute;
	bool m_bCannotTrade;
	char pad_001[0x2];
	float m_flRotateStart;
	float m_flRotateEnd;
	float m_flScaleMin;
	float m_flScaleMax;
	float m_flWearMin;
	float m_flWearMax;
	const char* m_szIconURLSmall;
	const char* m_szIconURLLarge;
	void* m_pKVItem;
};

inline constexpr std::uint64_t GetAlternateIconKeyForWeaponPaintWearItem(std::uint16_t nDefIdx, std::uint32_t nPaintId, std::uint32_t nWear)
{
	return (nDefIdx << 16) + (nPaintId << 2) + nWear;
}

struct ItemListEntry_t
{
	int m_nItemDefinition;
	int m_nPaintKit;
	char pad_001[20];
};

class EconLootListDefinition
{
public:
	virtual const char* GetName() = 0;

	virtual CUtlVector<ItemListEntry_t>& GetLootListContents() = 0;
};

class CEconItemSchema
{
public:
	char pad_001[0x128];
	CUtlMap<int, CEconItemDefinition*> m_SortedItemDefinitionMap;
	char pad_002[0x128];
	CUtlMap<uint64_t, AlternateIconData_t> m_AlternateIconsMap;
	char pad_003[0x50];
	CUtlMap<int, CPaintKit*> m_PaintKits;
	CUtlMap<int, CStickerKit*> m_StickerKits;
};

class CEconItemSystem
{
public:
    auto GetEconItemSchema() { return *reinterpret_cast<CEconItemSchema**>((uintptr_t)(this) + 0x8); }
};

class CClient
{
public:
	CEconItemSystem* GetEconItemSystem()
	{
		return CALL_VIRTUAL(this, CEconItemSystem*, 123);
	}

	CDebugOverlaySystem* GetDebugOverlaySystem()
	{
		return CALL_VIRTUAL(this, CDebugOverlaySystem*, 162);
	}
};