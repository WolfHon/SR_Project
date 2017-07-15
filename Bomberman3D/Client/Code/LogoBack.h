/*!
 * \class CLogoback
 *
 * \ingroup GroupName
 *
 * \brief 
 *
 * TODO: Logo Back Image
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

#ifndef __LogoBack_h__
#define __LogoBack_h__

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

#endif // __LogoBack_h__