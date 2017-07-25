/*!
 * \file CameraObserver.h
 * \date 2017/07/11 10:52
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

#ifndef CameraObserver_h__
#define CameraObserver_h__

#include "Observer.h"
#include "Include.h"
#include "CameraControl.h"

class CCameraObserver
	: public Engine::CObserver
{
private:
	CCameraObserver(void);

public:
	virtual ~CCameraObserver(void);

public:
	const CCameraControl::CAMERATYPE GetCamType() {return m_eCameraType;}

public:
	virtual void Update(const wstring& message, int iDataIndex = 0);

public:
	static CCameraObserver* Create(void);

private:
	HRESULT InitObserver(void);
	void Release(void);

private:
	CCameraControl::CAMERATYPE		m_eCameraType;
};

#endif // CameraObserver_h__