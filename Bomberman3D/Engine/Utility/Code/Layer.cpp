#include "Layer.h"

#include "GameObject.h"
#include "Transform.h"

Engine::CLayer::CLayer(LPDIRECT3DDEVICE9 pDevice)
:m_pDevice(pDevice)
{
}

Engine::CLayer::~CLayer(void)
{
	Release();
}

HRESULT Engine::CLayer::AddObject(const wstring& wstrObjKey, CGameObject* pGameObject)
{
	if(pGameObject)
	{
		MAPOBJLIST::iterator	iter = m_mapObjlist.find(wstrObjKey);
		if(iter == m_mapObjlist.end())
			m_mapObjlist[wstrObjKey] = OBJLIST();

		m_mapObjlist[wstrObjKey].push_back(pGameObject);
	}
	return S_OK;
}

void Engine::CLayer::Update(void)
{
	MAPOBJLIST::iterator	iter = m_mapObjlist.begin();
	MAPOBJLIST::iterator	iter_end = m_mapObjlist.end();
	
	for( ;iter != iter_end; ++iter)
	{
		OBJLIST::iterator		iterlist = iter->second.begin();
		OBJLIST::iterator		iterlist_end = iter->second.end();

		for( ;iterlist != iterlist_end ; ++iterlist)
			(*iterlist)->Update();
	}
}

void Engine::CLayer::Render(D3DXPLANE* m_plane, BOOL bCulling)
{
	MAPOBJLIST::iterator	iter = m_mapObjlist.begin();
	MAPOBJLIST::iterator	iter_end = m_mapObjlist.end();

	for( ;iter != iter_end; ++iter)
	{
		OBJLIST::iterator		iterlist = iter->second.begin();
		OBJLIST::iterator		iterlist_end = iter->second.end();

		for( ;iterlist != iterlist_end ; ++iterlist)
		{
			if(bCulling == FALSE || IsInSphere(m_plane, *iterlist) == TRUE)
				(*iterlist)->Render();
		}
	}
}

Engine::CLayer* Engine::CLayer::Create(LPDIRECT3DDEVICE9 pDevice)
{
	return new CLayer(pDevice);
}

void Engine::CLayer::Release(void)
{
	MAPOBJLIST::iterator	iter = m_mapObjlist.begin();
	MAPOBJLIST::iterator	iter_end = m_mapObjlist.end();

	for( ;iter != iter_end; ++iter)
	{
		OBJLIST::iterator		iterlist = iter->second.begin();
		OBJLIST::iterator		iterlist_end = iter->second.end();

		for( ;iterlist != iterlist_end ; ++iterlist)
			Safe_Delete(*iterlist);

		iter->second.clear();
	}
	m_mapObjlist.clear();
}

const Engine::CComponent* Engine::CLayer::GetComponent(const wstring& wstrObjKey, const wstring& wstrComponentKey)
{
	MAPOBJLIST::iterator	iter = m_mapObjlist.find(wstrObjKey);
	if(iter == m_mapObjlist.end())
		return NULL;

	OBJLIST::iterator	iterlist = iter->second.begin();
	OBJLIST::iterator	iterlist_end = iter->second.end();

	for( ; iterlist != iterlist_end; ++iterlist)
	{
		const CComponent* pComponent = (*iterlist)->GetComponent(wstrComponentKey);
		if(pComponent != NULL)
			return pComponent;
	}
	return NULL;
}

Engine::CGameObject* Engine::CLayer::GetObject(const wstring& wstrObjKey)
{
	MAPOBJLIST::iterator	iter = m_mapObjlist.find(wstrObjKey);
	if(iter == m_mapObjlist.end())
		return NULL;

	return *(iter->second.begin());
}

Engine::OBJLIST* Engine::CLayer::GetObjectList(const wstring& wstrObjKey)
{
	MAPOBJLIST::iterator	iter = m_mapObjlist.find(wstrObjKey);
	if(iter == m_mapObjlist.end())
		return NULL;

	return &(iter->second);
}

BOOL Engine::CLayer::IsInSphere(D3DXPLANE* m_plane, CGameObject* Obj)
{
	Engine::CComponent*	 pComponent = Obj->GetComponent(L"Transform");
	if(pComponent == NULL)
		return TRUE;

	D3DXVECTOR3 vtargetPos = dynamic_cast<Engine::CTransform*>(pComponent)->m_vPos;

	float		fDist;

	for(int i=0; i<6; ++i)
	{
		fDist = D3DXPlaneDotCoord(&m_plane[i], &vtargetPos);
		if( fDist > (8.f+PLANE_EPSILON) ) 
			return FALSE;
	}

	return TRUE;
}