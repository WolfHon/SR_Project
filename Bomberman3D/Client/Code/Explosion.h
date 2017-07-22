#ifndef __Explosion_h__
#define __Explosion_h__

#include "GameObject.h"

namespace Engine
{
	class CTexture;
	class CVIBuffer;
	class CTransform;
}

class CCollision_OBB;

class CExplosion
	: public Engine::CGameObject
{
public:
	enum EXPLOSION_DIR { DIR_LEFT, DIR_RIGHT, DIR_FORWARD, DIR_BACK };
public:
	explicit CExplosion(LPDIRECT3DDEVICE9 pDevice);

public:
	virtual ~CExplosion(void);

public:
	virtual Engine::OBJECT_RESULT Update(void);
	virtual void Render(void);

public:
	static CExplosion* Create(LPDIRECT3DDEVICE9 pDevice, D3DXVECTOR3 vPos, int iPower, EXPLOSION_DIR edir);

private:
	HRESULT Initialize(D3DXVECTOR3 vPos, int iPower, EXPLOSION_DIR edir);
	void CheckExplosion(void);
	HRESULT	AddComponent(void);
	Engine::OBJECT_RESULT FrameCheck(void);
	void Release(void);

private:
	Engine::CTexture*		m_pTexture;
	Engine::CVIBuffer*		m_pBuffer;
	Engine::CTransform*		m_pInfo;

	CCollision_OBB*	m_pCollisionOBB;

private:
	D3DXMATRIX		m_matCol;

	float			m_fFrame;
	float			m_fFrameSpeed;
	DWORD		m_dwMaxFrame;
	EXPLOSION_DIR	m_eDir;

	int				m_iPower;
};


#endif // __Explosion_h__