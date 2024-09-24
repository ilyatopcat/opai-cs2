#pragma once

#include <stdint.h>
#include <string>

#include "../../utils/utils.h"
#include "../math/CStrongHandle.h"
#include "../../sdk/math/CUtlBuffer.h"

#include "../math/Vector.h"
#include "../math/Color.h"
#include "CUtlVector.h"
#include "CGameSceneNode.h"

class CTransform
{
public:
	VectorAligned vecPosition;
	QuaternionAligned quatOrientation;
};

class CHitbox
{
public:
	CUtlString m_strName{ };//0x0
	Vector m_vecMins{ };//0x18
	Vector m_vecMaxs{ };//0x24
	float m_flShapeRadius;//0x30
	unsigned int m_nBoneNameHash{ };//0x34
	int m_nGroupId{ };//0x38
	char pad_001[0x34];// 0x3C

	__int64 GetBoneIndex(void* model) {
		using GetBoneIndexFromHitbox_t = __int64(__fastcall*) (void*, unsigned int);
		static GetBoneIndexFromHitbox_t GetBoneIndexFromHitbox = reinterpret_cast<GetBoneIndexFromHitbox_t>(Utils::OpcodeScan("client.dll", "48 83 EC 08 83 79 10 00 44 8B D2 4C 8B C9 75 0A B8"));

		return GetBoneIndexFromHitbox(reinterpret_cast<void*> (reinterpret_cast<std::uintptr_t>(model) + 0x130), m_nBoneNameHash);
	}
};

class CHitboxsets
{
public:
	char pad_001[0x10]; // 0x00

	int m_nHitboxCount{ }; // 0x10 (E8 ? ? ? ? 85 C0 0F 84 ? ? ? ? 48 8B CF E8 ? ? ? ? 85 C0 75 2D 49 8B CE)
	char pad_002[0x4];//0x14
	CHitbox* m_arrHitboxs{ };// 0x14
};

struct CSceneHitbox
{
	CHitbox* hitbox;
	char pad[0x8];
};

struct CSceneHitboxData
{
	std::uint64_t hitbox_count;
	void* hitbox_data;
	char pad[0x8];
	CSceneHitbox hitbox_array[19];
};

struct CHitboxPosition
{
	Vector position;
	float scale;
	Vector4D rotate;
};

struct CSceneHitboxPosition
{
	std::uint64_t hitbox_count;
	char pad[0x8];
	void* hitbox_data;
	char pad2[0x8];
	CHitboxPosition hitbox_array[19];
};

class CDrawcalls
{
public:
	int m_nPrimitiveType; // 0x0000
	int m_nBaseVertex;	  // 0x0004
	int m_nVertexCount;	  // 0x0008
	int m_nStartIndex;	  // 0x000C
	int m_nIndexCount;	  // 0x0010
	float	m_flUvDensity;	  // 0x0014
	float	m_vTintColor[3];  // 0x0018
	float	m_flAlpha;		  // 0x0024
	char	pad_0x0028[0xC0]; // 0x0028
};

class CBones
{
public:
	const char* m_boneName;		   // 0x0000
	const char* m_parentName;	   // 0x0008
	float		m_invBindPose[12]; // 0x0010
	Vector		m_vecCenter;	   // 0x0040
	Vector		m_vecSize;		   // 0x004C
	float		m_flSphereradius;  // 0x0058
	char		pad_0x005C[0x4];   // 0x005C
};

class CAttachments
{
public:
	char		pad_0x0000[0x10];		  // 0x0000
	const char* m_key;					  // 0x0010
	char		pad_0x0018[0x8];		  // 0x0018
	const char* m_name;					  // 0x0020
	const char* m_influenceNames[3];	  // 0x0028
	char		pad_0x0030[0x10];		  // 0x0030
	Vector4D		m_vInfluenceRotations[3]; // 0x0040
	Vector		m_vInfluenceOffsets[3];	  // 0x0070
	float		m_influenceWeights[3];	  // 0x0094
	char		pad_0x00A0[0x10];		  // 0x00A0
};

class CRendermesh
{
public:
	char		   pad_0x0000[0x28];	// 0x0000
	Vector		   m_vMinBounds;		// 0x0028
	Vector		   m_vMaxBounds;		// 0x0034
	int		   m_drawCallsCount;	// 0x0040
	char		   pad_0x0044[0x4];		// 0x0044
	CDrawcalls* m_drawCalls;			// 0x0048
	char		   pad_0x0050[0x68];	// 0x0050
	int		   m_skeletoncount;		// 0x00B8
	char		   pad_0x00BC[0x4];		// 0x00BC
	CBones* m_skeleton;			// 0x00C0
	char		   pad_0x00C8[0x8];		// 0x00C8
	int		   m_hashescount;		// 0x00D0
	char		   pad_0x00D4[0x4];		// 0x00D4
	uint32_t* m_hashes;			// 0x00D8
	char		   pad_0x00E0[0x20];	// 0x00E0
	int		   m_nBoneWeightCount;	// 0x0100
	char		   pad_0x0104[0xC];		// 0x0104
	CAttachments* m_attachments;		// 0x0110
	int		   m_attachments_count; // 0x0118
	char		   pad_0x011C[0x1C];	// 0x011C
	CHitboxsets* m_Hitboxsets;		// 0x0138
	int		   m_nHitboxSets;		// 0x0140
};

class InfoForResourceTypeCRenderMesh
{
private:
	[[maybe_unused]] uint8_t __pad0000[0x1]; // 0x0
public:
};

class InfoForResourceTypeCModel
{
private:
	[[maybe_unused]] uint8_t __pad0000[0x1]; // 0x0
public:
};

struct PermModelExtPart_t
{
public:
	CTransform m_Transform; // 0x0	
	CUtlString m_Name; // 0x20	
	int m_nParent; // 0x28	
private:
	[[maybe_unused]] uint8_t __pad002c[0x4]; // 0x2c
public:
	CStrongHandle< InfoForResourceTypeCModel > m_refModel; // 0x30	
};

struct PermModelInfo_t
{
public:
	unsigned int m_nFlags; // 0x0	
	Vector m_vHullMin; // 0x4	
	Vector m_vHullMax; // 0x10	
	Vector m_vViewMin; // 0x1c	
	Vector m_vViewMax; // 0x28	
	float m_flMass; // 0x34	
	Vector m_vEyePosition; // 0x38	
	float m_flMaxEyeDeflection; // 0x44	
	CUtlString m_sSurfaceProperty; // 0x48	
	CUtlString m_keyValueText; // 0x50	
};

class CPermModelData
{
public:
	CUtlString m_name; // 0x0	
	PermModelInfo_t m_modelInfo; // 0x8	
	CUtlVector< PermModelExtPart_t > m_ExtParts; // 0x60	
	CUtlVector< CRendermesh* > m_refMeshes; // 0x78	
	CUtlVector< unsigned long long > m_refMeshGroupMasks; // 0x90	
	CUtlVector< unsigned long long > m_refPhysGroupMasks; // 0xa8	
	CUtlVector< unsigned char > m_refLODGroupMasks; // 0xc0	
	CUtlVector< float > m_lodGroupSwitchDistances; // 0xd8
};

class CModel
{
public:
	OFFSET(CRendermesh*, m_renderMeshes, 0x78);
};