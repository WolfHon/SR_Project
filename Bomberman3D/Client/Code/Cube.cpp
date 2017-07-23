#include "stdafx.h"
#include "Cube.h"

#include "Texture.h"
#include "VIBuffer.h"
#include "Transform.h"
#include "Collision_OBB.h"
#include "Include.h"
#include "Export_Function.h"

CCube::CCube(LPDIRECT3DDEVICE9 pDevice)
: CBlock(pDevice)
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
	
	m_pInfo->m_vScale = m_tagTileInfo.vScale * WOLRD_SCALE;
	m_pInfo->m_vPos = m_tagTileInfo.vPos * WOLRD_SCALE;
	m_pInfo->m_fAngle[Engine::ANGLE_Y] = _TileInfo.fAngle;

	m_pInfo->Update();

	D3DXMATRIX matScale, matRotY, matTrans;
	D3DXMatrixScaling(&matScale, m_pInfo->m_vScale.x, m_pInfo->m_vScale.y, m_pInfo->m_vScale.z);
	D3DXMatrixRotationY(&matRotY, m_pInfo->m_fAngle[Engine::ANGLE_Y]);
	D3DXMatrixTranslation(&matTrans, m_pInfo->m_vPos.x, m_pInfo->m_vPos.y, m_pInfo->m_vPos.z);

	m_vUpPoint[0] = D3DXVECTOR3(-1.f, 1.f, 1.f);
	m_vUpPoint[1] = D3DXVECTOR3(1.f, 1.f, 1.f);
	m_vUpPoint[2] = D3DXVECTOR3(1.f, 1.f, -1.f);
	m_vUpPoint[3] = D3DXVECTOR3(-1.f, 1.f, -1.f);

	D3DXMATRIX matPoint = matScale * matRotY * matTrans;

	for(int i=0; i<4; ++i)
		D3DXVec3TransformCoord(&m_vUpPoint[i], &m_vUpPoint[i], &matPoint);



	D3DXVec3TransformNormal(&m_pInfo->m_vDir, &g_vLook, &m_pInfo->m_matWorld);	

	CBlock::Initialize();
	
	return S_OK;
}

Engine::OBJECT_RESULT CCube::Update(void)
{	
	if(m_bIsDead)
		return Engine::OR_DELETE;

	return Engine::OR_OK;
}

void CCube::Render(void)
{	
	m_pDevice->SetTransform(D3DTS_WORLD, &m_pInfo->m_matWorld);

	m_pTexture->Render(0, m_tagTileInfo.eTexture);
	m_pBuffer->Render();
	m_pCollisionOBB->Render(D3DCOLOR_ARGB(255, 255, 0, 0));
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
	
	pComponent = Engine::Get_ResourceMgr()->CloneResource(Engine::RESOURCE_DYNAMIC, L"Buffer_CubeTex");
	m_pBuffer = dynamic_cast<Engine::CVIBuffer*>(pComponent);
	NULL_CHECK_RETURN(m_pBuffer, E_FAIL);
	m_mapComponent.insert(MAPCOMPONENT::value_type(L"Buffer", pComponent));
	
	//OBBCollision_OBB
	pComponent = m_pCollisionOBB = CCollision_OBB::Create(m_pDevice);
	NULL_CHECK_RETURN(m_pCollisionOBB, E_FAIL);
	m_pCollisionOBB->SetColInfo(&m_pInfo->m_matWorld, &D3DXVECTOR3(-1.f, -1.f, -1.f), &D3DXVECTOR3(1.f, 1.f, 1.f));
	m_mapComponent.insert(MAPCOMPONENT::value_type(L"Collision_OBB", pComponent));

	return S_OK;
}