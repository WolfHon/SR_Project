#include "Management.h"

#include "Scene.h"
#include "Renderer.h"

IMPLEMENT_SINGLETON(Engine::CManagement)

Engine::CManagement::CManagement(void)
: m_pScene(NULL)
, m_pRenderer(NULL)
, m_pDevice(NULL)
{

}

Engine::CManagement::~CManagement(void)
{
	Release();
}

HRESULT Engine::CManagement::InitManagement(LPDIRECT3DDEVICE9 pDevice)
{
	m_pDevice = pDevice;
	m_pRenderer = CRenderer::Create(pDevice);
	NULL_CHECK_RETURN(m_pRenderer, E_FAIL);
	return S_OK;
}

void Engine::CManagement::Update(void)
{
	NULL_CHECK(m_pScene);
	m_pScene->Update();	
}

void Engine::CManagement::Render(const float& fTime)
{
	NULL_CHECK(m_pRenderer);
	m_pRenderer->Render(fTime);
}

void Engine::CManagement::Release(void)
{
	Safe_Delete(m_pRenderer);
	Safe_Delete(m_pScene);
}

