#include "Layer.h"

#include "GameObject.h"

Engine::CLayer::CLayer(void)
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

void Engine::CLayer::Render(void)
{
	MAPOBJLIST::iterator	iter = m_mapObjlist.begin();
	MAPOBJLIST::iterator	iter_end = m_mapObjlist.end();

	for( ;iter != iter_end; ++iter)
	{
		OBJLIST::iterator		iterlist = iter->second.begin();
		OBJLIST::iterator		iterlist_end = iter->second.end();

		for( ;iterlist != iterlist_end ; ++iterlist)
			(*iterlist)->Render();
	}
}

Engine::CLayer* Engine::CLayer::Create(void)
{
	return new CLayer;
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

