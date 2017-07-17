/*!
 * \class CBomb
 *
 * \ingroup GroupName
 *
 * \brief 
 *
 * TODO: long description
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
#ifndef Cube_h__
#define Cube_h__

#include "GameObject.h"

namespace Engine
{
	class CTexture;
	class CVIBuffer;
	class CTransform;
	class CCollision_OBB;
}

class CCameraObserver;

class CCube
	: public Engine::CGameObject
{
public:
	explicit CCube(LPDIRECT3DDEVICE9 pDevice);

public:
	virtual ~CCube(void);

public:
	virtual void Update(void);
	virtual void Render(void);

public:
	static CCube* Create(LPDIRECT3DDEVICE9 pDevice);

private:
	HRESULT Initialize(void);
	HRESULT	AddComponent(void);
	void Release(void);

private:
	Engine::CTexture*		m_pTexture;
	Engine::CVIBuffer*		m_pBuffer;
	Engine::CTransform*		m_pInfo;
	Engine::CCollision_OBB*	m_pCollisionOBB;

private:
	float			m_fSpeed;
	float			m_fAngle;
};


#endif // Cube_h__