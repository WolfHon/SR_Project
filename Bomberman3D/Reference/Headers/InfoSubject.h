/*!
 * \class CInfoSubject
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

#ifndef __InfoSubject_h__
#define __InfoSubject_h__

#include "Subject.h"

BEGIN(Engine)

typedef list<void*>					DATALIST;
typedef map<wstring, DATALIST>		MAPDATALIST;

class ENGINE_DLL CInfoSubject
	: public CSubject
{
public:
	DECLARE_SINGLETON(CInfoSubject)

private:
	CInfoSubject(void);
	virtual ~CInfoSubject(void);

public:
	DATALIST* GetDatalist(const wstring& message);

public:
	void AddData(const wstring& message, void* pData);
	void RemoveData(const wstring& message, void* pData);

private:
	void Release(void);

private:
	MAPDATALIST		m_mapDatalist;
};

END

#endif // __InfoSubject_h__