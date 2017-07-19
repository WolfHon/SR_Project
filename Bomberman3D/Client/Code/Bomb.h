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
	static CBomb* Create(LPDIRECT3DDEVICE9 pDevice, D3DXVECTOR3 vPos, int iPower);

private:
	HRESULT Initialize(D3DXVECTOR3 vPos, int iPower);
	HRESULT	AddComponent(void);
	void Explosion(void);
	void Release(void);

private:
	Engine::CTexture*		m_pTexture;
	Engine::CVIBuffer*		m_pBuffer;
	Engine::CTransform*		m_pInfo;
	Engine::CCollision_OBB*	m_pCollisionOBB;

private:
	float			m_fTime;
	int				m_iPower;
};


#endif // __Bomb_h__