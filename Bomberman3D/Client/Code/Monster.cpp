#include "stdafx.h"
#include "Monster.h"

#include "Texture.h"

#include "VIBuffer.h"
#include "Include.h"
#include "Transform.h"
#include "Export_Function.h"
#include "Collision_OBB.h"
#include "TerrainInfo.h"

CMonster::CMonster( LPDIRECT3DDEVICE9 pDevice )
:Engine::CGameObject(pDevice)
,m_pTexture(NULL)
,m_fSpeed(0.f)
,m_fAngle(0.f)
,m_pInfo(NULL)
,m_pCollisionOBB(NULL)
{

}

CMonster::~CMonster( void )
{
	Release();
}

HRESULT CMonster::Initialize( void )
{
	FAILED_CHECK(AddComponent());

	m_pInfo->m_vPos = D3DXVECTOR3(5.f , 2.f , 5.f);

	return S_OK;
}

Engine::OBJECT_RESULT CMonster::Update( void )
{

	MoveCheck();

	D3DXVec3TransformNormal(&m_pInfo->m_vDir, &g_vLook, &m_pInfo->m_matWorld);

	return Engine::CGameObject::Update();	

}

void CMonster::Render( void )
{
	m_pDevice->SetTransform(D3DTS_WORLD, &m_pInfo->m_matWorld);
	m_pTexture->Render(0,4);
	m_pBuffer->Render();
	m_pCollisionOBB->Render(D3DCOLOR_ARGB(255, 0, 0, 255));

}

CMonster* CMonster::Create( LPDIRECT3DDEVICE9 pDevice )
{
	CMonster*	pGameObject = new CMonster(pDevice);
	if(FAILED(pGameObject->Initialize()))
		Safe_Delete(pGameObject);

	return pGameObject;
}


HRESULT CMonster::AddComponent( void )
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

	pComponent = m_pCollisionOBB = CCollision_OBB::Create(m_pDevice);
	NULL_CHECK_RETURN(m_pCollisionOBB, E_FAIL);
	m_pCollisionOBB->SetColInfo(&m_pInfo->m_matWorld, &D3DXVECTOR3(-1.f, -1.f, -1.f), &D3DXVECTOR3(1.f, 1.f, 1.f));
	m_mapComponent.insert(MAPCOMPONENT::value_type(L"Collision_OBB", pComponent));

	return S_OK;	
}

void CMonster::MoveCheck( void )
{
	AI();
}

void CMonster::Release( void )
{


}

void CMonster::AI( void )
{

	D3DXVECTOR3 vExPos = m_pInfo->m_vPos;

		if(CTerrainInfo::GetInstance()->CheckCollision(m_pCollisionOBB, m_pInfo->m_vPos) != NULL)
		{		
			ChangeDir(vExPos);
		}
		else
		{
			m_pInfo->m_vPos += m_pInfo->m_vDir * 10.f * Engine::Get_TimeMgr()->GetInstance()->GetTime();
		}
	



	//이동 -> 충돌확인 ->  이동 -> 충돌확인 				
				//	->방향변경 -> 충돌확인 -> 이동
				//  -> 정지 -> 시간흐름 -> 이동


}

void CMonster::ChangeDir( D3DXVECTOR3 _pos )
{
	int irand = rand() % 4;

		m_pInfo->m_vPos = _pos - (m_pInfo->m_vDir);

	switch(irand)
	{
	case 0:
		m_pInfo->m_fAngle[Engine::ANGLE_Y] += D3DXToRadian(90.f);
		break;

	case 1:
		m_pInfo->m_fAngle[Engine::ANGLE_Y] -= D3DXToRadian(90.f);
		break;

	case 2:
		m_pInfo->m_fAngle[Engine::ANGLE_Y] += D3DXToRadian(180.f);
		break;

	case 3:
		break;
	}
}
