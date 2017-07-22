#include "StdAfx.h"
#include "TerrainInfo.h"

#include "Block.h"
#include "GameObject.h"

#include "Include.h"

IMPLEMENT_SINGLETON(CTerrainInfo)

CTerrainInfo::CTerrainInfo(void)
{
}

CTerrainInfo::~CTerrainInfo(void)
{
}

void CTerrainInfo::InsertInfo(CBlock* Block)
{
	D3DXVECTOR3 vPos = Block->GetTilePos() * WOLRD_SCALE;
	MAPVECTOR vMapPos;
	vMapPos.x = vPos.x;
	vMapPos.y = vPos.y;
	vMapPos.z = vPos.z;

	mapBlock.insert(make_pair(vMapPos, Block));
}

void CTerrainInfo::EraseInfo(CBlock* Block)
{
	D3DXVECTOR3 vPos = Block->GetTilePos() * WOLRD_SCALE;
	MAPVECTOR vMapPos;
	vMapPos.x = vPos.x;
	vMapPos.y = vPos.y;
	vMapPos.z = vPos.z;

	map<MAPVECTOR, CBlock*>::iterator iter = mapBlock.find(vMapPos);

	if(iter == mapBlock.end())
		NULL_CHECK(NULL);
	
	mapBlock.erase(iter);
}

CBlock* CTerrainInfo::CheckCollision(CCollision_OBB* srcObb, D3DXVECTOR3 vPos)
{
	float fX = int((vPos.x + (WOLRD_SCALE))/ (WOLRD_SCALE * 2.f)) * (WOLRD_SCALE * 2.f);
	float fY = int((vPos.y + (WOLRD_SCALE))/ (WOLRD_SCALE * 2.f)) * (WOLRD_SCALE * 2.f);
	float fZ = int((vPos.z + (WOLRD_SCALE))/ (WOLRD_SCALE * 2.f)) * (WOLRD_SCALE * 2.f);

	D3DXVECTOR3 SrcPos = D3DXVECTOR3(fX, fY, fZ);	

	for(int z = -1; z<2;++z)
	{
		for(int y = -1; y<2;++y)
		{
			for(int x = -1; x<2;++x)
			{
				MAPVECTOR vecTargetPos;
				vecTargetPos.x = SrcPos.x + x * WOLRD_SCALE * 2.f;
				vecTargetPos.y = SrcPos.y + y * WOLRD_SCALE * 2.f;
				vecTargetPos.z = SrcPos.z + z * WOLRD_SCALE * 2.f;

				map<MAPVECTOR, CBlock*>::iterator iter = mapBlock.find(vecTargetPos);
				if(iter != mapBlock.end())
				{
					if(srcObb->ProcessingCollision(iter->second->GetCollision_OBB()) == TRUE)
						return iter->second;
				}
			}
		}
	}

	return NULL;
}
