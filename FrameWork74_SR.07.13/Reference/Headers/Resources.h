/*!
 * \file Resources.h
 * \date 2017/07/03 10:50
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

#ifndef Resources_h__
#define Resources_h__

#include "Component.h"

BEGIN(Engine)

class ENGINE_DLL CResources
	: public CComponent
{
protected:
	explicit CResources(LPDIRECT3DDEVICE9 pDevice);

public:
	virtual ~CResources(void);

public:
	virtual CResources* CloneResource(void) PURE;

public:
	virtual DWORD Release(void) PURE;

protected:
	LPDIRECT3DDEVICE9		m_pDevice;
};

END

#endif // Resources_h__