#ifndef ToolCube_h__
#define ToolCube_h__

#include "GameObject.h"

namespace Engine
{
	class CTexture;
	class CVIBuffer;
	class CTransform;
	class CTerrainCol;
	class CMouseCol;
}
class CToolcameraObserver;
class CToolView;
class CToolCube
	:public Engine::CGameObject
{
public:
	explicit CToolCube(LPDIRECT3DDEVICE9 pDevice);

public:
	virtual ~CToolCube(void);

public:
	virtual void Update(void);
	virtual void Render(void);

public:
	static CToolCube* Create(LPDIRECT3DDEVICE9 pDevice);

public:
	void SetMainView(CToolView* pView)
	{
		m_pMainView = pView;
	}


public:
	HRESULT Initialize(void);
	HRESULT	AddComponent(void);
	void Release(void);

private:
	Engine::CTexture*		m_pTexture;
	Engine::CVIBuffer*		m_pBuffer;
	Engine::CTransform*		m_pInfo;
	Engine::CTerrainCol*	m_pTerrainCol;

private:
	CToolcameraObserver*		m_pCamObserver;

private:
	Engine::VTXCUBE*		m_pVertex;
	Engine::VTXCUBE*		m_pConvertVertex;
	DWORD					m_dwVtxCnt;

private:
	float			m_fSpeed;
	float			m_fAngle;
	CToolView*		m_pMainView;

};

#endif // ToolCube_h__