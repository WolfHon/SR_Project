#include "StdAfx.h"
#include "CameraControl.h"

#include "ActionCamera.h"
#include "FirstCamera.h"

#include "Transform.h"
#include "Export_Function.h"

CCameraControl::CCameraControl(LPDIRECT3DDEVICE9 pDevice)
: Engine::CGameObject(pDevice)
, m_eNowCam(CAM_END)
{
	ZeroMemory(m_pCamera, sizeof(void*) * ((int)CAM_END - 1));
}

CCameraControl::~CCameraControl(void)
{
	Release();
}

HRESULT CCameraControl::Initialize(const Engine::CTransform* pTargetInfo)
{
	ShowCursor(FALSE);

	m_pCamera[CAM_ACTION] = CActionCamera::Create(m_pDevice, pTargetInfo);
	NULL_CHECK_RETURN(m_pCamera[CAM_ACTION], E_FAIL);

	m_pCamera[CAM_FIRST] = CFirstCamera::Create(m_pDevice, pTargetInfo);
	NULL_CHECK_RETURN(m_pCamera[CAM_FIRST], E_FAIL);

	return S_OK;
}

void CCameraControl::Release(void)
{
	ShowCursor(TRUE);

	Engine::Safe_Delete(m_pCamera[CAM_ACTION]);
	Engine::Safe_Delete(m_pCamera[CAM_FIRST]);
}

Engine::OBJECT_RESULT CCameraControl::Update(void)
{
	return m_pCamera[m_eNowCam]->Update();
}

void CCameraControl::Render(void)
{
	m_pCamera[m_eNowCam]->Render();
}

CCameraControl* CCameraControl::Create(LPDIRECT3DDEVICE9 pDevice, const Engine::CTransform* pTargetInfo)
{
	CCameraControl*	pCamera = new CCameraControl(pDevice);

	if(FAILED(pCamera->Initialize(pTargetInfo)))
		Engine::Safe_Delete(pCamera);

	return pCamera;
}

void CCameraControl::SetCamera(CAMERATYPE NowCam)
{
	m_eNowCam = NowCam;
}

CCameraControl::CAMERATYPE CCameraControl::GetCamera()
{
	return m_eNowCam;
}