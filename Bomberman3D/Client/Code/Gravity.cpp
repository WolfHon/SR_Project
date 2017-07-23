#include "stdafx.h"
#include "Gravity.h"

#include "TerrainInfo.h"
#include "Export_Function.h"

CGravity::CGravity(void)
: CComponent()
, m_pMatWorld(NULL)
, m_pPos(NULL)
, m_fModelHeight(0.f)
, m_fAcc(0.f)
, m_fDownSpeed(0.f)
, m_bStopDown(FALSE)
{
}

CGravity::CGravity(const CGravity& rhs)
: CComponent(rhs)
, m_pMatWorld(rhs.m_pMatWorld)
, m_pPos(rhs.m_pPos)
, m_fModelHeight(rhs.m_fModelHeight)
, m_fAcc(rhs.m_fAcc)
, m_fDownSpeed(rhs.m_fDownSpeed)
{
}

CGravity::~CGravity(void)
{
	Release();
}

void CGravity::SetInfo(D3DXVECTOR3* vPoint, D3DXVECTOR3* vPos, D3DXMATRIX* matWorld, float Height)
{
	m_pMatWorld = matWorld;
	m_pPos = vPos;
	m_fModelHeight = Height;

	for(int i=0;i<4;++i)
		m_vPoint[i] = vPoint[i];
}

Engine::OBJECT_RESULT CGravity::Update(void)
{
	D3DXVECTOR3 vPoint[4];

	for(int i=0; i<4; ++i)
		D3DXVec3TransformCoord(&vPoint[i], &m_vPoint[i], m_pMatWorld);

	float Maxheight = -1000.f;
	float Height = 0.f;

	float vScaleY = m_pMatWorld->_22;

	for(int i=0; i<4; ++i)
	{
		Height = CTerrainInfo::GetInstance()->CheckHeight(vPoint[i]) + (m_fModelHeight * vScaleY) + 0.1f;
		if(Height > Maxheight)
			Maxheight = Height;
	}

	m_pPos->y = m_pPos->y;

	if(fabs(m_pPos->y - Maxheight) < 0.7f)
	{
		m_pPos->y = Maxheight;
		m_fAcc = 0.f;

		m_bStopDown = TRUE;
	}
	else
	{
		m_bStopDown = FALSE;

		m_fAcc += 5.f * Engine::Get_TimeMgr()->GetTime();

		float dir = -1.f;

		if(Maxheight > m_pPos->y)
			dir = 1.f;

		m_fExHeight = m_pPos->y;

		float Power = dir * m_fDownSpeed * m_fAcc - (-1 * dir * GRAVITY * m_fAcc * m_fAcc * 0.5f);

		m_pPos->y += Power * Engine::Get_TimeMgr()->GetTime();
	}

	return Engine::OR_OK;
}

DWORD CGravity::Release(void)
{
	if(m_dwRefCnt == 0)
	{
		return 0;
	}
	else
		--m_dwRefCnt;

	return m_dwRefCnt;
}

CGravity* CGravity::Create(void)
{
	CGravity*	pGravity = new CGravity();
	pGravity->InitializeGravity();
	return pGravity;
}

void CGravity::InitializeGravity(void)
{
	m_fAcc = 0.f;
	m_fDownSpeed = 5.f;
}