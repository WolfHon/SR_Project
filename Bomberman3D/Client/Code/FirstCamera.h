/*!
 * \class CFirstCamera
 *
 * \ingroup GroupName
 *
 * \brief 
 *
 * TODO: long description
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

#ifndef __FirstCamera_h__
#define __FirstCamera_h__

#include "Camera.h"

namespace Engine
{
	class CTransform;
}

class CFirstCamera
	: public Engine::CCamera
{
private:
	explicit CFirstCamera(LPDIRECT3DDEVICE9 pDevice);

public:
	virtual ~CFirstCamera(void);

public:
	virtual void Update(void);

private:
	HRESULT Initialize(void);

public:
	void SetCameraTarget(const Engine::CTransform* pTargetInfo);

public:
	static CFirstCamera* Create(LPDIRECT3DDEVICE9 pDevice
		, const Engine::CTransform* pTargetInfo);

private:
	void ViewCheck(void);
	void TargetRenewal(void);

private:
	void Release(void);

private:
	const Engine::CTransform*		m_pTargetInfo;

private:
	float		m_fAngleY;

	D3DXVECTOR3	m_vExMousePos;
};

#endif // __FirstCamera_h__