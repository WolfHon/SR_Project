#ifndef __Cube_h_
#define __Cube_h_

#include "GameObject.h"

namespace Engine
{
	class CTexture;
	class CVIBuffer;
	class CTransform;
}
class CCollision_OBB;

class CCube
	: public Engine::CGameObject
{
public:
	explicit CCube(LPDIRECT3DDEVICE9 pDevice);

public:
	virtual ~CCube(void);

public:
	virtual Engine::OBJECT_RESULT Update(void);
	virtual void Render(void);

public:
	static CCube* Create(LPDIRECT3DDEVICE9 pDevice, Engine::TILEINFO _TileInfo);

private:
	HRESULT Initialize(Engine::TILEINFO _TileInfo);
	HRESULT	AddComponent(void);
	void Release(void);

private:
	Engine::CTexture*		m_pTexture;
	Engine::CVIBuffer*		m_pBuffer;
	Engine::CTransform*		m_pInfo;
	Engine::TILEINFO		m_tagTileInfo;

	CCollision_OBB*	m_pCollisionOBB;
};

#endif // __Cube_h_