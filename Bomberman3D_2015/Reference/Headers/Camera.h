/*!
 * \class CCamera
 *
 * \ingroup GroupName
 *
 * \brief 
 *
 * TODO: Camera class
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

#ifndef __Camera_h__
#define __Camera_h__

#include "GameObject.h"

BEGIN(Engine)

class ENGINE_DLL CCamera
	: public CGameObject
{
protected:
	explicit CCamera(LPDIRECT3DDEVICE9 pDevice);

public:
	virtual ~CCamera(void);

public:
	void SetViewSpaceMatrix(const D3DXVECTOR3* pEye, const D3DXVECTOR3* pAt
		, const D3DXVECTOR3* pUp);
	void SetProjectionMatrix(const float& fFovY, const float& fAspect
		, const float& fNear, const float& fFar);

protected:
	D3DXMATRIX		m_matView, m_matProj;
	D3DXVECTOR3		m_vEye, m_vAt, m_vUp;
};

END

#endif // __Camera_h__