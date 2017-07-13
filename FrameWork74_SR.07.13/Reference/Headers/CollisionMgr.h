/*!
 * \file CollisionMgr.h
 * \date 2017/07/10 10:20
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

#ifndef CollisionMgr_h__
#define CollisionMgr_h__

#include "Engine_Include.h"

BEGIN(Engine)

class CCollision;

class ENGINE_DLL CCollisionMgr
{
public:
	DECLARE_SINGLETON(CCollisionMgr)

private:
	CCollisionMgr(void);
	~CCollisionMgr(void);

public:
	CCollision* GetColObject(COLLISIONID eCollisionID);

public:
	void SetTerrainVtx(const VTXTEX* pTerrainVtx);

public:
	HRESULT AddColObject(COLLISIONID eCollisionID, CCollision* pCollision);

private:
	void Release(void);

private:
	typedef map<COLLISIONID, CCollision*>		MAPCOLLISION;
	MAPCOLLISION		m_mapCollision;
};

END

#endif // CollisionMgr_h__