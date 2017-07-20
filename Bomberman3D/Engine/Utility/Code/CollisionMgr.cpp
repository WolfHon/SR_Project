#include "CollisionMgr.h"

#include "Collision_OBB.h"

IMPLEMENT_SINGLETON(Engine::CCollisionMgr)

Engine::CCollisionMgr::CCollisionMgr(void)
{
}

Engine::CCollisionMgr::~CCollisionMgr(void)
{
	Release();
}

HRESULT Engine::CCollisionMgr::AddColObject(COLLISIONID eCollisionID, LPDIRECT3DDEVICE9 pDevice)
{
	MAPCOLLISION::iterator	iter = m_mapCollision.find(eCollisionID);

	if(iter != m_mapCollision.end())
		return E_FAIL;

	CCollision*		pCollision = NULL;

	switch(eCollisionID)
	{
	case COLLISON_OBB:
		pCollision = CCollision_OBB::Create(pDevice);
		break;
	}

	NULL_CHECK_RETURN(pCollision, E_FAIL);

	m_mapCollision.insert(MAPCOLLISION::value_type(eCollisionID, pCollision));

	return S_OK;
}

void Engine::CCollisionMgr::Release(void)
{
	MAPCOLLISION::iterator	iter = m_mapCollision.begin();
	MAPCOLLISION::iterator	iter_end = m_mapCollision.end();

	for( ; iter != iter_end; ++iter )
	{
		DWORD dwRefCnt = iter->second->Release();
		if(dwRefCnt == 0)
			Safe_Delete(iter->second);
	}
	m_mapCollision.clear();
}

Engine::CCollision* Engine::CCollisionMgr::GetColObject(COLLISIONID eCollisionID)
{
	MAPCOLLISION::iterator	iter = m_mapCollision.find(eCollisionID);
	if(iter == m_mapCollision.end())
		return NULL;

	return iter->second->GetColObject();
}

Engine::CCollision* Engine::CCollisionMgr::CloneCollision(COLLISIONID eCollisionID)
{
	MAPCOLLISION::iterator	iter = m_mapCollision.find(eCollisionID);
	if(iter == m_mapCollision.end())
		return NULL;

	return iter->second->CloneCollision();
}

