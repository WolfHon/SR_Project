


#ifndef PowerNum_h__
#define PowerNum_h__




#include "GameObject.h"

namespace Engine
{
	class CTexture;
	class CVIBuffer;
	class CTransform;
}

class CPowerNum
	: public Engine::CGameObject
{

public:
	explicit CPowerNum(LPDIRECT3DDEVICE9 pDevice);
public:
	virtual ~CPowerNum(void);

public:
	virtual Engine::OBJECT_RESULT Update(void);
	virtual void Render(void);

public:
	static CPowerNum* Create(LPDIRECT3DDEVICE9 pDevice, D3DXVECTOR3 vPos);

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

#endif // PowerNum_h__

