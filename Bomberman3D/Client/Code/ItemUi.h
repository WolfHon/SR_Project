#ifndef ItemUi_h__
#define ItemUi_h__

#include "GameObject.h"

namespace Engine
{
	class CTexture;
	class CVIBuffer;
	class CTransform;
}

class CItemUi
	: public Engine::CGameObject
{

public:
	explicit CItemUi(LPDIRECT3DDEVICE9 pDevice);
public:
	virtual ~CItemUi(void);

public:
	virtual Engine::OBJECT_RESULT Update(void);
	virtual void Render(void);

	


public:
	static CItemUi* Create(LPDIRECT3DDEVICE9 pDevice, D3DXVECTOR3 vPos);
	
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




};

#endif // ItemUi_h__