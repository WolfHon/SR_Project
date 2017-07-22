#include "stdafx.h"
#include "BrokenCube.h"


#include "Texture.h"
#include "VIBuffer.h"
#include "Transform.h"
#include "Collision_OBB.h"
#include "Include.h"
#include "Export_Function.h"

CBrokenCube::CBrokenCube(LPDIRECT3DDEVICE9 pDevice)
: Engine::CGameObject(pDevice)
, m_pTexture(NULL)
, m_pBuffer(NULL)
, m_fSpeed(0.f)
, m_fAngle(0.f)
, m_pInfo(NULL)
, m_pCollisionOBB(NULL)
{

}

CBrokenCube::~CBrokenCube(void)
{
	Release();
}

HRESULT CBrokenCube::Initialize(Engine::TILEINFO _TileInfo)
{
	m_tagTileInfo = _TileInfo;


	FAILED_CHECK(AddComponent());

	
	m_pInfo->m_vScale = m_tagTileInfo.vScale * WOLRD_SCALE;
	m_pInfo->m_vPos = D3DXVECTOR3(m_tagTileInfo.vPos.x * WOLRD_SCALE, m_tagTileInfo.vPos.y * WOLRD_SCALE, m_tagTileInfo.vPos.z * WOLRD_SCALE);
	m_pInfo->m_fAngle[Engine::ANGLE_Y] = _TileInfo.fAngle;
	
	m_fSpeed = 10.f;

	return S_OK;
}

Engine::OBJECT_RESULT CBrokenCube::Update(void)
{
	D3DXVec3TransformNormal(&m_pInfo->m_vDir, &g_vLook, &m_pInfo->m_matWorld);

	Engine::CGameObject::Update();

	return Engine::OR_OK;

}

void CBrokenCube::Render(void)
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

CBrokenCube* CBrokenCube::Create(LPDIRECT3DDEVICE9 pDevice, Engine::TILEINFO _TileInfo)
{
	CBrokenCube*	pGameObject = new CBrokenCube(pDevice);
	if(FAILED(pGameObject->Initialize(_TileInfo)))
		Safe_Delete(pGameObject);

	return pGameObject;
}

void CBrokenCube::Release(void)
{	
}

HRESULT CBrokenCube::AddComponent(void)
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

	if(m_tagTileInfo.eTileShape == Engine::TILE_CUBE)
	{//Buffer
		pComponent = Engine::Get_ResourceMgr()->CloneResource(Engine::RESOURCE_DYNAMIC, L"Buffer_CubeTex");
		m_pBuffer = dynamic_cast<Engine::CVIBuffer*>(pComponent);
		NULL_CHECK_RETURN(m_pBuffer, E_FAIL);
		m_mapComponent.insert(MAPCOMPONENT::value_type(L"Buffer", pComponent));
	}
	else
	{
		pComponent = Engine::Get_ResourceMgr()->CloneResource(Engine::RESOURCE_DYNAMIC, L"Buffer_SlopeTex");
		m_pBuffer = dynamic_cast<Engine::CVIBuffer*>(pComponent);
		NULL_CHECK_RETURN(m_pBuffer, E_FAIL);
		m_mapComponent.insert(MAPCOMPONENT::value_type(L"Buffer", pComponent));

	}

	//OBBCollision_OBB
	pComponent = m_pCollisionOBB = CCollision_OBB::Create(m_pDevice);
	NULL_CHECK_RETURN(m_pCollisionOBB, E_FAIL);
	m_pCollisionOBB->SetColInfo(&m_pInfo->m_matWorld, &D3DXVECTOR3(-1.f, -1.f, -1.f), &D3DXVECTOR3(1.f, 1.f, 1.f));
	m_mapComponent.insert(MAPCOMPONENT::value_type(L"Collision_OBB", pComponent));

	return S_OK;
}