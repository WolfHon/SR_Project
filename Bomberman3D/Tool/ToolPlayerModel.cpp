#include "stdafx.h"
#include "ToolPlayerModel.h"
#include "Animation.h"
#include "Texture.h"
#include "Include.h"
#include "Transform.h"
#include "Engine_Include.h"
#include "Export_Function.h"
#include "PlayerModel.h"
#include "MainFrm.h"
#include "ToolView.h"

CPlayerAnimation::CPlayerAnimation(LPDIRECT3DDEVICE9 pDevice)
:Engine::CGameObject(pDevice)
,m_pTexture(NULL)
,m_pPlayerModel(NULL)
,m_fAngle(180.f)
,m_fSpeed(0.f)
,m_pInfo(NULL)
{

}

CPlayerAnimation::~CPlayerAnimation(void)
{
	Release();
}

Engine::OBJECT_RESULT CPlayerAnimation::Update(void)
{
	D3DXMATRIX matRotY;

	D3DXMatrixRotationY(&matRotY, m_fAngle);
	D3DXVec3TransformNormal(&m_pInfo->m_vDir, &g_vLook, &m_pInfo->m_matWorld);

	m_pInfo->m_matWorld = matRotY;

	return Engine::CGameObject::Update();
}

void CPlayerAnimation::Render(void)
{
	m_pDevice->SetTransform(D3DTS_WORLD, &m_pInfo->m_matWorld);

	m_pPlayerModel->Render();

}

CPlayerAnimation* CPlayerAnimation::Create(LPDIRECT3DDEVICE9 pDevice)
{
	CPlayerAnimation*		pGameObject = new CPlayerAnimation(pDevice);
	if(FAILED(pGameObject->Initialize()))
		Safe_Delete(pGameObject);

	return pGameObject;

}

HRESULT CPlayerAnimation::Initialize(void)
{

	FAILED_CHECK(AddComponent());

	m_fSpeed = 10.f;

	m_pInfo->m_vScale = D3DXVECTOR3(1.f, 1.f, 1.f);

	m_pInfo->m_vPos = D3DXVECTOR3(0.f, 0.f, 0.f);

	m_fAngle = 0.f;

	return S_OK;

}

HRESULT CPlayerAnimation::AddComponent(void)
{
	Engine::CComponent*		pComponent = NULL;

	//Transform
	pComponent = m_pInfo = Engine::CTransform::Create(g_vLook);
	NULL_CHECK_RETURN(m_pInfo, E_FAIL);
	m_mapComponent.insert(MAPCOMPONENT::value_type(L"Transform", pComponent));

	////Player
	pComponent = Engine::Get_ResourceMgr()->CloneResource(Engine::RESOURCE_DYNAMIC, L"Model_Player");
	m_pPlayerModel = dynamic_cast<Engine::CPlayerModel*>(pComponent);
	NULL_CHECK_RETURN(m_pPlayerModel, E_FAIL);
	m_mapComponent.insert(MAPCOMPONENT::value_type(L"Model", pComponent));

	return S_OK;
}

void CPlayerAnimation::MoveCheck(void)
{
	m_pPlayerModel->SetAngle(m_pAnimation);
}

void CPlayerAnimation::Release()
{

}

void CPlayerAnimation::SetAnimation(vector<Engine::ANIFRAME> _Animation)
{
	m_pAnimation = _Animation;
	MoveCheck();
}

void CPlayerAnimation::SetFrame(Engine::ANIFRAME _AniFrame)
{
	m_pAniFrame = _AniFrame;
	m_pPlayerModel->SetFrame(m_pAniFrame);

}

