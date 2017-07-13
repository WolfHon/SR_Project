/*!
 * \file LogoBack.h
 * \date 2017/07/05 10:15
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

#ifndef LogoBack_h__
#define LogoBack_h__

#include "GameObject.h"

namespace Engine
{
	class CTexture;
	class CVIBuffer;
}

class CLogoBack
	: public Engine::CGameObject
{
public:
	explicit CLogoBack(LPDIRECT3DDEVICE9 pDevice);

public:
	virtual ~CLogoBack(void);

public:
	virtual void Update(void);
	virtual void Render(void);

public:
	static CLogoBack* Create(LPDIRECT3DDEVICE9 pDevice);
	
private:
	HRESULT Initialize(void);
	HRESULT	AddComponent(void);
	void Release(void);

private:
	Engine::CTexture*		m_pTexture;
	Engine::CVIBuffer*		m_pBuffer;
};

#endif // LogoBack_h__