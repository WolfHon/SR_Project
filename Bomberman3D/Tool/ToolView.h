
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
	LPDIRECT3DDEVICE9 GetDevice(void)
	{
		return m_pDevice;
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


private:
	typedef map<WORD, CLayer*>		MAPLAYER;
	MAPLAYER		m_mapLayer;

protected:

// 생성된 메시지 맵 함수
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();

	
};

#ifndef _DEBUG  // ToolView.cpp의 디버그 버전
inline CToolDoc* CToolView::GetDocument() const
   { return reinterpret_cast<CToolDoc*>(m_pDocument); }
#endif

