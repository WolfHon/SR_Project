#include "stdafx.h"
#include "Player.h"

#include "Texture.h"

#include "Include.h"
#include "Transform.h"
#include "Export_Function.h"
#include "Collision_OBB.h"
#include "PlayerModel.h"
#include "CameraControl.h"

#ifdef _DEBUG
#include "CubeColor.h"
#endif

CPlayer::CPlayer(LPDIRECT3DDEVICE9 pDevice)
: Engine::CGameObject(pDevice)
, m_pTexture(NULL)
, m_pPlayerModel(NULL)
, m_fSpeed(0.f)
, m_fAngle(0.f)
, m_pInfo(NULL)
, m_pCollisionOBB(NULL)
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

	m_pInfo->m_vScale = D3DXVECTOR3(0.5f, 0.5f, 0.5f);

#ifdef _DEBUG
	pVertex = new Engine::VTXCOL[8];	
	m_pCubeColor->GetVtxInfo(pVertex);

	D3DXVECTOR3 vMin, vMax;
	m_pCollisionOBB->GetColBox(&vMin, &vMax);

	pVertex[0].vPos = D3DXVECTOR3(vMin.x, vMax.y, vMin.z);
	pVertex[1].vPos = D3DXVECTOR3(vMax.x, vMax.y, vMin.z);
	pVertex[2].vPos = D3DXVECTOR3(vMax.x, vMin.y, vMin.z);
	pVertex[3].vPos = D3DXVECTOR3(vMin.x, vMin.y, vMin.z);

	pVertex[4].vPos = D3DXVECTOR3(vMin.x, vMax.y, vMax.z);
	pVertex[5].vPos = D3DXVECTOR3(vMax.x, vMax.y, vMax.z);
	pVertex[6].vPos = D3DXVECTOR3(vMax.x, vMin.y, vMax.z);
	pVertex[7].vPos = D3DXVECTOR3(vMin.x, vMin.y, vMax.z);	
#endif

	return S_OK;
}

Engine::OBJECT_RESULT CPlayer::Update(void)
{
	D3DXVec3TransformNormal(&m_pInfo->m_vDir, &g_vLook, &m_pInfo->m_matWorld);

	MoveCheck();

	return Engine::CGameObject::Update();	
}

void CPlayer::Render(void)
{
	m_pDevice->SetTransform(D3DTS_WORLD, &m_pInfo->m_matWorld);
	m_pPlayerModel->Render();

#ifdef _DEBUG
	m_pCubeColor->SetVtxInfo(pVertex);
	m_pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	m_pDevice->SetTransform(D3DTS_WORLD, &m_pInfo->m_matWorld);
	m_pCubeColor->Render();
	m_pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
#endif
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
#ifdef _DEBUG
	Safe_Delete_Array(pVertex);
#endif
}

HRESULT CPlayer::AddComponent(void)
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

	//OBBCollision_OBB
	pComponent = Engine::Get_CollisionMgr()->CloneCollision(Engine::COLLISON_OBB);
	m_pCollisionOBB = static_cast<Engine::CCollision_OBB*>(pComponent);
	NULL_CHECK_RETURN(m_pCollisionOBB, E_FAIL);
	m_mapComponent.insert(MAPCOMPONENT::value_type(L"Collision_OBB", pComponent));
	m_pCollisionOBB->SetColInfo(&m_pInfo->m_matWorld, &D3DXVECTOR3(-2.f, -4.5f, -1.f), &D3DXVECTOR3(2.f, 3.5f, 1.f));

#ifdef _DEBUG
	pComponent = Engine::Get_ResourceMgr()->CloneResource(Engine::RESOURCE_DYNAMIC, L"Buffer_CubeColor");
	m_pCubeColor = dynamic_cast<Engine::CCubeColor*>(pComponent);
	NULL_CHECK_RETURN(m_pCubeColor, E_FAIL);
	m_mapComponent.insert(MAPCOMPONENT::value_type(L"Collision_Box", pComponent));
#endif

	return S_OK;
}

void CPlayer::MoveCheck(void)
{
	float		fTime = Engine::Get_TimeMgr()->GetTime();
	DWORD		KeyState = Engine::Get_KeyMgr()->GetKey();

	m_pInfo->m_vPos.y = 2.25f;

	CGameObject* pObject = Engine::Get_Management()->GetObject(Engine::LAYER_UI, L"CameraControl");
	NULL_CHECK(pObject);
	CCameraControl* pControl = dynamic_cast<CCameraControl*>(pObject);

	if(!(~KeyState & Engine::KEY_SPACE_PRESS) && pControl->GetCamera() != CCameraControl::CAM_ACTION)
	{
		pControl->SetCamera(CCameraControl::CAM_ACTION);
	}
	else if(pControl->GetCamera() == CCameraControl::CAM_FIRST)
	{
		float fExAngle = m_fAngle;
		D3DXVECTOR3 vExPos = m_pInfo->m_vPos;
		BOOL bChange = FALSE;

		D3DXVECTOR3 vMousePos = Engine::Get_MouseMgr()->GetMousePos();
		D3DXVECTOR3 vMouseMove = m_vExMousePos - vMousePos;

		m_vExMousePos = Engine::Get_MouseMgr()->InitMousePos();

		m_fAngle -= vMouseMove.x * D3DXToRadian(180.f) * fTime;		

		if(m_fAngle >= D3DXToRadian(360.f))
			m_fAngle -= D3DXToRadian(360.f);
		else if(m_fAngle <= D3DXToRadian(-360.f))
			m_fAngle += D3DXToRadian(360.f);

		m_pInfo->m_fAngle[Engine::ANGLE_Y] = m_fAngle;

		if(fExAngle != m_fAngle)
			bChange = TRUE;

		if(!(~KeyState & Engine::KEY_W_PRESS))
		{
			bChange = TRUE;
			m_pInfo->m_vPos += m_pInfo->m_vDir * m_fSpeed * Engine::Get_TimeMgr()->GetTime();
		}

		if(!(~KeyState & Engine::KEY_S_PRESS))
		{
			bChange = TRUE;
			m_pInfo->m_vPos -= m_pInfo->m_vDir * m_fSpeed * Engine::Get_TimeMgr()->GetTime();
		}

		D3DXVECTOR3		vRight;
		memcpy(&vRight, &m_pInfo->m_matWorld.m[0][0], sizeof(D3DXVECTOR3));
		D3DXVec3Normalize(&vRight, &vRight);

		if(!(~KeyState & Engine::KEY_A_PRESS))
		{
			bChange = TRUE;
			m_pInfo->m_vPos -= vRight * m_fSpeed * Engine::Get_TimeMgr()->GetTime();
		}

		if(!(~KeyState & Engine::KEY_D_PRESS))
		{
			bChange = TRUE;
			m_pInfo->m_vPos += vRight * m_fSpeed * Engine::Get_TimeMgr()->GetTime();
		}

		if(bChange == TRUE)
		{
			m_pInfo->Update();

			if(CheckCollision() == TRUE)
			{
				m_pInfo->m_fAngle[Engine::ANGLE_Y] = fExAngle;
				m_fAngle = fExAngle;
				m_pInfo->m_vPos = vExPos;
			}
		}
	}
}

BOOL CPlayer::CheckCollision(void)
{
	Engine::OBJLIST* listObj = Engine::Get_Management()->GetObjectList(Engine::LAYER_GAMELOGIC, L"UnBroken_Box");

	return m_pCollisionOBB->CheckCollision(m_pInfo->m_vPos, listObj);
}
