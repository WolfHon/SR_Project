#include "InfoSubject.h"

IMPLEMENT_SINGLETON(Engine::CInfoSubject)

Engine::CInfoSubject::CInfoSubject(void)
{
}

Engine::CInfoSubject::~CInfoSubject(void)
{
	Release();
}

Engine::DATALIST* Engine::CInfoSubject::GetDatalist(const wstring& message)
{
	MAPDATALIST::iterator	iter = m_mapDatalist.find(message);

	if(iter == m_mapDatalist.end())
		return NULL;

	return &iter->second;
}

void Engine::CInfoSubject::AddData(const wstring& message, void* pData)
{
	if(pData)
	{
		MAPDATALIST::iterator	iter = m_mapDatalist.find(message);

		if(iter == m_mapDatalist.end())
			m_mapDatalist[message] = DATALIST();

		m_mapDatalist[message].push_back(pData);
	}
}

void Engine::CInfoSubject::RemoveData(const wstring& message, void* pData)
{
	MAPDATALIST::iterator	iter = m_mapDatalist.find(message);

	if(iter != m_mapDatalist.end())
	{
		DATALIST::iterator	iterlist = iter->second.begin();
		DATALIST::iterator	iterlist_end = iter->second.end();

		for( ; iterlist != iterlist_end; ++iterlist)
		{
			if((*iterlist) == pData)
			{
				iter->second.erase(iterlist);
				return;
			}
		}
	}
}

void Engine::CInfoSubject::Release(void)
{
	for(MAPDATALIST::iterator iter = m_mapDatalist.begin(); iter != m_mapDatalist.end(); ++iter)
		iter->second.clear();

	m_mapDatalist.clear();
}
