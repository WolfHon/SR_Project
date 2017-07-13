#include "TerrainCol.h"

Engine::CTerrainCol::CTerrainCol(void)
: m_pTerrainVtx(NULL)
, m_pPos(NULL)
{

}

Engine::CTerrainCol::~CTerrainCol(void)
{

}

void Engine::CTerrainCol::SetColInfo(D3DXVECTOR3* pPos)
{
	m_pPos = pPos;
}

void Engine::CTerrainCol::Update(void)
{
	WORD	wCntX = 129;
	WORD	wCntZ = 129;
	WORD	wItv = 1;

	int		iIndex = (int(m_pPos->z) / wItv) * wCntX + (int(m_pPos->x) / wItv);

	float	fRatioX = (m_pPos->x - m_pTerrainVtx[iIndex + wCntX].vPos.x) / wItv;
	float	fRatioZ = (m_pTerrainVtx[iIndex + wCntX].vPos.z - m_pPos->z) / wItv;

	D3DXPLANE		Plane;

	if(fRatioX > fRatioZ) //오른쪽 위
	{
		D3DXPlaneFromPoints(&Plane, &m_pTerrainVtx[iIndex + wCntX].vPos
			, &m_pTerrainVtx[iIndex + wCntX + 1].vPos
			, &m_pTerrainVtx[iIndex + 1].vPos);
	}
	else //왼쪽 아래
	{
		D3DXPlaneFromPoints(&Plane, &m_pTerrainVtx[iIndex + wCntX].vPos
			, &m_pTerrainVtx[iIndex + 1].vPos
			, &m_pTerrainVtx[iIndex].vPos);
	}

	//ax + by + cz + d = 0
	//by = -ax -cz - d
	//y = (-ax -cz - d) / b
	m_pPos->y = (-Plane.a * m_pPos->x - Plane.c * m_pPos->z - Plane.d) / Plane.b;
	m_pPos->y += 1.f;
}

DWORD Engine::CTerrainCol::Release(void)
{
	if(m_dwRefCnt == 0)
		return 0;
	else
		--m_dwRefCnt;

	return m_dwRefCnt;
}

Engine::CTerrainCol* Engine::CTerrainCol::Create(void)
{
	return new CTerrainCol;
}

void Engine::CTerrainCol::SetTerrainVtx(const VTXTEX* pTerrainVtx)
{
	m_pTerrainVtx = pTerrainVtx;
}