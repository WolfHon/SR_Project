#include "stdafx.h"
#include "Collision_OBB.h"

#include "Export_Function.h"
#include "GameObject.h"

#include "CubeColor.h"

#ifdef _DEBUG	
bool	CCollision_OBB::m_bWireRender = FALSE;
#endif

CCollision_OBB::CCollision_OBB(LPDIRECT3DDEVICE9 pDevice)
: m_pDevice(pDevice)
, m_vMin(0.f, 0.f, 0.f)
, m_vMax(0.f, 0.f, 0.f)
, m_pmatWorld(NULL)
{
#ifdef _DEBUG
	m_bExWire = FALSE;
#endif
	ZeroMemory(m_vPoint, sizeof(D3DXVECTOR3) * 8);
}

CCollision_OBB::CCollision_OBB(const CCollision_OBB& rhs)
: CCollision(rhs)
, m_pDevice(rhs.m_pDevice)
, m_pmatWorld(rhs.m_pmatWorld)
, m_vMin(rhs.m_vMin)
, m_vMax(rhs.m_vMax)
, m_tOBB(rhs.m_tOBB)
, pVertex(rhs.pVertex)
{
#ifdef _DEBUG
	m_bExWire = rhs.m_bExWire;
#endif
	memcpy(m_vPoint, rhs.m_vPoint, sizeof(D3DXVECTOR3) * 8);
}

CCollision_OBB::~CCollision_OBB(void)
{
}

Engine::CCollision* CCollision_OBB::CloneCollision(void)
{
	return new CCollision_OBB(*this);
}

void CCollision_OBB::SetColInfo(const D3DXMATRIX* pWorld
										, const D3DXVECTOR3* pMin /*= NULL*/
										, const D3DXVECTOR3* pMax /*= NULL*/)
{
	m_pmatWorld = pWorld;

	m_vMin = *pMin;
	m_vMax = *pMax;
}

DWORD CCollision_OBB::Release(void)
{
	if(m_dwRefCnt == 0)
	{
#ifdef _DEBUG
		Safe_Delete_Array(pVertex);
		Safe_Delete(m_pCubeColor);
#endif

		return 0;
	}
	else
	{
		--m_dwRefCnt;
	}

	return m_dwRefCnt;
}

CCollision_OBB* CCollision_OBB::Create(LPDIRECT3DDEVICE9 pDevice)
{	
	CCollision_OBB*	pCollision = new CCollision_OBB(pDevice);

	if(FAILED(pCollision->InitCollision()))
		Safe_Delete(pCollision);

	return pCollision;
}

void CCollision_OBB::ComputePoint(void)
{
	m_vPoint[0] = D3DXVECTOR3(m_vMin.x, m_vMax.y, m_vMin.z);
	m_vPoint[1] = D3DXVECTOR3(m_vMax.x, m_vMax.y, m_vMin.z);
	m_vPoint[2] = D3DXVECTOR3(m_vMax.x, m_vMin.y, m_vMin.z);
	m_vPoint[3] = D3DXVECTOR3(m_vMin.x, m_vMin.y, m_vMin.z);

	m_vPoint[4] = D3DXVECTOR3(m_vMin.x, m_vMax.y, m_vMax.z);
	m_vPoint[5] = D3DXVECTOR3(m_vMax.x, m_vMax.y, m_vMax.z);
	m_vPoint[6] = D3DXVECTOR3(m_vMax.x, m_vMin.y, m_vMax.z);
	m_vPoint[7] = D3DXVECTOR3(m_vMin.x, m_vMin.y, m_vMax.z);

	for (int i = 0; i < 8; ++i)	
		m_tOBB.vCenter += m_vPoint[i];

	m_tOBB.vCenter *= 0.125f;
}

void CCollision_OBB::ComputeAxis(void)
{	
	m_tOBB.vProj[AXIS_X] = (m_vPoint[1] + m_vPoint[2] + m_vPoint[5] + m_vPoint[6]) * 0.25f
		- m_tOBB.vCenter; 
	m_tOBB.vParallel[AXIS_X] = m_vPoint[1] - m_vPoint[0]; 

	m_tOBB.vProj[AXIS_Y] = (m_vPoint[0] + m_vPoint[1] + m_vPoint[4] + m_vPoint[5]) * 0.25f
		- m_tOBB.vCenter;
	m_tOBB.vParallel[AXIS_Y] = m_vPoint[0] - m_vPoint[3];

	m_tOBB.vProj[AXIS_Z] = (m_vPoint[4] + m_vPoint[5] + m_vPoint[6] + m_vPoint[7]) * 0.25f
		- m_tOBB.vCenter;
	m_tOBB.vParallel[AXIS_Z] = m_vPoint[7] - m_vPoint[3];	

	for (int i = 0; i < AXIS_END; ++i)
		D3DXVec3Normalize(&m_tOBB.vParallel[i], &m_tOBB.vParallel[i]);
}

Engine::CGameObject* CCollision_OBB::CheckCollision(Engine::LAYERID eLayerID, wstring wstrName, D3DXVECTOR3 vPos)
{
	Engine::OBJLIST* listObj = Engine::Get_Management()->GetObjectList(eLayerID, wstrName);



	if(listObj == NULL)
		return NULL;


	Engine::OBJLIST::iterator iterBegin = listObj->begin();
	Engine::OBJLIST::iterator iterEnd = listObj->end();

	for (; iterBegin != iterEnd; ++iterBegin)
	{
		Engine::CComponent*      pComponent = NULL;

		pComponent = (*iterBegin)->GetComponent(L"Collision_OBB");
		NULL_CHECK_RETURN(pComponent, FALSE);
		CCollision_OBB* ptarget = dynamic_cast<CCollision_OBB*>(pComponent);

		if(CheckDist(ptarget) == FALSE)
			continue;			
		
		if (ProcessingCollision(ptarget))
			return *iterBegin;
	}

	return NULL;
}



bool CCollision_OBB::CheckDist(CCollision_OBB* pTarget)
{
	const D3DXMATRIX* pMatCollider = pTarget->GetMatrix();
	D3DXVECTOR3 vTargetScale = D3DXVECTOR3(pMatCollider->_11, pMatCollider->_22, pMatCollider->_33);
	D3DXVECTOR3 vTargetCol = ((*pTarget->GetMax()) - (*pTarget->GetMin())) / 2.f;
	D3DXVECTOR3	vTargetSize = D3DXVECTOR3(vTargetCol.x * vTargetScale.x, vTargetCol.y * vTargetScale.y, vTargetCol.z * vTargetScale.z);
	D3DXVECTOR3 vTargetPos;
	memcpy(&vTargetPos, &pMatCollider->m[3][0], sizeof(D3DXVECTOR3));

	D3DXVECTOR3 vScale = D3DXVECTOR3(m_pmatWorld->_11, m_pmatWorld->_22, m_pmatWorld->_33); 
	D3DXVECTOR3 vCol = (m_vMax - m_vMin) / 2.f;
	D3DXVECTOR3	vSize = D3DXVECTOR3(vCol.x * vScale.x, vCol.y * vScale.y, vCol.z * vScale.z);
	D3DXVECTOR3 vPos;
	memcpy(&vPos, &m_pmatWorld->m[3][0], sizeof(D3DXVECTOR3));

	float		fRadius = D3DXVec3Length(&vSize) + 2.f;
	float		fRadiusTarget = D3DXVec3Length(&vTargetSize) + 2.f;
	float		fDist = D3DXVec3Length(&(vPos - vTargetPos));
	
	if(fDist > fRadius + fRadiusTarget) 
		return FALSE;

	return TRUE;
}


bool CCollision_OBB::ProcessingCollision(CCollision_OBB* pTarget)
{
	CollisionUpdate();
	pTarget->CollisionUpdate();

	const OBB*	pOBB[2] = {&m_tOBB, pTarget->GetObbInfo()};	

	float		fDistance[3];
	for (int i = 0; i < 2; ++i)
	{
		for (int j = 0; j < AXIS_END; ++j)
		{
			fDistance[0] = fabs(D3DXVec3Dot(&pOBB[0]->vProj[AXIS_X], &pOBB[i]->vParallel[j]))
				+ fabs(D3DXVec3Dot(&pOBB[0]->vProj[AXIS_Y], &pOBB[i]->vParallel[j]))
				+ fabs(D3DXVec3Dot(&pOBB[0]->vProj[AXIS_Z], &pOBB[i]->vParallel[j]));

			fDistance[1] = fabs(D3DXVec3Dot(&pOBB[1]->vProj[AXIS_X], &pOBB[i]->vParallel[j]))
				+ fabs(D3DXVec3Dot(&pOBB[1]->vProj[AXIS_Y], &pOBB[i]->vParallel[j]))
				+ fabs(D3DXVec3Dot(&pOBB[1]->vProj[AXIS_Z], &pOBB[i]->vParallel[j]));

			D3DXVECTOR3		vTmp = pOBB[1]->vCenter - pOBB[0]->vCenter;

			fDistance[2] = fabs(D3DXVec3Dot(&vTmp, &pOBB[i]->vParallel[j]));

			if(fDistance[2] >= fDistance[1] + fDistance[0])
				return false;
		}
	}

	return true;
}

void CCollision_OBB::CollisionUpdate(void)
{
	ZeroMemory(&m_tOBB, sizeof(OBB));

	ComputePoint();

	for (int i = 0; i < 8; ++i)
		D3DXVec3TransformCoord(&m_vPoint[i], &m_vPoint[i], m_pmatWorld);

	D3DXVec3TransformCoord(&m_tOBB.vCenter, &m_tOBB.vCenter, m_pmatWorld);

	ComputeAxis();
}

HRESULT CCollision_OBB::InitCollision(void)
{
#ifdef _DEBUG	
	Engine::CComponent* pComponent = Engine::Get_ResourceMgr()->CloneResource(Engine::RESOURCE_STATIC, L"Buffer_CubeColor");
	m_pCubeColor = dynamic_cast<Engine::CCubeColor*>(pComponent);
	NULL_CHECK_RETURN(m_pCubeColor, E_FAIL);

	pVertex = new Engine::VTXCOL[8];	
#endif

	return S_OK;
}

void CCollision_OBB::Render(const DWORD& dwColor)
{
#ifdef _DEBUG	
	DWORD KeyState = Engine::Get_KeyMgr()->GetKey();

	if(!(~KeyState & Engine::KEY_F1_CLICK))
	{
		if(m_bExWire==m_bWireRender)
			m_bWireRender = !m_bWireRender;
	}
	m_bExWire = m_bWireRender;

	if(m_bWireRender == TRUE)
	{
	m_pCubeColor->GetVtxInfo(pVertex);

	pVertex[0].vPos = D3DXVECTOR3(m_vMin.x, m_vMax.y, m_vMin.z);	
	pVertex[1].vPos = D3DXVECTOR3(m_vMax.x, m_vMax.y, m_vMin.z);
	pVertex[2].vPos = D3DXVECTOR3(m_vMax.x, m_vMin.y, m_vMin.z);
	pVertex[3].vPos = D3DXVECTOR3(m_vMin.x, m_vMin.y, m_vMin.z);

	pVertex[4].vPos = D3DXVECTOR3(m_vMin.x, m_vMax.y, m_vMax.z);
	pVertex[5].vPos = D3DXVECTOR3(m_vMax.x, m_vMax.y, m_vMax.z);
	pVertex[6].vPos = D3DXVECTOR3(m_vMax.x, m_vMin.y, m_vMax.z);
	pVertex[7].vPos = D3DXVECTOR3(m_vMin.x, m_vMin.y, m_vMax.z);	

	for(int i=0;i<8;++i)
		pVertex[i].dwColor = dwColor;

	m_pCubeColor->SetVtxInfo(pVertex);

	m_pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	m_pDevice->SetTransform(D3DTS_WORLD, m_pmatWorld);
	m_pCubeColor->Render();
	m_pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	}
#endif
}