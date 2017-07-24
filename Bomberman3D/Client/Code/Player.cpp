#include "stdafx.h"
#include "Player.h"

#include "Texture.h"

#include "Include.h"
#include "Transform.h"
#include "Export_Function.h"
#include "Collision_OBB.h"
#include "PlayerModel.h"
#include "CameraControl.h"
#include "CameraObserver.h"

#include "TerrainInfo.h"

#include "Bomb.h"

CPlayer::CPlayer(LPDIRECT3DDEVICE9 pDevice)
: Engine::CGameObject(pDevice)
, m_pTexture(NULL)
, m_pPlayerModel(NULL)
, m_fSpeed(0.f)
, m_fAngle(0.f)
, m_pInfo(NULL)
, m_iAddBomb(0)
, m_iPower(0)
, m_fPlayerSpeed(0.f)
, m_pCollisionOBB(NULL)
{
}

CPlayer::~CPlayer(void)
{
	Release();
}

HRESULT CPlayer::Initialize(D3DXVECTOR3 vPos)
{
	FAILED_CHECK(AddComponent());

	m_pCamObserver = CCameraObserver::Create();
	Engine::Get_InfoSubject()->Subscribe(m_pCamObserver);

	m_vExMousePos = Engine::Get_MouseMgr()->InitMousePos();

	m_fSpeed = 10.f;

	m_fPlayerSpeed = 1.f;
	m_iAddBomb = 1;
	m_iPower = 1;

	m_pInfo->m_vScale = D3DXVECTOR3(WOLRD_SCALE/6.f, WOLRD_SCALE/6.f, WOLRD_SCALE/6.f);

	m_pInfo->m_vPos = vPos * WOLRD_SCALE;
	m_pInfo->m_vPos.y = 0.26f; //##TEMP 지형 높이 충돌 만들고 삭제
	m_pInfo->Update();

	return S_OK;
}

Engine::OBJECT_RESULT CPlayer::Update(void)
{
	D3DXVec3TransformNormal(&m_pInfo->m_vDir, &g_vLook, &m_pInfo->m_matWorld);

	CCameraControl::CAMERATYPE eCamType = m_pCamObserver->GetCamType();

	if(eCamType == CCameraControl::CAM_FIRST)
	{
		MoveCheck();
		AttackCheck();
	}

	return Engine::CGameObject::Update();	
}

void CPlayer::Render(void)
{
 	m_pDevice->SetTransform(D3DTS_WORLD, &m_pInfo->m_matWorld);
	m_pPlayerModel->Render();
	m_pCollisionOBB->Render(D3DCOLOR_ARGB(255, 255, 255, 255));
}

CPlayer* CPlayer::Create(LPDIRECT3DDEVICE9 pDevice, D3DXVECTOR3 vPos)
{
	CPlayer*	pGameObject = new CPlayer(pDevice);
	if(FAILED(pGameObject->Initialize(vPos)))
		Safe_Delete(pGameObject);

	return pGameObject;
}

void CPlayer::Release(void)
{	
	Engine::Get_InfoSubject()->UnSubscribe(m_pCamObserver);
	Safe_Delete(m_pCamObserver);
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
	pComponent = m_pCollisionOBB = CCollision_OBB::Create(m_pDevice);
	NULL_CHECK_RETURN(m_pCollisionOBB, E_FAIL);
	m_pCollisionOBB->SetColInfo(&m_pInfo->m_matWorld, &D3DXVECTOR3(-2.f, -4.5f, -1.f), &D3DXVECTOR3(2.f, 3.5f, 1.f));
	m_mapComponent.insert(MAPCOMPONENT::value_type(L"Collision_OBB", pComponent));
	
	return S_OK;
}

void CPlayer::MoveCheck(void)
{
	float		fTime = Engine::Get_TimeMgr()->GetTime();
	DWORD		KeyState = Engine::Get_KeyMgr()->GetKey();

	float fExAngle = m_fAngle;
	D3DXVECTOR3 vExPos = m_pInfo->m_vPos;
	BOOL bChange = FALSE;

	D3DXVECTOR3 vMousePos = Engine::Get_MouseMgr()->GetMousePos();
	D3DXVECTOR3 vMouseMove = m_vExMousePos - vMousePos;

	m_vExMousePos = Engine::Get_MouseMgr()->InitMousePos();

	m_fAngle -= vMouseMove.x * D3DXToRadian(200.f) * fTime;		

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
		m_pInfo->m_vPos += m_pInfo->m_vDir * m_fSpeed * Engine::Get_TimeMgr()->GetTime() * m_fPlayerSpeed;
	}

	if(!(~KeyState & Engine::KEY_S_PRESS))
	{
		bChange = TRUE;
		m_pInfo->m_vPos -= m_pInfo->m_vDir * m_fSpeed * Engine::Get_TimeMgr()->GetTime() * m_fPlayerSpeed * 0.5f;
	}

	D3DXVECTOR3		vRight;
	memcpy(&vRight, &m_pInfo->m_matWorld.m[0][0], sizeof(D3DXVECTOR3));
	D3DXVec3Normalize(&vRight, &vRight);

	if(!(~KeyState & Engine::KEY_A_PRESS))
	{
		bChange = TRUE;
		m_pInfo->m_vPos -= vRight * m_fSpeed * Engine::Get_TimeMgr()->GetTime() * m_fPlayerSpeed;
	}

	if(!(~KeyState & Engine::KEY_D_PRESS))
	{
		bChange = TRUE;
		m_pInfo->m_vPos += vRight * m_fSpeed * Engine::Get_TimeMgr()->GetTime() * m_fPlayerSpeed;
	}

	if(bChange == TRUE)
	{
		m_pInfo->Update();

		if( CTerrainInfo::GetInstance()->CheckCollision(m_pCollisionOBB, m_pInfo->m_vPos) != NULL ||
			m_pCollisionOBB->CheckCollision(Engine::LAYER_GAMELOGIC, L"Bomb", m_pInfo->m_vPos) != NULL)
		{
			m_pInfo->m_fAngle[Engine::ANGLE_Y] = fExAngle;
			m_fAngle = fExAngle;
			m_pInfo->m_vPos = vExPos;
		}
	}	
}

void CPlayer::AttackCheck(void)
{
	DWORD    MouseState = Engine::Get_MouseMgr()->GetMouseKey();

	if(!(~MouseState & Engine::MOUSE_LBUTTON_CLICK))
	{
		float DirX = fabs(m_pInfo->m_vDir.x) < fabs(m_pInfo->m_vDir.z) ? 0 : (m_pInfo->m_vDir.x < 0 ? -1.f : 1.f);
		float DirZ = fabs(m_pInfo->m_vDir.x) > fabs(m_pInfo->m_vDir.z) ? 0 : (m_pInfo->m_vDir.z < 0 ? -1.f : 1.f);
		
		if(fabs(m_pInfo->m_vDir.x) > 0.25f && fabs(m_pInfo->m_vDir.z) > 0.25f)
			return;

		float fX = int((m_pInfo->m_vPos.x + (DirX  * WOLRD_SCALE * 1.5f) + (WOLRD_SCALE))/ (WOLRD_SCALE * 2.f)) * (WOLRD_SCALE * 2.f);
		float fZ = int((m_pInfo->m_vPos.z + (DirZ * WOLRD_SCALE * 1.5f) + (WOLRD_SCALE))/ (WOLRD_SCALE * 2.f)) * (WOLRD_SCALE * 2.f);
		
		D3DXVECTOR3 vBombPos = D3DXVECTOR3(fX, m_pInfo->m_vPos.y, fZ);	

 		Engine::CGameObject* pGameObject = NULL;

		pGameObject = CBomb::Create(m_pDevice, vBombPos, m_iPower);

		if(pGameObject != NULL)
			Engine::Get_Management()->AddObject(Engine::LAYER_GAMELOGIC, L"Bomb", pGameObject);
	}		
}
