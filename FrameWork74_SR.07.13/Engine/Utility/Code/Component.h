/*!
 * \file Component.h
 * \date 2017/07/03 10:47
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

#ifndef Component_h__
#define Component_h__

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
	virtual void Update(void) {};
	virtual DWORD Release(void) PURE;

public:
	void AddRefCnt(void);

protected:
	DWORD		m_dwRefCnt;
};

END

#endif // Component_h__