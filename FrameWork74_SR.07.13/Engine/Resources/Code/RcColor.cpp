#include "RcColor.h"

Engine::CRcColor::CRcColor(LPDIRECT3DDEVICE9 pDevice)
: CVIBuffer(pDevice)
{

}

Engine::CRcColor::~CRcColor(void)
{

}

Engine::CResources* Engine::CRcColor::CloneResource(void)
{
	return new CRcColor(*this);
}

HRESULT Engine::CRcColor::CreateBuffer(void)
{
	m_dwVtxSize = sizeof(VTXCOL);
	m_dwVtxCnt = 4;
	m_dwVtxFVF = VTXFVF_COL;

	m_dwTriCnt = 2;
	m_dwIdxSize = sizeof(INDEX16);
	m_IdxFmt = D3DFMT_INDEX16;

	FAILED_CHECK(CVIBuffer::CreateBuffer());

	VTXCOL*		pVertex = NULL;
	m_pVB->Lock(0, 0, (void**)&pVertex, 0);

	pVertex[0].vPos = D3DXVECTOR3(-1.f, 1.f, 0.f);
	pVertex[0].dwColor = D3DCOLOR_ARGB(255, 255, 0, 0);

	pVertex[1].vPos = D3DXVECTOR3(1.f, 1.f, 0.f);
	pVertex[1].dwColor = D3DCOLOR_ARGB(255, 255, 255, 0);

	pVertex[2].vPos = D3DXVECTOR3(1.f, -1.f, 0.f);
	pVertex[2].dwColor = D3DCOLOR_ARGB(255, 0, 0, 255);

	pVertex[3].vPos = D3DXVECTOR3(-1.f, -1.f, 0.f);
	pVertex[3].dwColor = D3DCOLOR_ARGB(255, 0, 255, 0);

	m_pVB->Unlock();

	INDEX16*		pIndex = NULL;
	m_pIB->Lock(0, 0, (void**)&pIndex, 0);

	pIndex[0]._1 = 0;
	pIndex[0]._2 = 1;
	pIndex[0]._3 = 2;

	pIndex[1]._1 = 0;
	pIndex[1]._2 = 2;
	pIndex[1]._3 = 3;

	m_pIB->Unlock();
	return S_OK;
}

Engine::CRcColor* Engine::CRcColor::Create(LPDIRECT3DDEVICE9 pDevice)
{
	CRcColor*	pBuffer = new CRcColor(pDevice);
	if(FAILED(pBuffer->CreateBuffer()))
	{
		Safe_Delete(pBuffer);
	}
	return pBuffer;
}