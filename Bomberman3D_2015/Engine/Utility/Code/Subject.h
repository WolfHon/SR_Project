/*!
 * \class CSubject
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

#ifndef __Subject_h__
#define __Subject_h__

#include "Engine_Include.h"

BEGIN(Engine)

class CObserver;

class ENGINE_DLL CSubject
{
protected:
	CSubject(void);
	virtual ~CSubject(void);

public:
	virtual void Subscribe(CObserver* pObserver);
	virtual void UnSubscribe(CObserver* pObserver);
	virtual void Notify(const wstring& message, int iDataIndex = 0);

private:
	void Release(void);
	
protected:
	typedef list<CObserver*>		OBSERVERLIST;
	OBSERVERLIST		m_Observerlist;
};

END

#endif // __Subject_h__