/*!
 * \file Export_System.h
 * \date 2017/07/13 21:24
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

#ifndef __Export_System_h__
#define __Export_System_h__

#include "GraphicDev.h"
#include "TimeMgr.h"
#include "MouseMgr.h"
#include "KeyMgr.h"

BEGIN(Engine)

inline CGraphicDev* Get_GraphicDev(void);
inline CTimeMgr* Get_TimeMgr(void);
inline CMouseMgr* Get_MouseMgr(void);
inline CKeyMgr* Get_KeyMgr(void);

#include "Export_System.inl"

END

#endif // __Export_System_h__