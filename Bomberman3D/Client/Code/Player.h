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
	static CPlayer* Create(LPDIRECT3DDEVICE9 pDevice);

private:
	HRESULT Initialize(void);
	HRESULT	AddComponent(void);
	void AttackCheck(void);
	void MoveCheck(void);
	BOOL CheckCollision(void);
	void Release(void);

private:
	Engine::CTexture*		m_pTexture;
	Engine::CTransform*		m_pInfo;
	Engine::CPlayerModel*	m_pPlayerModel;

	CCollision_OBB*	m_pCollisionOBB;

private:	
	float			m_fSpeed;
	float			m_fAngle;

	D3DXVECTOR3 m_vExMousePos;
};

#endif // Player_h__