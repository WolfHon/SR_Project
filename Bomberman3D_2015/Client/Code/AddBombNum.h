
#ifndef AddBombNum_h__
#define AddBombNum_h__




#include "GameObject.h"

namespace Engine
{
	class CTexture;
	class CVIBuffer;
	class CTransform;
}

class CAddBombNum
	: public Engine::CGameObject
{

public:
	explicit CAddBombNum(LPDIRECT3DDEVICE9 pDevice);
public:
	virtual ~CAddBombNum(void);

public:
	virtual Engine::OBJECT_RESULT Update(void);
	virtual void Render(void);

public:
	static CAddBombNum* Create(LPDIRECT3DDEVICE9 pDevice, D3DXVECTOR3 vPos);

public:
	void SetiNum(int _inum)
	{
		m_iNum += _inum;
	}

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


	int				m_iNum;

};

#endif // AddBombNum_h__
