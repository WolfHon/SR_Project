/*!
 * \file TerrainTex.h
 * \date 2017/07/06 10:09
 *
 * \author Administrator
 * Contact: user@company.com
 *
 * \brief 
 *
 * TODO: long description
 *
 * \note
*/
#ifndef TerrainTex_h__
#define TerrainTex_h__

#include "VIBuffer.h"

BEGIN(Engine)

class ENGINE_DLL CTerrainTex
	: public CVIBuffer
{
private:
	explicit CTerrainTex(LPDIRECT3DDEVICE9 pDevice);
	explicit CTerrainTex(const CTerrainTex& rhs);

public:
	virtual ~CTerrainTex(void);

public:
	virtual CResources* CloneResource(void);

public:
	HRESULT	CreateBuffer(const WORD& wCntX, const WORD& wCntZ, const WORD& wItv);

public:
	static CTerrainTex* Create(LPDIRECT3DDEVICE9 pDevice
		, const WORD& wCntX, const WORD& wCntZ, const WORD& wItv);
};

END

#endif // TerrainTex_h__