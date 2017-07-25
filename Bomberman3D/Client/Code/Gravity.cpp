#include "stdafx.h"
#include "Gravity.h"

#include "TerrainInfo.h"
#include "Export_Function.h"
#include <iostream>
using namespace std;
CGravity::CGravity(void)
: CComponent()
, m_pMatWorld(NULL)
, m_pPos(NULL)
, m_fModelHeight(0.f)
, m_fAcc(0.f)
, m_bStopDown(FALSE)
, m_fPower(0.f)
, m_fRepulsivePower(0.f)
{
}

CGravity::CGravity(const CGravity& rhs)
: CComponent(rhs)
, m_pMatWorld(rhs.m_pMatWorld)
, m_pPos(rhs.m_pPos)
, m_fModelHeight(rhs.m_fModelHeight)
, m_fAcc(rhs.m_fAcc)
, m_fPower(rhs.m_fPower)
, m_fRepulsivePower(rhs.m_fRepulsivePower)
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

	m_bStopDown = FALSE;

	m_fAcc += 5.f * Engine::Get_TimeMgr()->GetTime();

	m_fExHeight = m_pPos->y;

	m_fPower = -1 * (GRAVITY * m_fAcc * m_fAcc * 0.5f);

	m_pPos->y += m_fPower * Engine::Get_TimeMgr()->GetTime();

	if(Maxheight > m_pPos->y)
	{
		m_pPos->y = Maxheight;
		m_fAcc = 0.f;

		m_fRepulsivePower = m_fPower * -0.4f;

		m_bStopDown = TRUE;
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
}

bool CGravity::Replusive(void)
{
	if(m_fRepulsivePower > 5.f)
	{
		m_fExHeight = m_pPos->y;

		m_pPos->y += m_fRepulsivePower * 0.4f * Engine::Get_TimeMgr()->GetTime();

		return TRUE;
	}

	return FALSE;
}
