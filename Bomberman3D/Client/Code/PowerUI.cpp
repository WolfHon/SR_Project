#include "stdafx.h"
#include "PowerUI.h"

#include "Texture.h"

#include "VIBuffer.h"

#include "Transform.h"
#include "Include.h"
#include "Export_Function.h"


CPowerUI::CPowerUI( LPDIRECT3DDEVICE9 pDevice )
: Engine::CGameObject(pDevice)
, m_pTexture(NULL)
, m_pBuffer(NULL)
, m_pInfo(NULL)
{

}

CPowerUI::~CPowerUI( void )
{

}

Engine::OBJECT_RESULT CPowerUI::Update( void )
{
	Engine::CGameObject::Update();

	D3DXVec3TransformNormal(&m_pInfo->m_vDir, &g_vLook, &m_pInfo->m_matWorld);

	//D3DXMATRIX		matBill;
	//D3DXMatrixIdentity(&matBill);
	//m_pDevice->GetTransform(D3DTS_VIEW, &matBill);
	//ZeroMemory(&matBill.m[3][0], sizeof(D3DXVECTOR3));

	//D3DXMatrixInverse(&matBill, NULL, &matBill);
	//
	//D3DXMatrixIdentity(&matUI);

	//D3DXMatrixOrthoLH(&matUI, WINCX, WINCY, 0.f, 500.f);

	//
	//m_pInfo->m_matWorld = matBill * m_pInfo->m_matWorld;

	return Engine::OR_OK;
}

void CPowerUI::Render( void )
{ 
	m_pDevice->GetTransform(D3DTS_PROJECTION,&m_mattemp1);
	m_pDevice->GetTransform(D3DTS_VIEW,&m_mattemp);
	CalculateOrtho();
	m_pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	//m_pDevice->SetTransform(D3DTS_WORLD, &m_pInfo->m_matWorld);
	m_pTexture->Render(0,1);
	m_pBuffer->Render();

	m_pDevice->SetTransform(D3DTS_PROJECTION,&m_mattemp1);
	m_pDevice->SetTransform(D3DTS_VIEW,&m_mattemp);
}

CPowerUI* CPowerUI::Create( LPDIRECT3DDEVICE9 pDevice, D3DXVECTOR3 vPos)
{
	CPowerUI*	pGameObject = new CPowerUI(pDevice);
	if(FAILED(pGameObject->Initialize(vPos)))
		Safe_Delete(pGameObject);

	return pGameObject;
}

HRESULT CPowerUI::Initialize( D3DXVECTOR3 vPos)
{
	FAILED_CHECK(AddComponent());

	m_pInfo->m_vPos = vPos;
	//m_pInfo->m_vScale = D3DXVECTOR3(2.f , 2.f ,2.f);

	return S_OK;
}

HRESULT CPowerUI::AddComponent( void )
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

void CPowerUI::Release( void )
{

}

void CPowerUI::CalculateOrtho( void )
{
	D3DVIEWPORT9 vp;
	float fFar = 1.f;
	float fNear = 0.f;

	m_pDevice->GetViewport(&vp);

	float w = 2.f / vp.Width ;
	float h = 2.f / vp.Height;
	float a = 1.f;
	float b = 0.f;

	D3DXMatrixIdentity(&m_matproj);
	m_matproj._11 = w;
	m_matproj._22 = h;
	m_matproj._33 = a;
	m_matproj._43 = b;
	m_matproj._44 = 1;

	m_pDevice->SetTransform(D3DTS_PROJECTION,&m_matproj);

	//D3DXMatrixOrthoLH(&m_matproj,vp.Width,vp.Height,0.f,1.f);


	D3DXMATRIX matWorld, matView, matProj, mattemp;
	D3DXMatrixIdentity(&matWorld);
	D3DXMatrixIdentity(&matView);
	D3DXMatrixIdentity(&matProj);
	m_pDevice->GetTransform(D3DTS_PROJECTION,&matProj);


	float fScale[3];
	fScale[0] = 30.f;
	fScale[1] = 30.f;
	fScale[2] = 1.f;

	for(int i=0; i< 3 ; ++i)
	{
		for(int j = 0; j < 3; ++j)
			matView(i,j)*=fScale[i];

	}


	D3DXVECTOR3 UIPos =m_pInfo->m_vPos;

	D3DXVECTOR3 convertUiPos = UIPos;

	//convertUiPos.y = -UIPos.y;
	//convertUiPos.x -= 20.f;
	//convertUiPos.y += 10.f;
	memcpy(&matView._41,&convertUiPos,sizeof(D3DXVECTOR3));


	m_pDevice->SetTransform(D3DTS_WORLD,&matWorld);
	m_pDevice->SetTransform(D3DTS_VIEW,&matView);
	m_pDevice->SetTransform(D3DTS_PROJECTION,&matProj);

}
