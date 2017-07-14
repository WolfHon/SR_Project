#include "stdafx.h"
#include "LogoBack.h"
#include "Texture.h"
#include "RcTex.h"

#include "Export_Function.h"

CLogoBack::CLogoBack(LPDIRECT3DDEVICE9 pDevice)
: Engine::CGameObject(pDevice)
, m_pTexture(NULL)
, m_pBuffer(NULL)
{
}

CLogoBack::~CLogoBack(void)
{
	Release();
}

HRESULT CLogoBack::Initialize(void)
{
	FAILED_CHECK(AddComponent());
	return S_OK;
}

void CLogoBack::Update(void)
{
	Engine::CGameObject::Update();
}

void CLogoBack::Render(void)
{
	m_pTexture->Render(0, 0);
	m_pBuffer->Render();	
}

CLogoBack* CLogoBack::Create(LPDIRECT3DDEVICE9 pDevice)
{
	CLogoBack*	pGameObject = new CLogoBack(pDevice);
	if(FAILED(pGameObject->Initialize()))
		Safe_Delete(pGameObject);

	return pGameObject;
}

void CLogoBack::Release(void)
{
}

HRESULT CLogoBack::AddComponent(void)
{
	Engine::CComponent*		pComponent = NULL;

	//Texture
	pComponent = Engine::Get_ResourceMgr()->CloneResource(Engine::RESOURCE_DYNAMIC, L"Texture_LogoBack");
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
