#include "stdafx.h"
#include "Skybox.h"

#include "Texture.h"
#include "VIBuffer.h"

#include "Include.h"
#include "Transform.h"
#include "Export_Function.h"

CSkybox::CSkybox(LPDIRECT3DDEVICE9 pDevice)
: Engine::CGameObject(pDevice)
, m_pTexture(NULL)
, m_pBuffer(NULL)
, m_pInfo(NULL)
{
}

CSkybox::~CSkybox(void)
{
	Release();
}

HRESULT CSkybox::Initialize(void)
{
	FAILED_CHECK(AddComponent());

	m_pInfo->m_vScale = D3DXVECTOR3(100.f, 100.f, 100.f);

	return S_OK;
}

Engine::OBJECT_RESULT CSkybox::Update(void)
{
	D3DXMATRIX matView;
	m_pDevice->GetTransform(D3DTS_VIEW, &matView);
	D3DXMatrixInverse(&matView, NULL, &matView);
	m_pInfo->m_vPos = D3DXVECTOR3(matView._41, matView._42 + 10.f, matView._43);

	return Engine::CGameObject::Update();
}

void CSkybox::Render(void)
{
	m_pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	m_pDevice->SetRenderState(D3DRS_ZENABLE, FALSE);   

	m_pDevice->SetTransform(D3DTS_WORLD, &m_pInfo->m_matWorld);

	m_pTexture->Render(0, 0);
	m_pBuffer->Render();

	m_pDevice->SetRenderState(D3DRS_ZENABLE, TRUE);   
	m_pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
}

CSkybox* CSkybox::Create(LPDIRECT3DDEVICE9 pDevice)
{
	CSkybox*	pGameObject = new CSkybox(pDevice);
	if(FAILED(pGameObject->Initialize()))
		Safe_Delete(pGameObject);

	return pGameObject;
}

void CSkybox::Release(void)
{	
}

HRESULT CSkybox::AddComponent(void)
{
	Engine::CComponent*		pComponent = NULL;

	//Transform
	pComponent = m_pInfo = Engine::CTransform::Create(g_vLook);
	NULL_CHECK_RETURN(m_pInfo, E_FAIL);
	m_mapComponent.insert(MAPCOMPONENT::value_type(L"Transform", pComponent));

	//Texture
	pComponent = Engine::Get_ResourceMgr()->CloneResource(Engine::RESOURCE_DYNAMIC, L"Texture_Skybox");
	m_pTexture = dynamic_cast<Engine::CTexture*>(pComponent);
	NULL_CHECK_RETURN(m_pTexture, E_FAIL);
	m_mapComponent.insert(MAPCOMPONENT::value_type(L"Texture", pComponent));

	//Buffer
	pComponent = Engine::Get_ResourceMgr()->CloneResource(Engine::RESOURCE_DYNAMIC, L"Buffer_CubeTex");
	m_pBuffer = dynamic_cast<Engine::CVIBuffer*>(pComponent);
	NULL_CHECK_RETURN(m_pBuffer, E_FAIL);
	m_mapComponent.insert(MAPCOMPONENT::value_type(L"Buffer", pComponent));

	return S_OK;
}