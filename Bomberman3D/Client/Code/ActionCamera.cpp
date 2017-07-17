#include "stdafx.h"
#include "ActionCamera.h"

#include "Include.h"
#include "Transform.h"
#include "Export_Function.h"
#include "CameraControl.h"

CActionCamera::CActionCamera(LPDIRECT3DDEVICE9 pDevice)
: Engine::CCamera(pDevice)
, m_fTargetDistance(0.f)
, m_fAngleX(0.f)
, m_fAngleY(0.f)
, m_fCamSpeed(0.f)
, m_pTargetInfo(NULL)
{
}

CActionCamera::~CActionCamera(void)
{
}

void CActionCamera::Update(void)
{
	ViewCheck();
	TargetRenewal();
}

HRESULT CActionCamera::Initialize(void)
{
	m_fMaxDistance = 60.f;
	m_fTargetDistance = 0.f;
	m_fAngleX = D3DXToRadian(0.f);
	m_fAngleY = D3DXToRadian(45.f);
	m_fCamSpeed = 80.f;

	m_vExMousePos = Engine::Get_MouseMgr()->InitMousePos();

	SetProjectionMatrix(D3DXToRadian(45.f), float(WINCX) / WINCY, 1.f, 1000.f);	

	return S_OK;
}

void CActionCamera::SetCameraTarget(const Engine::CTransform* pTargetInfo)
{
	m_pTargetInfo = pTargetInfo;
}

CActionCamera* CActionCamera::Create(LPDIRECT3DDEVICE9 pDevice , const Engine::CTransform* pTargetInfo)
{
	CActionCamera*	pCamera = new CActionCamera(pDevice);
	if(FAILED(pCamera->Initialize()))
		Engine::Safe_Delete(pCamera);

	pCamera->SetCameraTarget(pTargetInfo);
	return pCamera;
}

void CActionCamera::ViewCheck(void)
{
	float		fTime = Engine::Get_TimeMgr()->GetTime();

	D3DXVECTOR3 vMousePos = Engine::Get_MouseMgr()->GetMousePos();
	D3DXVECTOR3 vMouseMove = m_vExMousePos - vMousePos;

	m_vExMousePos = Engine::Get_MouseMgr()->InitMousePos();

	m_fAngleX += vMouseMove.x * D3DXToRadian(180.f) * fTime;

	if(m_fAngleX >= D3DXToRadian(360.f))
		m_fAngleX -= D3DXToRadian(360.f);
	else if(m_fAngleX <= D3DXToRadian(-360.f))
		m_fAngleX += D3DXToRadian(360.f);

	if(GetAsyncKeyState(VK_SPACE))
	{
		if(m_fTargetDistance >= m_fMaxDistance)
			m_fTargetDistance = m_fMaxDistance;
		else
			m_fTargetDistance += m_fCamSpeed * fTime;
	}
	else
	{
		if(m_fTargetDistance <= 0.f)
		{
			m_fTargetDistance = 0.f;	
			m_fAngleX = D3DXToRadian(0.f);

			CGameObject* pObject = Engine::Get_Management()->GetObject(Engine::LAYER_UI, L"CameraControl");
			NULL_CHECK(pObject);
			dynamic_cast<CCameraControl*>(pObject)->SetCamera(CCameraControl::CAM_FIRST);		
		}
		else
			m_fTargetDistance -= m_fCamSpeed * fTime;
	}
}

void CActionCamera::TargetRenewal(void)
{
	m_vEye = m_pTargetInfo->m_vDir * -1 * m_fTargetDistance;

	D3DXVECTOR3		vUp;
	memcpy(&vUp, &m_pTargetInfo->m_matWorld.m[1][0], sizeof(D3DXVECTOR3));

	D3DXVECTOR3		vRight;
	memcpy(&vRight, &m_pTargetInfo->m_matWorld.m[0][0], sizeof(D3DXVECTOR3));
	
	D3DXMATRIX		matRotAxisX, matRotAxisY;
	D3DXMatrixRotationAxis(&matRotAxisX, &vUp, m_fAngleX);
	D3DXMatrixRotationAxis(&matRotAxisY, &vRight, m_fAngleY);

	D3DXVec3TransformNormal(&m_vEye, &m_vEye, &matRotAxisY);
	D3DXVec3TransformNormal(&m_vEye, &m_vEye, &matRotAxisX);

	m_vAt = m_pTargetInfo->m_vPos;
	m_vEye += m_pTargetInfo->m_vPos;

	SetViewSpaceMatrix(&m_vEye, &m_vAt, &m_vUp);
}

void CActionCamera::Release(void)
{
}

