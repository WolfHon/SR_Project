/*!
 * \class CCubeColor
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

#ifndef __CubeColor_h__
#define __CubeColor_h__

#include "VIBuffer.h"

BEGIN(Engine)

class ENGINE_DLL CCubeColor
	: public CVIBuffer
{
private:
	explicit CCubeColor(LPDIRECT3DDEVICE9 pDevice);
	explicit CCubeColor(const CCubeColor& rhs);

public:
	virtual ~CCubeColor(void);

public:
	virtual CResources* CloneResource(void);

public:
	HRESULT	CreateBuffer(void);

public:
	static CCubeColor* Create(LPDIRECT3DDEVICE9 pDevice);
};

END

#endif // __CubeColor_h__