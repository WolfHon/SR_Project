#include "stdafx.h"
#include "Device.h"
#include "Include.h"


IMPLEMENT_SINGLETON(CDevice)

CDevice::CDevice( void )
: m_pSDK(NULL)
, m_pDevice(NULL)
{

}

CDevice::~CDevice( void )
{
	Release();

}

HRESULT CDevice::InitGraphicDev()
{
	m_pSDK = Direct3DCreate9(D3D_SDK_VERSION);

	D3DCAPS9		devicecaps;
	ZeroMemory(&devicecaps, sizeof(D3DCAPS9));

	if(FAILED(m_pSDK->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &devicecaps)))
	{
		MSG_BOX(L"GetDeviceCaps Failed");
		return E_FAIL;
	}

	DWORD		vp;

	if(devicecaps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)
		vp = D3DCREATE_HARDWARE_VERTEXPROCESSING;
	else
		vp = D3DCREATE_SOFTWARE_VERTEXPROCESSING;

	vp |= D3DCREATE_MULTITHREADED;

	D3DPRESENT_PARAMETERS	d3dpp;
	ZeroMemory(&d3dpp, sizeof(D3DPRESENT_PARAMETERS));

	SetParameters(d3dpp);

	if(FAILED(m_pSDK->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL
		, g_hWnd, vp, &d3dpp, &m_pDevice)))
	{
		MSG_BOX(L"CreateDevice Failed");
		return E_FAIL;
	}

	if(FAILED( D3DXCreateSprite(m_pDevice, &m_pSprite) ))
	{
		AfxMessageBox(L"��������Ʈ��ü �ʱ�ȭ ����!");
		return E_FAIL;
	}

	//��Ʈ��ü �ʱ�ȭ
	D3DXFONT_DESC FontInfo;
	ZeroMemory(&FontInfo, sizeof(D3DXFONT_DESC));

	FontInfo.Height = 20;
	FontInfo.Width = 10;

	FontInfo.Weight = FW_HEAVY;	//��Ʈ �β�
	FontInfo.CharSet = HANGUL_CHARSET;		//�ѱۻ��

	lstrcpy(FontInfo.FaceName, L"�ü�");		//�۲��� ����.

	if(FAILED(D3DXCreateFontIndirect(m_pDevice, &FontInfo, &m_pFont) ))
	{
		AfxMessageBox(L"��Ʈ��ü �ʱ�ȭ ����!");
		return E_FAIL;
	}

	return S_OK;

	
}

void CDevice::SetParameters( D3DPRESENT_PARAMETERS& d3dpp)
{
	d3dpp.BackBufferWidth = WINCX;
	d3dpp.BackBufferHeight = WINCY;
	d3dpp.BackBufferCount = 1;
	d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8;

	d3dpp.MultiSampleQuality = 0;
	d3dpp.MultiSampleType = D3DMULTISAMPLE_NONE;

	d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;
	d3dpp.EnableAutoDepthStencil = TRUE;

	d3dpp.hDeviceWindow = g_hWnd;
	d3dpp.Windowed = TRUE;

	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

}

void CDevice::Release( void )
{
	Engine::Safe_Release(m_pDevice);
	Engine::Safe_Release(m_pSDK);

}

void CDevice::Render_Begin( void )
{

	m_pDevice->Clear(0,	//������ ����
		NULL, //��ġ�� �ּҰ�
		D3DCLEAR_TARGET | D3DCLEAR_STENCIL | D3DCLEAR_ZBUFFER,	//D3DCLEAR_TARGET : �ĸ����, 
		D3DCOLOR_ARGB(255, 0, 0, 255),		//�������?
		1.f,	//�������Ŀ� ���̹����� �ʱⰪ
		0);	//���ٽ� ������ �ʱⰪ

	m_pDevice->BeginScene();
}

void CDevice::Render_End( void )
{

	m_pDevice->EndScene();
	m_pDevice->Present(NULL, NULL, NULL, NULL);//4���� : RGNDATA

}
