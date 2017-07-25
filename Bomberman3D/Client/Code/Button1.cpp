#include "stdafx.h"
#include "Button1.h"

#include "Texture.h"

#include "VIBuffer.h"

#include "Transform.h"
#include "Include.h"
#include "Export_Function.h"
#include "SoundMgr.h"


CButton1::CButton1( LPDIRECT3DDEVICE9 pDevice )
: Engine::CGameObject(pDevice)
, m_pTexture(NULL)
, m_pBuffer(NULL)
, m_pInfo(NULL)
, m_iNum(2)
{

}

CButton1::~CButton1( void )
{

}

Engine::OBJECT_RESULT CButton1::Update( void )
{
	Engine::CGameObject::Update();

	D3DXVec3TransformNormal(&m_pInfo->m_vDir, &g_vLook, &m_pInfo->m_matWorld);

	m_ptMouse.x = (LONG)Engine::CMouseMgr::GetInstance()->GetMousePos().x;
	m_ptMouse.y = (LONG)Engine::CMouseMgr::GetInstance()->GetMousePos().y;


	if(PtInRect(&m_RcButtonRect,m_ptMouse))
	{
		if(m_iNum == 3)
			return Engine::OR_OK;

		m_iNum = 3;
		CSoundMgr::GetInstance()->PlaySound(L"Rectin.wav",CSoundMgr::CHANNEL_EFFECT1);
	}
	else
	{
		if(m_iNum == 2)
			return Engine::OR_OK;

		m_iNum = 2;
		CSoundMgr::GetInstance()->PlaySound(L"RectOut.wav",CSoundMgr::CHANNEL_EFFECT1);
	}

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

void CButton1::Render( void )
{ 
	m_pDevice->GetTransform(D3DTS_PROJECTION,&m_mattemp1);
	m_pDevice->GetTransform(D3DTS_VIEW,&m_mattemp);
	m_pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	m_pDevice->SetRenderState(D3DRS_ALPHAREF, 0x00000088);
	m_pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	CalculateOrtho();

	m_pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	//m_pDevice->SetTransform(D3DTS_WORLD, &m_pInfo->m_matWorld);
	m_pTexture->Render(0,m_iNum);
	m_pBuffer->Render();

	m_pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	m_pDevice->SetTransform(D3DTS_PROJECTION,&m_mattemp1);
	m_pDevice->SetTransform(D3DTS_VIEW,&m_mattemp);
}

CButton1* CButton1::Create( LPDIRECT3DDEVICE9 pDevice, D3DXVECTOR3 vPos)
{
	CButton1*	pGameObject = new CButton1(pDevice);
	if(FAILED(pGameObject->Initialize(vPos)))
		Safe_Delete(pGameObject);

	return pGameObject;
}

HRESULT CButton1::Initialize( D3DXVECTOR3 vPos)
{
	FAILED_CHECK(AddComponent());


	m_pInfo->m_vPos = vPos;

	m_RcButtonRect.top = 580;
	m_RcButtonRect.bottom = 656;
	m_RcButtonRect.left = 461;
	m_RcButtonRect.right = 759;
	//m_pInfo->m_vScale = D3DXVECTOR3(2.f , 2.f ,2.f);

	return S_OK;
}

HRESULT CButton1::AddComponent( void )
{
	Engine::CComponent*		pComponent = NULL;

	//Transform
	pComponent = m_pInfo = Engine::CTransform::Create(g_vLook);
	NULL_CHECK_RETURN(m_pInfo, E_FAIL);
	m_mapComponent.insert(MAPCOMPONENT::value_type(L"Transform", pComponent));

	//Texture
	pComponent = Engine::Get_ResourceMgr()->CloneResource(Engine::RESOURCE_DYNAMIC, L"Texture_Button");
	m_pTexture = dynamic_cast<Engine::CTexture*>(pComponent);
	NULL_CHECK_RETURN(m_pTexture, E_FAIL);
	m_mapComponent.insert(MAPCOMPONENT::value_type(L"Texture", pComponent));

	//Buffer
	pComponent = Engine::Get_ResourceMgr()->CloneResource(Engine::RESOURCE_STATIC, L"Buffer_RcTex");
	m_pBuffer = dynamic_cast<Engine::CVIBuffer*>(pComponent);
	NULL_CHECK_RETURN(m_pBuffer, E_FAIL);
	m_mapComponent.insert(MAPCOMPONENT::value_type(L"Buffer", pComponent));


	return S_OK;

}

void CButton1::Release( void )
{

}

void CButton1::CalculateOrtho( void )
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
	fScale[0] = 150.f;
	fScale[1] = 50.f;
	fScale[2] = 1.f;

	for(int i=0; i< 3 ; ++i)
	{
		for(int j = 0; j < 3; ++j)
			matView(i,j)*=fScale[i];

	}


	D3DXVECTOR3 UIPos = m_pInfo->m_vPos;

	D3DXVECTOR3 convertUiPos = UIPos;

	//convertUiPos.y = -UIPos.y;
	//convertUiPos.x -= 20.f;
	//convertUiPos.y += 10.f;
	memcpy(&matView._41,&convertUiPos,sizeof(D3DXVECTOR3));


	m_pDevice->SetTransform(D3DTS_WORLD,&matWorld);
	m_pDevice->SetTransform(D3DTS_VIEW,&matView);
	m_pDevice->SetTransform(D3DTS_PROJECTION,&matProj);

}
