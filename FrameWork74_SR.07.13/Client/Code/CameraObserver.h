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

class CCameraObserver
	: public Engine::CObserver
{
private:
	CCameraObserver(void);

public:
	virtual ~CCameraObserver(void);

public:
	const LPD3DXMATRIX GetCamMatrix(CAMERAMATRIXID eMatrixID) {return &m_Matrix[eMatrixID];}

public:
	virtual void Update(const wstring& message, int iDataIndex = 0);

public:
	static CCameraObserver* Create(void);

private:
	HRESULT InitObserver(void);
	void Release(void);

private:
	D3DXMATRIX		m_Matrix[MATRIX_END];
};

#endif // CameraObserver_h__