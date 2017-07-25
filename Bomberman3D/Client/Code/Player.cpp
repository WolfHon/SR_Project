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
#include "Gravity.h"

#include "TerrainInfo.h"
#include "Block.h"

#include "Bomb.h"
#include "SoundMgr.h"

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
, m_pCollSlopeCheck(NULL)
, m_iState(Engine::STATE_END)
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

	m_fPress = 10.f;
	m_fPressValue = 1.f;

	
	m_bVibration = FALSE;
	m_fVibrationPower = 0.f;

	m_pInfo->m_vScale = D3DXVECTOR3(WORLD_SCALE/6.f, WORLD_SCALE/6.f, WORLD_SCALE/6.f);

	m_pInfo->m_vPos = vPos * WORLD_SCALE;	
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
	m_pCollSlopeCheck->Render(D3DCOLOR_ARGB(255, 255, 255, 0));
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

	pComponent = m_pCollSlopeCheck = CCollision_OBB::Create(m_pDevice);
	NULL_CHECK_RETURN(m_pCollSlopeCheck, E_FAIL);
	m_pCollSlopeCheck->SetColInfo(&m_pInfo->m_matWorld, &D3DXVECTOR3(-2.f, -2.f, -1.f), &D3DXVECTOR3(2.f, 3.5f, 1.f));
	m_mapComponent.insert(MAPCOMPONENT::value_type(L"Collision_Slope", pComponent));	

	CGravity* pGravity;
	pComponent = pGravity = CGravity::Create();
	NULL_CHECK_RETURN(pGravity, E_FAIL);
	D3DXVECTOR3 vPoint[4];
	vPoint[0] = D3DXVECTOR3(-2.f, 0.f, -1.f);
	vPoint[1] = D3DXVECTOR3(-2.f, 0.f, 1.f);
	vPoint[2] = D3DXVECTOR3(2.f, 0.f, -1.f);
	vPoint[3] = D3DXVECTOR3(2.f, 0.f, 1.f);
	pGravity->SetInfo(vPoint, &m_pInfo->m_vPos, &m_pInfo->m_matWorld, m_pCollisionOBB->GetMin()->y * - 1.f);
	m_mapComponent.insert(MAPCOMPONENT::value_type(L"Gravity", pComponent));	
	
	LoadData();

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
		SetState(Engine::STATE_RUN);
	}

	if(!(~KeyState & Engine::KEY_S_PRESS))
	{
		bChange = TRUE;
		m_pInfo->m_vPos -= m_pInfo->m_vDir * m_fSpeed * Engine::Get_TimeMgr()->GetTime() * m_fPlayerSpeed * 0.5f;
		SetState(Engine::STATE_RUN);
	}

	D3DXVECTOR3		vRight;
	memcpy(&vRight, &m_pInfo->m_matWorld.m[0][0], sizeof(D3DXVECTOR3));
	D3DXVec3Normalize(&vRight, &vRight);

	if(!(~KeyState & Engine::KEY_A_PRESS))
	{
		bChange = TRUE;
		m_pInfo->m_vPos -= vRight * m_fSpeed * Engine::Get_TimeMgr()->GetTime() * m_fPlayerSpeed;
		SetState(Engine::STATE_RUN);
	}

	if(!(~KeyState & Engine::KEY_D_PRESS))
	{
		bChange = TRUE;
		m_pInfo->m_vPos += vRight * m_fSpeed * Engine::Get_TimeMgr()->GetTime() * m_fPlayerSpeed;
		SetState(Engine::STATE_RUN);
	}

	if(bChange == FALSE)
			SetState(Engine::STATE_STAND);
	if(bChange == TRUE)
	{
		m_pInfo->Update();

		bool TerrainCheck = FALSE;
		CBlock* pBlock = CTerrainInfo::GetInstance()->CheckCollision(m_pCollisionOBB, m_pInfo->m_vPos);
		if(pBlock != NULL)
		{
			Engine::TILESHAPE eShpae = pBlock->GetTileShpae();
			if(eShpae == Engine::TILE_CUBE)
			{
				TerrainCheck = TRUE;
			}
			else if(eShpae == Engine::TILE_SLOPE)
			{
				if(CTerrainInfo::GetInstance()->CheckCollision(m_pCollSlopeCheck, m_pInfo->m_vPos) != NULL)
				{
					TerrainCheck = TRUE;
				}
			}
		}

		if(TerrainCheck == TRUE ||
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

	if(!(~MouseState & Engine::MOUSE_LBUTTON_PRESS))
	{
		m_fPress += m_fPressValue * 20.f * Engine::Get_TimeMgr()->GetTime();
		if(m_fPress > 50.f)
		{
			m_fPress = 50.f;
			m_fPressValue = -1.f;
		}
		if(m_fPress < 10.f)
		{
			m_fPress = 10.f;
			m_fPressValue = 1.f;
		}

		SetState(Engine::STATE_TROWSTAND);
	}

	if(!(~MouseState & Engine::MOUSE_LBUTTON_CLICK))
	{		
		int iCount = 0;

		Engine::OBJLIST* listObj = Engine::Get_Management()->GetObjectList(Engine::LAYER_GAMELOGIC, L"Bomb");

		if(listObj != NULL)
		{
			Engine::OBJLIST::iterator iterBegin = listObj->begin();
			Engine::OBJLIST::iterator iterEnd = listObj->end();

			for (; iterBegin != iterEnd; ++iterBegin)
			{
				if(dynamic_cast<CBomb*>((*iterBegin))->GetOwn() == this)
				{
					++iCount;
				}
			}
		}

		if(m_iAddBomb - iCount == 0)
		{
			m_fPress = 10.f;
			m_fPressValue = 1.f;
			return;
		}


		SetState(Engine::STATE_TROW);

		D3DXVECTOR3 vBombPos = D3DXVECTOR3(m_pInfo->m_vPos.x, m_pInfo->m_vPos.y + 2.6f, m_pInfo->m_vPos.z);	

 		Engine::CGameObject* pGameObject = NULL;

		pGameObject = CBomb::Create(m_pDevice, vBombPos, m_iPower, m_fPress, this);

		if(pGameObject != NULL)
			Engine::Get_Management()->AddObject(Engine::LAYER_GAMELOGIC, L"Bomb", pGameObject);

		m_fPress = 10.f;
		m_fPressValue = 1.f;
	}		
}

D3DXVECTOR3 CPlayer::GetPos( void )
{
	return m_pInfo->m_vPos;
}

void CPlayer::LoadData(void)
{
	DWORD dwByte = 0;

	HANDLE hFile = CreateFile(L"../../Data/Run.dat", GENERIC_READ, 0, 0, OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL, NULL);

	m_vecRunAni.clear();

	while(true)
	{
		Engine::ANIFRAME pFrameData;

		ReadFile(hFile, &pFrameData, sizeof(Engine::ANIFRAME), &dwByte, NULL);

		if(dwByte == 0)
			break;

		m_vecRunAni.push_back(pFrameData);
	}
	CloseHandle(hFile);


	DWORD dwByte1 = 0;

	HANDLE hFile1 = CreateFile(L"../../Data/Trow.dat", GENERIC_READ, 0, 0, OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL, NULL);

	m_vecThrowAni.clear();

	while(true)
	{
		Engine::ANIFRAME pFrameData;

		ReadFile(hFile1, &pFrameData, sizeof(Engine::ANIFRAME), &dwByte1, NULL);

		if(dwByte1 == 0)
			break;

		m_vecThrowAni.push_back(pFrameData);
	}

	CloseHandle(hFile1);



	DWORD dwByte2 = 0;

	HANDLE hFile2 = CreateFile(L"../../Data/Dead.dat", GENERIC_READ, 0, 0, OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL, NULL);

	m_vecDeadAni.clear();

	while(true)
	{
		Engine::ANIFRAME pFrameData;

		ReadFile(hFile2, &pFrameData, sizeof(Engine::ANIFRAME), &dwByte2, NULL);

		if(dwByte2 == 0)
			break;

		m_vecDeadAni.push_back(pFrameData);
	}

	CloseHandle(hFile2);

	DWORD dwByte3 = 0;

	HANDLE hFile3 = CreateFile(L"../../Data/ThrowStand.dat", GENERIC_READ, 0, 0, OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL, NULL);

	m_vecThrowStandAni.clear();

	while(true)
	{
		Engine::ANIFRAME pFrameData;

		ReadFile(hFile3, &pFrameData, sizeof(Engine::ANIFRAME), &dwByte3, NULL);

		if(dwByte3 == 0)
			break;

		m_vecThrowStandAni.push_back(pFrameData);
	}

	CloseHandle(hFile3);

	DWORD dwByte4 = 0;

	HANDLE hFile4 = CreateFile(L"../../Data/Stand.dat", GENERIC_READ, 0, 0, OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL, NULL);

	m_vecStand.clear();

	while(true)
	{
		Engine::ANIFRAME pFrameData;

		ReadFile(hFile4, &pFrameData, sizeof(Engine::ANIFRAME), &dwByte4, NULL);

		if(dwByte4 == 0)
			break;

		m_vecStand.push_back(pFrameData);
	}

	CloseHandle(hFile4);


}

void CPlayer::SetState(Engine::PLAYERSTATE m_NowState)
{
	if(m_NowState != m_iState)
	{

		m_iState = m_NowState;

		switch(m_iState)
		{
		case Engine::STATE_STAND:
			m_pPlayerModel->SetAngle(m_vecStand);
			break;

		case Engine::STATE_RUN:
			m_pPlayerModel->SetAngle(m_vecRunAni);
			break;

		case Engine::STATE_TROWSTAND:
			m_pPlayerModel->SetAngle(m_vecThrowStandAni);
			break;

		case Engine::STATE_TROW:
			m_pPlayerModel->SetAngle(m_vecThrowAni);
			break;

		case Engine::STATE_DEAD:
			m_pPlayerModel->SetAngle(m_vecDeadAni);
			break;
		}
	}
}

