/*!
 * \class CResources
 *
 * \ingroup GroupName
 *
 * \brief 
 *
 * TODO: Resource class
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

#ifndef __Resources_h__
#define __Resources_h__

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

#endif // __Resources_h__