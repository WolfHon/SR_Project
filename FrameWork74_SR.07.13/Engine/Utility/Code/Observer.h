/*!
 * \file Observer.h
 * \date 2017/07/11 10:17
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

#ifndef Observer_h__
#define Observer_h__

#include "Engine_Include.h"

BEGIN(Engine)

class ENGINE_DLL CObserver
{
protected:
	 CObserver(void);

public:
	 virtual ~CObserver(void);

public:
	virtual void Update(const wstring& message, int iDataIndex = 0) PURE;
};

END

#endif // Observer_h__