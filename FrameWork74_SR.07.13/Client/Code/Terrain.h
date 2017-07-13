/*!
 * \file Terrain.h
 * \date 2017/07/06 10:28
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
#ifndef Terrain_h__
#define Terrain_h__

#include "GameObject.h"

namespace Engine
{
	class CTexture;
	class CVIBuffer;
	class CTransform;
}

class CCameraObserver;

class CTerrain
	: public Engine::CGameObject
{
public:
	explicit CTerrain(LPDIRECT3DDEVICE9 pDevice);

public:
	virtual ~CTerrain(void);

public:
	const Engine::VTXTEX* GetTerrainVtx(void);

public:
	virtual void Update(void);
	virtual void Render(void);

public:
	static CTerrain* Create(LPDIRECT3DDEVICE9 pDevice);

private:
	HRESULT Initialize(void);
	HRESULT	AddComponent(void);
	void Release(void);

private:
	Engine::CTexture*		m_pTexture;
	Engine::CVIBuffer*		m_pBuffer;
	Engine::CTransform*		m_pInfo;

private:
	CCameraObserver*		m_pCamObserver;

private:
	Engine::VTXTEX*			m_pVertex;
	Engine::VTXTEX*			m_pConvertVertex;
	DWORD					m_dwVtxCnt;

};

#endif // Terrain_h__