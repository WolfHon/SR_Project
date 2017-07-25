/*!
 * \class CPlayer
 *
 * \ingroup GroupName
 *
 * \brief 
 *
 * TODO: Player Class
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

#ifndef __Player_h__
#define __Player_h__

#include "GameObject.h"

namespace Engine
{
	class CTexture;
	class CTransform;
	class CPlayerModel;
}

class CCollision_OBB;
class CCameraObserver;

class CPlayer
	: public Engine::CGameObject
{
public:
	explicit CPlayer(LPDIRECT3DDEVICE9 pDevice);

public:
	virtual ~CPlayer(void);

public:
	virtual Engine::OBJECT_RESULT Update(void);
	virtual void Render(void);

public:
	static CPlayer* Create(LPDIRECT3DDEVICE9 pDevice, D3DXVECTOR3 vPos);

public:
	void SetSpeed(float _Speed)
	{
		m_fPlayerSpeed += _Speed;
	}
	void SetPower(int _Power)
	{
		m_iPower += m_iPower;
	}
	void SetAddBomb(int _AddBomb)
	{
		m_iAddBomb += _AddBomb;
	}

public:
	float GetPress(void)
	{
		return m_fPress;
	}
private:
	HRESULT Initialize(D3DXVECTOR3 vPos);
	HRESULT	AddComponent(void);
	void AttackCheck(void);	
	void MoveCheck(void);
	void Release(void);

private:
	Engine::CTexture*		m_pTexture;
	Engine::CTransform*		m_pInfo;
	Engine::CPlayerModel*	m_pPlayerModel;

	CCollision_OBB*	m_pCollisionOBB;
	CCollision_OBB*	m_pCollSlopeCheck;

private:
	CCameraObserver*		m_pCamObserver;

private:	
	float			m_fSpeed;
	float			m_fAngle;	

	D3DXVECTOR3 m_vExMousePos;

private:
	float       m_fPlayerSpeed;
	int			m_iAddBomb;
	int			m_iPower;
	float		m_fPress;
	float		m_fPressValue;
};

#endif // Player_h__