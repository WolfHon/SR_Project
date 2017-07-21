#include "PlayerModel.h"

#include "Transform.h" 
#include "VIBuffer.h"
#include "Texture.h"
#include "Export_Resource.h"

Engine::CPlayerModel::CPlayerModel(LPDIRECT3DDEVICE9 pDevice)
: CResources(pDevice)
,m_vHeadPos(D3DXVECTOR3(0.f, 0.f, 0.f))
,m_vBodyPos(D3DXVECTOR3(0.f, 0.f, 0.f))
,m_vLeftArmPos(D3DXVECTOR3(0.f, 0.f, 0.f))
,m_vRightArmPos(D3DXVECTOR3(0.f, 0.f, 0.f))
,m_vLeftFootPos(D3DXVECTOR3(0.f, 0.f, 0.f))
,m_vRightFootPos(D3DXVECTOR3(0.f, 0.f, 0.f))
//PibotPos
,m_vHeadPibotPos(D3DXVECTOR3(0.f, 0.f, 0.f))
,m_vBodyPosPibotPos(D3DXVECTOR3(0.f, 0.f, 0.f))
,m_vLeftArmPibotPos(D3DXVECTOR3(0.f, 0.f, 0.f))
,m_vRightArmPibotPos(D3DXVECTOR3(0.f, 0.f, 0.f))
,m_vLeftFootPibotPos(D3DXVECTOR3(0.f, 0.f, 0.f))
,m_vRightFootPibotPos(D3DXVECTOR3(0.f, 0.f, 0.f))
//Scale
,m_vHeadScale(D3DXVECTOR3(0.f, 0.f, 0.f))
,m_vBodyScale(D3DXVECTOR3(0.f, 0.f, 0.f))
,m_vArmScale(D3DXVECTOR3(0.f, 0.f, 0.f))
,m_vFootScale(D3DXVECTOR3(0.f, 0.f, 0.f))
//Texture
,m_pHeadTexture(NULL)
,m_pBodyTexture(NULL)
,m_pLeftArmTexture(NULL)
,m_pRightArmTexture(NULL)
,m_pLeftFootTexture(NULL)
,m_pRightFootTexture(NULL)
//Buffer
,m_pHeadBuffer(NULL)
,m_pBodyBuffer(NULL)
,m_pLeftArmBuffer(NULL)
,m_pRightArmBuffer(NULL)
,m_pLeftFootBuffer(NULL)
,m_pRightFootBuffer(NULL)
,m_fScaleSize(1.f)
//Extra
,m_pFrameAngle(NULL)
,m_bFirst(true)
{
	D3DXMatrixIdentity(&m_matHeadWorld);
	D3DXMatrixIdentity(&m_matBodyWorld);
	D3DXMatrixIdentity(&m_matRightArmWorld);
	D3DXMatrixIdentity(&m_matLeftArmWorld);
	D3DXMatrixIdentity(&m_matRightFootWorld);
	D3DXMatrixIdentity(&m_matLeftFootWorld);
	D3DXMatrixIdentity(&m_matScale);

	D3DXMatrixIdentity(&m_matHeadTrans);
	D3DXMatrixIdentity(&m_matBodyTrans);
	D3DXMatrixIdentity(&m_matRightArmTrans);
	D3DXMatrixIdentity(&m_matLeftArmTrans);
	D3DXMatrixIdentity(&m_matRightFootTrans);
	D3DXMatrixIdentity(&m_matLeftFootTrans);

	D3DXMatrixIdentity(&m_matHeadPibotTrans);
	D3DXMatrixIdentity(&m_matBodyPibotTrans);
	D3DXMatrixIdentity(&m_matRightArmPibotTrans);
	D3DXMatrixIdentity(&m_matLeftArmPibotTrans);
	D3DXMatrixIdentity(&m_matRightFootPibotTrans);
	D3DXMatrixIdentity(&m_matLeftFootPibotTrans);

	D3DXMatrixIdentity(&m_matHeadRotate);
	D3DXMatrixIdentity(&m_matBodyRotate);
	D3DXMatrixIdentity(&m_matRightArmRotate);
	D3DXMatrixIdentity(&m_matLeftArmRotate);
	D3DXMatrixIdentity(&m_matRightFootRotate);
	D3DXMatrixIdentity(&m_matLeftFootRotate);
}

Engine::CPlayerModel::CPlayerModel(const CPlayerModel& rhs)
: CResources(rhs)
,m_vHeadPos(rhs.m_vHeadPos)
,m_vBodyPos(rhs.m_vBodyPos)
,m_vLeftArmPos(rhs.m_vLeftArmPos)
,m_vRightArmPos(rhs.m_vRightArmPos)
,m_vLeftFootPos(rhs.m_vLeftFootPos)
,m_vRightFootPos(rhs.m_vRightFootPos)
,m_vHeadPibotPos(rhs.m_vHeadPibotPos)
//PibotPos
,m_vBodyPosPibotPos(rhs.m_vBodyPosPibotPos)
,m_vLeftArmPibotPos(rhs.m_vLeftArmPibotPos)
,m_vRightArmPibotPos(rhs.m_vRightArmPibotPos)
,m_vLeftFootPibotPos(rhs.m_vLeftFootPibotPos)
,m_vRightFootPibotPos(rhs.m_vRightFootPibotPos)
//Scale
,m_vHeadScale(rhs.m_vHeadScale)
,m_vBodyScale(rhs.m_vBodyScale)
,m_vArmScale(rhs.m_vArmScale)
,m_vFootScale(rhs.m_vFootScale)
//Texture
,m_pHeadTexture(rhs.m_pHeadTexture)
,m_pBodyTexture(rhs.m_pBodyTexture)
,m_pLeftArmTexture(rhs.m_pLeftArmTexture)
,m_pRightArmTexture(rhs.m_pRightArmTexture)
,m_pLeftFootTexture(rhs.m_pLeftFootTexture)
,m_pRightFootTexture(rhs.m_pRightFootTexture)
//Buffer
,m_pHeadBuffer(rhs.m_pHeadBuffer)
,m_pBodyBuffer(rhs.m_pBodyBuffer)
,m_pLeftArmBuffer(rhs.m_pLeftArmBuffer)
,m_pRightArmBuffer(rhs.m_pRightArmBuffer)
,m_pLeftFootBuffer(rhs.m_pLeftFootBuffer)
,m_pRightFootBuffer(rhs.m_pRightFootBuffer)
//Mat
,m_matHeadWorld(rhs.m_matHeadWorld)
,m_matBodyWorld(rhs.m_matBodyWorld)
,m_matRightArmWorld(rhs.m_matRightArmWorld)
,m_matLeftArmWorld(rhs.m_matLeftArmWorld)
,m_matRightFootWorld(rhs.m_matRightFootWorld)
,m_matLeftFootWorld(rhs.m_matLeftFootWorld)
//Trans
,m_matHeadTrans(rhs.m_matHeadTrans)	
,m_matBodyTrans(rhs.m_matBodyTrans)
,m_matRightArmTrans(rhs.m_matRightArmTrans)
,m_matLeftArmTrans(rhs.m_matLeftArmTrans)
,m_matRightFootTrans(rhs.m_matRightFootTrans)
,m_matLeftFootTrans(rhs.m_matLeftFootTrans)
//PibotTrans
,m_matHeadPibotTrans(rhs.m_matHeadPibotTrans)	
,m_matBodyPibotTrans(rhs.m_matBodyPibotTrans)
,m_matRightArmPibotTrans(rhs.m_matRightArmPibotTrans)
,m_matLeftArmPibotTrans(rhs.m_matLeftArmPibotTrans)
,m_matRightFootPibotTrans(rhs.m_matRightFootPibotTrans)
,m_matLeftFootPibotTrans(rhs.m_matLeftFootPibotTrans)
{
	m_pHeadBuffer->AddRefCnt();
	m_pBodyBuffer->AddRefCnt();
	m_pLeftArmBuffer->AddRefCnt();
	m_pRightArmBuffer->AddRefCnt();
	m_pLeftFootBuffer->AddRefCnt();
	m_pRightFootBuffer->AddRefCnt();

	m_pHeadTexture->AddRefCnt();
	m_pBodyTexture->AddRefCnt();
	m_pLeftArmTexture->AddRefCnt();
	m_pRightArmTexture->AddRefCnt();
	m_pLeftFootTexture->AddRefCnt();
	m_pRightFootTexture->AddRefCnt();
}

Engine::CPlayerModel::~CPlayerModel(void)
{	
}

Engine::CPlayerModel* Engine::CPlayerModel::Create(LPDIRECT3DDEVICE9 pDevice)
{
	Engine::CPlayerModel*		pComponent = new Engine::CPlayerModel(pDevice);	

	if(FAILED(pComponent->Initialize()))
		Safe_Delete(pComponent);

	return pComponent;
}

DWORD Engine::CPlayerModel::Release(void)
{

	if( m_dwRefCnt == 0 )
	{		
		//buffer
		DWORD	dwRefCnt = m_pHeadBuffer->Release();
		if(dwRefCnt == 0)
			Safe_Delete(m_pHeadBuffer);

		dwRefCnt = m_pBodyBuffer->Release();
		if(dwRefCnt == 0)
			Safe_Delete(m_pBodyBuffer);

		dwRefCnt = m_pLeftArmBuffer->Release();
		if(dwRefCnt == 0)
			Safe_Delete(m_pLeftArmBuffer);

		dwRefCnt = m_pRightArmBuffer->Release();
		if(dwRefCnt == 0)
			Safe_Delete(m_pRightArmBuffer);

		dwRefCnt = m_pLeftFootBuffer->Release();
		if(dwRefCnt == 0)
			Safe_Delete(m_pLeftFootBuffer);

		dwRefCnt = m_pRightFootBuffer->Release();
		if(dwRefCnt == 0)
			Safe_Delete(m_pRightFootBuffer);

		//Texture
		dwRefCnt = m_pHeadTexture->Release();
		if(dwRefCnt == 0)
			Safe_Delete(m_pHeadTexture);

		dwRefCnt = m_pBodyTexture->Release();
		if(dwRefCnt == 0)
			Safe_Delete(m_pBodyTexture);

		dwRefCnt = m_pLeftArmTexture->Release();
		if(dwRefCnt == 0)
			Safe_Delete(m_pLeftArmTexture);

		dwRefCnt = m_pRightArmTexture->Release();
		if(dwRefCnt == 0)
			Safe_Delete(m_pRightArmTexture);

		dwRefCnt = m_pLeftFootTexture->Release();
		if(dwRefCnt == 0)
			Safe_Delete(m_pLeftFootTexture);

		dwRefCnt = m_pRightFootTexture->Release();
		if(dwRefCnt == 0)
			Safe_Delete(m_pRightFootTexture);

		return 0;
	}
	else
	{
		//buffer
		DWORD	dwRefCnt = m_pHeadBuffer->Release();
		if(dwRefCnt == 0)
			Safe_Delete(m_pHeadBuffer);

		dwRefCnt = m_pBodyBuffer->Release();
		if(dwRefCnt == 0)
			Safe_Delete(m_pBodyBuffer);

		dwRefCnt = m_pLeftArmBuffer->Release();
		if(dwRefCnt == 0)
			Safe_Delete(m_pLeftArmBuffer);

		dwRefCnt = m_pRightArmBuffer->Release();
		if(dwRefCnt == 0)
			Safe_Delete(m_pRightArmBuffer);

		dwRefCnt = m_pLeftFootBuffer->Release();
		if(dwRefCnt == 0)
			Safe_Delete(m_pLeftFootBuffer);

		dwRefCnt = m_pRightFootBuffer->Release();
		if(dwRefCnt == 0)
			Safe_Delete(m_pRightFootBuffer);

		//Texture
		dwRefCnt = m_pHeadTexture->Release();
		if(dwRefCnt == 0)
			Safe_Delete(m_pHeadTexture);

		dwRefCnt = m_pBodyTexture->Release();
		if(dwRefCnt == 0)
			Safe_Delete(m_pBodyTexture);

		dwRefCnt = m_pLeftArmTexture->Release();
		if(dwRefCnt == 0)
			Safe_Delete(m_pLeftArmTexture);

		dwRefCnt = m_pRightArmTexture->Release();
		if(dwRefCnt == 0)
			Safe_Delete(m_pRightArmTexture);

		dwRefCnt = m_pLeftFootTexture->Release();
		if(dwRefCnt == 0)
			Safe_Delete(m_pLeftFootTexture);

		dwRefCnt = m_pRightFootTexture->Release();
		if(dwRefCnt == 0)
			Safe_Delete(m_pRightFootTexture);

		--m_dwRefCnt;
	}

	return m_dwRefCnt;
}

HRESULT Engine::CPlayerModel::Initialize(void)
{	
	FAILED_CHECK(AddComponent());

	//OriginPibot
	m_vBodyPos		= D3DXVECTOR3(0.f, 0.f, 0.f);
	m_vHeadPos		= D3DXVECTOR3(m_vBodyPos.x,			m_vBodyPos.y + 2.5f, m_vBodyPos.z);
	m_vLeftArmPos   = D3DXVECTOR3(m_vBodyPos.x - 1.5f, m_vBodyPos.y, m_vBodyPos.z);
	m_vRightArmPos  = D3DXVECTOR3(m_vBodyPos.x + 1.5f, m_vBodyPos.y, m_vBodyPos.z);
	m_vLeftFootPos  = D3DXVECTOR3(m_vBodyPos.x - 0.5f, m_vBodyPos.y - 3.f , m_vBodyPos.z);
	m_vRightFootPos = D3DXVECTOR3(m_vBodyPos.x + 0.5f, m_vBodyPos.y - 3.f , m_vBodyPos.z);

	//MovePibotToOrigin
	m_vHeadPibotPos		 = D3DXVECTOR3(0, -1.f, 0);
	m_vLeftArmPibotPos	 = D3DXVECTOR3(0, 1.f, 0) ;
	m_vRightArmPibotPos  = D3DXVECTOR3(0, 1.f, 0);
	m_vLeftFootPibotPos  = D3DXVECTOR3(0, 2.f, 0);
	m_vRightFootPibotPos = D3DXVECTOR3(0, 2.f, 0);

	//원점(0, 0, 0)에서 회전할 중점까지의 거리를 통한 이동매트릭스 선언

	//회전할 중점 부터 큐브의 원점까지의 거리를 통한 이동매트릭스 선언

	m_vBodyScale = D3DXVECTOR3(1.f, 1.5f, 0.5f);
	m_vHeadScale = D3DXVECTOR3(1.f, 1.f, 1.f);
	m_vArmScale  = D3DXVECTOR3(0.5f, 1.5f, 0.5f);
	m_vFootScale = D3DXVECTOR3(0.5f, 1.5f, 0.5f);

	D3DXMatrixTranslation(&m_matHeadTrans
		, m_vHeadPos.x + m_vHeadPibotPos.x
		, m_vHeadPos.y + m_vHeadPibotPos.y
		, m_vHeadPos.z + m_vHeadPibotPos.z);
	//D3DXMatrixTranslation(&m_matBodyTrans, m_vBodyPos );
	D3DXMatrixTranslation(&m_matLeftArmTrans
		, m_vLeftArmPos.x + m_vLeftArmPibotPos.x
		, m_vLeftArmPos.y + m_vLeftArmPibotPos.y
		, m_vLeftArmPos.z + m_vLeftArmPibotPos.z);

	D3DXMatrixTranslation(&m_matRightArmTrans
		, m_vRightArmPos.x + m_vRightArmPibotPos.x
		, m_vRightArmPos.y + m_vRightArmPibotPos.y
		, m_vRightArmPos.z + m_vRightArmPibotPos.z);

	D3DXMatrixTranslation(&m_matLeftFootTrans
		, m_vLeftFootPos.x + m_vLeftFootPibotPos.x
		, m_vLeftFootPos.y + m_vLeftFootPibotPos.y
		, m_vLeftFootPos.z + m_vLeftFootPibotPos.z);

	D3DXMatrixTranslation(&m_matRightFootTrans
		, m_vRightFootPos.x + m_vRightFootPibotPos.x
		, m_vRightFootPos.y + m_vRightFootPibotPos.y
		, m_vRightFootPos.z + m_vRightFootPibotPos.z);

	D3DXMatrixTranslation(&m_matBodyWorld, m_vBodyPos.x, m_vBodyPos.y, m_vBodyPos.z);

	//회전 중점으로 부터 큐브의 중점까지의 거리
	D3DXMatrixTranslation(&m_matHeadPibotTrans,		 -m_vHeadPibotPos.x,	  -m_vHeadPibotPos.y,		-m_vHeadPibotPos.z);
	D3DXMatrixTranslation(&m_matLeftArmPibotTrans,	 -m_vLeftArmPibotPos.x,	  -m_vLeftArmPibotPos.y,	-m_vLeftArmPibotPos.z);
	D3DXMatrixTranslation(&m_matRightArmPibotTrans,	 -m_vRightArmPibotPos.x,  -m_vRightArmPibotPos.y,	-m_vRightArmPibotPos.z);
	D3DXMatrixTranslation(&m_matLeftFootPibotTrans,	 -m_vLeftFootPibotPos.x,  -m_vLeftFootPibotPos.y,	-m_vLeftFootPibotPos.z); 
	D3DXMatrixTranslation(&m_matRightFootPibotTrans, -m_vRightFootPibotPos.x, -m_vRightFootPibotPos.y,  -m_vRightFootPibotPos.z);
	return S_OK;
}

void Engine::CPlayerModel::Render(void)
{

	Animation();
	D3DXMATRIX matWorld;
	m_pDevice->GetTransform(D3DTS_WORLD, &matWorld);

	//--------------------------------------Body-----------------------------------------

	D3DXMatrixScaling(&m_matScale, m_vBodyScale.x ,m_vBodyScale.y ,m_vBodyScale.z);
	m_pDevice->SetTransform(D3DTS_WORLD, &(m_matScale * m_matBodyWorld * matWorld));
	m_pBodyTexture->Render(0,0);
	m_pBodyBuffer->Render();
	D3DXMatrixIdentity(&m_matScale);

	//--------------------------------------Head-----------------------------------------

	D3DXMatrixScaling(&m_matScale, m_vHeadScale.x ,m_vHeadScale.y ,m_vHeadScale.z);
	m_pDevice->SetTransform(D3DTS_WORLD,&(m_matScale * m_matHeadPibotTrans * m_matHeadWorld * matWorld));
	m_pHeadTexture->Render(0,0);
	m_pHeadBuffer->Render();
	D3DXMatrixIdentity(&m_matScale);

	//--------------------------------------LeftArm--------------------------------------

	D3DXMatrixScaling(&m_matScale, m_vArmScale.x ,m_vArmScale.y ,m_vArmScale.z);
	m_pDevice->SetTransform(D3DTS_WORLD,&(m_matScale * m_matLeftArmPibotTrans * m_matLeftArmWorld * matWorld));
	m_pLeftArmTexture->Render(0,0);
	m_pLeftArmBuffer->Render();
	D3DXMatrixIdentity(&m_matScale);

	//--------------------------------------RightArm-------------------------------------

	D3DXMatrixScaling(&m_matScale, m_vArmScale.x ,m_vArmScale.y ,m_vArmScale.z);
	m_pDevice->SetTransform(D3DTS_WORLD,&(m_matScale * m_matRightArmPibotTrans * m_matRightArmWorld * matWorld));
	m_pRightArmTexture->Render(0,0);
	m_pRightArmBuffer->Render();
	D3DXMatrixIdentity(&m_matScale);

	//--------------------------------------LeftFoot-------------------------------------

	D3DXMatrixScaling(&m_matScale, m_vFootScale.x ,m_vFootScale.y ,m_vFootScale.z);
	D3DXMATRIX matPibot, matTrans, matRot;
	m_pDevice->SetTransform(D3DTS_WORLD,&(m_matScale * m_matLeftFootPibotTrans * m_matLeftFootWorld * matWorld));
	m_pLeftFootTexture->Render(0,0);
	m_pLeftFootBuffer->Render();
	D3DXMatrixIdentity(&m_matScale);

	//--------------------------------------RightFoot------------------------------------

	D3DXMatrixScaling(&m_matScale, m_vFootScale.x ,m_vFootScale.y ,m_vFootScale.z);
	m_pDevice->SetTransform(D3DTS_WORLD,&(m_matScale * m_matRightFootPibotTrans * m_matRightFootWorld * matWorld));
	m_pRightFootTexture->Render(0,0);
	m_pRightFootBuffer->Render();
	D3DXMatrixIdentity(&m_matScale);
}

HRESULT Engine::CPlayerModel::AddComponent()
{
	CComponent*			pComponent = NULL;

	//Texture
	pComponent = Get_ResourceMgr()->CloneResource(RESOURCE_DYNAMIC, L"Texture_Player_Head");
	m_pHeadTexture = dynamic_cast<CTexture*>(pComponent);
	NULL_CHECK_RETURN(m_pHeadTexture, E_FAIL);

	pComponent = Get_ResourceMgr()->CloneResource(RESOURCE_DYNAMIC, L"Texture_Player_Body");
	m_pBodyTexture = dynamic_cast<CTexture*>(pComponent);
	NULL_CHECK_RETURN(m_pBodyTexture, E_FAIL);

	pComponent = Get_ResourceMgr()->CloneResource(RESOURCE_DYNAMIC, L"Texture_Player_Arm");
	m_pLeftArmTexture = dynamic_cast<CTexture*>(pComponent);
	NULL_CHECK_RETURN(m_pLeftArmTexture, E_FAIL);

	pComponent = Get_ResourceMgr()->CloneResource(RESOURCE_DYNAMIC, L"Texture_Player_Arm");
	m_pRightArmTexture = dynamic_cast<CTexture*>(pComponent);
	NULL_CHECK_RETURN(m_pRightArmTexture, E_FAIL);

	pComponent = Get_ResourceMgr()->CloneResource(RESOURCE_DYNAMIC, L"Texture_Player_Foot");
	m_pLeftFootTexture = dynamic_cast<CTexture*>(pComponent);
	NULL_CHECK_RETURN(m_pLeftFootTexture, E_FAIL);

	pComponent = Get_ResourceMgr()->CloneResource(RESOURCE_DYNAMIC, L"Texture_Player_Foot");
	m_pRightFootTexture = dynamic_cast<CTexture*>(pComponent);
	NULL_CHECK_RETURN(m_pRightFootTexture, E_FAIL);

	//Buffer
	pComponent = Get_ResourceMgr()->CloneResource(RESOURCE_DYNAMIC, L"Buffer_CubeTex");
	m_pHeadBuffer = dynamic_cast<CVIBuffer*>(pComponent);
	NULL_CHECK_RETURN(m_pHeadBuffer, E_FAIL);

	pComponent = Get_ResourceMgr()->CloneResource(RESOURCE_DYNAMIC, L"Buffer_CubeTex");
	m_pBodyBuffer = dynamic_cast<CVIBuffer*>(pComponent);
	NULL_CHECK_RETURN(m_pBodyBuffer, E_FAIL);

	pComponent = Get_ResourceMgr()->CloneResource(RESOURCE_DYNAMIC, L"Buffer_CubeTex");
	m_pLeftArmBuffer = dynamic_cast<CVIBuffer*>(pComponent);
	NULL_CHECK_RETURN(m_pLeftArmBuffer, E_FAIL);

	pComponent = Get_ResourceMgr()->CloneResource(RESOURCE_DYNAMIC, L"Buffer_CubeTex");
	m_pRightArmBuffer = dynamic_cast<CVIBuffer*>(pComponent);
	NULL_CHECK_RETURN(m_pRightArmBuffer, E_FAIL);

	pComponent = Get_ResourceMgr()->CloneResource(RESOURCE_DYNAMIC, L"Buffer_CubeTex");
	m_pLeftFootBuffer = dynamic_cast<CVIBuffer*>(pComponent);
	NULL_CHECK_RETURN(m_pLeftFootBuffer , E_FAIL);

	pComponent = Get_ResourceMgr()->CloneResource(RESOURCE_DYNAMIC, L"Buffer_CubeTex");
	m_pRightFootBuffer = dynamic_cast<CVIBuffer*>(pComponent);
	NULL_CHECK_RETURN(m_pRightFootBuffer , E_FAIL);


	return S_OK;
}

Engine::CResources* Engine::CPlayerModel::CloneResource(void)
{
	return new CPlayerModel(*this);
}


void Engine::CPlayerModel::Animation(void)
{

	static vector<ANIFRAME*>::iterator		iter;
	static vector<ANIFRAME*>::iterator		iter2;

	if(m_bFirst)
	{
		iter = m_listAni.begin();
		iter2 = m_listAni.begin();
		++iter2;
		m_bFirst = false;
	}

	vector<ANIFRAME*>::iterator		iter_begin = m_listAni.begin();
	vector<ANIFRAME*>::iterator		iter_end = m_listAni.end();


	if( iter == iter_end || iter2 == iter_end )
		iter2 = iter_begin;

	m_pFrameAngle = (*iter);
	m_pNextFrame = (*iter2);


	/*if(m_bFirst)
	{
		m_pFrameAngle = (*iter);
		if(++iter2 != iter_end)
			m_pNextFrame = (*iter2);
		else
		{
			m_pNextFrame = (*--iter2);
		}
		m_bFirst = false;
	}*/
	D3DXMatrixRotationX(&m_matHeadRotationX, D3DXToRadian(m_pFrameAngle->HeadAngle.AngleX));
	D3DXMatrixRotationY(&m_matHeadRotationY, D3DXToRadian(m_pFrameAngle->HeadAngle.AngleY));
	D3DXMatrixRotationZ(&m_matHeadRotationZ, D3DXToRadian(m_pFrameAngle->HeadAngle.AngleZ));
	m_matHeadWorld = m_matHeadRotationX * m_matHeadRotationY * m_matHeadRotationZ * m_matHeadTrans;

	D3DXMatrixRotationX(&m_matBodyRotationX, D3DXToRadian(m_pFrameAngle->BodyAngle.AngleX));
	D3DXMatrixRotationY(&m_matBodyRotationY, D3DXToRadian(m_pFrameAngle->BodyAngle.AngleY));
	D3DXMatrixRotationZ(&m_matBodyRotationZ, D3DXToRadian(m_pFrameAngle->BodyAngle.AngleZ));
	m_matBodyWorld = m_matBodyRotationX * m_matBodyRotationY * m_matBodyRotationZ * m_matBodyWorld;

	D3DXMatrixRotationX(&m_matLeftArmRotationX, D3DXToRadian(m_pFrameAngle->LeftArmAngle.AngleX));
	D3DXMatrixRotationY(&m_matLeftArmRotationY, D3DXToRadian(m_pFrameAngle->LeftArmAngle.AngleY));
	D3DXMatrixRotationZ(&m_matLeftArmRotationZ, D3DXToRadian(m_pFrameAngle->LeftArmAngle.AngleZ));
	m_matLeftArmWorld = m_matLeftArmRotationX * m_matLeftArmRotationY * m_matLeftArmRotationZ * m_matLeftArmTrans;

	D3DXMatrixRotationX(&m_matRightArmRotationX, D3DXToRadian(m_pFrameAngle->RightArmAngle.AngleX));
	D3DXMatrixRotationY(&m_matRightArmRotationY, D3DXToRadian(m_pFrameAngle->RightArmAngle.AngleY));
	D3DXMatrixRotationZ(&m_matRightArmRotationZ, D3DXToRadian(m_pFrameAngle->RightArmAngle.AngleZ));
	m_matRightArmWorld = m_matRightArmRotationX * m_matRightArmRotationY * m_matRightArmRotationZ * m_matRightArmTrans;

	D3DXMatrixRotationX(&m_matLeftFootRotationX, D3DXToRadian(m_pFrameAngle->LeftFootAngle.AngleX));
	D3DXMatrixRotationY(&m_matLeftFootRotationY, D3DXToRadian(m_pFrameAngle->LeftFootAngle.AngleY));
	D3DXMatrixRotationZ(&m_matLeftFootRotationZ, D3DXToRadian(m_pFrameAngle->LeftFootAngle.AngleZ));
	m_matLeftFootWorld = m_matLeftFootRotationX * m_matLeftFootRotationY * m_matLeftFootRotationZ * m_matLeftFootTrans;

	D3DXMatrixRotationX(&m_matRightFootRotationX, D3DXToRadian(m_pFrameAngle->RightFootAngle.AngleX));
	D3DXMatrixRotationY(&m_matRightFootRotationY, D3DXToRadian(m_pFrameAngle->RightFootAngle.AngleY));
	D3DXMatrixRotationZ(&m_matRightFootRotationZ, D3DXToRadian(m_pFrameAngle->RightFootAngle.AngleZ));
	m_matRightFootWorld = m_matRightFootRotationX * m_matRightFootRotationY * m_matRightFootRotationZ * m_matRightFootTrans;

	if(CompareAngle())
	{
		//++iter;
		//if(iter2 != iter_end)
		//	++iter2;

		//if(iter == iter2)
		//{
		//	iter = m_listAni.begin();
		//	iter2 = m_listAni.begin();
		//	++iter2;
		//}
		//m_pFrameAngle = (*iter);
		//m_pNextFrame  = (*iter2);

		iter = iter2;

		if( ++iter2 == iter_end )
			iter2 = iter_begin;
	}
}

bool Engine::CPlayerModel::CompareAngle(void)
{
	if(CompareHeadAngle() && CompareLeftArmAngle()
		&& CompareRightArmAngle() && CompareBodyAngle() 
		&& CompareLeftFootAngle() && CompareRightFootAngle())
		return true;
	else
		return false;
}

bool Engine::CPlayerModel::CompareHeadAngle(void)
{
	bool	ComX = false, ComY = false, ComZ = false;

	//Compare X
	if(m_pFrameAngle->HeadAngle.AngleX == m_pNextFrame->HeadAngle.AngleX)
		ComX = true;

	else if(m_pFrameAngle->HeadAngle.AngleX > m_pNextFrame->HeadAngle.AngleX)
		--(m_pFrameAngle->HeadAngle.AngleX);

	else if(m_pFrameAngle->HeadAngle.AngleX < m_pNextFrame->HeadAngle.AngleX)
		++(m_pFrameAngle->HeadAngle.AngleX);

	//Compare Y
	if(m_pFrameAngle->HeadAngle.AngleY == m_pNextFrame->HeadAngle.AngleY)
		ComY = true;

	else if(m_pFrameAngle->HeadAngle.AngleY > m_pNextFrame->HeadAngle.AngleY)
		--(m_pFrameAngle->HeadAngle.AngleY);

	else if(m_pFrameAngle->HeadAngle.AngleY < m_pNextFrame->HeadAngle.AngleY)
		++(m_pFrameAngle->HeadAngle.AngleY);

	//Compare Z
	if(m_pFrameAngle->HeadAngle.AngleZ == m_pNextFrame->HeadAngle.AngleZ)
		ComZ = true;

	else if(m_pFrameAngle->HeadAngle.AngleZ > m_pNextFrame->HeadAngle.AngleZ)
		--(m_pFrameAngle->HeadAngle.AngleZ);

	else if(m_pFrameAngle->HeadAngle.AngleZ < m_pNextFrame->HeadAngle.AngleZ)
		++(m_pFrameAngle->HeadAngle.AngleZ);

	if(ComX && ComY && ComZ)
		return true;

	else
		return false;
}

bool Engine::CPlayerModel::CompareLeftArmAngle(void)
{
	bool	ComX = false, ComY = false, ComZ = false;

	//Compare X
	if(m_pFrameAngle->LeftArmAngle.AngleX == m_pNextFrame->LeftArmAngle.AngleX)
		ComX = true;

	else if(m_pFrameAngle->LeftArmAngle.AngleX > m_pNextFrame->LeftArmAngle.AngleX)
		--(m_pFrameAngle->LeftArmAngle.AngleX);

	else if(m_pFrameAngle->LeftArmAngle.AngleX < m_pNextFrame->LeftArmAngle.AngleX)
		++(m_pFrameAngle->LeftArmAngle.AngleX);

	//Compare Y
	if(m_pFrameAngle->LeftArmAngle.AngleY == m_pNextFrame->LeftArmAngle.AngleY)
		ComY = true;

	else if(m_pFrameAngle->LeftArmAngle.AngleY > m_pNextFrame->LeftArmAngle.AngleY)
		--(m_pFrameAngle->LeftArmAngle.AngleY);

	else if(m_pFrameAngle->LeftArmAngle.AngleY < m_pNextFrame->LeftArmAngle.AngleY)
		++(m_pFrameAngle->LeftArmAngle.AngleY);

	//Compare Z
	if(m_pFrameAngle->LeftArmAngle.AngleZ == m_pNextFrame->LeftArmAngle.AngleZ)
		ComZ = true;

	else if(m_pFrameAngle->LeftArmAngle.AngleZ > m_pNextFrame->LeftArmAngle.AngleZ)
		--(m_pFrameAngle->LeftArmAngle.AngleZ);

	else if(m_pFrameAngle->LeftArmAngle.AngleZ < m_pNextFrame->LeftArmAngle.AngleZ)
		++(m_pFrameAngle->LeftArmAngle.AngleZ);

	if(ComX && ComY && ComZ)
		return true;


	else
		return false;

}

bool Engine::CPlayerModel::CompareRightArmAngle(void)
{
	bool	ComX = false, ComY = false, ComZ = false;

	//Compare X
	if(m_pFrameAngle->RightArmAngle.AngleX == m_pNextFrame->RightArmAngle.AngleX)
		ComX = true;

	else if(m_pFrameAngle->RightArmAngle.AngleX > m_pNextFrame->RightArmAngle.AngleX)
		--(m_pFrameAngle->RightArmAngle.AngleX);

	else if(m_pFrameAngle->RightArmAngle.AngleX < m_pNextFrame->RightArmAngle.AngleX)
		++(m_pFrameAngle->RightArmAngle.AngleX);

	//Compare Y
	if(m_pFrameAngle->RightArmAngle.AngleY == m_pNextFrame->RightArmAngle.AngleY)
		ComY = true;

	else if(m_pFrameAngle->RightArmAngle.AngleY > m_pNextFrame->RightArmAngle.AngleY)
		--(m_pFrameAngle->RightArmAngle.AngleY);

	else if(m_pFrameAngle->RightArmAngle.AngleY < m_pNextFrame->RightArmAngle.AngleY)
		++(m_pFrameAngle->RightArmAngle.AngleY);

	//Compare Z
	if(m_pFrameAngle->RightArmAngle.AngleZ == m_pNextFrame->RightArmAngle.AngleZ)
		ComZ = true;

	else if(m_pFrameAngle->RightArmAngle.AngleZ > m_pNextFrame->RightArmAngle.AngleZ)
		--(m_pFrameAngle->RightArmAngle.AngleZ);

	else if(m_pFrameAngle->RightArmAngle.AngleZ < m_pNextFrame->RightArmAngle.AngleZ)
		++(m_pFrameAngle->RightArmAngle.AngleZ);

	if(ComX && ComY && ComZ)
		return true;

	else
		return false;

}

bool Engine::CPlayerModel::CompareLeftFootAngle(void)
{
	bool	ComX = false, ComY = false, ComZ = false;

	//Compare X
	if(m_pFrameAngle->LeftFootAngle.AngleX == m_pNextFrame->LeftFootAngle.AngleX)
		ComX = true;

	else if(m_pFrameAngle->LeftFootAngle.AngleX > m_pNextFrame->LeftFootAngle.AngleX)
		--(m_pFrameAngle->LeftFootAngle.AngleX);

	else if(m_pFrameAngle->LeftFootAngle.AngleX < m_pNextFrame->LeftFootAngle.AngleX)
		++(m_pFrameAngle->LeftFootAngle.AngleX);

	//Compare Y
	if(m_pFrameAngle->LeftFootAngle.AngleY == m_pNextFrame->LeftFootAngle.AngleY)
		ComY = true;

	else if(m_pFrameAngle->LeftFootAngle.AngleY > m_pNextFrame->LeftFootAngle.AngleY)
		--(m_pFrameAngle->LeftFootAngle.AngleY);

	else if(m_pFrameAngle->LeftFootAngle.AngleY < m_pNextFrame->LeftFootAngle.AngleY)
		++(m_pFrameAngle->LeftFootAngle.AngleY);

	//Compare Z
	if(m_pFrameAngle->LeftFootAngle.AngleZ == m_pNextFrame->LeftFootAngle.AngleZ)
		ComZ = true;

	else if(m_pFrameAngle->LeftFootAngle.AngleZ > m_pNextFrame->LeftFootAngle.AngleZ)
		--(m_pFrameAngle->LeftFootAngle.AngleZ);

	else if(m_pFrameAngle->LeftFootAngle.AngleZ < m_pNextFrame->LeftFootAngle.AngleZ)
		++(m_pFrameAngle->LeftFootAngle.AngleZ);

	if(ComX && ComY && ComZ)
		return true;

	else
		return false;
}

bool Engine::CPlayerModel::CompareRightFootAngle(void)
{
	bool	ComX = false, ComY = false, ComZ = false;

	//Compare X
	if(m_pFrameAngle->RightFootAngle.AngleX == m_pNextFrame->RightFootAngle.AngleX)
		ComX = true;

	else if(m_pFrameAngle->RightFootAngle.AngleX > m_pNextFrame->RightFootAngle.AngleX)
		--(m_pFrameAngle->RightFootAngle.AngleX);

	else if(m_pFrameAngle->RightFootAngle.AngleX < m_pNextFrame->RightFootAngle.AngleX)
		++(m_pFrameAngle->RightFootAngle.AngleX);

	//Compare Y
	if(m_pFrameAngle->RightFootAngle.AngleY == m_pNextFrame->RightFootAngle.AngleY)
		ComY = true;

	else if(m_pFrameAngle->RightFootAngle.AngleY > m_pNextFrame->RightFootAngle.AngleY)
		--(m_pFrameAngle->RightFootAngle.AngleY);

	else if(m_pFrameAngle->RightFootAngle.AngleY < m_pNextFrame->RightFootAngle.AngleY)
		++(m_pFrameAngle->RightFootAngle.AngleY);

	//Compare Z
	if(m_pFrameAngle->RightFootAngle.AngleZ == m_pNextFrame->RightFootAngle.AngleZ)
		ComZ = true;

	else if(m_pFrameAngle->RightFootAngle.AngleZ > m_pNextFrame->RightFootAngle.AngleZ)
		--(m_pFrameAngle->RightFootAngle.AngleZ);

	else if(m_pFrameAngle->RightFootAngle.AngleZ < m_pNextFrame->RightFootAngle.AngleZ)
		++(m_pFrameAngle->RightFootAngle.AngleZ);

	if(ComX && ComY && ComZ)
		return true;

	else
		return false;
}

bool Engine::CPlayerModel::CompareBodyAngle(void)
{
	bool	ComX = false, ComY = false, ComZ = false;

	//Compare X
	if(m_pFrameAngle->BodyAngle.AngleX == m_pNextFrame->BodyAngle.AngleX)
		ComX = true;

	else if(m_pFrameAngle->BodyAngle.AngleX > m_pNextFrame->BodyAngle.AngleX)
		--(m_pFrameAngle->BodyAngle.AngleX);

	else if(m_pFrameAngle->BodyAngle.AngleX < m_pNextFrame->BodyAngle.AngleX)
		++(m_pFrameAngle->BodyAngle.AngleX);

	//Compare Y
	if(m_pFrameAngle->BodyAngle.AngleY == m_pNextFrame->BodyAngle.AngleY)
		ComY = true;

	else if(m_pFrameAngle->BodyAngle.AngleY > m_pNextFrame->BodyAngle.AngleY)
		--(m_pFrameAngle->BodyAngle.AngleY);

	else if(m_pFrameAngle->BodyAngle.AngleY < m_pNextFrame->BodyAngle.AngleY)
		++(m_pFrameAngle->BodyAngle.AngleY);

	//Compare Z
	if(m_pFrameAngle->BodyAngle.AngleZ == m_pNextFrame->BodyAngle.AngleZ)
		ComZ = true;

	else if(m_pFrameAngle->BodyAngle.AngleZ > m_pNextFrame->BodyAngle.AngleZ)
		--(m_pFrameAngle->BodyAngle.AngleZ);

	else if(m_pFrameAngle->BodyAngle.AngleZ < m_pNextFrame->BodyAngle.AngleZ)
		++(m_pFrameAngle->BodyAngle.AngleZ);

	if(ComX && ComY && ComZ)
		return true;


	else
		return false;

}

