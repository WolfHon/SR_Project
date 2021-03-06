#include "stdafx.h"
#include "Stage.h"

#include "Export_Function.h"
#include "Layer.h"

#include "Skybox.h"
#include "Player.h"
#include "CameraControl.h"

#include "Transform.h"

#include "Cube.h"
#include "Slope.h"
#include "Monster.h"
#include "ItemUi.h"

#include "Item.h"
#include "PowerUI.h"
#include "ShoseUI.h"
#include "Number1.h"
#include "ShoseNum.h"
#include "PowerNum.h"
#include "AddBombNum.h"
#include "Crosshair.h"
#include "PressedUIbar.h"
#include "PressedUI.h"
#include "SoundMgr.h"


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
		, Engine::TEXTURE_NORMAL, L"Bomb"
		, L"../bin/Texture/Bomb/Bomb%d.png", 2);
	FAILED_CHECK(hr);

	hr = Engine::Get_ResourceMgr()->AddTexture(m_pDevice, Engine::RESOURCE_DYNAMIC
		, Engine::TEXTURE_NORMAL, L"Texture_Explosion"
		, L"../bin/Texture/Effect/Explosion/Explosion%d.png", 40);
	FAILED_CHECK(hr);

	hr = Engine::Get_ResourceMgr()->AddTexture(m_pDevice, Engine::RESOURCE_DYNAMIC
		, Engine::TEXTURE_NORMAL, L"Texture_Bomb"
		, L"../bin/Texture/item/bomb/Bomb%d.png", 3);
	FAILED_CHECK(hr);

	hr = Engine::Get_ResourceMgr()->AddTexture(m_pDevice, Engine::RESOURCE_DYNAMIC
		, Engine::TEXTURE_CUBE, L"Texture_Skybox"
		, L"../bin/Texture/SkyBox/Skybox.dds", 1);
	FAILED_CHECK(hr);

	hr = Engine::Get_ResourceMgr()->AddTexture(m_pDevice, Engine::RESOURCE_DYNAMIC
		, Engine::TEXTURE_NORMAL, L"Texture_Num"
		, L"../bin/Texture/Number/Num%d.png", 12);
	FAILED_CHECK(hr);

	hr = Engine::Get_ResourceMgr()->AddTexture(m_pDevice, Engine::RESOURCE_DYNAMIC
		, Engine::TEXTURE_NORMAL, L"Texture_Crosshair"
		, L"../bin/Texture/Crosshair/crosshair%d.png", 1);
	FAILED_CHECK(hr);

	hr = Engine::Get_ResourceMgr()->AddTexture(m_pDevice, Engine::RESOURCE_DYNAMIC
		, Engine::TEXTURE_NORMAL, L"Gaugebar"
		, L"../bin/Texture/UI/gaugebar%d.png", 2);
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

	hr = Engine::Get_ResourceMgr()->AddBuffer(m_pDevice, Engine::RESOURCE_DYNAMIC
		, Engine::BUFFER_SPHERETEX, L"Buffer_SphereTex");
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

	Engine::CGameObject* pPlayer = iter->second->GetObject(L"Player");

	pGameObject = CCameraControl::Create(m_pDevice, pPlayer
		, dynamic_cast<const Engine::CTransform*>(pComponent));
	dynamic_cast<CCameraControl*>(pGameObject)->SetCamera(CCameraControl::CAM_FIRST);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);

	pLayer->AddObject(L"CameraControl", pGameObject);
	
	pGameObject = CItemUi::Create(m_pDevice, D3DXVECTOR3(560.f, -230.f, 0.f));
	NULL_CHECK_RETURN(pGameObject,E_FAIL);

	pLayer->AddObject(L"ItemUi", pGameObject);

	pGameObject = CPowerUI::Create(m_pDevice, D3DXVECTOR3(560.f, -160.f, 0.f));
	NULL_CHECK_RETURN(pGameObject,E_FAIL);

	pLayer->AddObject(L"ItemUi", pGameObject);

	pGameObject = CShoseUI::Create(m_pDevice, D3DXVECTOR3(560.f, -300.f, 0.f));
	NULL_CHECK_RETURN(pGameObject,E_FAIL);

	pLayer->AddObject(L"ItemUi", pGameObject);

	pGameObject = CNumber1::Create(m_pDevice, D3DXVECTOR3(505.f, -180.f , 0.f));
	NULL_CHECK_RETURN(pGameObject,E_FAIL);

	pLayer->AddObject(L"ItemUi", pGameObject);

	pGameObject = CNumber1::Create(m_pDevice, D3DXVECTOR3(505.f, -240.f , 0.f));
	NULL_CHECK_RETURN(pGameObject,E_FAIL);

	pLayer->AddObject(L"ItemUi", pGameObject);

	pGameObject = CNumber1::Create(m_pDevice, D3DXVECTOR3(505.f, -310.f , 0.f));
	NULL_CHECK_RETURN(pGameObject,E_FAIL);

	pLayer->AddObject(L"ItemUi", pGameObject);

	pGameObject = CShoseNum::Create(m_pDevice, D3DXVECTOR3(475.f, -170.f , 0.f));
	NULL_CHECK_RETURN(pGameObject,E_FAIL);

	pLayer->AddObject(L"ShoseNum", pGameObject);

	pGameObject = CPowerNum::Create(m_pDevice, D3DXVECTOR3(475.f, -230.f , 0.f));
	NULL_CHECK_RETURN(pGameObject,E_FAIL);

	pLayer->AddObject(L"PowerNum", pGameObject);

	pGameObject = CAddBombNum::Create(m_pDevice, D3DXVECTOR3(475.f, -300.f , 0.f));
	NULL_CHECK_RETURN(pGameObject,E_FAIL);

	pLayer->AddObject(L"AddBombNum", pGameObject);

	pGameObject = CCrosshair::Create(m_pDevice, D3DXVECTOR3(0.f, 40.f , 0.f));
	NULL_CHECK_RETURN(pGameObject,E_FAIL);

	pLayer->AddObject(L"ItemUi", pGameObject);


	pGameObject = CPressedUI::Create(m_pDevice, D3DXVECTOR3(560.f, 40.f , 0.f));
	NULL_CHECK_RETURN(pGameObject,E_FAIL);

	pLayer->AddObject(L"ItemUi", pGameObject);

	pGameObject = CPressedUIbar::Create(m_pDevice, D3DXVECTOR3(560.f, 40.f , 0.f));
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

	//vector<D3DXVECTOR3> t;

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
			pLayer->AddObject(L"Block", pGameObject);	
		}	
		else if(TileInfo.eTileShape == Engine::TILE_SLOPE)
		{
			pGameObject = CSlope::Create(m_pDevice, TileInfo);
			NULL_CHECK(pGameObject);
			pLayer->AddObject(L"Block", pGameObject);	
		}

		m_mapLayer.insert(MAPLAYER::value_type(Engine::LAYER_GAMELOGIC, pLayer));
	}
	CloseHandle(hFile);
}

