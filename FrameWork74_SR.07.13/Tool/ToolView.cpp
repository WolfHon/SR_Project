
// ToolView.cpp : CToolView 클래스의 구현
//

#include "stdafx.h"
#include "Include.h"
#include "Tool.h"
#include "MainFrm.h"

#include "ToolDoc.h"
#include "ToolView.h"
#include "Device.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CToolView

IMPLEMENT_DYNCREATE(CToolView, CScrollView)

BEGIN_MESSAGE_MAP(CToolView, CScrollView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CToolView::OnFilePrintPreview)
	ON_WM_DESTROY()
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()

// CToolView 생성/소멸

CToolView::CToolView()
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CToolView::~CToolView()
{
}

BOOL CToolView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CToolView 그리기

void CToolView::OnDraw(CDC* /*pDC*/)
{
	CToolDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	CDevice::GetInstance()->Render_Begin();

	//무언가 그림을 그리면 된다.

	CDevice::GetInstance()->Render_End();

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
}


// CToolView 인쇄


void CToolView::OnFilePrintPreview()
{
	AFXPrintPreview(this);
}

BOOL CToolView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CToolView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CToolView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}

void CToolView::OnRButtonUp(UINT nFlags, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CToolView::OnContextMenu(CWnd* pWnd, CPoint point)
{
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
}


// CToolView 진단

#ifdef _DEBUG
void CToolView::AssertValid() const
{
	CView::AssertValid();
}

void CToolView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CToolDoc* CToolView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CToolDoc)));
	return (CToolDoc*)m_pDocument;
}

void CToolView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	SetScrollSizes(MM_TEXT, CSize(1 ) );


	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.]

	CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();
	//AfxGetMainWnd : 창 테두리를 얻어오는 함수.

	RECT rcWindow;

	//프레임의 사이즈를 얻어오자.
	pMainFrame->GetWindowRect(&rcWindow);


	//얻어온 프레임의 크기를 0,0기준으로 변경을 해주자.
	SetRect(&rcWindow,
		0,
		0,
		rcWindow.right - rcWindow.left,
		rcWindow.bottom - rcWindow.top);

	RECT rcMainView;

	//순수 View창의 크기를 얻어오자
	GetClientRect(&rcMainView);

	//가로 프레임의 길이를 구하자.
	float fX = float(rcWindow.right - rcMainView.right);

	float fY = float(rcWindow.bottom - rcMainView.bottom);

	pMainFrame->SetWindowPos(
		NULL,	//프레임의 크기를 계산한 상태로 출력위치를 결정하는 옵션
		0,
		0,
		int(WINCX + fX),
		int(WINCY + fY),
		SWP_NOZORDER);
	g_hWnd = m_hWnd;
	if(FAILED(CDevice::GetInstance()->InitGraphicDev()))
	{
		AfxMessageBox(L"Device Create Failed!");
	}

}

#endif //_DEBUG


// CToolView 메시지 처리기

void CToolView::OnDestroy()
{
	CScrollView::OnDestroy();

	CDevice::GetInstance()->DestroyInstance();

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
}

void CToolView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CScrollView::OnKeyDown(nChar, nRepCnt, nFlags);

	switch (nChar)
	{
	case VK_ESCAPE:

		//(CMainFrame*)AfxGetMainWnd()
		dynamic_cast<CMainFrame*>(AfxGetMainWnd())->DestroyWindow();

		break;
	}

}
