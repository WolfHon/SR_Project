/*!
 * \file Renderer.h
 * \date 2017/07/04 10:49
 *
 * \author Administrator
 * Contact: user@company.com
 *
 * \brief 
 *
 * TODO: long description
 *
 * \note
*/

#ifndef Renderer_h__
#define Renderer_h__

#include "Engine_Include.h"

BEGIN(Engine)

class CScene;

class ENGINE_DLL CRenderer
{
private:
	explicit CRenderer(LPDIRECT3DDEVICE9 pDevice);

public:
	~CRenderer(void);

public:
	void SetScene(CScene* pScene);

public:
	void Render(const float& fTime);

public:
	static CRenderer* Create(LPDIRECT3DDEVICE9 pDevice);

private:
	HRESULT InitRenderer(void);
	void Release(void);

private:
	LPDIRECT3DDEVICE9	m_pDevice;
	CScene*		m_pScene;

private:
	ID3DXFont*		m_pD3DXFont;
	float			m_fTime;
	int				m_iFrameCnt;
	TCHAR			m_szFps[128];
};

END

#endif // Renderer_h__