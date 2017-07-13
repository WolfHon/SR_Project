/*!
 * \file Player.h
 * \date 2017/07/06 11:13
 *
 * \author Administrator
 * Contact: user@company.com
 *
 * \brief 
 *
 * TODO: long description
 *
 * \note
*/

#ifndef Player_h__
#define Player_h__

#include "GameObject.h"

namespace Engine
{
	class CTexture;
	class CVIBuffer;
	class CTransform;
	class CTerrainCol;
	class CMouseCol;
}

class CCameraObserver;

class CPlayer
	: public Engine::CGameObject
{
public:
	explicit CPlayer(LPDIRECT3DDEVICE9 pDevice);

public:
	virtual ~CPlayer(void);

public:
	virtual void Update(void);
	virtual void Render(void);

public:
	static CPlayer* Create(LPDIRECT3DDEVICE9 pDevice);

private:
	HRESULT Initialize(void);
	HRESULT	AddComponent(void);
	void KeyCheck(void);
	void Move(void);
	void Release(void);

private:
	Engine::CTexture*		m_pTexture;
	Engine::CVIBuffer*		m_pBuffer;
	Engine::CTransform*		m_pInfo;
	Engine::CTerrainCol*	m_pTerrainCol;
	Engine::CMouseCol*		m_pMouseCol;

private:
	CCameraObserver*		m_pCamObserver;

private:
	Engine::VTXTEX*			m_pVertex;
	Engine::VTXTEX*			m_pConvertVertex;
	DWORD					m_dwVtxCnt;

private:
	D3DXVECTOR3		m_vDestPos;
	bool			m_bMove;
	float			m_fSpeed;
	float			m_fAngle;
};

#endif // Player_h__