#include "stdafx.h"
#include "Block.h"

#include "Texture.h"
#include "VIBuffer.h"
#include "Transform.h"
#include "Collision_OBB.h"
#include "TerrainInfo.h"

CBlock::CBlock(LPDIRECT3DDEVICE9 pDevice)
: Engine::CGameObject(pDevice)
, m_pTexture(NULL)
, m_pBuffer(NULL)
, m_pInfo(NULL)
, m_pCollisionOBB(NULL)
{
}

CBlock::~CBlock(void)
{
	Release();
}

void CBlock::Initialize(void)
{
	CTerrainInfo::GetInstance()->InsertInfo(this);
}

void CBlock::Release(void)
{	
	CTerrainInfo::GetInstance()->EraseInfo(this);
}