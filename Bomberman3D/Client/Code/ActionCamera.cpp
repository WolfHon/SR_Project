#include "stdafx.h"
#include "ActionCamera.h"

#include "Include.h"
#include "Transform.h"
#include "Export_Function.h"
#include "CameraControl.h"
#include "Scene.h"

CActionCamera::CActionCamera(LPDIRECT3DDEVICE9 pDevice)
: Engine::CCamera(pDevice)
, m_fTargetDistance(0.f)
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
	DistCheck();
	TargetRenewal();
}

HRESULT CActionCamera::Initialize(void)
{
	m_fMaxDistance = 50.f;
	m_fTargetDistance = 0.f;
	m_fAngleY = D3DXToRadian(45.f);
	m_fCamSpeed = 20.f;

	SetProjectionMatrix(D3DXToRadian(45.f), float(WINCX) / WINCY, 1.f, 1500.f);

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

void CActionCamera::DistCheck(void)
{
	float		fTime = Engine::Get_TimeMgr()->GetTime();

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

			CGameObject* pObject = Engine::Get_Management()->GetScene()->GetObject(Engine::CScene::LAYER_UI, L"CameraControl");
			NULL_CHECK(pObject);
			dynamic_cast<CCameraControl*>(pObject)->SetCamera(CCameraControl::CAM_FIRST);		
		}
		else
			m_fTargetDistance -= m_fCamSpeed * fTime;
	}
}

void CActionCamera::TargetRenewal(void)
{
	m_vEye = g_vLook * -1 * m_fTargetDistance;

	D3DXVECTOR3		vRight = D3DXVECTOR3(1.f, 0.f, 0.f);
	
	D3DXMATRIX		matRotAxisY;
	D3DXMatrixRotationAxis(&matRotAxisY, &vRight, m_fAngleY);
	D3DXVec3TransformNormal(&m_vEye, &m_vEye, &matRotAxisY);

	m_vAt = m_pTargetInfo->m_vPos;
	m_vEye += m_pTargetInfo->m_vPos;

	SetViewSpaceMatrix(&m_vEye, &m_vAt, &m_vUp);
}

void CActionCamera::Release(void)
{
}

