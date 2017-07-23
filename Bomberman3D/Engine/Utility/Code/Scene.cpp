#include "Scene.h"

#include "Layer.h"

Engine::CScene::CScene(LPDIRECT3DDEVICE9 pDevice)
: m_pDevice(pDevice)
{
}

Engine::CScene::~CScene(void)
{
	Release();
}

HRESULT Engine::CScene::InitScene(void)
{
	return S_OK;
}

void Engine::CScene::Update(void)
{
	MAPLAYER::iterator		iter = m_mapLayer.begin();
	MAPLAYER::iterator		iter_end = m_mapLayer.end();

	for(; iter != iter_end; ++iter)
		iter->second->Update();
}

void Engine::CScene::Render(void)
{
	MakePlane();

	MAPLAYER::iterator		iter = m_mapLayer.begin();
	MAPLAYER::iterator		iter_end = m_mapLayer.end();

	for(; iter != iter_end; ++iter)
		iter->second->Render(m_plane, (iter->first == FALSE));//LAYER_GAMELOGIC ? TRUE : FALSE));
}

void Engine::CScene::Release(void)
{
	for_each(m_mapLayer.begin(), m_mapLayer.end(), CDeleteMap());
	m_mapLayer.clear();
}

const Engine::CComponent* Engine::CScene::GetComponent(const WORD& LayerID, const wstring& wstrObjKey, const wstring& wstrComponentKey)
{
	MAPLAYER::iterator	iter = m_mapLayer.find(LayerID);
	if(iter == m_mapLayer.end())
		return NULL;

	return iter->second->GetComponent(wstrObjKey, wstrComponentKey);
}

Engine::CGameObject* Engine::CScene::GetObject(const WORD& LayerID, const wstring& wstrObjKey)
{
	MAPLAYER::iterator	iter = m_mapLayer.find(LayerID);
	if(iter == m_mapLayer.end())
		return NULL;

	return iter->second->GetObject(wstrObjKey);
}

Engine::OBJLIST* Engine::CScene::GetObjectList(const WORD& LayerID, const wstring& wstrObjKey)
{
	MAPLAYER::iterator	iter = m_mapLayer.find(LayerID);
	if(iter == m_mapLayer.end())
		return NULL;

	return iter->second->GetObjectList(wstrObjKey);
}

void Engine::CScene::MakePlane(void)
{
	int				i;
	D3DXMATRIX	matInv;
	D3DXMATRIX	matView;
	m_pDevice->GetTransform(D3DTS_VIEW, &matView);
	D3DXMATRIX	matProj;
	m_pDevice->GetTransform(D3DTS_PROJECTION, &matProj);
	D3DXMATRIX	matViewProj = matView * matProj;

	m_vtx[0].x = -1.0f;	m_vtx[0].y = -1.0f;	m_vtx[0].z = 0.0f;
	m_vtx[1].x =  1.0f;	m_vtx[1].y = -1.0f;	m_vtx[1].z = 0.0f;
	m_vtx[2].x =  1.0f;	m_vtx[2].y = -1.0f;	m_vtx[2].z = 1.0f;
	m_vtx[3].x = -1.0f;	m_vtx[3].y = -1.0f;	m_vtx[3].z = 1.0f;
	m_vtx[4].x = -1.0f;	m_vtx[4].y =  1.0f;	m_vtx[4].z = 0.0f;
	m_vtx[5].x =  1.0f;	m_vtx[5].y =  1.0f;	m_vtx[5].z = 0.0f;
	m_vtx[6].x =  1.0f;	m_vtx[6].y =  1.0f;	m_vtx[6].z = 1.0f;
	m_vtx[7].x = -1.0f;	m_vtx[7].y =  1.0f;	m_vtx[7].z = 1.0f;

	D3DXMatrixInverse(&matInv, NULL, &matViewProj);

	for( i = 0; i < 8; i++ )
		D3DXVec3TransformCoord(&m_vtx[i], &m_vtx[i], &matInv);

	D3DXPlaneFromPoints(&m_plane[0], m_vtx+4, m_vtx+7, m_vtx+6);	// 상 평면(top)
	D3DXPlaneFromPoints(&m_plane[1], m_vtx  , m_vtx+1, m_vtx+2);	// 하 평면(bottom)
	D3DXPlaneFromPoints(&m_plane[2], m_vtx  , m_vtx+4, m_vtx+5);	// 근 평면(near)
	D3DXPlaneFromPoints(&m_plane[3], m_vtx+2, m_vtx+6, m_vtx+7);	// 원 평면(far)	
	D3DXPlaneFromPoints(&m_plane[4], m_vtx  , m_vtx+3, m_vtx+7);	// 좌 평면(left)	
	D3DXPlaneFromPoints(&m_plane[5], m_vtx+1, m_vtx+5, m_vtx+6);	// 우 평면(right)	
}

HRESULT Engine::CScene::AddObject(const WORD& LayerID, const wstring& wstrObjKey, CGameObject* pGameObject)
{
	MAPLAYER::iterator	iter = m_mapLayer.find(LayerID);
	if(iter == m_mapLayer.end())
		return NULL;

	return iter->second->AddObject(wstrObjKey, pGameObject);
}
