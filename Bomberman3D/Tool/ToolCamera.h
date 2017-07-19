#ifndef ToolCamera_h__
#define ToolCamera_h__


#include "Camera.h"

namespace Engine
{
	class CTransform;

}

class CToolCamera
	:public Engine::CCamera
{
private:
	explicit CToolCamera(LPDIRECT3DDEVICE9 pDevice);

public:
	virtual ~CToolCamera(void);

public:
	virtual Engine::OBJECT_RESULT Update(void);

private:
	HRESULT Initialize(void);

public:
	void SetCameraTarget(const Engine::CTransform* pTargetInfo);

public:
	static CToolCamera* Create(LPDIRECT3DDEVICE9 pDevice );

public:
	void KeyCheck(void);
	void TargetRenewal(void);
	void Rotate(const D3DXVECTOR3 vcDelta);
	D3DXVECTOR3 Getmouse(POINT pt);

private:
	void Release(void);

private:
	const Engine::CTransform*		m_pTargetInfo;

private:
	float		m_fTargetDistance;
	float		m_fAngle;
	float		m_fCamSpeed;

	Engine::CTransform*		m_pInfo;

	D3DXMATRIX		matView, matProj;

	D3DXVECTOR3  m_vEye;
	D3DXVECTOR3	 m_vAt;
	D3DXVECTOR3  m_vUp;
	D3DXVECTOR3  m_vLook;
	D3DXVECTOR3  m_vPos;
	D3DXVECTOR3  m_vDir;


	D3DXVECTOR3	m_vcCur;
	D3DXVECTOR3 m_vcOld;
	D3DXVECTOR3 m_vcEps;

	POINT       m_pt;


};
#endif // ToolCamera_h__