#include "stdafx.h"
#include "Item.h"

#include "Transform.h"
#include "Texture.h"
#include "VIBuffer.h"
#include "Export_Function.h"
#include "Collision_OBB.h"

#include "Include.h"
#include "Player.h"
#include "ShoseNum.h"
#include "PowerNum.h"
#include "AddBombNum.h"

CItem::CItem( LPDIRECT3DDEVICE9 pDevice )
:Engine::CGameObject(pDevice)
,m_pTexture(NULL)
,m_pBuffer(NULL)
,m_pInfo(NULL)
,m_inum(0)
,m_fPlayerSpeed(0)
,m_iAddBomb(0)
,m_iPower(0)

{

}

CItem::~CItem( void )
{
	Release();
}

CItem* CItem::Create( LPDIRECT3DDEVICE9 pDevice, D3DXVECTOR3 vpos, Engine::ITEMOPTION _ItemOption )
{
	CItem*	pGameObject = new CItem(pDevice);
	if(FAILED(pGameObject->Initialize(vpos, _ItemOption)))
		Safe_Delete(pGameObject);

	return pGameObject;

}

HRESULT CItem::Initialize( D3DXVECTOR3 vPos, Engine::ITEMOPTION _ItemOption )
{

	m_fTime = 0.f;
	FAILED_CHECK(AddComponent());
	m_pInfo->m_vPos = vPos;
	m_tagItemOption =_ItemOption;
	m_bDungSill =true;

	m_pInfo->Update();	

	switch(_ItemOption)
	{
		case Engine::ITEM_SPEED:
			m_fPlayerSpeed = 1.f;
			break;

		case Engine::ITEM_POWER:
			m_iPower = 1;
			break;

		case Engine::ITEM_ADDBOMB:
			m_iAddBomb = 1;
			break;
	}

	return S_OK;
}


Engine::OBJECT_RESULT CItem::Update( void )
{
	m_fTime += Engine::Get_TimeMgr()->GetTime();

	if( m_fTime > 1.f && m_bDungSill == true)
	{
		m_bDungSill = false;
		m_fTime = 0;

	}
	else if(m_fTime >1.f && m_bDungSill == false)
	{
		m_bDungSill = true;
		m_fTime = 0;
	}


	if(m_bDungSill)
	{
		m_pInfo->m_vPos.y +=1.f *Engine::Get_TimeMgr()->GetTime();
	}
	else
	{
		m_pInfo->m_vPos.y -=1.f *Engine::Get_TimeMgr()->GetTime();
	}

	

	D3DXVec3TransformNormal(&m_pInfo->m_vDir, &g_vLook, &m_pInfo->m_matWorld);
	m_pInfo->m_fAngle[Engine::ANGLE_Y] -= D3DXToRadian(120.f) * Engine::Get_TimeMgr()->GetTime();

	if(CheckCollision() == TRUE)
	{
		if(m_inum == 1)
			return Engine::OR_OK;
		else
			return Engine::OR_DELETE;
	}
	m_pInfo->m_matWorld = m_pInfo->m_matWorld;
		

	return Engine::CGameObject::Update();
}


void CItem::Render( void )
{
	m_pDevice->SetRenderState(D3DRS_CULLMODE,D3DCULL_NONE);
		m_pDevice->SetTransform(D3DTS_WORLD, &m_pInfo->m_matWorld);

		m_pTexture->Render(0, m_tagItemOption);
		m_pBuffer->Render();
		m_pDevice->SetRenderState(D3DRS_CULLMODE,D3DCULL_CCW);

}

HRESULT CItem::AddComponent( void )
{
	Engine::CComponent*		pComponent = NULL;

	//Transform
	pComponent = m_pInfo = Engine::CTransform::Create(g_vLook);
	NULL_CHECK_RETURN(m_pInfo, E_FAIL);
	m_mapComponent.insert(MAPCOMPONENT::value_type(L"Transform", pComponent));

	//Texture
	pComponent = Engine::Get_ResourceMgr()->CloneResource(Engine::RESOURCE_DYNAMIC, L"Texture_Bomb");
	m_pTexture = dynamic_cast<Engine::CTexture*>(pComponent);
	NULL_CHECK_RETURN(m_pTexture, E_FAIL);
	m_mapComponent.insert(MAPCOMPONENT::value_type(L"Texture", pComponent));

	//Buffer
	pComponent = Engine::Get_ResourceMgr()->CloneResource(Engine::RESOURCE_DYNAMIC, L"Buffer_RCTex");
	m_pBuffer = dynamic_cast<Engine::CVIBuffer*>(pComponent);
	NULL_CHECK_RETURN(m_pBuffer, E_FAIL);
	m_mapComponent.insert(MAPCOMPONENT::value_type(L"Buffer", pComponent));

	//OBBCollision_OBB	
	pComponent = m_pCollisionOBB = CCollision_OBB::Create(m_pDevice);
	NULL_CHECK_RETURN(m_pCollisionOBB, E_FAIL);
	m_pCollisionOBB->SetColInfo(&m_pInfo->m_matWorld, &D3DXVECTOR3(-1.f, -1.f, -1.f), &D3DXVECTOR3(1.f, 1.f, 1.f));
	m_mapComponent.insert(MAPCOMPONENT::value_type(L"Collision_OBB", pComponent));

	return S_OK;
	return Engine::OR_OK;

}

void CItem::Release( void )
{



}

BOOL CItem::CheckCollision( void )
{
	 Engine::CGameObject* pGameObject = m_pCollisionOBB->CheckCollision(Engine::LAYER_GAMELOGIC, L"Player", m_pInfo->m_vPos);
	 Engine::CGameObject* Shose = Engine::Get_Management()->GetObject(Engine::LAYER_UI, L"ShoseNum");
	 Engine::CGameObject* Power = Engine::Get_Management()->GetObject(Engine::LAYER_UI, L"PowerNum");
	 Engine::CGameObject* AddBomb = Engine::Get_Management()->GetObject(Engine::LAYER_UI, L"AddBombNum");

	



	if(pGameObject != NULL)
	{
		switch(m_tagItemOption)
		{
		case Engine::ITEM_SPEED:
			dynamic_cast<CPlayer*>(pGameObject)->SetSpeed(m_fPlayerSpeed);
			dynamic_cast<CShoseNum*>(Shose)->SetiNum(m_fPlayerSpeed);
			break;

		case Engine::ITEM_POWER:
			dynamic_cast<CPlayer*>(pGameObject)->SetPower(m_iPower);
			dynamic_cast<CPowerNum*>(Power)->SetiNum(m_iPower);
			break;

		case Engine::ITEM_ADDBOMB:
			dynamic_cast<CPlayer*>(pGameObject)->SetAddBomb(m_iAddBomb);
			dynamic_cast<CAddBombNum*>(AddBomb)->SetiNum(m_iAddBomb);
			break;
		}
		return TRUE;
	}
	else
	{
		return FALSE;
	}

	

	
}
