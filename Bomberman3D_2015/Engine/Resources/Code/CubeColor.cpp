#include "CubeColor.h"

Engine::CCubeColor::CCubeColor(LPDIRECT3DDEVICE9 pDevice)
: CVIBuffer(pDevice)
{
}

Engine::CCubeColor::CCubeColor(const CCubeColor& rhs)
: CVIBuffer(rhs)
{
}

Engine::CCubeColor::~CCubeColor(void)
{
}

Engine::CResources* Engine::CCubeColor::CloneResource(void)
{
	return new CCubeColor(*this);
}

HRESULT Engine::CCubeColor::CreateBuffer(void)
{
	m_dwVtxSize = sizeof(VTXCOL);
	m_dwVtxCnt = 8;
	m_dwVtxFVF = VTXFVF_COL;

	m_dwTriCnt = 12;
	m_dwIdxSize = sizeof(INDEX16);
	m_IdxFmt = D3DFMT_INDEX16;

	FAILED_CHECK(CVIBuffer::CreateBuffer());

	VTXCOL*		pVertex = NULL;
	m_pVB->Lock(0, 0, (void**)&pVertex, 0);

	pVertex[0].vPos = D3DXVECTOR3(-1.f, 1.f, -1.f);
	pVertex[0].dwColor = D3DCOLOR_ARGB(255, 255, 0, 0);

	pVertex[1].vPos = D3DXVECTOR3(1.f, 1.f, -1.f);
	pVertex[1].dwColor = D3DCOLOR_ARGB(255, 255, 0, 0);

	pVertex[2].vPos = D3DXVECTOR3(1.f, -1.f, -1.f);
	pVertex[2].dwColor = D3DCOLOR_ARGB(255, 255, 0, 0);

	pVertex[3].vPos = D3DXVECTOR3(-1.f, -1.f, -1.f);
	pVertex[3].dwColor = D3DCOLOR_ARGB(255, 255, 0, 0);

	pVertex[4].vPos = D3DXVECTOR3(-1.f, 1.f, 1.f);
	pVertex[4].dwColor = D3DCOLOR_ARGB(255, 255, 0, 0);

	pVertex[5].vPos = D3DXVECTOR3(1.f, 1.f, 1.f);
	pVertex[5].dwColor = D3DCOLOR_ARGB(255, 255, 0, 0);

	pVertex[6].vPos = D3DXVECTOR3(1.f, -1.f, 1.f);
	pVertex[6].dwColor = D3DCOLOR_ARGB(255, 255, 0, 0);

	pVertex[7].vPos = D3DXVECTOR3(-1.f, -1.f, 1.f);
	pVertex[7].dwColor = D3DCOLOR_ARGB(255, 255, 0, 0);

	m_pVB->Unlock();

	INDEX16*		pIndex = NULL;
	m_pIB->Lock(0, 0, (void**)&pIndex, 0);

	pIndex[0]._1 = 1;	pIndex[0]._2 = 5;	pIndex[0]._3 = 6;
	pIndex[1]._1 = 1;	pIndex[1]._2 = 6;	pIndex[1]._3 = 2;
	pIndex[2]._1 = 4;	pIndex[2]._2 = 0;	pIndex[2]._3 = 3;
	pIndex[3]._1 = 4;	pIndex[3]._2 = 3;	pIndex[3]._3 = 7;
	pIndex[4]._1 = 4;	pIndex[4]._2 = 5;	pIndex[4]._3 = 1;
	pIndex[5]._1 = 4;	pIndex[5]._2 = 1;	pIndex[5]._3 = 0;
	pIndex[6]._1 = 3;	pIndex[6]._2 = 2;	pIndex[6]._3 = 6;
	pIndex[7]._1 = 3;	pIndex[7]._2 = 6;	pIndex[7]._3 = 7;
	pIndex[8]._1 = 7;	pIndex[8]._2 = 6;	pIndex[8]._3 = 5;
	pIndex[9]._1 = 7;	pIndex[9]._2 = 5;	pIndex[9]._3 = 4;
	pIndex[10]._1 = 0;	pIndex[10]._2 = 1;	pIndex[10]._3 = 2;
	pIndex[11]._1 = 0;	pIndex[11]._2 = 2;	pIndex[11]._3 = 3;

	m_pIB->Unlock();
	return S_OK;
}

Engine::CCubeColor* Engine::CCubeColor::Create(LPDIRECT3DDEVICE9 pDevice)
{
	CCubeColor*	pBuffer = new CCubeColor(pDevice);
	if(FAILED(pBuffer->CreateBuffer()))
	{
		Safe_Delete(pBuffer);
	}
	return pBuffer;
}