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
	if(m_pScene != NULL)
		m_pScene->Render();

#ifdef _DEBUG

	D3DXMATRIX matFps;
	D3DXMatrixTranslation(&matFps, 20.f, 20.f, 0.f);

	++m_iFrameCnt;
	m_fTime += fTime;

	if(1.f < m_fTime)
	{
		wsprintf(m_szFps, L"FPS : %d", m_iFrameCnt);
		m_fTime = 0.f;
		m_iFrameCnt = 0;
	}

	m_pD3DXSprite->Begin(D3DXSPRITE_ALPHABLEND);
	m_pD3DXSprite->SetTransform(&matFps);
	m_pD3DXFont->DrawTextW(m_pD3DXSprite, m_szFps, lstrlen(m_szFps), NULL, NULL, D3DCOLOR_ARGB(255, 0, 255, 0));
	m_pD3DXSprite->End();

#endif
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
#ifdef _DEBUG
	if (FAILED(D3DXCreateSprite(m_pDevice, &m_pD3DXSprite)))
		return E_FAIL;

	D3DXFONT_DESC		hFont;
	ZeroMemory(&hFont, sizeof(D3DXFONT_DESC));
	hFont.Width = 15;
	hFont.Height = 20;
	hFont.Weight = FW_NORMAL;
	lstrcpy(hFont.FaceName, L"±¼¸²");
	hFont.CharSet = HANGEUL_CHARSET;

	HRESULT hr = D3DXCreateFontIndirect(m_pDevice, &hFont, &m_pD3DXFont);
	FAILED_CHECK(hr);
#endif

	return S_OK;
}

void Engine::CRenderer::Release(void)
{
#ifdef _DEBUG
	Safe_Release(m_pD3DXSprite);
	Safe_Release(m_pD3DXFont);
#endif
}

