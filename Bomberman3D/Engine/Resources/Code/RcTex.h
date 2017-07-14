/*!
 * \class CRcTex
 *
 * \ingroup GroupName
 *
 * \brief 
 *
 * TODO: Rect Texture
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

#ifndef __RcTex_h__
#define __RcTex_h__

#include "VIBuffer.h"

BEGIN(Engine)

class ENGINE_DLL CRcTex
	: public CVIBuffer
{
private:
	explicit CRcTex(LPDIRECT3DDEVICE9 pDevice);
	explicit CRcTex(const CRcTex& rhs);

public:
	virtual ~CRcTex(void);

public:
	virtual CResources* CloneResource(void);

public:
	HRESULT	CreateBuffer(void);

public:
	static CRcTex* Create(LPDIRECT3DDEVICE9 pDevice);
};

END

#endif // __RcTex_h__