#include "VIBuffer.h"

Engine::CVIBuffer::CVIBuffer(LPDIRECT3DDEVICE9 pDevice)
: CResources(pDevice)
, m_pVB(NULL)
, m_dwVtxSize(0)
, m_dwVtxCnt(0)
, m_dwVtxFVF(0)
, m_pIB(NULL)
, m_dwIdxSize(0)
, m_dwTriCnt(0)
, m_IdxFmt(D3DFMT_UNKNOWN)
{

}

Engine::CVIBuffer::CVIBuffer(const CVIBuffer& rhs)
: CResources(rhs)
, m_pVB(rhs.m_pVB)
, m_dwVtxSize(rhs.m_dwVtxSize)
, m_dwVtxCnt(rhs.m_dwVtxCnt)
, m_dwVtxFVF(rhs.m_dwVtxFVF)
, m_pIB(rhs.m_pIB)
, m_dwIdxSize(rhs.m_dwIdxSize)
, m_dwTriCnt(rhs.m_dwTriCnt)
, m_IdxFmt(rhs.m_IdxFmt)
{

}

Engine::CVIBuffer::~CVIBuffer(void)
{
	
}

void Engine::CVIBuffer::GetVtxInfo(void* pVertex)
{
	void* pOriVertex = NULL;
	m_pVB->Lock(0, 0, &pOriVertex, 0);
	memcpy(pVertex, pOriVertex, m_dwVtxSize * m_dwVtxCnt);
	m_pVB->Unlock();
}

void Engine::CVIBuffer::SetVtxInfo(void* pVertex)
{
	void* pOriVertex = NULL;
	m_pVB->Lock(0, 0, &pOriVertex, 0);
	memcpy(pOriVertex, pVertex, m_dwVtxSize * m_dwVtxCnt);
	m_pVB->Unlock();
}

HRESULT Engine::CVIBuffer::CreateBuffer(void)
{
	m_pDevice->CreateVertexBuffer(m_dwVtxSize * m_dwVtxCnt, 0, m_dwVtxFVF
		, D3DPOOL_MANAGED, &m_pVB, NULL);

	m_pDevice->CreateIndexBuffer(m_dwIdxSize * m_dwTriCnt, 0, m_IdxFmt
		, D3DPOOL_MANAGED, &m_pIB, NULL);
	return S_OK;
}

void Engine::CVIBuffer::Render(void)
{
	m_pDevice->SetStreamSource(0, m_pVB, 0, m_dwVtxSize);
	m_pDevice->SetFVF(m_dwVtxFVF);
	m_pDevice->SetIndices(m_pIB);
	/*m_pDevice->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 2);*/
	m_pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, m_dwVtxCnt, 0, m_dwTriCnt);
}

DWORD Engine::CVIBuffer::Release(void)
{
	if(m_dwRefCnt == 0)
	{
		Safe_Release(m_pVB);
		Safe_Release(m_pIB);
		return 0;
	}
	else
		--m_dwRefCnt;

	return m_dwRefCnt;
}
