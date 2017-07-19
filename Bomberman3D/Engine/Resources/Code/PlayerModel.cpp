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
,m_vHeadScale(D3DXVECTOR3(0.f, 0.f, 0.f))
,m_vBodyScale(D3DXVECTOR3(0.f, 0.f, 0.f))
,m_vArmScale(D3DXVECTOR3(0.f, 0.f, 0.f))
,m_vFootScale(D3DXVECTOR3(0.f, 0.f, 0.f))
,m_pHeadTexture(NULL)
,m_pBodyTexture(NULL)
,m_pLeftArmTexture(NULL)
,m_pRightArmTexture(NULL)
,m_pLeftFootTexture(NULL)
,m_pRightFootTexture(NULL)
,m_pHeadBuffer(NULL)
,m_pBodyBuffer(NULL)
,m_pLeftArmBuffer(NULL)
,m_pRightArmBuffer(NULL)
,m_pLeftFootBuffer(NULL)
,m_pRightFootBuffer(NULL)
,m_fScaleSize(1.f)

{
	D3DXMatrixIdentity(&m_matHeadWorld);
	D3DXMatrixIdentity(&m_matBodyWorld);
	D3DXMatrixIdentity(&m_matRightArmWorld);
	D3DXMatrixIdentity(&m_matLeftArmWorld);
	D3DXMatrixIdentity(&m_matRightFootWorld);
	D3DXMatrixIdentity(&m_matLeftFootWorld);
	D3DXMatrixIdentity(&m_matScale);
}

Engine::CPlayerModel::CPlayerModel(const CPlayerModel& rhs)
: CResources(rhs)
,m_vHeadPos(rhs.m_vHeadPos)
,m_vBodyPos(rhs.m_vBodyPos)
,m_vLeftArmPos(rhs.m_vLeftArmPos)
,m_vRightArmPos(rhs.m_vRightArmPos)
,m_vLeftFootPos(rhs.m_vLeftFootPos)
,m_vRightFootPos(rhs.m_vRightFootPos)
,m_vHeadScale(rhs.m_vHeadScale)
,m_vBodyScale(rhs.m_vBodyScale)
,m_vArmScale(rhs.m_vArmScale)
,m_vFootScale(rhs.m_vFootScale)
,m_pHeadTexture(rhs.m_pHeadTexture)
,m_pBodyTexture(rhs.m_pBodyTexture)
,m_pLeftArmTexture(rhs.m_pLeftArmTexture)
,m_pRightArmTexture(rhs.m_pRightArmTexture)
,m_pLeftFootTexture(rhs.m_pLeftFootTexture)
,m_pRightFootTexture(rhs.m_pRightFootTexture)
,m_pHeadBuffer(rhs.m_pHeadBuffer)
,m_pBodyBuffer(rhs.m_pBodyBuffer)
,m_pLeftArmBuffer(rhs.m_pLeftArmBuffer)
,m_pRightArmBuffer(rhs.m_pRightArmBuffer)
,m_pLeftFootBuffer(rhs.m_pLeftFootBuffer)
,m_pRightFootBuffer(rhs.m_pRightFootBuffer)
,m_matHeadWorld(rhs.m_matHeadWorld)
,m_matBodyWorld(rhs.m_matBodyWorld)
,m_matRightArmWorld(rhs.m_matRightArmWorld)
,m_matLeftArmWorld(rhs.m_matLeftArmWorld)
,m_matRightFootWorld(rhs.m_matRightFootWorld)
,m_matLeftFootWorld(rhs.m_matLeftFootWorld)
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

	m_vBodyPos = D3DXVECTOR3(0.f, 0.f, 0.f);
	m_vHeadPos = D3DXVECTOR3(m_vBodyPos.x, m_vBodyPos.y + (2.5f * m_fScaleSize), m_vBodyPos.z);
	m_vLeftArmPos = D3DXVECTOR3(m_vBodyPos.x - (1.5f * m_fScaleSize) , m_vBodyPos.y, m_vBodyPos.z);
	m_vRightArmPos = D3DXVECTOR3(m_vBodyPos.x + (1.5f * m_fScaleSize), m_vBodyPos.y, m_vBodyPos.z);
	m_vLeftFootPos = D3DXVECTOR3(m_vBodyPos.x - (0.5f * m_fScaleSize), m_vBodyPos.y - (3.f * m_fScaleSize), m_vBodyPos.z);
	m_vRightFootPos = D3DXVECTOR3(m_vBodyPos.x + (0.5f * m_fScaleSize), m_vBodyPos.y - (3.f * m_fScaleSize), m_vBodyPos.z);

	m_vBodyScale = D3DXVECTOR3(m_fScaleSize * 1.0f, m_fScaleSize *  1.5f, m_fScaleSize * 0.5f);
	m_vHeadScale = D3DXVECTOR3(m_fScaleSize * 1.f, m_fScaleSize * 1.f, m_fScaleSize * 1.f);
	m_vArmScale = D3DXVECTOR3(m_fScaleSize * 0.5f, m_fScaleSize * 1.5f, m_fScaleSize * 0.5f);
	m_vFootScale = D3DXVECTOR3(m_fScaleSize * 0.5f, m_fScaleSize * 1.5f, m_fScaleSize * 0.5f);

	D3DXMatrixTranslation(&m_matHeadWorld, m_vHeadPos.x, m_vHeadPos.y, m_vHeadPos.z);
	D3DXMatrixTranslation(&m_matBodyWorld, m_vBodyPos.x, m_vBodyPos.y, m_vBodyPos.z);
	D3DXMatrixTranslation(&m_matLeftArmWorld, m_vLeftArmPos.x, m_vLeftArmPos.y, m_vLeftArmPos.z);
	D3DXMatrixTranslation(&m_matRightArmWorld, m_vRightArmPos.x, m_vRightArmPos.y, m_vRightArmPos.z);
	D3DXMatrixTranslation(&m_matLeftFootWorld, m_vLeftFootPos.x, m_vLeftFootPos.y, m_vLeftFootPos.z);
	D3DXMatrixTranslation(&m_matRightFootWorld, m_vRightFootPos.x, m_vRightFootPos.y, m_vRightFootPos.z);

	return S_OK;
}

void Engine::CPlayerModel::Update(void)
{

}

void Engine::CPlayerModel::Render(void)
{
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
	m_pDevice->SetTransform(D3DTS_WORLD,&(m_matScale * m_matHeadWorld * matWorld));
	m_pHeadTexture->Render(0,0);
	m_pHeadBuffer->Render();
	D3DXMatrixIdentity(&m_matScale);

	//--------------------------------------LeftArm--------------------------------------

	D3DXMatrixScaling(&m_matScale, m_vArmScale.x ,m_vArmScale.y ,m_vArmScale.z);
	m_pDevice->SetTransform(D3DTS_WORLD,&(m_matScale * m_matLeftArmWorld * matWorld));
	m_pLeftArmTexture->Render(0,0);
	m_pLeftArmBuffer->Render();
	D3DXMatrixIdentity(&m_matScale);

	//--------------------------------------RightArm-------------------------------------

	D3DXMatrixScaling(&m_matScale, m_vArmScale.x ,m_vArmScale.y ,m_vArmScale.z);
	m_pDevice->SetTransform(D3DTS_WORLD,&(m_matScale * m_matRightArmWorld * matWorld));
	m_pRightArmTexture->Render(0,0);
	m_pRightArmBuffer->Render();
	D3DXMatrixIdentity(&m_matScale);

	//--------------------------------------LeftFoot-------------------------------------

	D3DXMatrixScaling(&m_matScale, m_vFootScale.x ,m_vFootScale.y ,m_vFootScale.z);
	m_pDevice->SetTransform(D3DTS_WORLD,&(m_matScale * m_matLeftFootWorld * matWorld));
	m_pLeftFootTexture->Render(0,0);
	m_pLeftFootBuffer->Render();
	D3DXMatrixIdentity(&m_matScale);

	//--------------------------------------RightFoot------------------------------------

	D3DXMatrixScaling(&m_matScale, m_vFootScale.x ,m_vFootScale.y ,m_vFootScale.z);
	m_pDevice->SetTransform(D3DTS_WORLD,&(m_matScale * m_matRightFootWorld * matWorld));
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
