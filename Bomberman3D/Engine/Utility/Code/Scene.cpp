#include "Scene.h"

#include "Layer.h"

Engine::CScene::CScene(LPDIRECT3DDEVICE9 pDevice)
: m_pDevice(pDevice)
{
}

Engine::CScene::~CScene(void)
{
	Release();
}

HRESULT Engine::CScene::InitScene(void)
{
	return S_OK;
}

void Engine::CScene::Update(void)
{
	MAPLAYER::iterator		iter = m_mapLayer.begin();
	MAPLAYER::iterator		iter_end = m_mapLayer.end();

	for(; iter != iter_end; ++iter)
		iter->second->Update();
}

void Engine::CScene::Render(void)
{
	MAPLAYER::iterator		iter = m_mapLayer.begin();
	MAPLAYER::iterator		iter_end = m_mapLayer.end();

	for(; iter != iter_end; ++iter)
		iter->second->Render();
}

void Engine::CScene::Release(void)
{
	for_each(m_mapLayer.begin(), m_mapLayer.end(), CDeleteMap());
	m_mapLayer.clear();
}

const Engine::CComponent* Engine::CScene::GetComponent(const WORD& LayerID, const wstring& wstrObjKey, const wstring& wstrComponentKey)
{
	MAPLAYER::iterator	iter = m_mapLayer.find(LayerID);
	if(iter == m_mapLayer.end())
		return NULL;

	return iter->second->GetComponent(wstrObjKey, wstrComponentKey);
}

Engine::CGameObject* Engine::CScene::GetObject(const WORD& LayerID, const wstring& wstrObjKey)
{
	MAPLAYER::iterator	iter = m_mapLayer.find(LayerID);
	if(iter == m_mapLayer.end())
		return NULL;

	return iter->second->GetObject(wstrObjKey);
}

Engine::OBJLIST* Engine::CScene::GetObjectList(const WORD& LayerID, const wstring& wstrObjKey)
{
	MAPLAYER::iterator	iter = m_mapLayer.find(LayerID);
	if(iter == m_mapLayer.end())
		return NULL;

	return iter->second->GetObjectList(wstrObjKey);
}

