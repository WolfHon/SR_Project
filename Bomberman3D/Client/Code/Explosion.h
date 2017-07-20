#ifndef __Explosion_h__
#define __Explosion_h__

#include "GameObject.h"

namespace Engine
{
	class CTexture;
	class CVIBuffer;
	class CTransform;
}

class CExplosion
	: public Engine::CGameObject
{
public:
	explicit CExplosion(LPDIRECT3DDEVICE9 pDevice);

public:
	virtual ~CExplosion(void);

public:
	virtual Engine::OBJECT_RESULT Update(void);
	virtual void Render(void);

public:
	static CExplosion* Create(LPDIRECT3DDEVICE9 pDevice, D3DXVECTOR3 vPos, int iPower);

private:
	HRESULT Initialize(D3DXVECTOR3 vPos, int iPower);
	HRESULT	AddComponent(void);
	void Release(void);

private:
	Engine::CTexture*		m_pTexture;
	Engine::CVIBuffer*		m_pBuffer;
	Engine::CTransform*		m_pInfo;

private:
	float			m_fFrame;
	float			m_fFrameSpeed;

	int				m_iPower;
};


#endif // __Explosion_h__