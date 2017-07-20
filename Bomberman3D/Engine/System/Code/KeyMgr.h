/*!
 * \class CKeyMgr
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

#ifndef __KeyMgr_h__
#define __KeyMgr_h__

#include "Engine_Include.h"

BEGIN(Engine)

class ENGINE_DLL CKeyMgr
{
public:
	DECLARE_SINGLETON(CKeyMgr)

public:
	CKeyMgr();
	virtual ~CKeyMgr();

public:
	void		 Update(void);

public:
	DWORD	GetKey() { return m_dwKey; }

private:
	DWORD	m_dwKey;
	bool	m_bPress[6];
};

END

#endif	// __KeyMgr_h__
