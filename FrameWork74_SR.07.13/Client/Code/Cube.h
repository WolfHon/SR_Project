/*!
 * \file Cube.h
 * \date 2017/07/13 10:19
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
#ifndef Cube_h__
#define Cube_h__

#include "GameObject.h"

namespace Engine
{
	class CTexture;
	class CVIBuffer;
	class CTransform;
	class CTerrainCol;
}

class CCameraObserver;

class CCube
	: public Engine::CGameObject
{
public:
	explicit CCube(LPDIRECT3DDEVICE9 pDevice);

public:
	virtual ~CCube(void);

public:
	virtual void Update(void);
	virtual void Render(void);

public:
	static CCube* Create(LPDIRECT3DDEVICE9 pDevice);

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
	Engine::VTXCUBE*		m_pVertex;
	Engine::VTXCUBE*		m_pConvertVertex;
	DWORD					m_dwVtxCnt;

private:
	float			m_fSpeed;
	float			m_fAngle;
};


#endif // Cube_h__