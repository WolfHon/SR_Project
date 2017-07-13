/*!
 * \file InfoSubject.h
 * \date 2017/07/11 10:41
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

#ifndef InfoSubject_h__
#define InfoSubject_h__

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

#endif // InfoSubject_h__