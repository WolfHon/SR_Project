#ifndef BrokenCube_h__
#define BrokenCube_h__

#include "GameObject.h"

namespace Engine
{
	class CTexture;
	class CVIBuffer;
	class CTransform;
	class CCollision_OBB;
}

class CBrokenCube
	: public Engine::CGameObject
{
public:
	explicit CBrokenCube(LPDIRECT3DDEVICE9 pDevice);

public:
	virtual ~CBrokenCube(void);

public:
	virtual Engine::OBJECT_RESULT Update(void);
	virtual void Render(void);

public:
	static CBrokenCube* Create(LPDIRECT3DDEVICE9 pDevice, Engine::TILEINFO _TileInfo);

private:
	HRESULT Initialize(Engine::TILEINFO _TileInfo);
	HRESULT	AddComponent(void);
	void Release(void);

private:
	Engine::CTexture*		m_pTexture;
	Engine::CVIBuffer*		m_pBuffer;
	Engine::CTransform*		m_pInfo;
	Engine::CCollision_OBB*	m_pCollisionOBB;
	Engine::TILEINFO		m_tagTileInfo;

private:
	float			m_fSpeed;
	float			m_fAngle;
};

#endif // BrokenCube_h__