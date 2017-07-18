#include "stdafx.h"
#include "ToolCamera.h"

#include "Include.h"
#include "Transform.h"
#include "Export_Function.h"



CToolCamera::CToolCamera( LPDIRECT3DDEVICE9 pDevice )
: Engine::CCamera(pDevice)
, m_fTargetDistance(0.f)
, m_fAngle(0.f)
, m_fCamSpeed(0.f)
, m_pTargetInfo(NULL)
, m_vEye(10.f, 10.f, -20.f)
, m_vAt (0.f, 0.f, 0.f)
, m_vUp (0.f, 1.f, 0.f)
, m_vLook(0.f , 0.f, 0.f)
, m_vPos (0.f , 0.f, -20.f)
, m_vDir (0.f, 0.f, 0.f)
, m_vcEps (0.f, 0.f , 0.f)
, m_vcOld(0.f, 0.f, 0.f)
, m_vcCur(0.f, 0.f, 0.f)
{

}

CToolCamera::~CToolCamera( void )
{

}

void CToolCamera::Update( void )
{
	KeyCheck();
	TargetRenewal();


}

HRESULT CToolCamera::Initialize( void )
{




	D3DXMatrixPerspectiveFovLH(&matProj, D3DXToRadian(45.f), float(WINCX) / WINCY
		, 1.f, 1000.f);
	m_pDevice->SetTransform(D3DTS_PROJECTION, &matProj);
	m_fCamSpeed = 10.f; 



	return S_OK;

}

void CToolCamera::SetCameraTarget( const Engine::CTransform* pTargetInfo  )
{
	m_pTargetInfo = pTargetInfo;
}

CToolCamera* CToolCamera::Create( LPDIRECT3DDEVICE9 pDevice)
{
	CToolCamera*	pCamera = new CToolCamera(pDevice);
	if(FAILED(pCamera->Initialize()))
		Engine::Safe_Delete(pCamera);


	return pCamera;

}

void CToolCamera::KeyCheck( void )
{

	//if(GetAsyncKeyState(VK_RIGHT))
	//	m_vEye.x += 0.1f;

	//if(GetAsyncKeyState(VK_LEFT))
	//	m_vEye.x -= 0.1f;

	//if(GetAsyncKeyState(VK_UP))
	//	m_vEye.y += 0.1f;

	//if(GetAsyncKeyState(VK_DOWN))
	//	m_vEye.y -= 0.1f;

	//if(GetAsyncKeyState('P'))
	//	m_vEye.z += 0.1f;

	//if(GetAsyncKeyState('O'))
	//	m_vEye.z -= 0.1f;

	if(GetAsyncKeyState('W') & 1)
	{
		D3DXVECTOR3 vcZ(matView._13,matView._23, matView._33);
		D3DXVec3Normalize(&vcZ,&vcZ);

		m_vEye += vcZ * 0.5f;
		m_vAt  += vcZ * 0.5f;
	}
	if(GetAsyncKeyState('S') & 1 )
	{	D3DXVECTOR3 vcZ(matView._13,matView._23 , matView._33);
	D3DXVec3Normalize(&vcZ,&vcZ);

	m_vEye -= vcZ * 0.5f;
	m_vAt  -= vcZ * 0.5f;
	}
	if(GetAsyncKeyState('A')& 1 )
	{
		D3DXVECTOR3 vcZ(matView._11,0, matView._31);
		D3DXVec3Normalize(&vcZ,&vcZ);

		m_vEye -= vcZ * 0.5f;
		m_vAt  -= vcZ * 0.5f;

	}

	if(GetAsyncKeyState('D') & 1 )
	{
		D3DXVECTOR3 vcZ(matView._11,0, matView._31);
		D3DXVec3Normalize(&vcZ,&vcZ);

		m_vEye += vcZ * 0.5f;
		m_vAt  += vcZ * 0.5f;

	}

	if(GetAsyncKeyState('Q')& 1 )
	{
		D3DXVECTOR3 vcZ(matView._12,matView._22, matView._32);
		D3DXVec3Normalize(&vcZ,&vcZ);

		m_vEye -= vcZ * 0.5f;
		m_vAt  -= vcZ * 0.5f;

	}

	if(GetAsyncKeyState('E') & 1 )
	{
		D3DXVECTOR3 vcZ(matView._12,matView._22, matView._32);
		D3DXVec3Normalize(&vcZ,&vcZ);

		m_vEye += vcZ * 0.5f;
		m_vAt  += vcZ * 0.5f;

	}


	//if(GetAsyncKeyState(VK_RBUTTON) & 1)
	//{	
	//	GetCursorPos(&m_pt);
	//	ScreenToClient(g_hWnd, &m_pt);
	//	D3DXVECTOR3 vcDelta = Getmouse(m_pt);
	//	Rotate(vcDelta);

	//}



}

void CToolCamera::TargetRenewal( void )
{


	//m_vAt = m_vEye * 1.1;

	//m_vEye = m_pTargetInfo->m_vDir * -1 * m_fTargetDistance;


	//D3DXVECTOR3		vRight;

	//memcpy(&vRight, &m_vLook.x, sizeof(D3DXVECTOR3));

	//D3DXMATRIX		matRotAxis;
	//D3DXMatrixRotationAxis(&matRotAxis, &vRight, m_fAngle);
	//D3DXVec3TransformNormal(&m_vEye, &m_vEye, &matRotAxis);

	//m_vAt = m_vAt;
	////m_vEye += m_pTargetInfo->m_vPos;

	////SetViewSpaceMatrix(&m_vEye, &m_vAt, &m_vUp);

	D3DXMatrixLookAtLH(&matView, &m_vEye
		, &m_vAt, &m_vUp);

	m_pDevice->SetTransform(D3DTS_VIEW, &matView);
	m_pDevice->SetTransform(D3DTS_PROJECTION,&matProj);

}



void CToolCamera::Release( void )
{

}

void CToolCamera::Rotate( const D3DXVECTOR3 vcDelta )
{
	D3DXVECTOR3 vcEps = vcDelta;

	FLOAT	fYaw	;
	FLOAT	fPitch	;

	D3DXVECTOR3 vcZ;
	D3DXVECTOR3 vcY;
	D3DXVECTOR3 vcX;

	D3DXMATRIX rtY;
	D3DXMATRIX rtX;

	// 월드 좌표 y 축에 대한 회전
	fYaw	= D3DXToRadian(vcEps.x * 0.1);
	D3DXMatrixRotationY(&rtY, fYaw);

	vcZ = m_vAt-m_vEye;
	vcY = D3DXVECTOR3(matView._12, matView._22, matView._32);

	D3DXVec3TransformCoord(&vcZ, &vcZ, &rtY);
	D3DXVec3TransformCoord(&vcY, &vcY, &rtY);

	m_vAt= vcZ + m_vEye;
	m_vUp	= vcY;
	D3DXMatrixLookAtLH(&matView, &m_vEye, &m_vAt, &m_vUp);


	// 카메라의 x 축에 대한 회전
	fPitch	= D3DXToRadian(vcEps.y  * 0.1);
	vcX	= D3DXVECTOR3(matView._11, matView._21, matView._31);
	vcY = D3DXVECTOR3(matView._12, matView._22, matView._32);
	vcZ = m_vAt-m_vEye;

	D3DXMatrixRotationAxis(&rtX, &vcX, fPitch);
	D3DXVec3TransformCoord(&vcZ, &vcZ, &rtX);
	D3DXVec3TransformCoord(&vcY, &vcY, &rtX);

	m_vAt= vcZ + m_vEye;
	m_vUp	= vcY;
	D3DXMatrixLookAtLH(&matView, &m_vEye, &m_vAt, &m_vUp);



}

D3DXVECTOR3 CToolCamera::Getmouse( POINT pt )
{

	//if(pt.x < 0 || pt.x > 800 || pt.y < 0 || pt.y > 600)
	//	return D3DXVECTOR3(0.f,0.f,0.f);

	m_vcOld.x = m_vcCur.x;
	m_vcOld.y = m_vcCur.y;

	m_vcCur.x = FLOAT(pt.x);
	m_vcCur.y = FLOAT(pt.y);

	m_vcEps = m_vcCur - m_vcOld;
	m_vcOld.z = m_vcCur.z;

	return m_vcEps;

}
