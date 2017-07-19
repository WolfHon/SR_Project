/*!
 * \class CComponent
 *
 * \ingroup GroupName
 *
 * \brief 
 *
 * TODO: Component
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

#ifndef __Component_h__
#define __Component_h__

#include "Engine_Include.h"

BEGIN(Engine)

class ENGINE_DLL CComponent
{
protected:
	CComponent(void);
	CComponent(const CComponent& rhs);

public:
	virtual ~CComponent(void) = 0;

public:
	virtual Engine::OBJECT_RESULT Update(void) { return Engine::OR_OK;};
	virtual DWORD Release(void) PURE;

public:
	void AddRefCnt(void);

protected:
	DWORD		m_dwRefCnt;
};

END

#endif // __Component_h__