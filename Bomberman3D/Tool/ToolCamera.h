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
	virtual void Update(void);

private:
	HRESULT Initialize(void);

public:
	void SetCameraTarget(const Engine::CTransform* pTargetInfo);

	void SetPtPos(POINT _pt)
	{
			m_pPT = _pt;
	}

public:
	static CToolCamera* Create(LPDIRECT3DDEVICE9 pDevice );

private:
	void KeyCheck(void);
	void TargetRenewal(void);

public:
	D3DXVECTOR3 Getmouse();
	void Rotate(const D3DXVECTOR3 vcDelta);

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
	POINT		 m_pPT;


	D3DXVECTOR3	m_vcCur;
	D3DXVECTOR3 m_vcOld;
	D3DXVECTOR3 m_vcEps;


};
#endif // ToolCamera_h__