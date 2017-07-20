/*!
 * \class CCollisionMgr
 *
 * \ingroup GroupName
 *
 * \brief 
 *
 * TODO: Collision Managerment
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

#ifndef __CollisionMgr_h__
#define __CollisionMgr_h__

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
	CCollision* CloneCollision(COLLISIONID eCollisionID);

public:
	HRESULT AddColObject(COLLISIONID eCollisionID, LPDIRECT3DDEVICE9 pDevice);

private:
	void Release(void);

private:
	typedef map<COLLISIONID, CCollision*>		MAPCOLLISION;
	MAPCOLLISION		m_mapCollision;
};

END

#endif // __CollisionMgr_h__