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
	class CCollision_OBB;

#ifdef _DEBUG
	class CCubeColor;
#endif
}

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
	static CCube* Create(LPDIRECT3DDEVICE9 pDevice, Engine::TILEINFO _TileInfo);

private:
	HRESULT Initialize(Engine::TILEINFO _TileInfo);
	HRESULT	AddComponent(void);
	void Release(void);

private:
	Engine::CTexture*		m_pTexture;
	Engine::CVIBuffer*		m_pBuffer;
	Engine::CTransform*		m_pInfo;
	Engine::CCollision_OBB*	m_pCollisionOBB;
	Engine::TILEINFO		m_tagTileInfo;

#ifdef _DEBUG
	Engine::CCubeColor*		m_pCubeColor;

	Engine::VTXCOL*	pVertex;
#endif


private:
	float			m_fSpeed;
	float			m_fAngle;
};


#endif // Cube_h__