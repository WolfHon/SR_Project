#include "stdafx.h"
#include "Terrain.h"
#include "Texture.h"
#include "RcTex.h"

#include "Export_Function.h"
#include "Transform.h"
#include "Include.h"
#include "CameraObserver.h"
#include "..\..\Engine\Utility\Code\Pipeline.h"

CTerrain::CTerrain(LPDIRECT3DDEVICE9 pDevice)
: Engine::CGameObject(pDevice)
, m_pTexture(NULL)
, m_pBuffer(NULL)
, m_pInfo(NULL)
, m_pVertex(NULL)
, m_pCamObserver(NULL)
, m_pConvertVertex(NULL)
, m_dwVtxCnt(0)
{

}

CTerrain::~CTerrain(void)
{
	Release();
}

HRESULT CTerrain::Initialize(void)
{
	FAILED_CHECK(AddComponent());

	m_dwVtxCnt = VTXCNTX * VTXCNTZ;
	m_pVertex = new Engine::VTXTEX[m_dwVtxCnt];
	m_pConvertVertex = new Engine::VTXTEX[m_dwVtxCnt];
	m_pBuffer->GetVtxInfo(m_pVertex);

	Engine::Get_CollisionMgr()->SetTerrainVtx(m_pVertex);

	m_pCamObserver = CCameraObserver::Create();
	Engine::Get_InfoSubject()->Subscribe(m_pCamObserver);
	return S_OK;
}

void CTerrain::Update(void)
{
	D3DXVec3TransformNormal(&m_pInfo->m_vDir, &g_vLook, &m_pInfo->m_matWorld);
	Engine::CGameObject::Update();

	const LPD3DXMATRIX		pmatView = m_pCamObserver->GetCamMatrix(MATRIX_VIEW);
	const LPD3DXMATRIX		pmatProj = m_pCamObserver->GetCamMatrix(MATRIX_PROJECTION);

	for(DWORD i = 0; i < m_dwVtxCnt; ++i)
	{
		m_pConvertVertex[i] = m_pVertex[i];
		Engine::CPipeline::MyTransformCoord(&m_pConvertVertex[i].vPos, &m_pConvertVertex[i].vPos, &m_pInfo->m_matWorld);
		Engine::CPipeline::MyTransformCoord(&m_pConvertVertex[i].vPos, &m_pConvertVertex[i].vPos, pmatView);
		if(m_pConvertVertex[i].vPos.z < 0.f)
			m_pConvertVertex[i].vPos.z = 0.f;
		Engine::CPipeline::MyTransformCoord(&m_pConvertVertex[i].vPos, &m_pConvertVertex[i].vPos, pmatProj);
	}
}

void CTerrain::Render(void)
{
	//m_pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);

	//m_pDevice->SetTransform(D3DTS_WORLD, &m_pInfo->m_matWorld);
	m_pBuffer->SetVtxInfo(m_pConvertVertex);

	m_pTexture->Render(0, 0);
	m_pBuffer->Render();

	//m_pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
}

CTerrain* CTerrain::Create(LPDIRECT3DDEVICE9 pDevice)
{
	CTerrain*	pGameObject = new CTerrain(pDevice);
	if(FAILED(pGameObject->Initialize()))
		Safe_Delete(pGameObject);

	return pGameObject;
}

void CTerrain::Release(void)
{
	Safe_Delete_Array(m_pVertex);
	Safe_Delete_Array(m_pConvertVertex);
	Safe_Delete(m_pCamObserver);
}

HRESULT CTerrain::AddComponent(void)
{
	Engine::CComponent*		pComponent = NULL;

	//Transform
	pComponent = m_pInfo = Engine::CTransform::Create(g_vLook);
	NULL_CHECK_RETURN(m_pInfo, E_FAIL);
	m_mapComponent.insert(MAPCOMPONENT::value_type(L"Transform", pComponent));

	//Texture
	pComponent = Engine::Get_ResourceMgr()->CloneResource(Engine::RESOURCE_DYNAMIC, L"Texture_TerrainTex");
	m_pTexture = dynamic_cast<Engine::CTexture*>(pComponent);
	NULL_CHECK_RETURN(m_pTexture, E_FAIL);
	m_mapComponent.insert(MAPCOMPONENT::value_type(L"Texture", pComponent));

	//Buffer
	pComponent = Engine::Get_ResourceMgr()->CloneResource(Engine::RESOURCE_DYNAMIC, L"Buffer_TerrainTex");
	m_pBuffer = dynamic_cast<Engine::CVIBuffer*>(pComponent);
	NULL_CHECK_RETURN(m_pBuffer, E_FAIL);
	m_mapComponent.insert(MAPCOMPONENT::value_type(L"Buffer", pComponent));

	return S_OK;
}

const Engine::VTXTEX* CTerrain::GetTerrainVtx(void)
{
	return m_pVertex;
}
