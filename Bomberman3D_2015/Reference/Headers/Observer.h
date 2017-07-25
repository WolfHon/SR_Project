/*!
 * \class CObserver
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

#ifndef __Observer_h__
#define __Observer_h__

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

#endif // __Observer_h__