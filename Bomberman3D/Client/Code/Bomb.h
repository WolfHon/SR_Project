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

#ifndef __Bomb_h__
#define __Bomb_h__

#include "GameObject.h"

namespace Engine
{
	class CTexture;
	class CVIBuffer;
	class CTransform;
	class CCollision_OBB;
}

class CBomb
	: public Engine::CGameObject
{
public:
	explicit CBomb(LPDIRECT3DDEVICE9 pDevice);

public:
	virtual ~CBomb(void);

public:
	virtual void Update(void);
	virtual void Render(void);

public:
	static CBomb* Create(LPDIRECT3DDEVICE9 pDevice, float fPower);

private:
	HRESULT Initialize(float fPower);
	HRESULT	AddComponent(void);
	void Release(void);

private:
	Engine::CTexture*		m_pTexture;
	Engine::CVIBuffer*		m_pBuffer;
	Engine::CTransform*		m_pInfo;
	Engine::CCollision_OBB*	m_pCollisionOBB;

private:
	float			m_fTime;
	float			m_fPower;
};


#endif // __Bomb_h__