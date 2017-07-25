


#ifndef PressedUI_h__
#define PressedUI_h__



#include "GameObject.h"

namespace Engine
{
	class CTexture;
	class CVIBuffer;
	class CTransform;
}

class CPressedUI
	: public Engine::CGameObject
{

public:
	explicit CPressedUI(LPDIRECT3DDEVICE9 pDevice);
public:
	virtual ~CPressedUI(void);

public:
	virtual Engine::OBJECT_RESULT Update(void);
	virtual void Render(void);

public:
	static CPressedUI* Create(LPDIRECT3DDEVICE9 pDevice, D3DXVECTOR3 vPos);

private:
	void CalculateOrtho(void);

private:
void Gauge(void);

private:
	HRESULT Initialize(D3DXVECTOR3 vPos);
	HRESULT	AddComponent(void);
	void Release(void);

private:
	Engine::CTexture*		m_pTexture;
	Engine::CVIBuffer*		m_pBuffer;
	Engine::CTransform*		m_pInfo;

	D3DXMATRIX				m_matproj;
	D3DXMATRIX				m_mattemp;
	D3DXMATRIX				m_mattemp1;

	float				m_fScale;
	float				m_fverpos;

};


#endif // PressedUI_h__
