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
	static CToolCube* Create(LPDIRECT3DDEVICE9 pDevice, Engine::TILEINFO _tileInfo );

public:
	void SetMainView(CToolView* pView)
	{
		m_pMainView = pView;
	}
	void SetInfoX(float _X)
	{
		m_TileInfo.vPos.x = _X;
	}
	void SetInfoY(float _Y)
	{
		m_TileInfo.vPos.y = _Y;
	}
	void SetInfoZ(float _Z)
	{
		m_TileInfo.vPos.z = _Z;
	}
	void SetOption(int _option)
	{
		m_TileInfo.eTileOption = (Engine::TILETYPE)_option;
	}

	Engine::TILEINFO GetInfo(void)
	{
		return m_TileInfo;
	}


public:
	HRESULT Initialize(Engine::TILEINFO _tileInfo);
	HRESULT	AddComponent(Engine::TILEINFO _tileInfo);
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
	Engine::TILEINFO		m_TileInfo;
	DWORD					m_dwVtxCnt;
	

private:
	float			m_fSpeed;
	float			m_fAngle;
	CToolView*		m_pMainView;
	Engine::TILETYPE				m_eTileOption;
	Engine::TILETEXTURE				m_eTexture;



};

#endif // ToolCube_h__