#include "stdafx.h"
#include "SliceBlock.h"

#include "Texture.h"
#include "VIBuffer.h"
#include "Transform.h"
#include "Collision_OBB.h"
#include "Gravity.h"

#include "Export_Function.h"
#include "TerrainInfo.h"
#include "Include.h"

CSliceBlock::CSliceBlock(LPDIRECT3DDEVICE9 pDevice)
: Engine::CGameObject(pDevice)
, m_pTexture(NULL)
, m_pBuffer(NULL)
, m_pInfo(NULL)
, m_pCollisionOBB(NULL)
, m_fDestroyTime(0.f)
{
}

CSliceBlock::~CSliceBlock(void)
{
	Release();
}

HRESULT CSliceBlock::Initialize(D3DXVECTOR3 vPos, Engine::TILETEXTURE eTexture)
{
	FAILED_CHECK(AddComponent());

	m_pInfo->m_vPos = vPos;
	m_pInfo->m_vScale = D3DXVECTOR3(WORLD_SCALE/10.f, WORLD_SCALE/10.f, WORLD_SCALE/10.f);	

	m_pInfo->m_vDir.x = (float)Engine::getInt(-10, 11);
	m_pInfo->m_vDir.y = (float)Engine::getInt(-1, 11);
	m_pInfo->m_vDir.z = (float)Engine::getInt(-10, 11);

	D3DXVec3Normalize(&m_pInfo->m_vDir, &m_pInfo->m_vDir);

	m_eTexture = eTexture;

	m_fPower = 50.f;

	m_fTime = 0.f;
	m_fDestroyTime = 3.f;
	m_fDecreasePower = 5.f;

	return S_OK;
}

Engine::OBJECT_RESULT CSliceBlock::Update(void)
{
	D3DXVECTOR3 a = D3DXVECTOR3(m_pInfo->m_vDir.x, 0.f, m_pInfo->m_vDir.z);
	D3DXVec3Normalize(&a, &a);
	D3DXVECTOR3 b = D3DXVECTOR3(0.f, 0.0f, 1.f);

	float cosAngle  = acosf(D3DXVec3Dot(&a, &b));
	m_pInfo->m_fAngle[Engine::ANGLE_Y] =  (b.x * a.z - b.z * a.x < 0.0f) ? cosAngle : -cosAngle; 

	if(DestroyCheck() == Engine::OR_DELETE)
		return Engine::OR_DELETE;

	if(Engine::CGameObject::Update() == Engine::OR_DELETE)
		return Engine::OR_DELETE;

	Move();


	return Engine::OR_OK;
}

void CSliceBlock::Render(void)
{
	if(m_fTime < m_fDestroyTime - 1.f || int(m_fTime * 10)%2 == 0)
	{
		m_pDevice->SetTransform(D3DTS_WORLD, &m_pInfo->m_matWorld);	

		m_pTexture->Render(0, m_eTexture);
		m_pBuffer->Render();
	}

	m_pCollisionOBB->Render(D3DCOLOR_ARGB(255, 0, 255, 255));
}

CSliceBlock* CSliceBlock::Create(LPDIRECT3DDEVICE9 pDevice, D3DXVECTOR3 vPos, Engine::TILETEXTURE eTexture)
{
	CSliceBlock*	pGameObject = new CSliceBlock(pDevice);
	if(FAILED(pGameObject->Initialize(vPos, eTexture)))
		Safe_Delete(pGameObject);

	return pGameObject;
}

HRESULT CSliceBlock::AddComponent(void)
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

	//Gravity
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

Engine::OBJECT_RESULT CSliceBlock::DestroyCheck(void)
{
	m_fTime += Engine::Get_TimeMgr()->GetTime();

	if(m_fTime > m_fDestroyTime)
		return Engine::OR_DELETE;

	return Engine::OR_OK;
}

void CSliceBlock::Release(void)
{

}

void CSliceBlock::Move(void)
{
	bool bStopDown = m_pGravity->GetStopDown();
	
	if(bStopDown == TRUE)
	{
		m_pInfo->m_vDir.y = 0.f;

		if(m_fPower > 12.f)
			m_fPower = 12.f;

		m_fDecreasePower = 25.f;
	}

	if(m_pGravity->Replusive() == TRUE)
	{
		m_fDecreasePower = 15.f;	

		m_pInfo->Update();
		
		if(CTerrainInfo::GetInstance()->CheckCollision(m_pCollisionOBB, m_pInfo->m_vPos) != NULL)
		{
			m_pInfo->m_vPos.y = m_pGravity->GetExHeight();
			m_pInfo->Update();
		}
	}

	m_fPower -= m_fDecreasePower * Engine::Get_TimeMgr()->GetTime();

	if(m_fPower <= 0.f)
	{
		m_fPower = 0.f;
	}
	else
	{
		D3DXVECTOR3 ExPos = m_pInfo->m_vPos;

		m_pInfo->m_vPos += m_fPower * m_pInfo->m_vDir * Engine::Get_TimeMgr()->GetTime();		

		m_pInfo->Update();

		if(CTerrainInfo::GetInstance()->CheckCollision(m_pCollisionOBB, m_pInfo->m_vPos) != NULL)
		{
			m_fPower = m_fPower * 0.6f;

			D3DXVECTOR3 vDir;
			D3DXVec3Cross(&vDir, &m_pInfo->m_vDir, &D3DXVECTOR3(0.f, 1.f, 0.f));

			m_pInfo->m_vPos = ExPos + m_fPower * vDir * Engine::Get_TimeMgr()->GetTime();	
			m_pInfo->Update();

			if(CTerrainInfo::GetInstance()->CheckCollision(m_pCollisionOBB, m_pInfo->m_vPos) != NULL)
			{
				D3DXVec3Cross(&vDir, &D3DXVECTOR3(0.f, 1.f, 0.f), &m_pInfo->m_vDir);
			}

			m_pInfo->m_vDir = vDir;

			m_pInfo->m_vPos = ExPos;
			m_pInfo->Update();
		}
	}
}
