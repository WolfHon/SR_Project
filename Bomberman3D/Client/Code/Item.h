#ifndef Item_h__
#define Item_h__

#include "GameObject.h"

namespace Engine
{
	class CTexture;
	class CVIBuffer;
	class CTransform;
}

class CCollision_OBB;
class CItem
	:public Engine::CGameObject
{
public:
	explicit CItem(LPDIRECT3DDEVICE9 pDevice);

public:
	virtual ~CItem(void);

public:
	virtual Engine::OBJECT_RESULT Update(void);
	virtual void Render(void);

public:
	static CItem* create(LPDIRECT3DDEVICE9 pDevice, D3DXVECTOR3 vpos, Engine::ITEMOPTION _ItemOption);


private:
	HRESULT Initialize(D3DXVECTOR3 vPos, Engine::ITEMOPTION _ItemOption);
	HRESULT	AddComponent(void);
	BOOL CheckCollision(void);
	//Engine::OBJECT_RESULT Explosion(void);
	void Release(void);


private:
	Engine::CTexture*		m_pTexture;
	Engine::CVIBuffer*		m_pBuffer;
	Engine::CTransform*		m_pInfo;

	Engine::ITEMOPTION     m_tagItemOption;



	CCollision_OBB*	m_pCollisionOBB;

	float       m_fPlayerSpeed;
	int			m_iAddBomb;
	float		m_fPower;



	int				m_inum;
};

#endif // Item_h__