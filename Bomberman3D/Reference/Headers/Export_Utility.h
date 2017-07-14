/*!
 * \file Export_Utility.h
 * \date 2017/07/14 10:23
 *
 * \author Han
 * Contact: user@company.com
 *
 * \brief 
 *
 * TODO: long description
 *
 * \note
*/

#ifndef __Export_Utility_h__
#define __Export_Utility_h__

#include "Management.h"
#include "CollisionMgr.h"
#include "InfoSubject.h"

BEGIN(Engine)

inline CManagement* Get_Management(void);
inline CCollisionMgr* Get_CollisionMgr(void);
inline CInfoSubject* Get_InfoSubject(void);

#include "Export_Utility.inl"

END

#endif // __Export_Utility_h__