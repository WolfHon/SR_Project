#include "Renderer.h"

#include "Scene.h"

Engine::CRenderer::CRenderer(LPDIRECT3DDEVICE9 pDevice)
: m_pDevice(pDevice)
, m_pD3DXFont(NULL)
, m_fTime(0.f)
, m_iFrameCnt(0)
, m_pScene(NULL)
{
	ZeroMemory(m_szFps, sizeof(TCHAR) * 128);
}

Engine::CRenderer::~CRenderer(void)
{
	Release();
}

void Engine::CRenderer::SetScene(CScene* pScene)
{
	m_pScene = pScene;
}

void Engine::CRenderer::Render(const float& fTime)
{
	RECT		rc = {100, 100, 300, 200};
	++m_iFrameCnt;
	m_fTime += fTime;

	if(1.f < m_fTime)
	{
		wsprintf(m_szFps, L"FPS : %d", m_iFrameCnt);
		m_fTime = 0.f;
		m_iFrameCnt = 0;
	}

	if(m_pScene != NULL)
		m_pScene->Render();

	m_pD3DXFont->DrawTextW(NULL, m_szFps, 0, &rc, DT_NOCLIP, D3DCOLOR_ARGB(255, 255, 255, 255));
}

Engine::CRenderer* Engine::CRenderer::Create(LPDIRECT3DDEVICE9 pDevice)
{
	CRenderer* pRenderer = new CRenderer(pDevice);
	if(FAILED(pRenderer->InitRenderer()))
		Safe_Delete(pRenderer);

	return pRenderer;
}

HRESULT Engine::CRenderer::InitRenderer(void)
{
	D3DXFONT_DESC		hFont;
	ZeroMemory(&hFont, sizeof(D3DXFONT_DESC));
	hFont.Width = 10;
	hFont.Height = 15;
	hFont.Weight = FW_NORMAL;
	lstrcpy(hFont.FaceName, L"±¼¸²");
	hFont.CharSet = HANGEUL_CHARSET;

	HRESULT hr = D3DXCreateFontIndirect(m_pDevice, &hFont, &m_pD3DXFont);
	FAILED_CHECK(hr);

	return S_OK;
}

void Engine::CRenderer::Release(void)
{
	Safe_Release(m_pD3DXFont);
}

