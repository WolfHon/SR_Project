#include "StdAfx.h"
#include "TerrainInfo.h"

#include "Block.h"
#include "GameObject.h"
#include "Collision_OBB.h"

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
	D3DXVECTOR3 vPos = Block->GetTilePos() * WORLD_SCALE;
	MAPVECTOR vMapPos;
	vMapPos.x = vPos.x;
	vMapPos.y = vPos.y;
	vMapPos.z = vPos.z;

	mapBlock.insert(make_pair(vMapPos, Block));
}

void CTerrainInfo::EraseInfo(CBlock* Block)
{
	D3DXVECTOR3 vPos = Block->GetTilePos() * WORLD_SCALE;
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
	if(srcObb == NULL)
		return NULL;

	float fX = int((vPos.x + (WORLD_SCALE))/ (WORLD_SCALE * 2.f)) * (WORLD_SCALE * 2.f);
	float fY = int((vPos.y + (WORLD_SCALE))/ (WORLD_SCALE * 2.f)) * (WORLD_SCALE * 2.f);
	float fZ = int((vPos.z + (WORLD_SCALE))/ (WORLD_SCALE * 2.f)) * (WORLD_SCALE * 2.f);

	D3DXVECTOR3 SrcPos = D3DXVECTOR3(fX, fY, fZ);	

	for(int z = -1; z<2;++z)
	{
		for(int y = -1; y<2;++y)
		{
			for(int x = -1; x<2;++x)
			{
				MAPVECTOR vecTargetPos;
				vecTargetPos.x = SrcPos.x + x * WORLD_SCALE * 2.f;
				vecTargetPos.y = SrcPos.y + y * WORLD_SCALE * 2.f;
				vecTargetPos.z = SrcPos.z + z * WORLD_SCALE * 2.f;

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

float CTerrainInfo::CheckHeight(D3DXVECTOR3 vPos)
{
	float fX = int((vPos.x + (WORLD_SCALE))/ (WORLD_SCALE * 2.f)) * (WORLD_SCALE * 2.f);
	float fY = int((vPos.y + (WORLD_SCALE))/ (WORLD_SCALE * 2.f)) * (WORLD_SCALE * 2.f);
	float fZ = int((vPos.z + (WORLD_SCALE))/ (WORLD_SCALE * 2.f)) * (WORLD_SCALE * 2.f);
	
	D3DXVECTOR3 SrcPos = D3DXVECTOR3(fX, fY, fZ);	

	for(int y = 0; ;y--)
	{
		MAPVECTOR vecTargetPos;
		vecTargetPos.x = SrcPos.x;
		vecTargetPos.y = SrcPos.y + y * WORLD_SCALE * 2.f;
		vecTargetPos.z = SrcPos.z;

		if(vecTargetPos.y < -12.f)
			break;

		map<MAPVECTOR, CBlock*>::iterator iter = mapBlock.find(vecTargetPos);
		if(iter != mapBlock.end())
		{
			if(y == 0 && iter->second->GetTileShpae() == Engine::TILE_CUBE)
				continue;

			D3DXVECTOR3* vUpPoint = iter->second->GetUpPoint();
		
			float	fRatioX = (vPos.x - vUpPoint[0].x) / (WORLD_SCALE * 2.f);
			float	fRatioZ = (vUpPoint[0].z - vPos.z) / (WORLD_SCALE * 2.f);

			D3DXPLANE		Plane;

			if(fRatioX > fRatioZ)
				D3DXPlaneFromPoints(&Plane, &vUpPoint[0], &vUpPoint[1], &vUpPoint[2]);
			else 
				D3DXPlaneFromPoints(&Plane, &vUpPoint[0], &vUpPoint[2], &vUpPoint[3]);
			
			return (-Plane.a * vPos.x - Plane.c * vPos.z - Plane.d) / Plane.b;
		}
	}

	return -1000.f;
}
