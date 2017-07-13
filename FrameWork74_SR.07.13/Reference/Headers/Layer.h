/*!
 * \file Layer.h
 * \date 2017/07/04 10:34
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

#ifndef Layer_h__
#define Layer_h__

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

#endif // Layer_h__