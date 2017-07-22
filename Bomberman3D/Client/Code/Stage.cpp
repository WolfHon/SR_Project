#include "stdafx.h"
#include "Stage.h"

#include "Export_Function.h"
#include "Layer.h"

#include "Skybox.h"
#include "Player.h"
#include "CameraControl.h"

#include "Transform.h"

#include "Cube.h"
#include "Monster.h"
#include "ItemUi.h"

#include "Item.h"

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
		, Engine::TEXTURE_CUBE, L"Bomb"
		, L"../bin/Texture/bomb/bomb%d.dds", 2);
	FAILED_CHECK(hr);

	hr = Engine::Get_ResourceMgr()->AddTexture(m_pDevice, Engine::RESOURCE_DYNAMIC
		, Engine::TEXTURE_NORMAL, L"Texture_Explosion"
		, L"../bin/Texture/Effect/Explosion/Explosion%d.png", 48);
	FAILED_CHECK(hr);

	hr = Engine::Get_ResourceMgr()->AddTexture(m_pDevice, Engine::RESOURCE_DYNAMIC
		, Engine::TEXTURE_NORMAL, L"Texture_Bomb"
		, L"../bin/Texture/item/bomb/Bomb%d.png", 1);
	FAILED_CHECK(hr);

	hr = Engine::Get_ResourceMgr()->AddTexture(m_pDevice, Engine::RESOURCE_DYNAMIC
		, Engine::TEXTURE_NORMAL, L"Texture_Fire"
		, L"../bin/Texture/item/fire/Fire%d.png", 1);
	FAILED_CHECK(hr);
	hr = Engine::Get_ResourceMgr()->AddTexture(m_pDevice, Engine::RESOURCE_DYNAMIC
		, Engine::TEXTURE_NORMAL, L"Texture_Shoes"
		, L"../bin/Texture/item/shoes/shoes%d.png", 1);
	FAILED_CHECK(hr);

	hr = Engine::Get_ResourceMgr()->AddTexture(m_pDevice, Engine::RESOURCE_DYNAMIC
		, Engine::TEXTURE_CUBE, L"Texture_Skybox"
		, L"../bin/Texture/SkyBox/Skybox.dds", 1);
	FAILED_CHECK(hr);

	//Buffer
	hr = Engine::Get_ResourceMgr()->AddBuffer(m_pDevice, Engine::RESOURCE_DYNAMIC
		, Engine::BUFFER_CUBETEX, L"Buffer_CubeTex");
	FAILED_CHECK(hr);

	hr = Engine::Get_ResourceMgr()->AddBuffer(m_pDevice, Engine::RESOURCE_DYNAMIC
		, Engine::BUFFER_SLOPETEX, L"Buffer_SlopeTex");
	FAILED_CHECK(hr);

	hr = Engine::Get_ResourceMgr()->AddBuffer(m_pDevice, Engine::RESOURCE_DYNAMIC
		, Engine::BUFFER_RCTEX, L"Buffer_RCTex");
	FAILED_CHECK(hr);

	//Model
	hr = Engine::Get_ResourceMgr()->AddBuffer(m_pDevice, Engine::RESOURCE_DYNAMIC
		, Engine::MODEL_PLAYER, L"Model_Player");
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
	Engine::CLayer*			pLayer = Engine::CLayer::Create(m_pDevice);

	Engine::CGameObject*	pGameObject = NULL;

	pGameObject = CSkybox::Create(m_pDevice);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	pLayer->AddObject(L"Skybox", pGameObject);

	m_mapLayer.insert(MAPLAYER::value_type(Engine::LAYER_ENVIROMENT, pLayer));

	return S_OK;
}

HRESULT CStage::Add_GameLogic_Layer(void)
{
	Engine::CLayer*			pLayer = Engine::CLayer::Create(m_pDevice);

	Engine::CGameObject*	pGameObject = NULL;

	/*pGameObject = CItem::Create(m_pDevice, D3DXVECTOR3(6.f, 3.f, 12.f), Engine::ITEM_POWER);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	pLayer->AddObject(L"Item", pGameObject);

	pGameObject = CMonster::Create(m_pDevice);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	pLayer->AddObject(L"Monster", pGameObject);*/

	LoadData(pLayer,pGameObject);
	
	m_mapLayer.insert(MAPLAYER::value_type(Engine::LAYER_GAMELOGIC, pLayer));

	return S_OK;
}

HRESULT CStage::Add_UI_Layer(void)
{
	Engine::CLayer*			pLayer = Engine::CLayer::Create(m_pDevice);

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

		pGameObject = CItemUi::Create(m_pDevice, D3DXVECTOR3(10.f, 0.f , 0.f));
	NULL_CHECK_RETURN(pGameObject,E_FAIL);

	pLayer->AddObject(L"ItemUi", pGameObject);
	
	m_mapLayer.insert(MAPLAYER::value_type(Engine::LAYER_UI, pLayer));

	return S_OK;
}

void CStage::LoadData(Engine::CLayer* pLayer , Engine::CGameObject*	pGameObject)
{
	DWORD dwByte = 0;

	HANDLE hFile = CreateFile(L"../../Data/STAGE3.dat", GENERIC_READ, 0, 0, OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL, NULL);

	vector<D3DXVECTOR3> t;

	while(1)
	{
		Engine::TILEINFO TileInfo;

		ReadFile(hFile , &TileInfo, sizeof(Engine::TILEINFO), &dwByte, NULL);

		if(dwByte == 0)
		{
			break;
		}

		//for(size_t i = 0; i<t.size(); ++i)
		//{
		//	if(t[i] == TileInfo.vPos)
		//		int t = 0;
		//}

		/*t.push_back(TileInfo.vPos);*/

		if(TileInfo.eTileOption == Engine::TILE_START)
		{
			pGameObject = CPlayer::Create(m_pDevice, TileInfo.vPos);
			NULL_CHECK(pGameObject);
			pLayer->AddObject(L"Player", pGameObject);
		}
		else if(TileInfo.eTileShape == Engine::TILE_CUBE )
		{
			pGameObject = CCube::Create(m_pDevice, TileInfo);
			NULL_CHECK(pGameObject);
			pLayer->AddObject(L"Block_Cube", pGameObject);	
		}			

		m_mapLayer.insert(MAPLAYER::value_type(Engine::LAYER_GAMELOGIC, pLayer));
	}
	CloseHandle(hFile);
}

