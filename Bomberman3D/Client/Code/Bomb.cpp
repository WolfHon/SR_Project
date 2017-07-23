#include "stdafx.h"
#include "Bomb.h"

#include "Texture.h"
#include "VIBuffer.h"
#include "Transform.h"
#include "Collision_OBB.h"

#include "Include.h"
#include "Export_Function.h"

#include "TerrainInfo.h"
#include "Block.h"
#include "Gravity.h"
#include "Player.h"

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

HRESULT CBomb::Initialize(D3DXVECTOR3 vPos, int iPower, float Throw, CPlayer* Own)
{
	FAILED_CHECK(AddComponent());

	m_pInfo->m_vPos = vPos;
	m_pInfo->m_vScale = D3DXVECTOR3(WOLRD_SCALE/3.f, WOLRD_SCALE/3.f, WOLRD_SCALE/3.f);

	D3DXMATRIX matView;
	m_pDevice->GetTransform(D3DTS_VIEW, &matView);

	D3DXMatrixInverse(&matView, NULL, &matView);
	memcpy(&m_pInfo->m_vDir, &matView.m[2][0], sizeof(D3DXVECTOR3));

	if(m_pInfo->m_vDir.y < -0.92f)
		return E_FAIL;
	
	m_ThrowPower = Throw;
	m_iPower = iPower;
	m_wEffect = 255;
	m_iExplosionTime = 65;

	m_Own = Own;

	m_pInfo->Update();

	if(CTerrainInfo::GetInstance()->CheckCollision(m_pCollisionOBB, m_pInfo->m_vPos) != NULL)
	{
		return E_FAIL;
	}

	return S_OK;
}

Engine::OBJECT_RESULT CBomb::Update(void)
{
	if(Engine::CGameObject::Update() == Engine::OR_DELETE)
		return Engine::OR_DELETE;

	FrameCheck();
	Move();

	if(Explosion() == Engine::OR_DELETE)
		return Engine::OR_DELETE;

	return Engine::OR_OK;
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

CBomb* CBomb::Create(LPDIRECT3DDEVICE9 pDevice, D3DXVECTOR3 vPos, int iPower, float Throw, CPlayer* Own)
{
	CBomb*	pGameObject = new CBomb(pDevice);
	if(FAILED(pGameObject->Initialize(vPos, iPower, Throw, Own)))
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
	
	pComponent = m_pGravity = CGravity::Create();
	NULL_CHECK_RETURN(m_pGravity, E_FAIL);
	D3DXVECTOR3 vPoint[4];
	vPoint[0] = D3DXVECTOR3(-1.f, 0.f, -1.f);
	vPoint[1] = D3DXVECTOR3(-1.f, 0.f, 1.f);
	vPoint[2] = D3DXVECTOR3(1.f, 0.f, -1.f);
	vPoint[3] = D3DXVECTOR3(1.f, 0.f, 1.f);
	m_pGravity->SetInfo(vPoint, &m_pInfo->m_vPos, &m_pInfo->m_matWorld, m_pCollisionOBB->GetMin()->y * - 1.f);
	m_mapComponent.insert(MAPCOMPONENT::value_type(L"Gravity", pComponent));

	return S_OK;
}

Engine::OBJECT_RESULT CBomb::Explosion(void)
{
	if(m_wEffect <= 100 || m_bIsDead == TRUE)
	{
		Engine::CGameObject*	pGameObject = NULL;

		float fX = int((m_pInfo->m_vPos.x + (WOLRD_SCALE)) / (WOLRD_SCALE * 2.f)) * (WOLRD_SCALE * 2.f);
		float fY = int((m_pInfo->m_vPos.y + (WOLRD_SCALE)) / (WOLRD_SCALE * 2.f)) * (WOLRD_SCALE * 2.f);
		float fZ = int((m_pInfo->m_vPos.z + (WOLRD_SCALE)) / (WOLRD_SCALE * 2.f)) * (WOLRD_SCALE * 2.f);

		pGameObject = CExplosion::Create(m_pDevice,  D3DXVECTOR3(fX, fY, fZ), 0, CExplosion::DIR_LEFT);
		if(pGameObject != NULL)
			Engine::Get_Management()->AddObject(Engine::LAYER_GAMELOGIC, L"Effect_Explosion", pGameObject);

		pGameObject = CExplosion::Create(m_pDevice, D3DXVECTOR3(fX - 2.f * WOLRD_SCALE, fY, fZ), m_iPower - 1, CExplosion::DIR_LEFT);
		if(pGameObject != NULL)
			Engine::Get_Management()->AddObject(Engine::LAYER_GAMELOGIC, L"Effect_Explosion", pGameObject);

		pGameObject = CExplosion::Create(m_pDevice, D3DXVECTOR3(fX + 2.f * WOLRD_SCALE, fY, fZ), m_iPower - 1, CExplosion::DIR_RIGHT);
		if(pGameObject != NULL)
			Engine::Get_Management()->AddObject(Engine::LAYER_GAMELOGIC, L"Effect_Explosion", pGameObject);

		pGameObject = CExplosion::Create(m_pDevice, D3DXVECTOR3(fX, fY, fZ + 2.f * WOLRD_SCALE), m_iPower - 1, CExplosion::DIR_BACK);
		if(pGameObject != NULL)
			Engine::Get_Management()->AddObject(Engine::LAYER_GAMELOGIC, L"Effect_Explosion", pGameObject);

		pGameObject = CExplosion::Create(m_pDevice, D3DXVECTOR3(fX, fY, fZ - 2.f * WOLRD_SCALE), m_iPower - 1, CExplosion::DIR_FORWARD);
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

void CBomb::Move(void)
{
	bool bStopDown = m_pGravity->GetStopDown();
	float DecreasePower = 5.f;

	if(bStopDown == FALSE)
	{		
		CGameObject* pGameObj = m_pCollisionOBB->CheckCollision(Engine::LAYER_GAMELOGIC, L"Bomb", m_pInfo->m_vPos);

		if((pGameObj != NULL && pGameObj != this) ||
			m_pCollisionOBB->CheckCollision(Engine::LAYER_GAMELOGIC, L"Player", m_pInfo->m_vPos) != NULL)
		{	
			m_pInfo->m_vPos.y = m_pGravity->GetExHeight();
			m_pInfo->Update();
		}
	}	
	else
	{
		if(m_ThrowPower > 12.f)
			m_ThrowPower = 12.f;

		DecreasePower = 20.f;
	}

	m_ThrowPower -= DecreasePower * Engine::Get_TimeMgr()->GetTime();

	if(m_ThrowPower <= 0.f)
	{
		m_ThrowPower = 0.f;
	}
	else
	{
		D3DXVECTOR3 ExPos = m_pInfo->m_vPos;

		m_pInfo->m_vPos += m_ThrowPower * m_pInfo->m_vDir * Engine::Get_TimeMgr()->GetTime();		

		m_pInfo->Update();

		CGameObject* pGameObj = m_pCollisionOBB->CheckCollision(Engine::LAYER_GAMELOGIC, L"Bomb", m_pInfo->m_vPos);
		CGameObject* pPlayer = m_pCollisionOBB->CheckCollision(Engine::LAYER_GAMELOGIC, L"Player", m_pInfo->m_vPos);

		if(CTerrainInfo::GetInstance()->CheckCollision(m_pCollisionOBB, m_pInfo->m_vPos) != NULL ||
			(pGameObj != NULL && pGameObj != this) ||
			(pPlayer != NULL && pPlayer != m_Own))
		{
			if(m_ThrowPower > 20.f)
				m_ThrowPower = 20.f;

			m_pInfo->m_vPos = ExPos;
		}
	}		
}
