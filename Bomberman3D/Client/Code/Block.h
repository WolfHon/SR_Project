#ifndef __Block_h_
#define __Block_h_

#include "GameObject.h"

namespace Engine
{
	class CTexture;
	class CVIBuffer;
	class CTransform;
}
class CCollision_OBB;

class CBlock
	: public Engine::CGameObject
{
public:
	explicit CBlock(LPDIRECT3DDEVICE9 pDevice);

public:
	virtual ~CBlock(void);

public:
	void Initialize(void);

public:
	Engine::TILETYPE GetTileType(void) { return m_tagTileInfo.eTileOption; }
	Engine::TILESHAPE GetTileShpae(void) { return m_tagTileInfo.eTileShape; }
	D3DXVECTOR3 GetTilePos(void) { return m_tagTileInfo.vPos; }
	CCollision_OBB* GetCollision_OBB(void) { return m_pCollisionOBB; }
	D3DXVECTOR3*	GetUpPoint(void) { return m_vUpPoint; }

private:
	void Release(void);

protected:
	Engine::CTexture*		m_pTexture;
	Engine::CVIBuffer*		m_pBuffer;
	Engine::CTransform*		m_pInfo;
	Engine::TILEINFO		m_tagTileInfo;

	D3DXVECTOR3				m_vUpPoint[4];

	CCollision_OBB*	m_pCollisionOBB;
};

#endif // __Block_h_