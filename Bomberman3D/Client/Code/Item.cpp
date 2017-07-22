#include "stdafx.h"
#include "Item.h"

#include "Transform.h"
#include "Texture.h"
#include "VIBuffer.h"
#include "Export_Function.h"
#include "Collision_OBB.h"

#include "Include.h"
#include "Player.h"

CItem::CItem( LPDIRECT3DDEVICE9 pDevice )
:Engine::CGameObject(pDevice)
,m_pTexture(NULL)
,m_pBuffer(NULL)
,m_pInfo(NULL)
,m_inum(0)
,m_fPlayerSpeed(0)
,m_iAddBomb(0)
,m_fPower(0)

{

}

CItem::~CItem( void )
{
	Release();
}

CItem* CItem::create( LPDIRECT3DDEVICE9 pDevice, D3DXVECTOR3 vpos, Engine::ITEMOPTION _ItemOption )
{
	CItem*	pGameObject = new CItem(pDevice);
	if(FAILED(pGameObject->Initialize(vpos, _ItemOption)))
		Safe_Delete(pGameObject);

	return pGameObject;

}

HRESULT CItem::Initialize( D3DXVECTOR3 vPos, Engine::ITEMOPTION _ItemOption )
{
	FAILED_CHECK(AddComponent());
	m_pInfo->m_vPos = vPos;
	m_tagItemOption =_ItemOption;

	switch(_ItemOption)
	{
		case Engine::ITEM_SPEED:
			m_fPlayerSpeed = 1.f;
			break;

		case Engine::ITEM_POWER:
			m_fPower = 1.f;
			break;

		case Engine::ITEM_ADDBOMB:
			m_iAddBomb = 1;
			break;
	}

	return S_OK;
}


Engine::OBJECT_RESULT CItem::Update( void )
{
	

	if(CheckCollision() == TRUE)
	{
		if(m_inum == 1)
			return Engine::OR_OK;
		else
			return Engine::OR_DELETE;
	}
	
		
		//return Engine::OR_DELETE;

	 return Engine::CGameObject::Update();
}


void CItem::Render( void )
{
		m_pDevice->SetTransform(D3DTS_WORLD, &m_pInfo->m_matWorld);

		m_pTexture->Render(0, 0);
		m_pBuffer->Render();

}

HRESULT CItem::AddComponent( void )
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
	return Engine::OR_OK;

}

void CItem::Release( void )
{



}

BOOL CItem::CheckCollision( void )
{
	 Engine::CGameObject* pGameObject = NULL;
	++m_inum;

	Engine::OBJLIST* listObj = Engine::Get_Management()->GetObjectList(Engine::LAYER_GAMELOGIC, L"Player");

	if(m_pCollisionOBB->CheckCollision(m_pInfo->m_vPos, listObj))
	{
		Engine::OBJLIST::iterator iter = listObj->begin();
		Engine::OBJLIST::iterator iter_end = listObj->end();

		for( ; iter != iter_end ; ++iter)
		{
			if(m_inum == 1)
				continue;

			switch(m_tagItemOption)
			{
			case Engine::ITEM_SPEED:
				dynamic_cast<CPlayer*>((*iter))->SetSpeed(m_fPlayerSpeed);
				break;

			case Engine::ITEM_POWER:
				dynamic_cast<CPlayer*>((*iter))->SetPower(m_fPower);
				break;

			case Engine::ITEM_ADDBOMB:
				dynamic_cast<CPlayer*>((*iter))->SetAddBomb(m_iAddBomb);
				break;

			}
		}
	return TRUE;
	}
	else
	{
		return FALSE;
	}

	

	
}
