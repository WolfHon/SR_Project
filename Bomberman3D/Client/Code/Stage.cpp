#include "stdafx.h"
#include "Stage.h"

#include "Export_Function.h"
#include "Layer.h"

#include "Skybox.h"
#include "Player.h"
#include "CameraControl.h"

#include "Transform.h"
#include "Collision_OBB.h"

#include "Cube.h" //Test용 임시

CStage::CStage(LPDIRECT3DDEVICE9 pDevice)
: Engine::CScene(pDevice)
{
}

CStage::~CStage(void)
{
	Release();
}

HRESULT CStage::Initialize(void)
{
	HRESULT		hr = NULL;

	//Texture
	hr = Engine::Get_ResourceMgr()->AddTexture(m_pDevice, Engine::RESOURCE_DYNAMIC
		, Engine::TEXTURE_CUBE, L"Texture_Player_Head"
		, L"../bin/Texture/Player1/Player1Head.dds", 1);
	FAILED_CHECK(hr);

	hr = Engine::Get_ResourceMgr()->AddTexture(m_pDevice, Engine::RESOURCE_DYNAMIC
		, Engine::TEXTURE_CUBE, L"Texture_Player_Body"
		, L"../bin/Texture/Player1/Player1Body.dds", 1);
	FAILED_CHECK(hr);

	hr = Engine::Get_ResourceMgr()->AddTexture(m_pDevice, Engine::RESOURCE_DYNAMIC
		, Engine::TEXTURE_CUBE, L"Texture_Player_Foot"
		, L"../bin/Texture/Player1/Player1Foot.dds", 1);
	FAILED_CHECK(hr);

	hr = Engine::Get_ResourceMgr()->AddTexture(m_pDevice, Engine::RESOURCE_DYNAMIC
		, Engine::TEXTURE_CUBE, L"Texture_Player_Arm"
		, L"../bin/Texture/Player1/Player1Arm.dds", 1);
	FAILED_CHECK(hr);

	hr = Engine::Get_ResourceMgr()->AddTexture(m_pDevice, Engine::RESOURCE_DYNAMIC
		, Engine::TEXTURE_CUBE, L"Block"
		, L"../bin/Texture/Block/Block%d.dds", 9);
	FAILED_CHECK(hr);

	hr = Engine::Get_ResourceMgr()->AddTexture(m_pDevice, Engine::RESOURCE_DYNAMIC
		, Engine::TEXTURE_CUBE, L"Texture_Skybox"
		, L"../bin/Texture/SkyBox/Skybox.dds", 1);
	FAILED_CHECK(hr);

	//Buffer
	hr = Engine::Get_ResourceMgr()->AddBuffer(m_pDevice, Engine::RESOURCE_DYNAMIC
		, Engine::BUFFER_CUBETEX, L"Buffer_CubeTex");
	FAILED_CHECK(hr);


	//Model
	hr = Engine::Get_ResourceMgr()->AddBuffer(m_pDevice, Engine::RESOURCE_DYNAMIC
		, Engine::MODEL_PLAYER, L"Model_Player");
	FAILED_CHECK(hr);

	//Collision
	hr = Engine::Get_CollisionMgr()->AddColObject(Engine::COLLISON_OBB);
	FAILED_CHECK(hr);


	FAILED_CHECK(Add_Enviroment_Layer());
	FAILED_CHECK(Add_GameLogic_Layer());
	FAILED_CHECK(Add_UI_Layer());

	return S_OK;
}

void CStage::Update(void)
{
	Engine::CScene::Update();
}

void CStage::Render(void)
{
	Engine::CScene::Render();
}

CStage* CStage::Create(LPDIRECT3DDEVICE9 pDevice)
{
	CStage*	pScene = new CStage(pDevice);
	if(FAILED(pScene->Initialize()))
		Safe_Delete(pScene);

	return pScene;
}

void CStage::Release(void)
{
	
}

HRESULT CStage::Add_Enviroment_Layer(void)
{
	Engine::CLayer*			pLayer = Engine::CLayer::Create();

	Engine::CGameObject*	pGameObject = NULL;

	pGameObject = CSkybox::Create(m_pDevice);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	pLayer->AddObject(L"Skybox", pGameObject);

	m_mapLayer.insert(MAPLAYER::value_type(Engine::LAYER_ENVIROMENT, pLayer));

	return S_OK;
}

HRESULT CStage::Add_GameLogic_Layer(void)
{
	Engine::CLayer*			pLayer = Engine::CLayer::Create();

	Engine::CGameObject*	pGameObject = NULL;
	
	pGameObject = CPlayer::Create(m_pDevice);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	pLayer->AddObject(L"Player", pGameObject);

	//Test용 임시
	for(int i = 0; i < 30; ++i)
	{
		//pGameObject = CCube::Create(m_pDevice, );
		//NULL_CHECK_RETURN(pGameObject, E_FAIL);
		//pLayer->AddObject(L"UnBroken_Box", pGameObject);
	}
	//LoadData(pLayer,pGameObject);
	
	m_mapLayer.insert(MAPLAYER::value_type(Engine::LAYER_GAMELOGIC, pLayer));

	return S_OK;
}

HRESULT CStage::Add_UI_Layer(void)
{
	Engine::CLayer*			pLayer = Engine::CLayer::Create();

	Engine::CGameObject*	pGameObject = NULL;

	MAPLAYER::iterator iter = m_mapLayer.find(Engine::LAYER_GAMELOGIC);
	if(iter == m_mapLayer.end())
		return E_FAIL;

	const Engine::CComponent*	pComponent = iter->second->GetComponent(L"Player", L"Transform");
	NULL_CHECK_RETURN(pComponent, E_FAIL);

	pGameObject = CCameraControl::Create(m_pDevice
		, dynamic_cast<const Engine::CTransform*>(pComponent));
	dynamic_cast<CCameraControl*>(pGameObject)->SetCamera(CCameraControl::CAM_FIRST);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);

	pLayer->AddObject(L"CameraControl", pGameObject);
	
	m_mapLayer.insert(MAPLAYER::value_type(Engine::LAYER_UI, pLayer));

	return S_OK;
}

void CStage::LoadData(Engine::CLayer* pLayer , Engine::CGameObject*	pGameObject)
{
	DWORD dwByte = 0;

	HANDLE hFile = CreateFile(L"../../Data/STAGE1.dat", GENERIC_READ, 0, 0, OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL, NULL);

	while(1)
	{
		Engine::TILEINFO* pTileInfo = new Engine::TILEINFO;

		ReadFile(hFile , pTileInfo, sizeof(Engine::TILEINFO), &dwByte, NULL);

		if(dwByte == 0)
		{
			Engine::Safe_Delete(pTileInfo);
			break;
		}
		if(pTileInfo->eTileShape == Engine::TILE_CUBE)
		pGameObject = CCube::Create(m_pDevice, (*pTileInfo));
		pLayer->AddObject(L"Terrain", pGameObject);
		
		m_mapLayer.insert(MAPLAYER::value_type(Engine::LAYER_GAMELOGIC, pLayer));

		Engine::Safe_Delete(pTileInfo);

	}
	CloseHandle(hFile);

}

