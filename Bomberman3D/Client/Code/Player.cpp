#include "stdafx.h"
#include "Player.h"

#include "Texture.h"
#include "VIBuffer.h"

#include "Include.h"
#include "Transform.h"
#include "Export_Function.h"
#include "CameraControl.h"
#include "Scene.h"

CPlayer::CPlayer(LPDIRECT3DDEVICE9 pDevice)
: Engine::CGameObject(pDevice)
, m_pTexture(NULL)
, m_pBuffer(NULL)
, m_fSpeed(0.f)
, m_fAngle(0.f)
, m_pInfo(NULL)
{

}

CPlayer::~CPlayer(void)
{
	Release();
}

HRESULT CPlayer::Initialize(void)
{
	FAILED_CHECK(AddComponent());

	m_vExMousePos = Engine::Get_MouseMgr()->InitMousePos();

	m_fSpeed = 10.f;

	return S_OK;
}

void CPlayer::Update(void)
{
	Engine::CGameObject::Update();

	D3DXVec3TransformNormal(&m_pInfo->m_vDir, &g_vLook, &m_pInfo->m_matWorld);

	MoveCheck();
}

void CPlayer::Render(void)
{
	m_pDevice->SetTransform(D3DTS_WORLD, &m_pInfo->m_matWorld);

	m_pTexture->Render(0, 0);
	m_pBuffer->Render();
}

CPlayer* CPlayer::Create(LPDIRECT3DDEVICE9 pDevice)
{
	CPlayer*	pGameObject = new CPlayer(pDevice);
	if(FAILED(pGameObject->Initialize()))
		Safe_Delete(pGameObject);

	return pGameObject;
}

void CPlayer::Release(void)
{	
}

HRESULT CPlayer::AddComponent(void)
{
	Engine::CComponent*		pComponent = NULL;

	//Transform
	pComponent = m_pInfo = Engine::CTransform::Create(g_vLook);
	NULL_CHECK_RETURN(m_pInfo, E_FAIL);
	m_mapComponent.insert(MAPCOMPONENT::value_type(L"Transform", pComponent));

	//Texture
	pComponent = Engine::Get_ResourceMgr()->CloneResource(Engine::RESOURCE_DYNAMIC, L"Texture_Player1Head");
	m_pTexture = dynamic_cast<Engine::CTexture*>(pComponent);
	NULL_CHECK_RETURN(m_pTexture, E_FAIL);
	m_mapComponent.insert(MAPCOMPONENT::value_type(L"Texture", pComponent));

	//Buffer
	pComponent = Engine::Get_ResourceMgr()->CloneResource(Engine::RESOURCE_DYNAMIC, L"Buffer_CubeTex");
	m_pBuffer = dynamic_cast<Engine::CVIBuffer*>(pComponent);
	NULL_CHECK_RETURN(m_pBuffer, E_FAIL);
	m_mapComponent.insert(MAPCOMPONENT::value_type(L"Buffer", pComponent));

	return S_OK;
}

void CPlayer::MoveCheck(void)
{
	float		fTime = Engine::Get_TimeMgr()->GetTime();

	CGameObject* pObject = Engine::Get_Management()->GetScene()->GetObject(Engine::CScene::LAYER_UI, L"CameraControl");
	NULL_CHECK(pObject);
	CCameraControl* pControl = dynamic_cast<CCameraControl*>(pObject);

	if(GetAsyncKeyState(VK_SPACE) && pControl->GetCamera() != CCameraControl::CAM_ACTION)
	{
		pControl->SetCamera(CCameraControl::CAM_ACTION);
	}
	else if(pControl->GetCamera() == CCameraControl::CAM_FIRST)
	{
		D3DXVECTOR3 vMousePos = Engine::Get_MouseMgr()->GetMousePos();
		D3DXVECTOR3 vMouseMove = m_vExMousePos - vMousePos;

		m_vExMousePos = Engine::Get_MouseMgr()->InitMousePos();

		m_fAngle -= vMouseMove.x * D3DXToRadian(180.f) * fTime;

		if(m_fAngle >= D3DXToRadian(360.f))
			m_fAngle -= D3DXToRadian(360.f);
		else if(m_fAngle <= D3DXToRadian(-360.f))
			m_fAngle += D3DXToRadian(360.f);

		m_pInfo->m_fAngle[Engine::ANGLE_Y] = m_fAngle;

		if(GetAsyncKeyState('W'))
			m_pInfo->m_vPos += m_pInfo->m_vDir * m_fSpeed * Engine::Get_TimeMgr()->GetTime();

		if(GetAsyncKeyState('S'))
			m_pInfo->m_vPos -= m_pInfo->m_vDir * m_fSpeed * Engine::Get_TimeMgr()->GetTime();
	}
}
