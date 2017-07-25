#include "SphereTex.h"

Engine::CSphereTex::CSphereTex(LPDIRECT3DDEVICE9 pDevice)
: CVIBuffer(pDevice)
{
}

Engine::CSphereTex::CSphereTex(const CSphereTex& rhs)
: CVIBuffer(rhs)
{
}

Engine::CSphereTex::~CSphereTex(void)
{
}

Engine::CResources* Engine::CSphereTex::CloneResource(void)
{
	return new CSphereTex(*this);
}

HRESULT Engine::CSphereTex::CreateBuffer(void)
{
	int mDetail = 20;
	m_dwVtxSize = sizeof(VTXTEX);
	m_dwVtxCnt = mDetail*mDetail;
	m_dwVtxFVF = VTXFVF_TEX;

	m_dwTriCnt = (mDetail-1)*(mDetail-1)*2;
	m_dwIdxSize = sizeof(INDEX16);
	m_IdxFmt = D3DFMT_INDEX16;

	FAILED_CHECK(CVIBuffer::CreateBuffer());

	VTXTEX*		pVertex = NULL;
	m_pVB->Lock(0, 0, (void**)&pVertex, 0);

	for (int v=0; v<mDetail; ++v) 
	{
		for (int u=0; u<mDetail; ++u) 
		{
			float al = 2.f * D3DX_PI * ((float)u / (mDetail-1.0f));
			float th = 2.f * D3DX_PI * ((float)v / (mDetail-1.0f));

			pVertex[v * mDetail + u].vNormal.x = sin(th) * sin(al);
			pVertex[v * mDetail + u].vNormal.y = cos(th);
			pVertex[v * mDetail + u].vNormal.z = sin(th) * cos(al);

			pVertex[v * mDetail + u].vPos.x = pVertex[v * mDetail + u].vNormal.x * 1.f;
			pVertex[v * mDetail + u].vPos.y = pVertex[v * mDetail + u].vNormal.y * 1.f;
			pVertex[v * mDetail + u].vPos.z = pVertex[v * mDetail + u].vNormal.z * 1.f;

			pVertex[v * mDetail + u].vTexUV.x = 1.0f - (al / D3DX_PI * 0.5f);
			pVertex[v * mDetail + u].vTexUV.y = 1.0f - (th / D3DX_PI);
		}
	}

	m_pVB->Unlock();

	INDEX16*		pIndex = NULL;
	m_pIB->Lock(0, 0, (void**)&pIndex, 0);

	int i = 0;
	for (int v=0; v<mDetail-1; ++v) 
	{
		for (int u=0; u<mDetail-1; ++u) 
		{			
			pIndex[i]._1 = v * mDetail + u;
			pIndex[i]._2 = v * mDetail + u + 1;
			pIndex[i]._3 = (v + 1) * mDetail + u;
			++i;

			pIndex[i]._1 = (v + 1) * mDetail + u;
			pIndex[i]._2 = v * mDetail + u + 1;
			pIndex[i]._3 = (v + 1) * mDetail + u + 1;

			++i;
		}
	}

	m_pIB->Unlock();

	return S_OK;
}

Engine::CSphereTex* Engine::CSphereTex::Create(LPDIRECT3DDEVICE9 pDevice)
{
	CSphereTex*	pBuffer = new CSphereTex(pDevice);

	if(FAILED(pBuffer->CreateBuffer()))
		Safe_Delete(pBuffer);

	return pBuffer;
}