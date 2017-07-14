#include "stdafx.h"
#include "Logo.h"

#include "Export_Function.h"
#include "SceneSelector.h"
#include "Layer.h"
#include "LogoBack.h"

CLogo::CLogo(LPDIRECT3DDEVICE9 pDevice)
: Engine::CScene(pDevice)
{
}

CLogo::~CLogo(void)
{
	Release();
}

HRESULT CLogo::Initialize(void)
{
	HRESULT		hr = NULL;
	hr = Engine::Get_ResourceMgr()->AddTexture(m_pDevice, Engine::RESOURCE_DYNAMIC
		, Engine::TEXTURE_NORMAL, L"Texture_LogoBack"
		, L"../bin/Texture/LogoBack/LogoBack.png", 1);
	FAILED_CHECK(hr);

	FAILED_CHECK(Add_Enviroment_Layer());
	FAILED_CHECK(Add_GameLogic_Layer());
	FAILED_CHECK(Add_UI_Layer());

	return S_OK;
}

void CLogo::Update(void)
{
	if(GetAsyncKeyState(VK_RETURN))
	{
		HRESULT hr = Engine::Get_Management()->SceneChange(CSceneSelector(SCENE_STAGE), m_pDevice);
		FAILED_CHECK_RETURN(hr, );
		return ;
	}
	Engine::CScene::Update();
}

void CLogo::Render(void)
{
	Engine::CScene::Render();
}

CLogo* CLogo::Create(LPDIRECT3DDEVICE9 pDevice)
{
	CLogo*	pScene = new CLogo(pDevice);
	if(FAILED(pScene->Initialize()))
		Safe_Delete(pScene);

	return pScene;
}

void CLogo::Release(void)
{
	Engine::Get_ResourceMgr()->ResetDynamic();
}

HRESULT CLogo::Add_Enviroment_Layer(void)
{
	return S_OK;
}

HRESULT CLogo::Add_GameLogic_Layer(void)
{
	Engine::CLayer*			pLayer = Engine::CLayer::Create();
	Engine::CGameObject*	pGameObject = NULL;

	pGameObject = CLogoBack::Create(m_pDevice);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	pLayer->AddObject(L"LogoBack", pGameObject);

	m_mapLayer.insert(MAPLAYER::value_type(LAYER_GAMELOGIC, pLayer));
	return S_OK;
}

HRESULT CLogo::Add_UI_Layer(void)
{
	return S_OK;
}

