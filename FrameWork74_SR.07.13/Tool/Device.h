#ifndef Device_h__
#define Device_h__


class CDevice
{
public:
	DECLARE_SINGLETON(CDevice)

public:
	enum WINMODE {MODE_FULL, MODE_WIN};
private:
	CDevice(void);
public:
	~CDevice(void);
public: // getter
	LPDIRECT3DDEVICE9 GetDevice(void) {
		return m_pDevice;}
public:	// setter
	void SetRenderState(_D3DRENDERSTATETYPE Type, const DWORD& dwFlag) {
		m_pDevice->SetRenderState(Type, dwFlag); }
	void SetSamplerState(_D3DSAMPLERSTATETYPE Type, const DWORD& dwFlag)	{		
		m_pDevice->SetSamplerState(0, Type, dwFlag);}

public:
	HRESULT InitGraphicDev();

private:
	LPDIRECT3D9					m_pSDK;
	LPDIRECT3DDEVICE9			m_pDevice; // 장치를 대표하는 객체다.
	LPD3DXFONT					m_pFont;
	LPD3DXSPRITE				m_pSprite;

public:
	void SetParameters(D3DPRESENT_PARAMETERS& d3dpp);
	void Render_Begin(void);
	void Render_End(void);
	void Release(void);
};



#endif // Device_h__