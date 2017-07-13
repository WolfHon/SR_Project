#include "MouseCol.h"

Engine::CMouseCol::CMouseCol(void)
{

}

Engine::CMouseCol::~CMouseCol(void)
{

}

void Engine::CMouseCol::PickTerrain(D3DXVECTOR3* pOut
									, const D3DXMATRIX* pmatProj
									, const D3DXMATRIX* pmatView)
{
	Translation_ViewSpace(pmatProj);
	D3DXMATRIX		matWorld;
	D3DXMatrixIdentity(&matWorld);
	Translation_Local(pmatView, &matWorld);

	float		fU, fV, fDist;
	const WORD	VTXCNTX = 129;

	for(int z = 0; z < 128; ++z)
	{
		for(int x = 0; x < VTXCNTX - 1; ++x)
		{
			int		iIndex = z * VTXCNTX + x;
			//오른쪽 위
			if(D3DXIntersectTri(&m_pTerrainVtx[iIndex + VTXCNTX + 1].vPos
				, &m_pTerrainVtx[iIndex + VTXCNTX].vPos
				, &m_pTerrainVtx[iIndex + 1].vPos
				, &m_vPivotPos, &m_vRayDir, &fU, &fV, &fDist))
			{
				*pOut = m_pTerrainVtx[iIndex + VTXCNTX + 1].vPos
					+ (m_pTerrainVtx[iIndex + VTXCNTX].vPos - m_pTerrainVtx[iIndex + VTXCNTX + 1].vPos) * fU
					+ (m_pTerrainVtx[iIndex + 1].vPos - m_pTerrainVtx[iIndex + VTXCNTX + 1].vPos) * fV;
				return ;
			}

			if(D3DXIntersectTri(&m_pTerrainVtx[iIndex].vPos
				, &m_pTerrainVtx[iIndex + 1].vPos
				, &m_pTerrainVtx[iIndex + VTXCNTX].vPos
				, &m_vPivotPos, &m_vRayDir, &fU, &fV, &fDist))
			{
				*pOut = m_pTerrainVtx[iIndex].vPos
					+ (m_pTerrainVtx[iIndex + 1].vPos - m_pTerrainVtx[iIndex].vPos) * fU
					+ (m_pTerrainVtx[iIndex + VTXCNTX].vPos - m_pTerrainVtx[iIndex].vPos) * fV;
				return ;
			}
		}
	}
}

Engine::CMouseCol* Engine::CMouseCol::Create(HWND hWnd, const VTXTEX* pTerrainVtx)
{
	CMouseCol*	pCollision = new CMouseCol;
	if(FAILED(pCollision->InitCollision(hWnd, pTerrainVtx)))
		Safe_Delete(pCollision);

	return pCollision;
}

DWORD Engine::CMouseCol::Release(void)
{
	if(m_dwRefCnt == 0)
		return 0;
	else
		--m_dwRefCnt;

	return m_dwRefCnt;
}

POINT Engine::CMouseCol::GetMousePos(void)
{
	POINT	pt;

	GetCursorPos(&pt);
	ScreenToClient(m_hWnd, &pt);

	return pt;
}

void Engine::CMouseCol::Translation_ViewSpace(const D3DXMATRIX* pmatProj)
{
	const WORD WINCX = 800;
	const WORD WINCY = 600;

	POINT	ptMouse = GetMousePos();

	D3DXVECTOR3		vTemp;

	//2 * 3 = 6
	//6 / 3 = 2
	//로컬 * 월드 * 뷰 * 투영 * 투영 역행렬
	//x : 0 ->	-1		800 -> 1
	vTemp.x = (float(ptMouse.x) / (WINCX / 2.f) - 1.f) / pmatProj->_11;
	vTemp.y = (float(-ptMouse.y) / (WINCY / 2.f) + 1.f) / pmatProj->_22;
	vTemp.z = 1.f;

	m_vPivotPos = D3DXVECTOR3(0.f, 0.f, 0.f);
	m_vRayDir = vTemp - m_vPivotPos;
	D3DXVec3Normalize(&m_vRayDir, &m_vRayDir);
}

HRESULT Engine::CMouseCol::InitCollision(HWND hWnd, const VTXTEX* pTerrainVtx)
{
	m_hWnd = hWnd;
	m_pTerrainVtx = pTerrainVtx;

	return S_OK;
}

void Engine::CMouseCol::Translation_Local(const D3DXMATRIX* pmatView 
										  , const D3DXMATRIX* pmatWorld)
{
	D3DXMATRIX		matViewInv;
	D3DXMatrixInverse(&matViewInv, NULL, pmatView);
	D3DXVec3TransformCoord(&m_vPivotPos, &m_vPivotPos, &matViewInv);
	D3DXVec3TransformNormal(&m_vRayDir, &m_vRayDir, &matViewInv);

	D3DXMATRIX		matWorldInv;
	D3DXMatrixInverse(&matWorldInv, NULL, pmatWorld);
	D3DXVec3TransformCoord(&m_vPivotPos, &m_vPivotPos, &matWorldInv);
	D3DXVec3TransformNormal(&m_vRayDir, &m_vRayDir, &matWorldInv);
}

void Engine::CMouseCol::PickObject(D3DXVECTOR3* pOut 
								   , const Engine::VTXTEX* pVertex 
								   , const D3DXMATRIX* pmatProj 
								   , const D3DXMATRIX* pmatView
								   , const D3DXMATRIX* pmatWorld)
{
	Translation_ViewSpace(pmatProj);
	Translation_Local(pmatView, pmatWorld);

	float		fU, fV, fDist;

	//오른쪽 위
	if(D3DXIntersectTri(&pVertex[1].vPos
		, &pVertex[0].vPos
		, &pVertex[2].vPos
		, &m_vPivotPos, &m_vRayDir, &fU, &fV, &fDist))
	{
		*pOut = pVertex[1].vPos
			+ (pVertex[0].vPos - pVertex[1].vPos) * fU
			+ (pVertex[2].vPos - pVertex[1].vPos) * fV;
		return ;
	}
}

