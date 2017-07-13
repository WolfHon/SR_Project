#include "stdafx.h"
#include "Monster.h"
#include "Texture.h"
#include "RcTex.h"

#include "Include.h"
#include "Transform.h"
#include "Export_Function.h"
#include "TerrainCol.h"
#include "CameraObserver.h"
#include "Pipeline.h"

CMonster::CMonster(LPDIRECT3DDEVICE9 pDevice)
: Engine::CGameObject(pDevice)
, m_pTexture(NULL)
, m_pBuffer(NULL)
, m_fSpeed(0.f)
, m_fAngle(0.f)
, m_pInfo(NULL)
, m_pTerrainCol(NULL)
{

}

CMonster::~CMonster(void)
{
	Release();
}

HRESULT CMonster::Initialize(void)
{
	FAILED_CHECK(AddComponent());

	m_pInfo->m_vPos = D3DXVECTOR3(float(rand() % VTXCNTX), 0.f, float(rand() % VTXCNTZ));

	m_dwVtxCnt = 4;
	m_pVertex = new Engine::VTXTEX[m_dwVtxCnt];
	m_pConvertVertex = new Engine::VTXTEX[m_dwVtxCnt];
	m_pBuffer->GetVtxInfo(m_pVertex);

	m_pCamObserver = CCameraObserver::Create();
	Engine::Get_InfoSubject()->Subscribe(m_pCamObserver);

	m_fSpeed = 10.f;
	return S_OK;
}

void CMonster::Update(void)
{
	D3DXVec3TransformNormal(&m_pInfo->m_vDir, &g_vLook, &m_pInfo->m_matWorld);
	m_pTerrainCol->SetColInfo(&m_pInfo->m_vPos);

	Engine::CGameObject::Update();

	D3DXMATRIX		matBill;
	D3DXMatrixIdentity(&matBill);
	matBill = *m_pCamObserver->GetCamMatrix(MATRIX_VIEW);
	ZeroMemory(&matBill.m[3][0], sizeof(D3DXVECTOR3));

	D3DXMatrixInverse(&matBill, NULL, &matBill);

	m_pInfo->m_matWorld = matBill * m_pInfo->m_matWorld;

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

	/*D3DXMATRIX		matBill, matView;
	D3DXMatrixIdentity(&matBill);

	m_pDevice->GetTransform(D3DTS_VIEW, &matView);
	ZeroMemory(&matBill.m[3][0], sizeof(D3DXVECTOR3));

	matBill._11 = matView._11;
	matBill._13 = matView._13;
	matBill._31 = matView._31;
	matBill._33 = matView._33;

	D3DXMatrixInverse(&matBill, NULL, &matBill);

	m_pInfo->m_matWorld = matBill * m_pInfo->m_matWorld;*/
}

void CMonster::Render(void)
{
	m_pBuffer->SetVtxInfo(m_pConvertVertex);
	//m_pDevice->SetTransform(D3DTS_WORLD, &m_pInfo->m_matWorld);
	
	/*m_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	m_pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	m_pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	m_pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);*/

	m_pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	m_pDevice->SetRenderState(D3DRS_ALPHAREF, 0x00000088);
	m_pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	m_pTexture->Render(0, 0);
	m_pBuffer->Render();

	m_pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	/*m_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);*/
}

CMonster* CMonster::Create(LPDIRECT3DDEVICE9 pDevice)
{
	CMonster*	pGameObject = new CMonster(pDevice);
	if(FAILED(pGameObject->Initialize()))
		Safe_Delete(pGameObject);

	return pGameObject;
}

void CMonster::Release(void)
{
	Safe_Delete_Array(m_pVertex);
	Safe_Delete_Array(m_pConvertVertex);
	Safe_Delete(m_pCamObserver);
}

HRESULT CMonster::AddComponent(void)
{
	Engine::CComponent*		pComponent = NULL;

	//Transform
	pComponent = m_pInfo = Engine::CTransform::Create(g_vLook);
	NULL_CHECK_RETURN(m_pInfo, E_FAIL);
	m_mapComponent.insert(MAPCOMPONENT::value_type(L"Transform", pComponent));

	//Texture
	pComponent = Engine::Get_ResourceMgr()->CloneResource(Engine::RESOURCE_DYNAMIC, L"Texture_Monster");
	m_pTexture = dynamic_cast<Engine::CTexture*>(pComponent);
	NULL_CHECK_RETURN(m_pTexture, E_FAIL);
	m_mapComponent.insert(MAPCOMPONENT::value_type(L"Texture", pComponent));

	//Buffer
	pComponent = Engine::Get_ResourceMgr()->CloneResource(Engine::RESOURCE_STATIC, L"Buffer_RcTex");
	m_pBuffer = dynamic_cast<Engine::CVIBuffer*>(pComponent);
	NULL_CHECK_RETURN(m_pBuffer, E_FAIL);
	m_mapComponent.insert(MAPCOMPONENT::value_type(L"Buffer", pComponent));

	//TerrainCol
	pComponent = Engine::Get_CollisionMgr()->GetColObject(Engine::COLLISON_TERRAIN);
	m_pTerrainCol = dynamic_cast<Engine::CTerrainCol*>(pComponent);
	NULL_CHECK_RETURN(m_pTerrainCol, E_FAIL);
	m_mapComponent.insert(MAPCOMPONENT::value_type(L"TerrainCol", pComponent));
	return S_OK;
}