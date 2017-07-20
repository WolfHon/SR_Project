#ifndef Monster_h__
#define Monster_h__

#include "GameObject.h"

namespace Engine
{
	class CTexture;
	class CTransform;

	
	class CPlayerModel;

	class CVIBuffer;
}

class CCollision_OBB;

class CMonster
	:public Engine::CGameObject
{

public:
	explicit CMonster(LPDIRECT3DDEVICE9 pDevice);

public:
	virtual ~CMonster(void);

public:
	virtual Engine::OBJECT_RESULT Update(void);
	virtual void Render(void);

public:
	static CMonster* Create(LPDIRECT3DDEVICE9 pDevice);

private:
	HRESULT Initialize(void);
	HRESULT	AddComponent(void);
	void MoveCheck(void);
	BOOL CheckCollision(void);
	void Release(void);
	void AI(void);
	void ChangeDir(D3DXVECTOR3 _dir);

private:
	Engine::CTexture*		m_pTexture;
	Engine::CTransform*		m_pInfo;
	Engine::CPlayerModel*	m_pPlayerModel;
	Engine::CVIBuffer*		m_pBuffer;

	CCollision_OBB*	m_pCollisionOBB;



private:	
	float			m_fSpeed;
	float			m_fAngle;

};
#endif // Monster_h__