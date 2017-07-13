
// ToolView.cpp : CToolView Ŭ������ ����
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
	// ǥ�� �μ� ����Դϴ�.
	ON_COMMAND(ID_FILE_PRINT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CToolView::OnFilePrintPreview)
	ON_WM_DESTROY()
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()

// CToolView ����/�Ҹ�

CToolView::CToolView()
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.

}

CToolView::~CToolView()
{
}

BOOL CToolView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	return CView::PreCreateWindow(cs);
}

// CToolView �׸���

void CToolView::OnDraw(CDC* /*pDC*/)
{
	CToolDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	CDevice::GetInstance()->Render_Begin();

	//���� �׸��� �׸��� �ȴ�.

	CDevice::GetInstance()->Render_End();

	// TODO: ���⿡ ���� �����Ϳ� ���� �׸��� �ڵ带 �߰��մϴ�.
}


// CToolView �μ�


void CToolView::OnFilePrintPreview()
{
	AFXPrintPreview(this);
}

BOOL CToolView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// �⺻���� �غ�
	return DoPreparePrinting(pInfo);
}

void CToolView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ��ϱ� ���� �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
}

void CToolView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ� �� ���� �۾��� �߰��մϴ�.
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


// CToolView ����

#ifdef _DEBUG
void CToolView::AssertValid() const
{
	CView::AssertValid();
}

void CToolView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CToolDoc* CToolView::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CToolDoc)));
	return (CToolDoc*)m_pDocument;
}

void CToolView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	SetScrollSizes(MM_TEXT, CSize(1 ) );


	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.]

	CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();
	//AfxGetMainWnd : â �׵θ��� ������ �Լ�.

	RECT rcWindow;

	//�������� ����� ������.
	pMainFrame->GetWindowRect(&rcWindow);


	//���� �������� ũ�⸦ 0,0�������� ������ ������.
	SetRect(&rcWindow,
		0,
		0,
		rcWindow.right - rcWindow.left,
		rcWindow.bottom - rcWindow.top);

	RECT rcMainView;

	//���� Viewâ�� ũ�⸦ ������
	GetClientRect(&rcMainView);

	//���� �������� ���̸� ������.
	float fX = float(rcWindow.right - rcMainView.right);

	float fY = float(rcWindow.bottom - rcMainView.bottom);

	pMainFrame->SetWindowPos(
		NULL,	//�������� ũ�⸦ ����� ���·� �����ġ�� �����ϴ� �ɼ�
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


// CToolView �޽��� ó����

void CToolView::OnDestroy()
{
	CScrollView::OnDestroy();

	CDevice::GetInstance()->DestroyInstance();

	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
}

void CToolView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	CScrollView::OnKeyDown(nChar, nRepCnt, nFlags);

	switch (nChar)
	{
	case VK_ESCAPE:

		//(CMainFrame*)AfxGetMainWnd()
		dynamic_cast<CMainFrame*>(AfxGetMainWnd())->DestroyWindow();

		break;
	}

}
