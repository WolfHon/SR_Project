#include "stdafx.h"
#include "Logo.h"

#include "Export_Function.h"
#include "SceneSelector.h"
#include "Layer.h"
#include "LogoBack.h"
#include "SoundMgr.h"
#include "Button.h"
#include "Button1.h"

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
	CSoundMgr::GetInstance()->StopSoundAll();
	CSoundMgr::GetInstance()->PlayBGM(L"Logo.mp3");


	m_RcButtonRect.top = 580;
	m_RcButtonRect.bottom = 656;
	m_RcButtonRect.left = 461;
	m_RcButtonRect.right = 759;


	HRESULT		hr = NULL;
	hr = Engine::Get_ResourceMgr()->AddTexture(m_pDevice, Engine::RESOURCE_DYNAMIC
		, Engine::TEXTURE_NORMAL, L"Texture_LogoBack"
		, L"../bin/Texture/LogoBack/LogoBack.png", 1);
	FAILED_CHECK(hr);


	hr = Engine::Get_ResourceMgr()->AddTexture(m_pDevice, Engine::RESOURCE_DYNAMIC
		, Engine::TEXTURE_NORMAL, L"Texture_Button"
		, L"../bin/Texture/UI/Button/Button%d.png", 4);
	FAILED_CHECK(hr);

	FAILED_CHECK(Add_Enviroment_Layer());
	FAILED_CHECK(Add_GameLogic_Layer());
	FAILED_CHECK(Add_UI_Layer());

	return S_OK;
}

void CLogo::Update(void)
{
	DWORD		KeyState = Engine::Get_KeyMgr()->GetKey();


	m_ptMouse.x =(LONG)Engine::CMouseMgr::GetInstance()->GetMousePos().x;
	m_ptMouse.y = (LONG)Engine::CMouseMgr::GetInstance()->GetMousePos().y;

		/*if(!(~KeyState & Engine::MOUSE_LBUTTON_PRESS))
		{*/
		if(GetAsyncKeyState(VK_LBUTTON))
		{
			if(PtInRect(&m_RcButtonRect,m_ptMouse))
			{
			HRESULT hr = Engine::Get_Management()->SceneChange(CSceneSelector(SCENE_STAGE), m_pDevice);
			FAILED_CHECK_RETURN(hr, );
			return ;
			}
		}
		//}

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
	Engine::CLayer*			pLayer = Engine::CLayer::Create(m_pDevice);
	Engine::CGameObject*	pGameObject = NULL;

	pGameObject = CLogoBack::Create(m_pDevice);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	pLayer->AddObject(L"LogoBack", pGameObject);




	m_mapLayer.insert(MAPLAYER::value_type(Engine::LAYER_GAMELOGIC, pLayer));
	return S_OK;
}

HRESULT CLogo::Add_UI_Layer(void)
{

	Engine::CLayer*			pLayer = Engine::CLayer::Create(m_pDevice);
	Engine::CGameObject*	pGameObject = NULL;

	pGameObject = CButton::Create(m_pDevice,D3DXVECTOR3(10.f, -110.f, 0.f));
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	pLayer->AddObject(L"Button", pGameObject);


	pGameObject = CButton1::Create(m_pDevice,D3DXVECTOR3(10.f, -210.f, 0.f));
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	pLayer->AddObject(L"Button", pGameObject);

	m_mapLayer.insert(MAPLAYER::value_type(Engine::LAYER_UI, pLayer));

	return S_OK;
}

