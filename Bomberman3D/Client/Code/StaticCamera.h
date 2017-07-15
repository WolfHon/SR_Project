/*!
 * \class CStaticCamera
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

#ifndef __StaticCamera_h__
#define __StaticCamera_h__

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
	float		m_fAngleY;
	float		m_fAngleX;
	float		m_fCamSpeed;
};

#endif // StaticCamera_h__