#include "stdafx.h"
#include "FirstCamera.h"

#include "Include.h"
#include "Transform.h"
#include "Export_Function.h"
#include "CameraControl.h"
#include "Player.h"

CFirstCamera::CFirstCamera(LPDIRECT3DDEVICE9 pDevice)
: Engine::CCamera(pDevice)
, m_fAngleY(0.f)
, m_pTargetInfo(NULL)
{
}

CFirstCamera::~CFirstCamera(void)
{
	
}

Engine::OBJECT_RESULT CFirstCamera::Update(void)
{
	ViewCheck();
	TargetRenewal();
	KeyCheck();
	SetProjectionMatrix(D3DXToRadian(60.f), float(WINCX) / WINCY, 0.1f, 500.f);

	
	return Engine::OR_OK;
}

HRESULT CFirstCamera::Initialize(void)
{
	m_fAngleY = D3DXToRadian(0.f);

	m_fTime = 0.f;	
	
	m_vExMousePos = Engine::Get_MouseMgr()->InitMousePos();

	return S_OK;
}

void CFirstCamera::SetCameraTarget(Engine::CGameObject* pTarget, const Engine::CTransform* pTargetInfo)
{
	m_pTarget = pTarget;
	m_pTargetInfo = pTargetInfo;
}

CFirstCamera* CFirstCamera::Create(LPDIRECT3DDEVICE9 pDevice , Engine::CGameObject* pTarget, const Engine::CTransform* pTargetInfo)
{
	CFirstCamera*	pCamera = new CFirstCamera(pDevice);
	if(FAILED(pCamera->Initialize()))
		Engine::Safe_Delete(pCamera);

	pCamera->SetCameraTarget(pTarget, pTargetInfo);
	return pCamera;
}

void CFirstCamera::ViewCheck(void)
{
	float		fTime = Engine::Get_TimeMgr()->GetTime();

	D3DXVECTOR3 vMousePos = Engine::Get_MouseMgr()->GetMousePos();
	D3DXVECTOR3 vMouseMove = m_vExMousePos - vMousePos;

	m_vExMousePos = Engine::Get_MouseMgr()->InitMousePos();

	m_fAngleY -= vMouseMove.y * D3DXToRadian(90.f) * fTime;

	if(m_fAngleY >= D3DXToRadian(80.f))
		m_fAngleY = D3DXToRadian(80.f);

	if(m_fAngleY <= D3DXToRadian(-80.f))
		m_fAngleY = D3DXToRadian(-80.f);

}

void CFirstCamera::TargetRenewal(void)
{	
	m_vAt = m_pTargetInfo->m_vDir;

	D3DXVECTOR3		vRight;
	memcpy(&vRight, &m_pTargetInfo->m_matWorld.m[0][0], sizeof(D3DXVECTOR3));	
	
	D3DXMATRIX		matRotAxisY;
	D3DXMatrixRotationAxis(&matRotAxisY, &vRight, m_fAngleY);
	D3DXVec3TransformNormal(&m_vAt, &m_vAt, &matRotAxisY);

	CPlayer* pPlayer = dynamic_cast<CPlayer*>(m_pTarget);
	float	fVibration = pPlayer->GetVibrationPower();
	bool	bVibration = pPlayer->GetVibration();

	D3DXVECTOR3 MovePos = m_pTargetInfo->m_vPos;

	if(bVibration == TRUE)
	{
		if(m_fTime < 2.f)
		{
			m_fTime += Engine::Get_TimeMgr()->GetTime();

			MovePos += vRight * sin(m_fTime*fVibration * 9) * powf(0.1f, m_fTime) * fVibration * 0.05f;
			MovePos.y += sin(m_fTime*fVibration * 5) * powf(0.1f, m_fTime) * fVibration * 0.03f;
		}
		else
		{
			pPlayer->SetVibration(FALSE);
		}
	}
	else
	{
		m_fTime = 0.f;
	}

	m_vEye = MovePos + m_pTargetInfo->m_vDir * 0.7f + D3DXVECTOR3(0.f, 1.25f, 0.f);
	m_vAt += MovePos + m_pTargetInfo->m_vDir * 0.7f + D3DXVECTOR3(0.f, 1.25f, 0.f);

	SetViewSpaceMatrix(&m_vEye, &m_vAt, &m_vUp);
}

void CFirstCamera::Release(void)
{
}

void CFirstCamera::KeyCheck(void)
{
	DWORD		KeyState = Engine::Get_KeyMgr()->GetKey();

	if(!(~KeyState & Engine::KEY_SPACE_PRESS))
	{
		CGameObject* pObject = Engine::Get_Management()->GetObject(Engine::LAYER_UI, L"CameraControl");
		NULL_CHECK(pObject);
		dynamic_cast<CCameraControl*>(pObject)->SetCamera(CCameraControl::CAM_ACTION);
	}
}
