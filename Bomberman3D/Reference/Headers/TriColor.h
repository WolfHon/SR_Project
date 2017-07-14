/*!
 * \class CTriColor
 *
 * \ingroup GroupName
 *
 * \brief 
 *
 * TODO: Triangle Color
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

#ifndef __TriColor_h__
#define __TriColor_h__

#include "VIBuffer.h"

BEGIN(Engine)

class ENGINE_DLL CTriColor
	: public CVIBuffer
{
private:
	explicit CTriColor(LPDIRECT3DDEVICE9 pDevice);
	explicit CTriColor(const CTriColor& rhs);

public:
	virtual ~CTriColor(void);

public:
	virtual CResources* CloneResource(void);

public:
	HRESULT	CreateBuffer(void);

public:
	static CTriColor* Create(LPDIRECT3DDEVICE9 pDevice);

public:
	virtual void Render(void);
};

END

#endif // __TriColor_h__