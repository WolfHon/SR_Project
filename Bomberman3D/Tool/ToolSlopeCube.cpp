#include "stdafx.h"
#include "ToolSlopeCube.h"
#include "RcTex.h"

#include "Texture.h"
#include "Include.h"
#include "Transform.h"
#include "Engine_Include.h"
#include "Export_Function.h"


CToolSlopeCube::CToolSlopeCube( LPDIRECT3DDEVICE9 pDevice , Engine::TILEINFO _tileInfo )
:Engine::CGameObject(pDevice)
, m_pTexture(NULL)
, m_pBuffer(NULL)
, m_fSpeed(0.f)
, m_fAngle(0.f)
, m_pInfo(NULL)
, m_pTerrainCol(NULL)
, m_eTexture(Engine::TILE_IMAGE0)
, m_eTileOption(Engine::TILE_UNBROKEN)
, m_TileInfo(_tileInfo)
{
	

}

CToolSlopeCube::~CToolSlopeCube( void )
{

		Release();
}

Engine::OBJECT_RESULT CToolSlopeCube::Update( void )
{
	D3DXMATRIX matTrans;
	D3DXMATRIX matScale;
	D3DXMATRIX matRotY;

 	m_pInfo->m_vPos = m_TileInfo.vPos;
	m_pInfo->m_vScale = m_TileInfo.vScale;

	D3DXMatrixRotationY(&matRotY,m_TileInfo.fAngle);
	D3DXVec3TransformNormal(&m_pInfo->m_vDir, &g_vLook, &m_pInfo->m_matWorld);
	D3DXMatrixScaling(&matScale, m_pInfo->m_vScale.x , m_pInfo->m_vScale.y, m_pInfo->m_vScale.z);
	D3DXMatrixTranslation(&matTrans, m_pInfo->m_vPos.x, m_pInfo->m_vPos.y, m_pInfo->m_vPos.z);

	m_pInfo->m_matWorld =matScale * matRotY * matTrans;

	return Engine::CGameObject::Update();	
}

void CToolSlopeCube::Render( void )
{

	//m_pBuffer->SetVtxInfo(m_pConvertVertex);
	m_pDevice->SetTransform(D3DTS_WORLD, &m_pInfo->m_matWorld);
	
	/*m_pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	m_pDevice->SetRenderState(D3DRS_ALPHAREF, 0x00000088);
	m_pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);*/

	m_pTexture->Render(0, m_TileInfo.eTexture);
	m_pBuffer->Render();

	//m_pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	/*m_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);*/

	m_pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	//m_pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
		
}

CToolSlopeCube* CToolSlopeCube::Create( LPDIRECT3DDEVICE9 pDevice, Engine::TILEINFO _tileInfo )
{
	CToolSlopeCube*	pGameObject = new CToolSlopeCube(pDevice , _tileInfo );
	if(FAILED(pGameObject->Initialize(_tileInfo)))
		Safe_Delete(pGameObject);

	return pGameObject;

}

HRESULT CToolSlopeCube::Initialize( Engine::TILEINFO _tileInfo )
{
	FAILED_CHECK(AddComponent());

	Engine::TILEINFO* pTile = new Engine::TILEINFO;

	//m_TileInfo.vPos = _tileInfo.vPos;
	//m_TileInfo.vScale = _tileInfo.vScale;
	//m_TileInfo.fAngle = _tileInfo.fAngle;
	//m_TileInfo.eTexture = _tileInfo.eTexture;
	//m_TileInfo.eTileOption = _tileInfo.eTileOption;
	//m_TileInfo.eTileShape = Engine::TILE_SLOPE;

	

	//m_pInfo->m_vPos = D3DXVECTOR3(float(rand() % VTXCNTX), 0.f, float(rand() % VTXCNTZ));

	//	m_dwVtxCnt = 8;
	//m_pVertex = new Engine::VTXCUBE[m_dwVtxCnt];
	//m_pConvertVertex = new Engine::VTXCUBE[m_dwVtxCnt];
	//m_pBuffer->GetVtxInfo(m_pVertex);

	return S_OK;
}

HRESULT CToolSlopeCube::AddComponent( )
{

		Engine::CComponent*		pComponent = NULL;

		////Transform
		pComponent = m_pInfo = Engine::CTransform::Create(g_vLook);
		NULL_CHECK_RETURN(m_pInfo, E_FAIL);
		//m_mapComponent.insert(MAPCOMPONENT::value_type(L"Transform", pComponent));

		////Texture
		pComponent = Engine::Get_ResourceMgr()->CloneResource(Engine::RESOURCE_DYNAMIC, L"BreakCube");
		m_pTexture = dynamic_cast<Engine::CTexture*>(pComponent);
		NULL_CHECK_RETURN(m_pTexture, E_FAIL);
		m_mapComponent.insert(MAPCOMPONENT::value_type(L"Texture", pComponent));	

		//Buffer
		pComponent = Engine::Get_ResourceMgr()->CloneResource(Engine::RESOURCE_DYNAMIC, L"Buffer_SlopeTex");
		m_pBuffer = dynamic_cast<Engine::CVIBuffer*>(pComponent);
		NULL_CHECK_RETURN(m_pBuffer, E_FAIL);
		m_mapComponent.insert(MAPCOMPONENT::value_type(L"Buffer", pComponent));

		////TerrainCol
		//pComponent = Engine::Get_CollisionMgr()->GetColObject(Engine::COLLISON_TERRAIN);
		//m_pTerrainCol = dynamic_cast<Engine::CTerrainCol*>(pComponent);
		//NULL_CHECK_RETURN(m_pTerrainCol, E_FAIL);
		//m_mapComponent.insert(MAPCOMPONENT::value_type(L"TerrainCol", pComponent));
		return S_OK;

}

void CToolSlopeCube::Release( void )
{

//	Safe_Delete_Array(m_pVertex);
//	Safe_Delete_Array(m_pConvertVertex);

}
