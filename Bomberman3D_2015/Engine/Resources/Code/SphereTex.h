/*!
 * \file SphereTex.h
 * \date 2017/07/25 16:05
 *
 * \author Han
 * Contact: user@company.com
 *
 * \brief 
 *
 * TODO: long description
 *
 * \note
*/

#ifndef __SphereTex_h__
#define __SphereTex_h__

#include "VIBuffer.h"

BEGIN(Engine)

class ENGINE_DLL CSphereTex
	: public CVIBuffer
{
private:
	explicit CSphereTex(LPDIRECT3DDEVICE9 pDevice);
	explicit CSphereTex(const CSphereTex& rhs);

public:
	virtual ~CSphereTex(void);

public:
	virtual CResources* CloneResource(void);

public:
	HRESULT	CreateBuffer(void);

public:
	static CSphereTex* Create(LPDIRECT3DDEVICE9 pDevice);
};

END

#endif // __SphereTex_h__