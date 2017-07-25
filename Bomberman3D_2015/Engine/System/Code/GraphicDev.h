/*!
 * \class CGraphicDev
 *
 * \ingroup GroupName
 *
 * \brief 
 *
 * TODO: DirectX Device Class
 *
 * \note 
 *
 * \author Han
 *
 * \version 1.0
 *
 * \date July 2017
 *
 * Contact: user@company.com
 *
 */

#ifndef __GraphicDev_h__
#define __GraphicDev_h__

#include "Engine_Include.h"

BEGIN(Engine)

class ENGINE_DLL CGraphicDev
{
public:
	DECLARE_SINGLETON(CGraphicDev)

public:
	enum WINMODE {MODE_FULL, MODE_WIN};
private:
	CGraphicDev(void);
public:
	~CGraphicDev(void);
public: 
	LPDIRECT3DDEVICE9 GetDevice(void) {
		return m_pDevice;}
public:	
	void SetRenderState(_D3DRENDERSTATETYPE Type, const DWORD& dwFlag) {
		m_pDevice->SetRenderState(Type, dwFlag); }
	void SetSamplerState(_D3DSAMPLERSTATETYPE Type, const DWORD& dwFlag)	{		
		m_pDevice->SetSamplerState(0, Type, dwFlag);}

public:
	HRESULT InitGraphicDev(WINMODE Mode, HWND hWnd, const WORD& wSizeX, const WORD& wSizeY);

private:
	LPDIRECT3D9					m_pSDK;
	LPDIRECT3DDEVICE9			m_pDevice; 

private:
	void SetParameters(D3DPRESENT_PARAMETERS& d3dpp, WINMODE Mode, HWND hWnd, const WORD& wSizeX, const WORD& wSizeY);
	void Release(void);
};

END

#endif // _GraphicDev_h__
