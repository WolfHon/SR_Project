/*!
 * \file StaticCamera.h
 * \date 2017/07/07 10:29
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

#ifndef StaticCamera_h__
#define StaticCamera_h__

#include "Camera.h"

namespace Engine
{
	class CTransform;
}

class CStaticCamera
	: public Engine::CCamera
{
private:
	explicit CStaticCamera(LPDIRECT3DDEVICE9 pDevice);

public:
	virtual ~CStaticCamera(void);

public:
	virtual void Update(void);

private:
	HRESULT Initialize(void);

public:
	void SetCameraTarget(const Engine::CTransform* pTargetInfo);

public:
	static CStaticCamera* Create(LPDIRECT3DDEVICE9 pDevice
		, const Engine::CTransform* pTargetInfo);

private:
	void KeyCheck(void);
	void TargetRenewal(void);

private:
	void Release(void);

private:
	const Engine::CTransform*		m_pTargetInfo;

private:
	float		m_fTargetDistance;
	float		m_fAngle;
	float		m_fCamSpeed;
};

#endif // StaticCamera_h__