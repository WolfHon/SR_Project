/*!
 * \class CSlopeTex
 *
 * \ingroup GroupName
 *
 * \brief 
 *
 * TODO: SlopeTexture
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

#ifndef __SlopeTex_h__
#define __SlopeTex_h__

#include "VIBuffer.h"

BEGIN(Engine)

class ENGINE_DLL CSlopeTex
	: public CVIBuffer
{
private:
	explicit CSlopeTex(LPDIRECT3DDEVICE9 pDevice);
	explicit CSlopeTex(const CSlopeTex& rhs);

public:
	virtual ~CSlopeTex(void);

public:
	virtual CResources* CloneResource(void);

public:
	HRESULT	CreateBuffer(void);

public:
	static CSlopeTex* Create(LPDIRECT3DDEVICE9 pDevice);
};

END

#endif // __SlopeTex_h__