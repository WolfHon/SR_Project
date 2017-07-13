#include "MathMgr.h"

Engine::CMathMgr::CMathMgr(void)
{

}

Engine::CMathMgr::~CMathMgr(void)
{

}

void Engine::CMathMgr::MyRotationX(D3DXVECTOR3* pOut, D3DXVECTOR3* pIn, float fAngle)
{
/*	1열 2열 3열 4열  
	1	0	0	0	1행
	0	c	s	0	2행
	0	-s	c	0	3행
	0	0	0	1	4행
	*/
	D3DXVECTOR3		vTemp = *pIn;
	pOut->x = vTemp.x;
	pOut->y = vTemp.y * cosf(fAngle) - vTemp.z * sinf(fAngle);
	pOut->z = vTemp.y * sinf(fAngle) + vTemp.z * cosf(fAngle);
}

void Engine::CMathMgr::MyRotationY(D3DXVECTOR3* pOut, D3DXVECTOR3* pIn, float fAngle)
{
	/*
	c	0	-s	0
	0	1	0	0
	s	0	c	0
	0	0	0	1
	*/
	D3DXVECTOR3		vTemp = *pIn;
	pOut->x = vTemp.x * cosf(fAngle) + vTemp.z * sinf(fAngle);
	pOut->y = vTemp.y;
	pOut->z = vTemp.x * -sinf(fAngle) + vTemp.z * cosf(fAngle);
}

void Engine::CMathMgr::MyRotationZ(D3DXVECTOR3* pOut, D3DXVECTOR3* pIn, float fAngle)
{
	/*
	c	s	0	0
	-s	c	0	0
	0	0	1	0
	0	0	0	1
	*/
	D3DXVECTOR3		vTemp = *pIn;
	pOut->x = vTemp.x * cosf(fAngle) - vTemp.y * sinf(fAngle);
	pOut->y = vTemp.x * sinf(fAngle) + vTemp.y * cosf(fAngle);
	pOut->z = vTemp.z;
}

