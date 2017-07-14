/*!
 * \class CRcColor
 *
 * \ingroup GroupName
 *
 * \brief 
 *
 * TODO: Rect Color
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

#ifndef __RcColor_h__
#define __RcColor_h__

#include "VIBuffer.h"

BEGIN(Engine)

class ENGINE_DLL CRcColor
	: public CVIBuffer
{
private:
	explicit CRcColor(LPDIRECT3DDEVICE9 pDevice);

public:
	virtual ~CRcColor(void);

public:
	virtual CResources* CloneResource(void);

public:
	HRESULT	CreateBuffer(void);

public:
	static CRcColor* Create(LPDIRECT3DDEVICE9 pDevice);
};

END

#endif // __RcColor_h__