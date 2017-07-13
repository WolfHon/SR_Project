/*!
 * \file Monster.h
 * \date 2017/07/10 11:33
 *
 * \author Administrator
 * Contact: user@company.com
 *
 * \brief 7
 *
 * TODO: long description
 *
 * \note
*/

#ifndef Monster_h__
#define Monster_h__

#include "GameObject.h"

namespace Engine
{
	class CTexture;
	class CVIBuffer;
	class CTransform;
	class CTerrainCol;
}

class CCameraObserver;

class CMonster
	: public Engine::CGameObject
{
public:
	explicit CMonster(LPDIRECT3DDEVICE9 pDevice);

public:
	virtual ~CMonster(void);

public:
	virtual void Update(void);
	virtual void Render(void);

public:
	static CMonster* Create(LPDIRECT3DDEVICE9 pDevice);

private:
	HRESULT Initialize(void);
	HRESULT	AddComponent(void);
	void Release(void);

private:
	Engine::CTexture*		m_pTexture;
	Engine::CVIBuffer*		m_pBuffer;
	Engine::CTransform*		m_pInfo;
	Engine::CTerrainCol*	m_pTerrainCol;

private:
	CCameraObserver*		m_pCamObserver;

private:
	Engine::VTXTEX*			m_pVertex;
	Engine::VTXTEX*			m_pConvertVertex;
	DWORD					m_dwVtxCnt;

private:
	float			m_fSpeed;
	float			m_fAngle;
};


#endif // Monster_h__