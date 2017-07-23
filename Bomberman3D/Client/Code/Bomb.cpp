#include "stdafx.h"
#include "Bomb.h"

#include "Texture.h"
#include "VIBuffer.h"
#include "Transform.h"
#include "Collision_OBB.h"

#include "Include.h"
#include "Export_Function.h"

#include "TerrainInfo.h"

#include "Explosion.h"

CBomb::CBomb(LPDIRECT3DDEVICE9 pDevice)
: Engine::CGameObject(pDevice)
, m_pTexture(NULL)
, m_pBuffer(NULL)
, m_pInfo(NULL)
, m_pCollisionOBB(NULL)
, m_iPower(1)
, m_fTime(0.f)
{
}

CBomb::~CBomb(void)
{
	Release();
}

HRESULT CBomb::Initialize(D3DXVECTOR3 vPos, int iPower)
{
	FAILED_CHECK(AddComponent());

	m_pInfo->m_vPos = vPos;
	m_pInfo->m_vScale = D3DXVECTOR3(WOLRD_SCALE/3.f, WOLRD_SCALE/3.f, WOLRD_SCALE/3.f);
	
	m_iPower = iPower;
	m_wEffect = 255;
	m_iExplosionTime = 65;

	m_pInfo->Update();

	if( m_pCollisionOBB->CheckCollision(Engine::LAYER_GAMELOGIC, L"Bomb", m_pInfo->m_vPos) ||
		m_pCollisionOBB->CheckCollision(Engine::LAYER_GAMELOGIC, L"Player", m_pInfo->m_vPos) != NULL ||		
		CTerrainInfo::GetInstance()->CheckCollision(m_pCollisionOBB, m_pInfo->m_vPos) != NULL
		)
	{
		return E_FAIL;
	}

	return S_OK;
}

Engine::OBJECT_RESULT CBomb::Update(void)
{
	D3DXVec3TransformNormal(&m_pInfo->m_vDir, &g_vLook, &m_pInfo->m_matWorld);

	FrameCheck();

	if(Explosion() == Engine::OR_DELETE)
		return Engine::OR_DELETE;

	return Engine::CGameObject::Update();
}

void CBomb::Render(void)
{	
	m_pDevice->SetTransform(D3DTS_WORLD, &m_pInfo->m_matWorld);

	m_pDevice->SetRenderState(D3DRS_TEXTUREFACTOR, D3DCOLOR_RGBA( 0, 0, 0, m_wEffect));
	m_pDevice->SetTextureStageState( 0, D3DTSS_COLORARG1, D3DTA_TEXTURE );
	m_pDevice->SetTextureStageState( 0, D3DTSS_COLOROP, D3DTOP_SELECTARG1 );

	m_pDevice->SetTextureStageState( 1, D3DTSS_COLORARG1, D3DTA_CURRENT );
	m_pDevice->SetTextureStageState( 1, D3DTSS_COLORARG2, D3DTA_TEXTURE );
	m_pDevice->SetTextureStageState( 1, D3DTSS_COLOROP, D3DTOP_BLENDFACTORALPHA );

	m_pTexture->Render(0, 0);
	m_pTexture->Render(1, 1);
	m_pBuffer->Render();

	m_pDevice->SetTextureStageState( 0, D3DTSS_COLORARG1, D3DTA_TEXTURE );
	m_pDevice->SetTextureStageState( 0, D3DTSS_COLOROP, D3DTOP_MODULATE );

	m_pDevice->SetTextureStageState( 1, D3DTSS_COLORARG1, D3DTA_TEXTURE );
	m_pDevice->SetTextureStageState( 1, D3DTSS_COLORARG2, D3DTA_CURRENT );
	m_pDevice->SetTextureStageState( 1, D3DTSS_COLOROP, D3DTOP_DISABLE  );
	m_pDevice->SetRenderState(D3DRS_TEXTUREFACTOR, 0xFFFFFFFF);

	m_pCollisionOBB->Render(D3DCOLOR_ARGB(255, 255, 0, 0));
}

CBomb* CBomb::Create(LPDIRECT3DDEVICE9 pDevice, D3DXVECTOR3 vPos, int iPower)
{
	CBomb*	pGameObject = new CBomb(pDevice);
	if(FAILED(pGameObject->Initialize(vPos, iPower)))
		Safe_Delete(pGameObject);

	return pGameObject;
}

void CBomb::Release(void)
{	
}

HRESULT CBomb::AddComponent(void)
{
	Engine::CComponent*		pComponent = NULL;

	//Transform
	pComponent = m_pInfo = Engine::CTransform::Create(g_vLook);
	NULL_CHECK_RETURN(m_pInfo, E_FAIL);
	m_mapComponent.insert(MAPCOMPONENT::value_type(L"Transform", pComponent));

	//Texture
	pComponent = Engine::Get_ResourceMgr()->CloneResource(Engine::RESOURCE_DYNAMIC, L"Bomb");
	m_pTexture = dynamic_cast<Engine::CTexture*>(pComponent);
	NULL_CHECK_RETURN(m_pTexture, E_FAIL);
	m_mapComponent.insert(MAPCOMPONENT::value_type(L"Texture", pComponent));

	//Buffer
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

Engine::OBJECT_RESULT CBomb::Explosion(void)
{
	if(m_wEffect <= 100 || m_bIsDead == TRUE)
	{
		Engine::CGameObject*	pGameObject = NULL;

		pGameObject = CExplosion::Create(m_pDevice,  D3DXVECTOR3(m_pInfo->m_vPos.x, m_pInfo->m_vPos.y + 1.25f, m_pInfo->m_vPos.z), 0, CExplosion::DIR_LEFT);
		if(pGameObject != NULL)
			Engine::Get_Management()->AddObject(Engine::LAYER_GAMELOGIC, L"Effect_Explosion", pGameObject);

		pGameObject = CExplosion::Create(m_pDevice, D3DXVECTOR3(m_pInfo->m_vPos.x - 2.f * WOLRD_SCALE, m_pInfo->m_vPos.y + 1.25f, m_pInfo->m_vPos.z), m_iPower - 1, CExplosion::DIR_LEFT);
		if(pGameObject != NULL)
			Engine::Get_Management()->AddObject(Engine::LAYER_GAMELOGIC, L"Effect_Explosion", pGameObject);

		pGameObject = CExplosion::Create(m_pDevice, D3DXVECTOR3(m_pInfo->m_vPos.x + 2.f * WOLRD_SCALE, m_pInfo->m_vPos.y + 1.25f, m_pInfo->m_vPos.z), m_iPower - 1, CExplosion::DIR_RIGHT);
		if(pGameObject != NULL)
			Engine::Get_Management()->AddObject(Engine::LAYER_GAMELOGIC, L"Effect_Explosion", pGameObject);

		pGameObject = CExplosion::Create(m_pDevice, D3DXVECTOR3(m_pInfo->m_vPos.x, m_pInfo->m_vPos.y + 1.25f, m_pInfo->m_vPos.z + 2.f * WOLRD_SCALE), m_iPower - 1, CExplosion::DIR_BACK);
		if(pGameObject != NULL)
			Engine::Get_Management()->AddObject(Engine::LAYER_GAMELOGIC, L"Effect_Explosion", pGameObject);

		pGameObject = CExplosion::Create(m_pDevice, D3DXVECTOR3(m_pInfo->m_vPos.x, m_pInfo->m_vPos.y + 1.25f, m_pInfo->m_vPos.z - 2.f * WOLRD_SCALE), m_iPower - 1, CExplosion::DIR_FORWARD);
		if(pGameObject != NULL)
			Engine::Get_Management()->AddObject(Engine::LAYER_GAMELOGIC, L"Effect_Explosion", pGameObject);

		return Engine::OR_DELETE;
	}

	return Engine::OR_OK;
}

void CBomb::FrameCheck(void)
{
	m_fTime += Engine::Get_TimeMgr()->GetTime();

	if(m_wEffect > 100)
		m_wEffect = 255 - WORD(m_fTime * m_iExplosionTime);
}
