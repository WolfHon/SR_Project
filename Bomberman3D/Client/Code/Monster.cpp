#include "stdafx.h"
#include "Monster.h"

#include "Texture.h"

#include "Include.h"
#include "Transform.h"
#include "Export_Function.h"
#include "Collision_OBB.h"

#ifdef _DEBUG
#include "CubeColor.h"
#endif

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

	m_pInfo->m_vPos = D3DXVECTOR3(2.f , 2.f , 2.f);

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

	pComponent = Engine::Get_CollisionMgr()->CloneCollision(Engine::COLLISON_OBB);
	m_pCollisionOBB = static_cast<Engine::CCollision_OBB*>(pComponent);
	NULL_CHECK_RETURN(m_pCollisionOBB, E_FAIL);
	m_mapComponent.insert(MAPCOMPONENT::value_type(L"Collision_OBB", pComponent));
	m_pCollisionOBB->SetColInfo(&m_pInfo->m_matWorld, &D3DXVECTOR3(-2.f, -4.5f, -1.f), &D3DXVECTOR3(2.f, 3.5f, 1.f));

#ifdef _DEBUG
	pComponent = Engine::Get_ResourceMgr()->CloneResource(Engine::RESOURCE_DYNAMIC, L"Buffer_CubeColor");
	m_pCubeColor = dynamic_cast<Engine::CCubeColor*>(pComponent);
	NULL_CHECK_RETURN(m_pCubeColor, E_FAIL);
	m_mapComponent.insert(MAPCOMPONENT::value_type(L"Collision_Box", pComponent));
#endif

	return S_OK;	
}

void CMonster::MoveCheck( void )
{
	AI();
}

BOOL CMonster::CheckCollision( void )
{
	Engine::OBJLIST* listObj = Engine::Get_Management()->GetObjectList(Engine::LAYER_GAMELOGIC, L"UnBroken_Box");

	return m_pCollisionOBB->CheckCollision(m_pInfo->m_vPos, listObj);
}

void CMonster::Release( void )
{


}

void CMonster::AI( void )
{


		if(CheckCollision() == TRUE)
		{
			   ChangeDir(m_pInfo->m_vDir);
			//   move();
		}
		else
		m_pInfo->m_vPos += m_pInfo->m_vDir * 0.01f;
	



	//이동 -> 충돌확인 ->  이동 -> 충돌확인 				
				//	->방향변경 -> 충돌확인 -> 이동
				//  -> 정지 -> 시간흐름 -> 이동


}

void CMonster::ChangeDir( D3DXVECTOR3 _dir )
{
	D3DXVECTOR3 vtemp = m_pInfo->m_vDir;
	D3DXMATRIX	vMatY;
	static float fAngle= 90.0;
	


	int irand = rand() % 2 +1;

	switch(irand)
	{
	case 1:
		D3DXMatrixRotationY(&vMatY,D3DXToRadian(fAngle));
		D3DXVec3TransformNormal(&vtemp,&vtemp,&vMatY);
		break;

	case 2:
		D3DXMatrixRotationY(&vMatY,D3DXToRadian(-fAngle));
		D3DXVec3TransformNormal(&vtemp,&vtemp,&vMatY);
		break;
	}


	m_pInfo->m_vDir = _dir;
	
		
}
