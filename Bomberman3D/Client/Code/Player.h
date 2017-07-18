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
	class CCollision_OBB;
	class CPlayerModel;

#ifdef _DEBUG
	class CCubeColor;
#endif
}

class CPlayer
	: public Engine::CGameObject
{
public:
	explicit CPlayer(LPDIRECT3DDEVICE9 pDevice);

public:
	virtual ~CPlayer(void);

public:
	virtual void Update(void);
	virtual void Render(void);

public:
	static CPlayer* Create(LPDIRECT3DDEVICE9 pDevice);

private:
	HRESULT Initialize(void);
	HRESULT	AddComponent(void);
	void MoveCheck(void);
	BOOL CheckCollision(void);
	void Release(void);

private:
	Engine::CTexture*		m_pTexture;
	Engine::CTransform*		m_pInfo;
	Engine::CCollision_OBB*	m_pCollisionOBB;
	Engine::CPlayerModel*	m_pPlayerModel;

#ifdef _DEBUG
	Engine::CCubeColor*		m_pCubeColor;
	Engine::VTXCOL*	pVertex;
#endif

private:	
	float			m_fSpeed;
	float			m_fAngle;

	D3DXVECTOR3 m_vExMousePos;
};

#endif // Player_h__