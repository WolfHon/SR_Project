#include "stdafx.h"
#include "Stage.h"

#include "Export_Function.h"
#include "Include.h"
#include "Terrain.h"
#include "Layer.h"
#include "GameObject.h"
#include "Player.h"
#include "StaticCamera.h"
#include "..\..\Engine\Utility\Code\Transform.h"
#include "Monster.h"
#include "TerrainCol.h"
#include "..\..\Engine\Utility\Code\MouseCol.h"
#include "Cube.h"

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
		, Engine::TEXTURE_NORMAL, L"Texture_TerrainTex"
		, L"../bin/Texture/Terrain/Terrain%d.png", 1);
	FAILED_CHECK(hr);

	hr = Engine::Get_ResourceMgr()->AddTexture(m_pDevice, Engine::RESOURCE_DYNAMIC
		, Engine::TEXTURE_CUBE, L"Texture_Cube"
		, L"../bin/Texture/Cube%d.dds", 1);
	FAILED_CHECK(hr);

	hr = Engine::Get_ResourceMgr()->AddTexture(m_pDevice, Engine::RESOURCE_DYNAMIC
		, Engine::TEXTURE_NORMAL, L"Texture_Player"
		, L"../bin/Texture/Player.png", 1);
	FAILED_CHECK(hr);

	hr = Engine::Get_ResourceMgr()->AddTexture(m_pDevice, Engine::RESOURCE_DYNAMIC
		, Engine::TEXTURE_NORMAL, L"Texture_Monster"
		, L"../bin/Texture/Monster%d.png", 1);
	FAILED_CHECK(hr);

	//Buffer
	hr = Engine::Get_ResourceMgr()->AddBuffer(m_pDevice, Engine::RESOURCE_DYNAMIC
		, Engine::BUFFER_TERRAINTEX, L"Buffer_TerrainTex"
		, VTXCNTX, VTXCNTZ, VTXITV);
	FAILED_CHECK(hr);

	hr = Engine::Get_ResourceMgr()->AddBuffer(m_pDevice, Engine::RESOURCE_DYNAMIC
		, Engine::BUFFER_CUBETEX, L"Buffer_CubeTex");
	FAILED_CHECK(hr);

	hr = Engine::Get_CollisionMgr()->AddColObject(Engine::COLLISON_TERRAIN
		, Engine::CTerrainCol::Create());
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
	return S_OK;
}

HRESULT CStage::Add_GameLogic_Layer(void)
{
	Engine::CLayer*			pLayer = Engine::CLayer::Create();
	Engine::CGameObject*	pGameObject = NULL;

	pGameObject = CTerrain::Create(m_pDevice);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	pLayer->AddObject(L"Terrain", pGameObject);
	const Engine::VTXTEX* pTerrainVtx = ((CTerrain*)pGameObject)->GetTerrainVtx();
	Engine::Get_CollisionMgr()->AddColObject(Engine::COLLISON_MOUSE
		, Engine::CMouseCol::Create(g_hWnd, pTerrainVtx));

	pGameObject = CPlayer::Create(m_pDevice);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	pLayer->AddObject(L"Player", pGameObject);

	for(int i = 0; i < 30; ++i)
	{
		pGameObject = CMonster::Create(m_pDevice);
		NULL_CHECK_RETURN(pGameObject, E_FAIL);
		pLayer->AddObject(L"Monster", pGameObject);
	}

	for(int i = 0; i < 30; ++i)
	{
		pGameObject = CCube::Create(m_pDevice);
		NULL_CHECK_RETURN(pGameObject, E_FAIL);
		pLayer->AddObject(L"Cube", pGameObject);
	}

	m_mapLayer.insert(MAPLAYER::value_type(LAYER_GAMELOGIC, pLayer));
	return S_OK;
}

HRESULT CStage::Add_UI_Layer(void)
{
	Engine::CLayer*			pLayer = Engine::CLayer::Create();
	Engine::CGameObject*	pGameObject = NULL;

	MAPLAYER::iterator iter = m_mapLayer.find(LAYER_GAMELOGIC);
	if(iter == m_mapLayer.end())
		return E_FAIL;

	const Engine::CComponent*	pComponent = iter->second->GetComponent(L"Player", L"Transform");
	NULL_CHECK_RETURN(pComponent, E_FAIL);

	pGameObject = CStaticCamera::Create(m_pDevice
		, dynamic_cast<const Engine::CTransform*>(pComponent));
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	pLayer->AddObject(L"StaticCamera", pGameObject);

	m_mapLayer.insert(MAPLAYER::value_type(LAYER_UI, pLayer));
	return S_OK;
}

