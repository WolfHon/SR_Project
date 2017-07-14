#include "stdafx.h"
#include "Stage.h"

#include "Export_Function.h"
#include "Layer.h"

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
	
	m_mapLayer.insert(MAPLAYER::value_type(LAYER_GAMELOGIC, pLayer));

	return S_OK;
}

HRESULT CStage::Add_UI_Layer(void)
{
	Engine::CLayer*			pLayer = Engine::CLayer::Create();
	
	m_mapLayer.insert(MAPLAYER::value_type(LAYER_UI, pLayer));

	return S_OK;
}

