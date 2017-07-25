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
}

class CCollision_OBB;
class CGravity;
class CPlayer;

class CBomb
	: public Engine::CGameObject
{
public:
	explicit CBomb(LPDIRECT3DDEVICE9 pDevice);

public:
	virtual ~CBomb(void);

public:
	virtual Engine::OBJECT_RESULT Update(void);
	virtual void Render(void);

public:
	CPlayer* GetOwn(void) { return m_Own; }

public:
	static CBomb* Create(LPDIRECT3DDEVICE9 pDevice, D3DXVECTOR3 vPos, int iPower, float Throw, CPlayer* Own);

private:
	HRESULT Initialize(D3DXVECTOR3 vPos, int iPower, float Throw, CPlayer* Own);
	HRESULT	AddComponent(void);
	void VibrationCamera(void);
	void FrameCheck(void);
	void Move(void);
	Engine::OBJECT_RESULT Explosion(void);
	void Release(void);

private:
	Engine::CTexture*		m_pTexture;
	Engine::CVIBuffer*		m_pBuffer;
	Engine::CTransform*		m_pInfo;

	CCollision_OBB*	m_pCollisionOBB;
	CGravity*		m_pGravity;

	CPlayer*		m_Own;
private:
	float			m_ThrowPower;
	float			m_fTime;
	WORD			m_wEffect;
	int				m_iPower;
	float			m_fExplosionTime;
	float			m_fDecreasePower;

	bool			m_bCollPlayer;
};


#endif // __Bomb_h__