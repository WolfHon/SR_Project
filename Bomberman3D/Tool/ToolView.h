
// ToolView.h : CToolView 클래스의 인터페이스
//


#pragma once

#include "Engine_Include.h"

namespace Engine
{
	class CGraphicDev;
	class CVIBuffer;
	class CTexture;
	class CLayer;
}

class CPlayerAnimation;
class CToolSlopeCube;
class CLayer;
class CToolCamera;
class CToolCube;
class CToolDoc;
class CToolView 
	: public CScrollView
{
public:


private:
	CToolCube*	m_pCube;
	CToolCamera* m_pCamera;
	CPlayerAnimation*	m_pPlayer;

	vector<CToolCube*>	m_vecCube;
	vector<CToolSlopeCube*> m_vecSlopeCube;
protected: // serialization에서만 만들어집니다.
	CToolView();
	DECLARE_DYNCREATE(CToolView)

// 특성입니다.
public:
	CToolDoc* GetDocument() const;

// 작업입니다.
public:
	CToolCube* GetCube(void)
	{
		return m_pCube;
	}
	CPlayerAnimation*	GetModel()
	{
		return	m_pPlayer;
	}
	LPDIRECT3DDEVICE9 GetDevice(void)
	{
		return m_pDevice;
	}
public:
	void SetVec(vector<CToolCube*> _vec)
	{
		m_vecCube = _vec;
	}

	void SetVecSlope(vector<CToolSlopeCube*> _vec)
	{
		m_vecSlopeCube = _vec;
	}

	void SetPlayer(CPlayerAnimation*	_Player)
	{
		m_pPlayer = _Player;
		m_bPlayerIn = true;
	}
// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 구현입니다.
public:
	virtual ~CToolView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

private:
	Engine::CGraphicDev*		m_pGraphicDev;
	LPDIRECT3DDEVICE9			m_pDevice;

private:
	Engine::CVIBuffer*			m_pBuffer;
	Engine::CTexture*			m_pTextre;

	D3DXVECTOR3 m_pt;
	bool		m_click;
	bool		m_bPlayerIn;


private:
	typedef map<WORD, CLayer*>		MAPLAYER;
	MAPLAYER		m_mapLayer;

protected:

// 생성된 메시지 맵 함수
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();

	
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
};

#ifndef _DEBUG  // ToolView.cpp의 디버그 버전
inline CToolDoc* CToolView::GetDocument() const
   { return reinterpret_cast<CToolDoc*>(m_pDocument); }
#endif

