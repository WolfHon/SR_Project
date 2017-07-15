#include "stdafx.h"
#include "MainApp.h"

#include "Include.h"
#include "Export_Function.h"
#include "SceneSelector.h"

CMainApp::CMainApp(void) 
: m_pGraphicDev(Engine::Get_GraphicDev())
, m_pDevice(NULL)
{
}

CMainApp::~CMainApp(void)
{
	Release();
}

HRESULT CMainApp::InitApp(void)
{
	HRESULT		hr = NULL;
	hr = m_pGraphicDev->InitGraphicDev(Engine::CGraphicDev::MODE_WIN, g_hWnd, WINCX, WINCY);
	FAILED_CHECK_MSG(hr, L"Device Initialize Fail");

	m_pDevice = m_pGraphicDev->GetDevice();
	NULL_CHECK_RETURN(m_pDevice, E_FAIL);

	m_pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	hr = Engine::Get_ResourceMgr()->AddBuffer(m_pDevice, Engine::RESOURCE_STATIC
		, Engine::BUFFER_RCTEX, L"Buffer_RcTex");
	FAILED_CHECK(hr);

	hr = Engine::Get_Management()->InitManagement(m_pDevice);
	FAILED_CHECK(hr);

	hr = Engine::Get_Management()->SceneChange(CSceneSelector(SCENE_LOGO), m_pDevice);
	FAILED_CHECK(hr);

	hr = Engine::Get_MouseMgr()->Initialize(g_hWnd, WINCX, WINCY);
	FAILED_CHECK(hr);
	

	Engine::Get_TimeMgr()->InitTime();

	return S_OK;
}

void CMainApp::Update(void)
{
	Engine::Get_TimeMgr()->SetTime();
	Engine::Get_MouseMgr()->Update();
	Engine::Get_Management()->Update();
}

void CMainApp::Render(void)
{
	m_pDevice->Clear(0, NULL, D3DCLEAR_STENCIL | D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER
		, D3DCOLOR_ARGB(255, 0, 0, 255), 1.f, 0);
	m_pDevice->BeginScene();

	Engine::Get_Management()->Render(Engine::Get_TimeMgr()->GetTime());

	m_pDevice->EndScene();
	m_pDevice->Present(NULL, NULL, NULL, NULL);
}

CMainApp* CMainApp::Create(void)
{
	CMainApp* pMain= new CMainApp;
	if(FAILED(pMain->InitApp()))
	{
		delete pMain;
		pMain = NULL;
	}
	return pMain;
}

void CMainApp::Release(void)
{
	Safe_Single_Destory(m_pGraphicDev);

	Engine::Get_Management()->DestroyInstance();
	Engine::Get_ResourceMgr()->DestroyInstance();
	Engine::Get_TimeMgr()->DestroyInstance();
	Engine::Get_InfoSubject()->DestroyInstance();
	Engine::Get_CollisionMgr()->DestroyInstance();
	Engine::Get_MouseMgr()->DestroyInstance();
}