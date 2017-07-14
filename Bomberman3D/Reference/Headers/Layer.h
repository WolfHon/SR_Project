/*!
 * \class CLayer
 *
 * \ingroup GroupName
 *
 * \brief 
 *
 * TODO: Layer class
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

#ifndef __Layer_h__
#define __Layer_h__

#include "Engine_Include.h"

BEGIN(Engine)

class CGameObject;
class CComponent;

class ENGINE_DLL CLayer
{
private:
	CLayer(void);

public:
	~CLayer(void);

public:
	const CComponent* GetComponent(const wstring& wstrObjKey, const wstring& wstrComponentKey);

public:
	HRESULT AddObject(const wstring& wstrObjKey, CGameObject* pGameObject);

public:
	void Update(void);
	void Render(void);

public:
	static CLayer* Create(void);

public:
	void Release(void);

private:
	typedef list<CGameObject*>		OBJLIST;
	typedef map<wstring, OBJLIST>	MAPOBJLIST;
	MAPOBJLIST		m_mapObjlist;
};

END

#endif // __Layer_h__