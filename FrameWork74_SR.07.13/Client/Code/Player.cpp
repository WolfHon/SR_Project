#include "stdafx.h"
#include "Player.h"
#include "Texture.h"
#include "RcTex.h"

#include "Include.h"
#include "Transform.h"
#include "Export_Function.h"
#include "TerrainCol.h"
#include "CameraObserver.h"
#include "Pipeline.h"
#include "MouseCol.h"

CPlayer::CPlayer(LPDIRECT3DDEVICE9 pDevice)
: Engine::CGameObject(pDevice)
, m_pTexture(NULL)
, m_pBuffer(NULL)
, m_fSpeed(0.f)
, m_fAngle(0.f)
, m_pInfo(NULL)
, m_pTerrainCol(NULL)
, m_pVertex(NULL)
, m_pConvertVertex(NULL)
, m_dwVtxCnt(0)
, m_vDestPos(0.f, 0.f, 0.f)
, m_bMove(false)
{

}

CPlayer::~CPlayer(void)
{
	Release();
}

HRESULT CPlayer::Initialize(void)
{
	FAILED_CHECK(AddComponent());

	m_dwVtxCnt = 4;
	m_pVertex = new Engine::VTXTEX[m_dwVtxCnt];
	m_pConvertVertex = new Engine::VTXTEX[m_dwVtxCnt];
	m_pBuffer->GetVtxInfo(m_pVertex);

	m_pCamObserver = CCameraObserver::Create();
	Engine::Get_InfoSubject()->Subscribe(m_pCamObserver);

	m_fSpeed = 10.f;
	return S_OK;
}

void CPlayer::Update(void)
{
	D3DXVec3TransformNormal(&m_pInfo->m_vDir, &g_vLook, &m_pInfo->m_matWorld);
	KeyCheck();

	m_pTerrainCol->SetColInfo(&m_pInfo->m_vPos);

	/*D3DXIntersectTri();*/

	if(m_bMove)
		Move();

	Engine::CGameObject::Update();

	const LPD3DXMATRIX		pmatView = m_pCamObserver->GetCamMatrix(MATRIX_VIEW);
	const LPD3DXMATRIX		pmatProj = m_pCamObserver->GetCamMatrix(MATRIX_PROJECTION);

	for(DWORD i = 0; i < m_dwVtxCnt; ++i)
	{
		m_pConvertVertex[i] = m_pVertex[i];
		Engine::CPipeline::MyTransformCoord(&m_pConvertVertex[i].vPos, &m_pConvertVertex[i].vPos, &m_pInfo->m_matWorld);
		Engine::CPipeline::MyTransformCoord(&m_pConvertVertex[i].vPos, &m_pConvertVertex[i].vPos, pmatView);
		if(m_pConvertVertex[i].vPos.z < 0.f)
			m_pConvertVertex[i].vPos.z = 0.f;
		Engine::CPipeline::MyTransformCoord(&m_pConvertVertex[i].vPos, &m_pConvertVertex[i].vPos, pmatProj);
	}
}

void CPlayer::Render(void)
{
	m_pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	/*m_pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);*/

	//m_pDevice->SetTransform(D3DTS_WORLD, &m_pInfo->m_matWorld);
	m_pBuffer->SetVtxInfo(m_pConvertVertex);

	m_pTexture->Render(0, 0);
	m_pBuffer->Render();

	m_pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	/*m_pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);*/
}

CPlayer* CPlayer::Create(LPDIRECT3DDEVICE9 pDevice)
{
	CPlayer*	pGameObject = new CPlayer(pDevice);
	if(FAILED(pGameObject->Initialize()))
		Safe_Delete(pGameObject);

	return pGameObject;
}

void CPlayer::Release(void)
{
	Safe_Delete_Array(m_pVertex);
	Safe_Delete_Array(m_pConvertVertex);
	Safe_Delete(m_pCamObserver);
}

HRESULT CPlayer::AddComponent(void)
{
	Engine::CComponent*		pComponent = NULL;

	//Transform
	pComponent = m_pInfo = Engine::CTransform::Create(g_vLook);
	NULL_CHECK_RETURN(m_pInfo, E_FAIL);
	m_mapComponent.insert(MAPCOMPONENT::value_type(L"Transform", pComponent));

	//Texture
	pComponent = Engine::Get_ResourceMgr()->CloneResource(Engine::RESOURCE_DYNAMIC, L"Texture_Player");
	m_pTexture = dynamic_cast<Engine::CTexture*>(pComponent);
	NULL_CHECK_RETURN(m_pTexture, E_FAIL);
	m_mapComponent.insert(MAPCOMPONENT::value_type(L"Texture", pComponent));

	//Buffer
	pComponent = Engine::Get_ResourceMgr()->CloneResource(Engine::RESOURCE_STATIC, L"Buffer_RcTex");
	m_pBuffer = dynamic_cast<Engine::CVIBuffer*>(pComponent);
	NULL_CHECK_RETURN(m_pBuffer, E_FAIL);
	m_mapComponent.insert(MAPCOMPONENT::value_type(L"Buffer", pComponent));

	pComponent = Engine::Get_CollisionMgr()->GetColObject(Engine::COLLISON_TERRAIN);
	m_pTerrainCol = dynamic_cast<Engine::CTerrainCol*>(pComponent);
	NULL_CHECK_RETURN(m_pTerrainCol, E_FAIL);
	m_mapComponent.insert(MAPCOMPONENT::value_type(L"TerrainCol", pComponent));

	pComponent = Engine::Get_CollisionMgr()->GetColObject(Engine::COLLISON_MOUSE);
	m_pMouseCol = dynamic_cast<Engine::CMouseCol*>(pComponent);
	NULL_CHECK_RETURN(m_pMouseCol, E_FAIL);
	m_mapComponent.insert(MAPCOMPONENT::value_type(L"MouseCol", pComponent));
	return S_OK;
}

void CPlayer::KeyCheck(void)
{
	if(GetAsyncKeyState('A'))
		m_pInfo->m_fAngle[Engine::ANGLE_Y] -= D3DXToRadian(90.f) * Engine::Get_TimeMgr()->GetTime();

	if(GetAsyncKeyState('D'))
		m_pInfo->m_fAngle[Engine::ANGLE_Y] += D3DXToRadian(90.f) * Engine::Get_TimeMgr()->GetTime();

	if(GetAsyncKeyState('W'))
		m_pInfo->m_vPos += m_pInfo->m_vDir * m_fSpeed * Engine::Get_TimeMgr()->GetTime();

	if(GetAsyncKeyState('S'))
		m_pInfo->m_vPos -= m_pInfo->m_vDir * m_fSpeed * Engine::Get_TimeMgr()->GetTime();

	if(GetAsyncKeyState(VK_LBUTTON))
	{
		/*m_bMove = true;
		m_pMouseCol->PickTerrain(&m_vDestPos
			, m_pCamObserver->GetCamMatrix(MATRIX_PROJECTION)
			, m_pCamObserver->GetCamMatrix(MATRIX_VIEW));*/

		m_pMouseCol->PickObject(&m_vDestPos
			, m_pVertex
			, m_pCamObserver->GetCamMatrix(MATRIX_PROJECTION)
			, m_pCamObserver->GetCamMatrix(MATRIX_VIEW)
			, &m_pInfo->m_matWorld);
	}
}

void CPlayer::Move(void)
{
	D3DXVECTOR3		vDir = m_vDestPos - m_pInfo->m_vPos;

	float		fDistance = D3DXVec3Length(&vDir);
	D3DXVec3Normalize(&vDir, &vDir);

	m_pInfo->m_vPos += vDir * m_fSpeed * Engine::Get_TimeMgr()->GetTime();

	if(fDistance < 1.f)
		m_bMove = false;
}

