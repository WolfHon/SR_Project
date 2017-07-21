#pragma once

#include "GameObject.h"
#include "Engine_Struct.h"

namespace Engine
{
	class CTexture;
	class CTransform;
	class CPlayerModel;
	class CMouseCol;
}

class CToolcameraObserver;
class CToolView;
class CPlayerAnimation
	: public Engine::CGameObject
{
public:
	explicit CPlayerAnimation(LPDIRECT3DDEVICE9 pDevice);

public:
	virtual ~CPlayerAnimation(void);

public:
	virtual Engine::OBJECT_RESULT Update(void);
	virtual void Render(void);

public:
	static CPlayerAnimation*	Create(LPDIRECT3DDEVICE9 pDevice);

private:
	HRESULT	Initialize(void);
	HRESULT	AddComponent(void);
	void	MoveCheck(void);
	void	Release();

public:
	void SetMainView(CToolView*	pView)
	{
		m_pMainView = pView;
	}

	void SetAnimation(Engine::ANIFRAME* _AniFrame);

private:
	Engine::CTexture*		m_pTexture;
	Engine::CTransform*		m_pInfo;
	Engine::CPlayerModel*	m_pPlayerModel;

private:
	vector<Engine::LPANIFRAME>		m_pAnimation;
	CToolView*		m_pMainView;
	Engine::ANIFRAME*	m_pAniFrame;
	float			m_fAngle;
	float			m_fSpeed;
};