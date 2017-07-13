/*!
 * \file RcColor.h
 * \date 2017/07/03 11:32
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

#ifndef RcColor_h__
#define RcColor_h__

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

#endif // RcColor_h__