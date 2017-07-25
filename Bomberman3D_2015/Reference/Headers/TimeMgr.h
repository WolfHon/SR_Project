/*!
 * \class CTimeMgr
 *
 * \ingroup GroupName
 *
 * \brief 
 *
 * TODO: Time Manager
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

#ifndef __TimeMgr_h__
#define __TimeMgr_h__

#include "Engine_Include.h"

BEGIN(Engine)

class ENGINE_DLL CTimeMgr
{
public:
	DECLARE_SINGLETON(CTimeMgr)

private:
	CTimeMgr(void);
	~CTimeMgr(void);

public:
	void InitTime(void);
	void SetTime(void);

public:
	float GetTime(void);

private:
	LARGE_INTEGER		m_FrameTime;
	LARGE_INTEGER		m_FixTime;
	LARGE_INTEGER		m_LastTime;
	LARGE_INTEGER		m_CpuTick;

	float				m_fTime;
};

END

#endif // __TimeMgr_h__