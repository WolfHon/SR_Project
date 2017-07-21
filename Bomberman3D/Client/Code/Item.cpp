#include "stdafx.h"
#include "Item.h"

#include "Transform.h"
#include "Texture.h"
#include "VIBuffer.h"
#include "Export_Function.h"

CItem::CItem( LPDIRECT3DDEVICE9 pDevice )
:Engine::CGameObject(pDevice)
,m_pTexture(NULL)
,m_pBuffer(NULL)
,m_pInfo(NULL)
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

	m_pInfo->m_vPos = vPos;

	switch(_ItemOption)
	{
	case Engine::ITEM_SPEED:
		break;
	}

	return S_OK;
}

Engine::OBJECT_RESULT CItem::Update( void )
{
	return Engine::CGameObject::Update();

}

void CItem::Render( void )
{

}


HRESULT CItem::AddComponent( void )
{

	return Engine::OR_OK;
}

void CItem::Release( void )
{

}



