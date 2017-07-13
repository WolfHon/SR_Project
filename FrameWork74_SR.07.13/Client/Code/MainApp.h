/*!
 * \file MainApp.h
 * \date 2017/06/29 10:20
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

#ifndef MainApp_h__
#define MainApp_h__

namespace Engine
{
	class CGraphicDev;
	class CVIBuffer;

	class CTexture;
}

class CMainApp
{
private:
	CMainApp(void);

public:
	~CMainApp(void);

public:
	HRESULT InitApp(void);
	void Update(void);
	void Render(void);

public:
	static CMainApp* Create(void);

private:
	void Release(void);

private:
	Engine::CGraphicDev*		m_pGraphicDev;
	LPDIRECT3DDEVICE9			m_pDevice;

private:
	Engine::CVIBuffer*			m_pBuffer;
	Engine::CTexture*			m_pTextre;
};

#endif // MainApp_h__