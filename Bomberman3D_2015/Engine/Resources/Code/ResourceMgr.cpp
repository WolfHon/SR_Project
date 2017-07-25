#include "ResourceMgr.h"

#include "RcTex.h"
#include "Texture.h"
#include "SlopeTex.h"
#include "CubeTex.h"
#include "SphereTex.h"
#include "CubeColor.h"
#include "PlayerModel.h"

IMPLEMENT_SINGLETON(Engine::CResouceMgr)

Engine::CResouceMgr::CResouceMgr(void)
{
}

Engine::CResouceMgr::~CResouceMgr(void)
{
	Release();
}

HRESULT Engine::CResouceMgr::AddBuffer(LPDIRECT3DDEVICE9 pDevice 
										, RESOURCETYPE eResourceID 
										, BUFFERTYPE eBufferID 
										, const wstring& wstrResourceKey 
										, const WORD& wCntX /*= 0*/
										, const WORD& wCntZ /*= 0*/
										, const WORD& wItv /*= 1*/)
{
	MAPRESOURCE::iterator	iter = m_mapResource[eResourceID].find(wstrResourceKey);

	if(iter != m_mapResource[eResourceID].end())
	{
		MSG_BOX(wstrResourceKey.c_str());
		return E_FAIL;
	}

	CResources*		pResource = NULL;

	switch(eBufferID)
	{
	case BUFFER_RCTEX:
		pResource = CRcTex::Create(pDevice);
		break;

	case BUFFER_SLOPETEX:
		pResource = CSlopeTex::Create(pDevice);
		break;

	case BUFFER_CUBETEX:
		pResource = CCubeTex::Create(pDevice);
		break;

	case BUFFER_CUBECOLOR:
		pResource = CCubeColor::Create(pDevice);
		break;

	case BUFFER_SPHERETEX:
		pResource = CSphereTex::Create(pDevice);
		break;
	case MODEL_PLAYER:
		pResource = CPlayerModel::Create(pDevice);
		break;
	}

	NULL_CHECK_RETURN(pResource, E_FAIL);

	m_mapResource[eResourceID].insert(MAPRESOURCE::value_type(wstrResourceKey, pResource));

	return S_OK;
}

HRESULT Engine::CResouceMgr::AddTexture(LPDIRECT3DDEVICE9 pDevice 
										 , RESOURCETYPE eResourceID 
										 , TEXTURETYPE eTextureID 
										 , const wstring& wstrResourceKey 
										 , const wstring& wstrFilePath 
										 , const WORD& wCnt)
{
	MAPRESOURCE::iterator	iter = m_mapResource[eResourceID].find(wstrResourceKey);

	if(iter != m_mapResource[eResourceID].end())
	{
		MSG_BOX(wstrResourceKey.c_str());
		return E_FAIL;
	}

	CResources*		pResource = CTexture::Create(pDevice, eTextureID, wstrFilePath, wCnt);
	NULL_CHECK_RETURN_MSG(pResource, E_FAIL, wstrFilePath.c_str());

	m_mapResource[eResourceID].insert(MAPRESOURCE::value_type(wstrResourceKey, pResource));

	return S_OK;
}

void Engine::CResouceMgr::Release(void)
{
	for(int i = 0; i < RESOURCE_END; ++i)
	{
		MAPRESOURCE::iterator	iter = m_mapResource[i].begin();
		MAPRESOURCE::iterator	iter_end = m_mapResource[i].end();

		for( ;iter != iter_end; ++iter)
		{
			DWORD	dwRefCnt = iter->second->Release();
			if(dwRefCnt == 0)
				Safe_Delete(iter->second);
		}

		m_mapResource[i].clear();
	}
}

Engine::CComponent* Engine::CResouceMgr::CloneResource(RESOURCETYPE eResourceID, const wstring& wstrResourceKey)
{
	MAPRESOURCE::iterator	iter = m_mapResource[eResourceID].find(wstrResourceKey);

	if(iter == m_mapResource[eResourceID].end())
		return NULL;

	return iter->second->CloneResource();
}

void Engine::CResouceMgr::ResetDynamic(void)
{
	MAPRESOURCE::iterator	iter = m_mapResource[RESOURCE_DYNAMIC].begin();
	MAPRESOURCE::iterator	iter_end = m_mapResource[RESOURCE_DYNAMIC].end();

	for( ;iter != iter_end; ++iter)
	{
		DWORD	dwRefCnt = iter->second->Release();
		if(dwRefCnt == 0)
			Safe_Delete(iter->second);
	}

	m_mapResource[RESOURCE_DYNAMIC].clear();
}
