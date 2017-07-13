/*!
 * \file Management.h
 * \date 2017/07/03 10:21
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

#ifndef Management_h__
#define Management_h__

#include "Engine_Include.h"

#include "Renderer.h"

BEGIN(Engine)

class CScene;

class ENGINE_DLL CManagement
{
public:
	DECLARE_SINGLETON(CManagement)

private:
	CManagement(void);
	~CManagement(void);

public:
	HRESULT InitManagement(LPDIRECT3DDEVICE9 pDevice);
	void Update(void);
	void Render(const float& fTime);

public:
	template <typename T>
	HRESULT SceneChange(T& Functor, LPDIRECT3DDEVICE9 pDevice);

private:
	void Release(void);

protected:
	LPDIRECT3DDEVICE9		m_pDevice;

private:
	CScene*		m_pScene;
	CRenderer*	m_pRenderer;
};

template <typename T>
HRESULT Engine::CManagement::SceneChange(T& Functor, LPDIRECT3DDEVICE9 pDevice)
{
	if(m_pScene != NULL)
		Safe_Delete(m_pScene);

	HRESULT hr = Functor(&m_pScene, pDevice);
	FAILED_CHECK(hr);

	m_pScene->Update();
	m_pRenderer->SetScene(m_pScene);
	return S_OK;
}

END

#endif // Management_h__