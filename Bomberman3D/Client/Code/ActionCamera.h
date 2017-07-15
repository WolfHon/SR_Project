/*!
 * \class CActionCamera
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

#ifndef __ActionCamera_h__
#define __ActionCamera_h__

#include "Camera.h"

namespace Engine
{
	class CTransform;
}

class CActionCamera
	: public Engine::CCamera
{
private:
	explicit CActionCamera(LPDIRECT3DDEVICE9 pDevice);

public:
	virtual ~CActionCamera(void);

public:
	virtual void Update(void);

private:
	HRESULT Initialize(void);

public:
	void SetCameraTarget(const Engine::CTransform* pTargetInfo);

public:
	static CActionCamera* Create(LPDIRECT3DDEVICE9 pDevice
		, const Engine::CTransform* pTargetInfo);

private:
	void DistCheck(void);
	void TargetRenewal(void);

private:
	void Release(void);

private:
	const Engine::CTransform*		m_pTargetInfo;

private:
	float		m_fMaxDistance;
	float		m_fTargetDistance;
	float		m_fAngleY;
	float		m_fCamSpeed;
};

#endif // __ActionCamera_h__