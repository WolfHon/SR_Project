#include "stdafx.h"
#include "Cube.h"

#include "Texture.h"
#include "VIBuffer.h"
#include "Transform.h"
#include "Collision_OBB.h"

#include "Include.h"
#include "Export_Function.h"

#ifdef _DEBUG
#include "CubeColor.h"
#endif

CCube::CCube(LPDIRECT3DDEVICE9 pDevice)
: Engine::CGameObject(pDevice)
, m_pTexture(NULL)
, m_pBuffer(NULL)
, m_fSpeed(0.f)
, m_fAngle(0.f)
, m_pInfo(NULL)
, m_pCollisionOBB(NULL)
{

}

CCube::~CCube(void)
{
	Release();
}

HRESULT CCube::Initialize(D3DXVECTOR3 vPos)
{
	FAILED_CHECK(AddComponent());

	m_pInfo->m_vPos = vPos;
	m_pInfo->m_vScale = D3DXVECTOR3(2.f, 2.f, 2.f);

	m_fSpeed = 10.f;

#ifdef _DEBUG
	pVertex =  new Engine::VTXCOL[8];	
	m_pCubeColor->GetVtxInfo(pVertex);

	D3DXVECTOR3 vMin, vMax;
	m_pCollisionOBB->GetColBox(&vMin, &vMax);

	pVertex[0].vPos = D3DXVECTOR3(vMin.x, vMax.y, vMin.z);
	pVertex[1].vPos = D3DXVECTOR3(vMax.x, vMax.y, vMin.z);
	pVertex[2].vPos = D3DXVECTOR3(vMax.x, vMin.y, vMin.z);
	pVertex[3].vPos = D3DXVECTOR3(vMin.x, vMin.y, vMin.z);

	pVertex[4].vPos = D3DXVECTOR3(vMin.x, vMax.y, vMax.z);
	pVertex[5].vPos = D3DXVECTOR3(vMax.x, vMax.y, vMax.z);
	pVertex[6].vPos = D3DXVECTOR3(vMax.x, vMin.y, vMax.z);
	pVertex[7].vPos = D3DXVECTOR3(vMin.x, vMin.y, vMax.z);
#endif

	return S_OK;
}

void CCube::Update(void)
{
	D3DXVec3TransformNormal(&m_pInfo->m_vDir, &g_vLook, &m_pInfo->m_matWorld);

	Engine::CGameObject::Update();

}

void CCube::Render(void)
{	
	//m_pDevice->SetTransform(D3DTS_WORLD, &m_pInfo->m_matWorld);
	
	/*m_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	m_pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	m_pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	m_pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);*/

	/*m_pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	m_pDevice->SetRenderState(D3DRS_ALPHAREF, 0x00000088);
	m_pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);*/

	m_pDevice->SetTransform(D3DTS_WORLD, &m_pInfo->m_matWorld);

	m_pTexture->Render(0, 0);
	m_pBuffer->Render();

#ifdef _DEBUG
	m_pCubeColor->SetVtxInfo(pVertex);
	m_pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	m_pDevice->SetTransform(D3DTS_WORLD, &m_pInfo->m_matWorld);
	m_pCubeColor->Render();
	m_pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
#endif

	//m_pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	/*m_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);*/
}

CCube* CCube::Create(LPDIRECT3DDEVICE9 pDevice, D3DXVECTOR3 vPos)
{
	CCube*	pGameObject = new CCube(pDevice);
	if(FAILED(pGameObject->Initialize(vPos)))
		Safe_Delete(pGameObject);

	return pGameObject;
}

void CCube::Release(void)
{	
#ifdef _DEBUG
	Safe_Delete_Array(pVertex);
#endif
}

HRESULT CCube::AddComponent(void)
{
	Engine::CComponent*		pComponent = NULL;

	//Transform
	pComponent = m_pInfo = Engine::CTransform::Create(g_vLook);
	NULL_CHECK_RETURN(m_pInfo, E_FAIL);
	m_mapComponent.insert(MAPCOMPONENT::value_type(L"Transform", pComponent));

	//Texture
	pComponent = Engine::Get_ResourceMgr()->CloneResource(Engine::RESOURCE_DYNAMIC, L"Texture_UnBrokenBox");
	m_pTexture = dynamic_cast<Engine::CTexture*>(pComponent);
	NULL_CHECK_RETURN(m_pTexture, E_FAIL);
	m_mapComponent.insert(MAPCOMPONENT::value_type(L"Texture", pComponent));

	//Buffer
	pComponent = Engine::Get_ResourceMgr()->CloneResource(Engine::RESOURCE_DYNAMIC, L"Buffer_CubeTex");
	m_pBuffer = dynamic_cast<Engine::CVIBuffer*>(pComponent);
	NULL_CHECK_RETURN(m_pBuffer, E_FAIL);
	m_mapComponent.insert(MAPCOMPONENT::value_type(L"Buffer", pComponent));

	//OBBCollision_OBB
	pComponent = Engine::Get_CollisionMgr()->CloneCollision(Engine::COLLISON_OBB);
	m_pCollisionOBB = static_cast<Engine::CCollision_OBB*>(pComponent);
	NULL_CHECK_RETURN(m_pCollisionOBB, E_FAIL);
	m_mapComponent.insert(MAPCOMPONENT::value_type(L"Collision_OBB", pComponent));
	m_pCollisionOBB->SetColInfo(&m_pInfo->m_matWorld, &D3DXVECTOR3(-1.f, -1.f, -1.f), &D3DXVECTOR3(1.f, 1.f, 1.f));

#ifdef _DEBUG
	pComponent = Engine::Get_ResourceMgr()->CloneResource(Engine::RESOURCE_DYNAMIC, L"Buffer_CubeColor");
	m_pCubeColor = dynamic_cast<Engine::CCubeColor*>(pComponent);
	NULL_CHECK_RETURN(m_pCubeColor, E_FAIL);
	m_mapComponent.insert(MAPCOMPONENT::value_type(L"Collision_Box", pComponent));
#endif

	return S_OK;
}