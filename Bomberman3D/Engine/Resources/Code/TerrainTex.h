/*!
 * \class CTerrainTex
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

#ifndef __TerrainTex_h__
#define __TerrainTex_h__

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

#endif // __TerrainTex_h__