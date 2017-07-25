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
	virtual Engine::OBJECT_RESULT Update(void);

private:
	HRESULT Initialize(void);
	void	KeyCheck(void);

public:
	void SetCameraTarget(Engine::CGameObject* pTarget, const Engine::CTransform* pTargetInfo);

public:
	static CFirstCamera* Create(LPDIRECT3DDEVICE9 pDevice, Engine::CGameObject* pTarget
		, const Engine::CTransform* pTargetInfo);

private:
	void ViewCheck(void);
	void TargetRenewal(void);

private:
	void Release(void);

private:
	const Engine::CTransform*		m_pTargetInfo;
	Engine::CGameObject*			m_pTarget;

private:
	float		m_fAngleY;
	float		m_fTime;

	D3DXVECTOR3	m_vExMousePos;
};

#endif // __FirstCamera_h__