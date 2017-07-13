/*!
 * \class CMainApp
 *
 * \ingroup GroupName
 *
 * \brief 
 *
 * TODO: Main Application
 *
 * \note 
 *
 * \author Han
 *
 * \version 1.0
 *
 * \date July 2017
 *
 * Contact: user@company.com
 *
 */

#ifndef __MainApp_h__
#define __MainApp_h__

namespace Engine
{
	class CGraphicDev;
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
};

#endif // __MainApp_h__