#include "stdafx.h"
#include "Explosion.h"
#include "Texture.h"
#include "RcTex.h"

#include "Include.h"

#include "Transform.h"
#include "Collision_OBB.h"

#include "TerrainInfo.h"

#include "Block.h"
#include "Export_Function.h"
#include "FirstCamera.h"

CExplosion::CExplosion(LPDIRECT3DDEVICE9 pDevice)
: Engine::CGameObject(pDevice)
, m_pTexture(NULL)
, m_pBuffer(NULL)
, m_fFrame(0.f)
, m_fFrameSpeed(0.f)
, m_pInfo(NULL)
, m_dwMaxFrame(0)
{
}

CExplosion::~CExplosion(void)
{
	Release();
}

HRESULT CExplosion::Initialize(D3DXVECTOR3 vPos, int iPower, EXPLOSION_DIR edir)
{
	FAILED_CHECK(AddComponent());
	
	m_dwMaxFrame = m_pTexture->GetMaxSize();

	m_eDir = edir;
	
	m_pInfo->m_vPos = vPos;
	m_pInfo->m_vScale = D3DXVECTOR3(WORLD_SCALE, WORLD_SCALE, WORLD_SCALE);

	m_iPower = iPower;
	m_fFrameSpeed = 50.f;

	m_pInfo->Update();	

	m_matCol = m_pInfo->m_matWorld;

	CBlock* pBlock = NULL;

	pBlock = CTerrainInfo::GetInstance()->CheckCollision(m_pCollisionOBB, m_pInfo->m_vPos);
	if(pBlock != NULL && pBlock->GetTileType() == Engine::TILE_UNBROKEN)
	{
		return E_FAIL;
	}

	return S_OK;
}

Engine::OBJECT_RESULT CExplosion::Update(void)
{
	D3DXVec3TransformNormal(&m_pInfo->m_vDir, &g_vLook, &m_pInfo->m_matWorld);
	
	if(FrameCheck() == Engine::OR_DELETE)
		return Engine::OR_DELETE;

	CheckExplosion();
		
	if(Engine::CGameObject::Update() == Engine::OR_DELETE)
		return Engine::OR_DELETE;

	
	D3DXMATRIX		matBill;
	D3DXMatrixIdentity(&matBill);
	m_pDevice->GetTransform(D3DTS_VIEW, &matBill);

	ZeroMemory(&matBill.m[3][0], sizeof(D3DXVECTOR3));
	D3DXMatrixInverse(&matBill, NULL, &matBill);
	
	//matBill._11 = m_pInfo->m_vScale.x;
	//matBill._22 = m_pInfo->m_vScale.y;
	//matBill._33 = m_pInfo->m_vScale.z;

	//vBillpos = m_pInfo->m_vPos;

	//memcpy(&matBill._41,&vBillpos,sizeof(D3DXVECTOR3));

	m_matCol = m_pInfo->m_matWorld;
 	m_pInfo->m_matWorld = matBill * m_pInfo->m_matWorld;
	
	return Engine::OR_OK;
}

void CExplosion::Render(void)
{	
	m_pDevice->SetTransform(D3DTS_WORLD, &m_pInfo->m_matWorld);
	
	m_pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	m_pDevice->SetRenderState(D3DRS_ALPHAREF, 0x00000088);
	m_pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	m_pTexture->Render(0, (int)m_fFrame);
	m_pBuffer->Render();

	m_pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);	

	m_pCollisionOBB->Render(D3DCOLOR_ARGB(255, 255, 255, 0));
}

CExplosion* CExplosion::Create(LPDIRECT3DDEVICE9 pDevice, D3DXVECTOR3 vPos, int iPower, EXPLOSION_DIR edir)
{
	CExplosion*	pGameObject = new CExplosion(pDevice);
	if(FAILED(pGameObject->Initialize(vPos, iPower, edir)))
		Safe_Delete(pGameObject);

	return pGameObject;
}

void CExplosion::Release(void)
{
}

HRESULT CExplosion::AddComponent(void)
{
	Engine::CComponent*		pComponent = NULL;

	//Transform
	pComponent = m_pInfo = Engine::CTransform::Create(g_vLook);
	NULL_CHECK_RETURN(m_pInfo, E_FAIL);
	m_mapComponent.insert(MAPCOMPONENT::value_type(L"Transform", pComponent));

	//Texture
	pComponent = Engine::Get_ResourceMgr()->CloneResource(Engine::RESOURCE_DYNAMIC, L"Texture_Explosion");
	m_pTexture = dynamic_cast<Engine::CTexture*>(pComponent);
	NULL_CHECK_RETURN(m_pTexture, E_FAIL);
	m_mapComponent.insert(MAPCOMPONENT::value_type(L"Texture", pComponent));

	//Buffer
	pComponent = Engine::Get_ResourceMgr()->CloneResource(Engine::RESOURCE_STATIC, L"Buffer_RcTex");
	m_pBuffer = dynamic_cast<Engine::CVIBuffer*>(pComponent);
	NULL_CHECK_RETURN(m_pBuffer, E_FAIL);
	m_mapComponent.insert(MAPCOMPONENT::value_type(L"Buffer", pComponent));

	//OBBCollision_OBB	
	pComponent = m_pCollisionOBB = CCollision_OBB::Create(m_pDevice);
	NULL_CHECK_RETURN(m_pCollisionOBB, E_FAIL);
	m_pCollisionOBB->SetColInfo(&m_matCol, &D3DXVECTOR3(-0.9f, -0.9f, -0.9f), &D3DXVECTOR3(0.9f, 0.9f, 0.9f));
	m_mapComponent.insert(MAPCOMPONENT::value_type(L"Collision_OBB", pComponent));

	return S_OK;
}

Engine::OBJECT_RESULT CExplosion::FrameCheck(void)
{
	m_fFrame += m_fFrameSpeed * Engine::Get_TimeMgr()->GetTime();

	if (m_fFrame >= float(m_dwMaxFrame))	
		return Engine::OR_DELETE;
	
	if (m_fFrame >= float(m_dwMaxFrame) / 10.f)
	{
		if(m_iPower != 0 && m_bIsDead == FALSE)
		{
			CGameObject* pGameObject = NULL;

			switch(m_eDir)
			{	
			case DIR_LEFT:
				pGameObject = CExplosion::Create(m_pDevice, D3DXVECTOR3(m_pInfo->m_vPos.x - 2.f * WORLD_SCALE, m_pInfo->m_vPos.y, m_pInfo->m_vPos.z), m_iPower - 1, CExplosion::DIR_LEFT);
				if(pGameObject != NULL)
					Engine::Get_Management()->AddObject(Engine::LAYER_GAMELOGIC, L"Effect_Explosion", pGameObject);
				break;
			case DIR_RIGHT:
				pGameObject = CExplosion::Create(m_pDevice, D3DXVECTOR3(m_pInfo->m_vPos.x + 2.f * WORLD_SCALE, m_pInfo->m_vPos.y, m_pInfo->m_vPos.z), m_iPower - 1, CExplosion::DIR_RIGHT);
				if(pGameObject != NULL)
					Engine::Get_Management()->AddObject(Engine::LAYER_GAMELOGIC, L"Effect_Explosion", pGameObject);
				break;
			case DIR_BACK:
				pGameObject = CExplosion::Create(m_pDevice, D3DXVECTOR3(m_pInfo->m_vPos.x, m_pInfo->m_vPos.y, m_pInfo->m_vPos.z + 2.f * WORLD_SCALE), m_iPower - 1, CExplosion::DIR_BACK);
				if(pGameObject != NULL)
					Engine::Get_Management()->AddObject(Engine::LAYER_GAMELOGIC, L"Effect_Explosion", pGameObject);
				break;
			case DIR_FORWARD:
				pGameObject = CExplosion::Create(m_pDevice, D3DXVECTOR3(m_pInfo->m_vPos.x, m_pInfo->m_vPos.y, m_pInfo->m_vPos.z - 2.f * WORLD_SCALE), m_iPower - 1, CExplosion::DIR_FORWARD);
				if(pGameObject != NULL)
					Engine::Get_Management()->AddObject(Engine::LAYER_GAMELOGIC, L"Effect_Explosion", pGameObject);
				break;
			}

			m_iPower = 0;
		}
	}

	return Engine::OR_OK;
}

void CExplosion::CheckExplosion(void)
{		
	CBlock* pBlockObj = NULL;

	pBlockObj = CTerrainInfo::GetInstance()->CheckCollision(m_pCollisionOBB, m_pInfo->m_vPos);
	if(pBlockObj != NULL)
	{
		if(pBlockObj->GetTileType() == Engine::TILE_BROKEN)
		{
			m_bIsDead = TRUE;
			pBlockObj->IsDead();
		}
	}

	CGameObject* pGameObj = m_pCollisionOBB->CheckCollision(Engine::LAYER_GAMELOGIC, L"Player", m_pInfo->m_vPos);
	if(pGameObj != NULL)
		pGameObj->IsDead();

	pGameObj = m_pCollisionOBB->CheckCollision(Engine::LAYER_GAMELOGIC, L"Bomb", m_pInfo->m_vPos);
	if(pGameObj != NULL)
		pGameObj->IsDead();

	pGameObj = m_pCollisionOBB->CheckCollision(Engine::LAYER_GAMELOGIC, L"Item", m_pInfo->m_vPos);
	if(pGameObj != NULL)
		pGameObj->IsDead();
}
