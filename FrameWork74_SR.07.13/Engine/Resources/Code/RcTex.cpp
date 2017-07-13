#include "RcTex.h"

Engine::CRcTex::CRcTex(LPDIRECT3DDEVICE9 pDevice)
: CVIBuffer(pDevice)
{

}

Engine::CRcTex::CRcTex(const CRcTex& rhs)
: CVIBuffer(rhs)
{

}

Engine::CRcTex::~CRcTex(void)
{

}

Engine::CResources* Engine::CRcTex::CloneResource(void)
{
	return new CRcTex(*this);
}

HRESULT Engine::CRcTex::CreateBuffer(void)
{
	m_dwVtxSize = sizeof(VTXTEX);
	m_dwVtxCnt = 4;
	m_dwVtxFVF = VTXFVF_TEX;

	m_dwTriCnt = 2;
	m_dwIdxSize = sizeof(INDEX16);
	m_IdxFmt = D3DFMT_INDEX16;

	FAILED_CHECK(CVIBuffer::CreateBuffer());

	VTXTEX*		pVertex = NULL;
	m_pVB->Lock(0, 0, (void**)&pVertex, 0);

	/*0, 0		1, 0
	-1,1		1,1
		0-------1
		|		|
		|		|	
		3-------2
	-1,-1		1,-1
	0, 1		1, 1*/

	pVertex[0].vPos = D3DXVECTOR3(-1.f, 1.f, 0.f);
	pVertex[0].vTexUV = D3DXVECTOR2(0.f, 0.f);

	pVertex[1].vPos = D3DXVECTOR3(1.f, 1.f, 0.f);
	pVertex[1].vTexUV = D3DXVECTOR2(1.f, 0.f);

	pVertex[2].vPos = D3DXVECTOR3(1.f, -1.f, 0.f);
	pVertex[2].vTexUV = D3DXVECTOR2(1.f, 1.f);

	pVertex[3].vPos = D3DXVECTOR3(-1.f, -1.f, 0.f);
	pVertex[3].vTexUV = D3DXVECTOR2(0.f, 1.f);

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

Engine::CRcTex* Engine::CRcTex::Create(LPDIRECT3DDEVICE9 pDevice)
{
	CRcTex*	pBuffer = new CRcTex(pDevice);
	if(FAILED(pBuffer->CreateBuffer()))
	{
		Safe_Delete(pBuffer);
	}
	return pBuffer;
}