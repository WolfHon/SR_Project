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

#define PLANE_EPSILON	5.0f

BEGIN(Engine)

class CGameObject;
class CComponent;

class ENGINE_DLL CLayer
{
private:
	explicit CLayer(LPDIRECT3DDEVICE9 pDevice);

public:
	~CLayer(void);

public:
	const CComponent* GetComponent(const wstring& wstrObjKey, const wstring& wstrComponentKey);
	CGameObject* GetObject(const wstring& wstrObjKey);
	Engine::OBJLIST* GetObjectList(const wstring& wstrObjKey);

public:
	HRESULT AddObject(const wstring& wstrObjKey, CGameObject* pGameObject);

public:
	void Update(void);
	void Render(D3DXPLANE* m_plane, BOOL bCulling);

public:
	static CLayer* Create(LPDIRECT3DDEVICE9 pDevice);

public:
	void Release(void);

private:
	BOOL IsInSphere(D3DXPLANE* m_plane, CGameObject* Obj);

private:	
	typedef map<wstring, OBJLIST>	MAPOBJLIST;
	MAPOBJLIST		m_mapObjlist;

	LPDIRECT3DDEVICE9 m_pDevice;
};

END

#endif // __Layer_h__