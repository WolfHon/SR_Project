#include "TriColor.h"

Engine::CTriColor::CTriColor(LPDIRECT3DDEVICE9 pDevice)
: CVIBuffer(pDevice)
{

}

Engine::CTriColor::CTriColor(const CTriColor& rhs)
: CVIBuffer(rhs)
{

}

Engine::CTriColor::~CTriColor(void)
{

}

HRESULT Engine::CTriColor::CreateBuffer(void)
{
	m_dwVtxSize = sizeof(VTXCOL);
	m_dwVtxCnt = 3;
	m_dwVtxFVF = VTXFVF_COL;

	m_dwTriCnt = 1;
	m_dwIdxSize = sizeof(INDEX16);
	m_IdxFmt = D3DFMT_INDEX16;

	FAILED_CHECK(CVIBuffer::CreateBuffer());

	VTXCOL*		pVertex = NULL;
	m_pVB->Lock(0, 0, (void**)&pVertex, 0);

	pVertex[0].vPos = D3DXVECTOR3(0.f, 1.f, 0.f);
	pVertex[0].dwColor = D3DCOLOR_ARGB(255, 255, 0, 0);

	pVertex[1].vPos = D3DXVECTOR3(1.f, -1.f, 0.f);
	pVertex[1].dwColor = D3DCOLOR_ARGB(255, 255, 255, 0);

	pVertex[2].vPos = D3DXVECTOR3(-1.f, -1.f, 0.f);
	pVertex[2].dwColor = D3DCOLOR_ARGB(255, 0, 0, 255);

	m_pVB->Unlock();

	return S_OK;
}

Engine::CTriColor* Engine::CTriColor::Create(LPDIRECT3DDEVICE9 pDevice)
{
	CTriColor*	pBuffer = new CTriColor(pDevice);
	if(FAILED(pBuffer->CreateBuffer()))
	{
		Safe_Delete(pBuffer);
	}
	return pBuffer;
}

void Engine::CTriColor::Render(void)
{
	m_pDevice->SetStreamSource(0, m_pVB, 0, m_dwVtxSize);
	m_pDevice->SetFVF(m_dwVtxFVF);
	m_pDevice->DrawPrimitive(D3DPT_TRIANGLELIST, 0, m_dwTriCnt);
}

Engine::CResources* Engine::CTriColor::CloneResource(void)
{
	return new CTriColor(*this);
}

