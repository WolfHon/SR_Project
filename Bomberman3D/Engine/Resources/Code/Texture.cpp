#include "Texture.h"

Engine::CTexture::CTexture(LPDIRECT3DDEVICE9 pDevice)
: CResources(pDevice)
{
}

Engine::CTexture::CTexture(const CTexture& rhs)
: CResources(rhs)
, m_dwContainerSize(rhs.m_dwContainerSize)
, m_vecTexture(rhs.m_vecTexture)
{
}

Engine::CTexture::~CTexture(void)
{	
}

Engine::CResources* Engine::CTexture::CloneResource(void)
{
	return new CTexture(*this);
}

HRESULT Engine::CTexture::LoadTexture(TEXTURETYPE eTextureType, const wstring& wstrFilePath, const WORD& wCnt)
{
	IDirect3DBaseTexture9*		pTexture = NULL;

	if(wCnt == 0)
		return E_FAIL;

	m_vecTexture.reserve(wCnt);

	TCHAR		szFullPath[MAX_PATH] = L"";

	for(size_t i = 0; i < wCnt; ++i)
	{
		wsprintf(szFullPath, wstrFilePath.c_str(), i);

		HRESULT		hr = NULL;
		switch(eTextureType)
		{
		case TEXTURE_NORMAL:
			hr = D3DXCreateTextureFromFile(m_pDevice, szFullPath, (LPDIRECT3DTEXTURE9*)&pTexture);
			break;

		case TEXTURE_CUBE:
			hr = D3DXCreateCubeTextureFromFile(m_pDevice, szFullPath, (LPDIRECT3DCUBETEXTURE9*)&pTexture);
			break;
		}
		FAILED_CHECK_MSG(hr, szFullPath);

		m_vecTexture.push_back(pTexture);
	}

	m_dwContainerSize = m_vecTexture.size();

	return S_OK;
}

void Engine::CTexture::Render(const DWORD& dwStage, const DWORD& iIndex)
{
	if(iIndex >= m_dwContainerSize)
		return;

	m_pDevice->SetTexture(dwStage, m_vecTexture[iIndex]);
}

Engine::CTexture* Engine::CTexture::Create(LPDIRECT3DDEVICE9 pGraphicDev, TEXTURETYPE eTextureType
										   , const wstring& wstrFilePath, const WORD& wCnt)
{
	CTexture*	pTexture = new CTexture(pGraphicDev);

	if(FAILED(pTexture->LoadTexture(eTextureType, wstrFilePath, wCnt)))
		Safe_Delete(pTexture);

	return pTexture;
}

DWORD Engine::CTexture::Release(void)
{
	if( m_dwRefCnt == 0 )
	{
		DWORD		dwSize = m_vecTexture.size();

		for(DWORD i = 0; i < dwSize; ++i)
			Engine::Safe_Release(m_vecTexture[i]);

		m_vecTexture.clear();

		return 0;
	}
	else
		--m_dwRefCnt;

	return m_dwRefCnt;
}

