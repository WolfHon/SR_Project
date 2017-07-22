#include "stdafx.h"
#include "ItemUi.h"

#include "Texture.h"

#include "VIBuffer.h"

#include "Transform.h"
#include "Include.h"
#include "Export_Function.h"


CItemUi::CItemUi( LPDIRECT3DDEVICE9 pDevice )
: Engine::CGameObject(pDevice)
, m_pTexture(NULL)
, m_pBuffer(NULL)
, m_pInfo(NULL)
{

}

CItemUi::~CItemUi( void )
{

}

Engine::OBJECT_RESULT CItemUi::Update( void )
{

	Engine::CGameObject::Update();

	D3DXVec3TransformNormal(&m_pInfo->m_vDir, &g_vLook, &m_pInfo->m_matWorld);

	D3DXMATRIX		matBill;
	D3DXMatrixIdentity(&matBill);
	m_pDevice->GetTransform(D3DTS_VIEW, &matBill);
	ZeroMemory(&matBill.m[3][0], sizeof(D3DXVECTOR3));

	D3DXMatrixInverse(&matBill, NULL, &matBill);
	
	;

	D3DXMatrixIdentity(&matUI);

	D3DXMatrixOrthoLH(&matUI, WINCX, WINCY, 0.f, 1.f);
	


	m_pInfo->m_matWorld = matBill * m_pInfo->m_matWorld;

	return Engine::OR_OK;
}

void CItemUi::Render( void )
{
		

	m_pDevice->SetTransform(D3DTS_WORLD, &m_pInfo->m_matWorld);
	
	m_pTexture->Render(0,0);
	m_pBuffer->Render();

}

CItemUi* CItemUi::Create( LPDIRECT3DDEVICE9 pDevice, D3DXVECTOR3 vPos)
{
	CItemUi*	pGameObject = new CItemUi(pDevice);
	if(FAILED(pGameObject->Initialize(vPos)))
		Safe_Delete(pGameObject);

	return pGameObject;
}

HRESULT CItemUi::Initialize( D3DXVECTOR3 vPos)
{


	FAILED_CHECK(AddComponent());

	m_pInfo->m_vPos = vPos;


	return S_OK;
}

HRESULT CItemUi::AddComponent( void )
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


	return S_OK;

}

void CItemUi::Release( void )
{

}
