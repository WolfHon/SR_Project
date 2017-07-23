#ifndef __Cube_h_
#define __Cube_h_

#include "Block.h"

class CCube
	: public CBlock
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

public:
	Engine::TILETYPE GetTileType(void) { return m_tagTileInfo.eTileOption; }

private:
	HRESULT Initialize(Engine::TILEINFO _TileInfo);
	HRESULT	AddComponent(void);
	void Release(void);
};

#endif // __Cube_h_