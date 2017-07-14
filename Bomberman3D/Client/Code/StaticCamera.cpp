#include "stdafx.h"
#include "StaticCamera.h"

#include "Include.h"
#include "Transform.h"
#include "Export_Function.h"

CStaticCamera::CStaticCamera(LPDIRECT3DDEVICE9 pDevice)
: Engine::CCamera(pDevice)
, m_fTargetDistance(0.f)
, m_fAngle(0.f)
, m_fCamSpeed(0.f)
, m_pTargetInfo(NULL)
{
}

CStaticCamera::~CStaticCamera(void)
{
}

void CStaticCamera::Update(void)
{
	KeyCheck();
	TargetRenewal();

	Engine::Get_InfoSubject()->Notify(L"StaticCamera_Matrix");
}

HRESULT CStaticCamera::Initialize(void)
{
	m_fTargetDistance = 20.f;
	m_fAngle = D3DXToRadian(25.f);
	m_fCamSpeed = 10.f;

	SetProjectionMatrix(D3DXToRadian(45.f), float(WINCX) / WINCY, 1.f, 1500.f);

	return S_OK;
}

void CStaticCamera::SetCameraTarget(const Engine::CTransform* pTargetInfo)
{
	m_pTargetInfo = pTargetInfo;
}

CStaticCamera* CStaticCamera::Create(LPDIRECT3DDEVICE9 pDevice , const Engine::CTransform* pTargetInfo)
{
	CStaticCamera*	pCamera = new CStaticCamera(pDevice);
	if(FAILED(pCamera->Initialize()))
		Engine::Safe_Delete(pCamera);

	pCamera->SetCameraTarget(pTargetInfo);
	return pCamera;
}

void CStaticCamera::KeyCheck(void)
{
	float		fTime = Engine::Get_TimeMgr()->GetTime();

	if(GetAsyncKeyState(VK_UP))
		m_fAngle += D3DXToRadian(45.f) * fTime;

	if(GetAsyncKeyState(VK_DOWN))
		m_fAngle -= D3DXToRadian(45.f) * fTime;

	if(GetAsyncKeyState('O'))
		m_fTargetDistance += m_fCamSpeed * fTime;

	if(GetAsyncKeyState('P'))
		m_fTargetDistance -= m_fCamSpeed * fTime;
}

void CStaticCamera::TargetRenewal(void)
{
	m_vEye = m_pTargetInfo->m_vDir * -1 * m_fTargetDistance;

	D3DXVECTOR3		vRight;
	memcpy(&vRight, &m_pTargetInfo->m_matWorld.m[0][0], sizeof(D3DXVECTOR3));

	D3DXMATRIX		matRotAxis;
	D3DXMatrixRotationAxis(&matRotAxis, &vRight, m_fAngle);
	D3DXVec3TransformNormal(&m_vEye, &m_vEye, &matRotAxis);

	m_vAt = m_pTargetInfo->m_vPos;
	m_vEye += m_pTargetInfo->m_vPos;

	SetViewSpaceMatrix(&m_vEye, &m_vAt, &m_vUp);
}

void CStaticCamera::Release(void)
{
}

