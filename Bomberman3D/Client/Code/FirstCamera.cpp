#include "stdafx.h"
#include "FirstCamera.h"

#include "Include.h"
#include "Transform.h"
#include "Export_Function.h"

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

	return Engine::OR_OK;
}

HRESULT CFirstCamera::Initialize(void)
{
	m_fAngleY = D3DXToRadian(0.f);
	
	SetProjectionMatrix(D3DXToRadian(45.f), float(WINCX) / WINCY, 0.1f, 200.f);

	m_vExMousePos = Engine::Get_MouseMgr()->InitMousePos();

	return S_OK;
}

void CFirstCamera::SetCameraTarget(const Engine::CTransform* pTargetInfo)
{
	m_pTargetInfo = pTargetInfo;
}

CFirstCamera* CFirstCamera::Create(LPDIRECT3DDEVICE9 pDevice , const Engine::CTransform* pTargetInfo)
{
	CFirstCamera*	pCamera = new CFirstCamera(pDevice);
	if(FAILED(pCamera->Initialize()))
		Engine::Safe_Delete(pCamera);

	pCamera->SetCameraTarget(pTargetInfo);
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

	m_vEye = m_pTargetInfo->m_vPos + m_pTargetInfo->m_vDir * 0.7f + D3DXVECTOR3(0.f, 1.25f, 0.f);
	m_vAt += m_pTargetInfo->m_vPos + m_pTargetInfo->m_vDir * 0.7f + D3DXVECTOR3(0.f, 1.25f, 0.f);

	SetViewSpaceMatrix(&m_vEye, &m_vAt, &m_vUp);
}

void CFirstCamera::Release(void)
{
}