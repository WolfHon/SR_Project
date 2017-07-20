#include "stdafx.h"
#include "Cube.h"

#include "Texture.h"
#include "VIBuffer.h"
#include "Transform.h"
#include "Collision_OBB.h"

#include "Include.h"
#include "Export_Function.h"

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

HRESULT CCube::Initialize(Engine::TILEINFO _TileInfo)
{
	m_tagTileInfo = _TileInfo;

	FAILED_CHECK(AddComponent());


	m_pInfo->m_vScale = m_tagTileInfo.vScale;
	m_pInfo->m_vPos = D3DXVECTOR3(m_tagTileInfo.vPos.x * 2.f, m_tagTileInfo.vPos.y * 4.f - 2.f, m_tagTileInfo.vPos.z * 2.f);
	m_pInfo->m_fAngle[Engine::ANGLE_Y] = _TileInfo.fAngle;
	m_fSpeed = 10.f;

	return S_OK;
}

Engine::OBJECT_RESULT CCube::Update(void)
{
	D3DXVec3TransformNormal(&m_pInfo->m_vDir, &g_vLook, &m_pInfo->m_matWorld);

	return Engine::CGameObject::Update();
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

	m_pTexture->Render(0, m_tagTileInfo.eTexture);
	m_pBuffer->Render();

	//m_pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	/*m_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);*/
}

CCube* CCube::Create(LPDIRECT3DDEVICE9 pDevice, Engine::TILEINFO _TileInfo)
{
	CCube*	pGameObject = new CCube(pDevice);
	if(FAILED(pGameObject->Initialize(_TileInfo)))
		Safe_Delete(pGameObject);

	return pGameObject;
}

void CCube::Release(void)
{	
}

HRESULT CCube::AddComponent(void)
{
	Engine::CComponent*		pComponent = NULL;

	//Transform
	pComponent = m_pInfo = Engine::CTransform::Create(g_vLook);
	NULL_CHECK_RETURN(m_pInfo, E_FAIL);
	m_mapComponent.insert(MAPCOMPONENT::value_type(L"Transform", pComponent));

	//Texture
	pComponent = Engine::Get_ResourceMgr()->CloneResource(Engine::RESOURCE_DYNAMIC, L"Block");
	m_pTexture = dynamic_cast<Engine::CTexture*>(pComponent);
	NULL_CHECK_RETURN(m_pTexture, E_FAIL);
	m_mapComponent.insert(MAPCOMPONENT::value_type(L"Texture", pComponent));

	switch(m_tagTileInfo.eTileShape)
	{

	case Engine::TILE_CUBE://Buffer
		pComponent = Engine::Get_ResourceMgr()->CloneResource(Engine::RESOURCE_DYNAMIC, L"Buffer_CubeTex");
		m_pBuffer = dynamic_cast<Engine::CVIBuffer*>(pComponent);
		NULL_CHECK_RETURN(m_pBuffer, E_FAIL);
		m_mapComponent.insert(MAPCOMPONENT::value_type(L"Buffer", pComponent));
		break;

	case Engine::TILE_SLOPE:
		pComponent = Engine::Get_ResourceMgr()->CloneResource(Engine::RESOURCE_DYNAMIC, L"Buffer_SlopeTex");
		m_pBuffer = dynamic_cast<Engine::CVIBuffer*>(pComponent);
		NULL_CHECK_RETURN(m_pBuffer, E_FAIL);
		m_mapComponent.insert(MAPCOMPONENT::value_type(L"Buffer", pComponent));
		break;



	}
	//OBBCollision_OBB
	pComponent = Engine::Get_CollisionMgr()->CloneCollision(Engine::COLLISON_OBB);
	m_pCollisionOBB = static_cast<Engine::CCollision_OBB*>(pComponent);
	NULL_CHECK_RETURN(m_pCollisionOBB, E_FAIL);
	m_mapComponent.insert(MAPCOMPONENT::value_type(L"Collision_OBB", pComponent));
	m_pCollisionOBB->SetColInfo(&m_pInfo->m_matWorld, &D3DXVECTOR3(-1.f, -1.f, -1.f), &D3DXVECTOR3(1.f, 1.f, 1.f));

	return S_OK;
}