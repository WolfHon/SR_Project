#include "Collision_OBB.h"

Engine::CCollision_OBB::CCollision_OBB(void)
: m_vMin(0.f, 0.f, 0.f)
, m_vMax(0.f, 0.f, 0.f)
, m_pmatWorld(NULL)
{
	ZeroMemory(m_vPoint, sizeof(D3DXVECTOR3) * 8);
}

Engine::CCollision_OBB::CCollision_OBB(const CCollision_OBB& rhs)
: CCollision(rhs)
, m_pmatWorld(rhs.m_pmatWorld)
, m_vMin(rhs.m_vMin)
, m_vMax(rhs.m_vMax)
, m_tOBB(rhs.m_tOBB)
{
	memcpy(m_vPoint, rhs.m_vPoint, sizeof(D3DXVECTOR3) * 8);
}

Engine::CCollision_OBB::~CCollision_OBB(void)
{
}

Engine::CCollision* Engine::CCollision_OBB::CloneCollision(void)
{
	return new CCollision_OBB(*this);
}

void Engine::CCollision_OBB::SetColInfo(const D3DXMATRIX* pWorld
										, const D3DXVECTOR3* pMin /*= NULL*/
										, const D3DXVECTOR3* pMax /*= NULL*/)
{
	m_pmatWorld = pWorld;

	m_vMin = *pMin;
	m_vMax = *pMax;
}

DWORD Engine::CCollision_OBB::Release(void)
{
	if(m_dwRefCnt == 0)
	{
		return 0;
	}
	else
	{
		--m_dwRefCnt;
	}

	return m_dwRefCnt;
}

Engine::CCollision_OBB* Engine::CCollision_OBB::Create(void)
{	
	return new CCollision_OBB();
}

void Engine::CCollision_OBB::ComputePoint(void)
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

void Engine::CCollision_OBB::ComputeAxis(void)
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


bool Engine::CCollision_OBB::CheckCollision(CCollision_OBB* pTerget)
{
	CollisionUpdate();
	pTerget->CollisionUpdate();

	const OBB*	pOBB[2] = {&m_tOBB, pTerget->GetObbInfo()};	
	
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

void Engine::CCollision_OBB::GetColBox(D3DXVECTOR3* pMin, D3DXVECTOR3* pMax)
{
	*pMin = m_vMin;
	*pMax = m_vMax;
}

void Engine::CCollision_OBB::CollisionUpdate(void)
{
	ZeroMemory(&m_tOBB, sizeof(OBB));

	ComputePoint();

	for (int i = 0; i < 8; ++i)
		D3DXVec3TransformCoord(&m_vPoint[i], &m_vPoint[i], m_pmatWorld);

	D3DXVec3TransformCoord(&m_tOBB.vCenter, &m_tOBB.vCenter, m_pmatWorld);

	ComputeAxis();
}
