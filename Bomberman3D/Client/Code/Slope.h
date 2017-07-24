/*!
 * \class CSlope
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

#ifndef __Slope_h__
#define __Slope_h__

#include "Block.h"

class CSlope
	: public CBlock
{
public:
	explicit CSlope(LPDIRECT3DDEVICE9 pDevice);

public:
	virtual ~CSlope(void);

public:
	virtual Engine::OBJECT_RESULT Update(void);
	virtual void Render(void);

public:
	static CSlope* Create(LPDIRECT3DDEVICE9 pDevice, Engine::TILEINFO _TileInfo);

public:
	Engine::TILETYPE GetTileType(void) { return m_tagTileInfo.eTileOption; }

private:
	HRESULT Initialize(Engine::TILEINFO _TileInfo);
	HRESULT	AddComponent(void);
	void Release(void);

private:
	D3DXMATRIX		m_matSlope;
};

#endif // __Slope_h__