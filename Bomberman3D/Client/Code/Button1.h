
#ifndef Button1_h__
#define Button1_h__




#include "GameObject.h"

namespace Engine
{
	class CTexture;
	class CVIBuffer;
	class CTransform;
}

class CButton1
	: public Engine::CGameObject
{

public:
	explicit CButton1(LPDIRECT3DDEVICE9 pDevice);
public:
	virtual ~CButton1(void);

public:
	virtual Engine::OBJECT_RESULT Update(void);
	virtual void Render(void);

public:
	static CButton1* Create(LPDIRECT3DDEVICE9 pDevice, D3DXVECTOR3 vPos);

private:
	void CalculateOrtho(void);

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

	RECT					m_RcButtonRect;
	POINT						m_ptMouse;


	int				m_iNum;

};

#endif // Button1_h__
