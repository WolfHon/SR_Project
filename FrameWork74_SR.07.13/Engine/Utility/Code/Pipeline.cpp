#include "Pipeline.h"
#include "MathMgr.h"

Engine::CPipeline::CPipeline(void)
{

}

Engine::CPipeline::~CPipeline(void)
{

}

void Engine::CPipeline::MakeWorldMatrix(D3DXMATRIX* pOut 
										, const D3DXVECTOR3* pScale 
										, const float* pAngle 
										, const D3DXVECTOR3* pPos)
{
	D3DXMatrixIdentity(pOut);

	D3DXVECTOR3		vRight	= D3DXVECTOR3(1.f, 0.f, 0.f);//1青
	D3DXVECTOR3		vUp		= D3DXVECTOR3(0.f, 1.f, 0.f);//2青
	D3DXVECTOR3		vLook	= D3DXVECTOR3(0.f, 0.f, 1.f);//3青
	D3DXVECTOR3		vPos	= D3DXVECTOR3(0.f, 0.f, 0.f);//4青

	//胶纳老
	vRight *= pScale->x;
	vUp *= pScale->y;
	vLook *= pScale->z;

	//磊傈
	//CMathMgr::MyRotationX(&vRight, &vRight, pAngle[ANGLE_X]);
	CMathMgr::MyRotationX(&vUp, &vUp, pAngle[ANGLE_X]);
	CMathMgr::MyRotationX(&vLook, &vLook, pAngle[ANGLE_X]);

	CMathMgr::MyRotationY(&vRight, &vRight, pAngle[ANGLE_Y]);
	//CMathMgr::MyRotationY(&vUp, &vUp, pAngle[ANGLE_Y]);
	CMathMgr::MyRotationY(&vLook, &vLook, pAngle[ANGLE_Y]);

	CMathMgr::MyRotationZ(&vRight, &vRight, pAngle[ANGLE_Z]);
	CMathMgr::MyRotationZ(&vUp, &vUp, pAngle[ANGLE_Z]);
	//CMathMgr::MyRotationZ(&vLook, &vLook, pAngle[ANGLE_Z]);

	//捞悼
	vPos = *pPos;

	MakeTransformMatrix(pOut, &vRight, &vUp, &vLook, &vPos);
}

void Engine::CPipeline::MakeViewSpaceMatrix(D3DXMATRIX* pOut 
											, const D3DXVECTOR3* pEye 
											, const D3DXVECTOR3* pAt 
											, const D3DXVECTOR3* pUp)
{
	D3DXMatrixIdentity(pOut);

	D3DXVECTOR3		vRight	= D3DXVECTOR3(1.f, 0.f, 0.f);//1青
	D3DXVECTOR3		vUp		= D3DXVECTOR3(0.f, 1.f, 0.f);//2青
	D3DXVECTOR3		vLook	= D3DXVECTOR3(0.f, 0.f, 1.f);//3青
	D3DXVECTOR3		vPos	= D3DXVECTOR3(0.f, 0.f, 0.f);//4青

	//Look
	vLook = *pAt - *pEye;
	D3DXVec3Normalize(&vLook, &vLook);

	//Right
	D3DXVec3Cross(&vRight, pUp, &vLook);
	D3DXVec3Normalize(&vRight, &vRight);

	//Up
	D3DXVec3Cross(&vUp, &vLook, &vRight);
	D3DXVec3Normalize(&vUp, &vUp);

	vPos = *pEye;

	MakeTransformMatrix(pOut, &vRight, &vUp, &vLook, &vPos);
	D3DXMatrixInverse(pOut, NULL, pOut);
}

void Engine::CPipeline::MakeProjectionMatrix(D3DXMATRIX* pOut , const float& fFovY , const float& fAspect , const float& fNear , const float& fFar)
{
	D3DXMatrixIdentity(pOut);

	pOut->_11 = (1.f / tanf(fFovY / 2.f)) / fAspect;
	pOut->_22 = 1.f / tanf(fFovY / 2.f);

	pOut->_33 = fFar / (fFar - fNear);
	pOut->_43 = -fNear * fFar / (fFar - fNear);

	pOut->_34 = 1.f;
	pOut->_44 = 0.f;
}

void Engine::CPipeline::MakeTransformMatrix(D3DXMATRIX* pOut , const D3DXVECTOR3* pRight , const D3DXVECTOR3* pUp , const D3DXVECTOR3* pLook , const D3DXVECTOR3* pPos)
{
	memcpy(&pOut->m[0][0], pRight, sizeof(D3DXVECTOR3));
	memcpy(&pOut->m[1][0], pUp, sizeof(D3DXVECTOR3));
	memcpy(&pOut->m[2][0], pLook, sizeof(D3DXVECTOR3));
	memcpy(&pOut->m[3][0], pPos, sizeof(D3DXVECTOR3));
}

void Engine::CPipeline::MyTransformCoord(D3DXVECTOR3* pOut , const D3DXVECTOR3* pVector, const D3DXMATRIX* pMatrix)
{
	D3DXVECTOR4	vVector(pVector->x, pVector->y, pVector->z, 1.f);

	pOut->x = vVector.x * pMatrix->_11
		+ vVector.y * pMatrix->_21
		+ vVector.z * pMatrix->_31
		+ vVector.w * pMatrix->_41;

	pOut->y = vVector.x * pMatrix->_12
		+ vVector.y * pMatrix->_22
		+ vVector.z * pMatrix->_32
		+ vVector.w * pMatrix->_42;

	pOut->z = vVector.x * pMatrix->_13
		+ vVector.y * pMatrix->_23
		+ vVector.z * pMatrix->_33
		+ vVector.w * pMatrix->_43;

	float		fZ = vVector.x * pMatrix->_14
		+ vVector.y * pMatrix->_24
		+ vVector.z * pMatrix->_34
		+ vVector.w * pMatrix->_44;

	pOut->x /= fZ;
	pOut->y /= fZ;
	pOut->z /= fZ;
}
