#include "GameObject.h"

#include "Component.h"

Engine::CGameObject::CGameObject(LPDIRECT3DDEVICE9 pDevice)
: m_pDevice(pDevice)
{
}

Engine::CGameObject::~CGameObject(void)
{
	Release();
}

const Engine::CComponent* Engine::CGameObject::GetComponent(const wstring& wstrComponentKey)
{
	MAPCOMPONENT::iterator	iter = m_mapComponent.find(wstrComponentKey);
	if(iter == m_mapComponent.end())
		return NULL;

	return iter->second;
}

void Engine::CGameObject::Update(void)
{
	MAPCOMPONENT::iterator	iter = m_mapComponent.begin();
	MAPCOMPONENT::iterator	iter_end = m_mapComponent.end();

	for( ; iter != iter_end; ++iter)
		iter->second->Update();
}

void Engine::CGameObject::Render(void)
{	
}

void Engine::CGameObject::Release(void)
{
	MAPCOMPONENT::iterator	iter = m_mapComponent.begin();
	MAPCOMPONENT::iterator	iter_end = m_mapComponent.end();

	for( ;iter != iter_end ; ++iter)
	{
		DWORD dwRefCnt = iter->second->Release();
		if(dwRefCnt == 0)
			Safe_Delete(iter->second);
	}
	m_mapComponent.clear();
}
