#include "SlopeTex.h"

Engine::CSlopeTex::CSlopeTex(LPDIRECT3DDEVICE9 pDevice)
: CVIBuffer(pDevice)
{
}

Engine::CSlopeTex::CSlopeTex(const CSlopeTex& rhs)
: CVIBuffer(rhs)
{
}

Engine::CSlopeTex::~CSlopeTex(void)
{
}

Engine::CResources* Engine::CSlopeTex::CloneResource(void)
{
	return new CSlopeTex(*this);
}

HRESULT Engine::CSlopeTex::CreateBuffer(void)
{
	m_dwVtxSize = sizeof(VTXCUBE);
	m_dwVtxCnt = 6;
	m_dwVtxFVF = VTXFVF_CUBE;

	m_dwTriCnt = 8;
	m_dwIdxSize = sizeof(INDEX16);
	m_IdxFmt = D3DFMT_INDEX16;

	FAILED_CHECK(CVIBuffer::CreateBuffer());

	VTXCUBE*		pVertex = NULL;
	m_pVB->Lock(0, 0, (void**)&pVertex, 0);

	pVertex[0].vPos = D3DXVECTOR3(-1.f, 1.f, 1.f);
	pVertex[0].vTex = pVertex[0].vPos;

	pVertex[1].vPos = D3DXVECTOR3(1.f, 1.f, 1.f);
	pVertex[1].vTex = pVertex[1].vPos;

	pVertex[2].vPos = D3DXVECTOR3(1.f, -1.f, -1.f);
	pVertex[2].vTex = pVertex[2].vPos;

	pVertex[3].vPos = D3DXVECTOR3(-1.f, -1.f, -1.f);
	pVertex[3].vTex = pVertex[3].vPos;

	pVertex[4].vPos = D3DXVECTOR3(1.f, -1.f, 1.f);
	pVertex[4].vTex = pVertex[4].vPos;

	pVertex[5].vPos = D3DXVECTOR3(-1.f, -1.f, 1.f);
	pVertex[5].vTex = pVertex[5].vPos;

	m_pVB->Unlock();

	INDEX16*		pIndex = NULL;
	m_pIB->Lock(0, 0, (void**)&pIndex, 0);

	pIndex[0]._1 = 0;	pIndex[0]._2 = 1;	pIndex[0]._3 = 2;
	pIndex[1]._1 = 0;	pIndex[1]._2 = 2;	pIndex[1]._3 = 3;
	pIndex[2]._1 = 2;	pIndex[2]._2 = 1;	pIndex[2]._3 = 4;
	pIndex[3]._1 = 0;	pIndex[3]._2 = 3;	pIndex[3]._3 = 5;
	pIndex[4]._1 = 5;	pIndex[4]._2 = 4;	pIndex[4]._3 = 1;
	pIndex[5]._1 = 5;	pIndex[5]._2 = 1;	pIndex[5]._3 = 0;
	pIndex[6]._1 = 3;	pIndex[6]._2 = 4;	pIndex[6]._3 = 5;
	pIndex[7]._1 = 3;	pIndex[7]._2 = 2;	pIndex[7]._3 = 4;

	m_pIB->Unlock();

	return S_OK;
}

Engine::CSlopeTex* Engine::CSlopeTex::Create(LPDIRECT3DDEVICE9 pDevice)
{
	CSlopeTex*	pBuffer = new CSlopeTex(pDevice);

	if(FAILED(pBuffer->CreateBuffer()))
		Safe_Delete(pBuffer);

	return pBuffer;
}