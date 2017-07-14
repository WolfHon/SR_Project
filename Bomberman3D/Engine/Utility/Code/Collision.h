/*!
 * \class CCollision
 *
 * \ingroup GroupName
 *
 * \brief 
 *
 * TODO: Collision Componenet
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

#ifndef __Collision_h__
#define __Collision_h__

#include "Component.h"

BEGIN(Engine)

class ENGINE_DLL CCollision
	: public CComponent
{
protected:
	CCollision(void);
	CCollision(const CCollision& rhs);

public:
	virtual ~CCollision(void);

public:
	CCollision* GetColObject(void);

public:
	virtual DWORD Release(void) PURE;
};

END

#endif // __Collision_h__