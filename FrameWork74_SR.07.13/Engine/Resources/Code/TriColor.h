/*!
 * \file TriColor.h
 * \date 2017/07/03 11:20
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

#ifndef TriColor_h__
#define TriColor_h__

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

#endif // TriColor_h__