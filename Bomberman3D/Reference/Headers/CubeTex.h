/*!
 * \class CCubeTex
 *
 * \ingroup GroupName
 *
 * \brief 
 *
 * TODO: Cube Texture
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

#ifndef __CubeTex_h__
#define __CubeTex_h__

#include "VIBuffer.h"

BEGIN(Engine)

class ENGINE_DLL CCubeTex
	: public CVIBuffer
{
private:
	explicit CCubeTex(LPDIRECT3DDEVICE9 pDevice);
	explicit CCubeTex(const CCubeTex& rhs);

public:
	virtual ~CCubeTex(void);

public:
	virtual CResources* CloneResource(void);

public:
	HRESULT	CreateBuffer(void);

public:
	static CCubeTex* Create(LPDIRECT3DDEVICE9 pDevice);
};

END

#endif // __CubeTex_h__