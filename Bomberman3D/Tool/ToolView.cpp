
// ToolView.cpp : CToolView Ŭ������ ����
#include "stdafx.h"
#include "Tool.h"

#include "ToolDoc.h"
#include "ToolView.h"
#include "Export_Function.h"
#include "Include.h"
#include "RcTex.h"
#include "ResourceMgr.h"
#include "Export_Resource.h"
#include "AddCube.h"
#include "MainFrm.h"

#include "ToolCube.h"
#include "Layer.h"
#include "GameObject.h"
#include "Transform.h"
#include "Scene.h"
#include "ToolCamera.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CToolView

IMPLEMENT_DYNCREATE(CToolView, CScrollView)

BEGIN_MESSAGE_MAP(CToolView, CScrollView)
	// ǥ�� �μ� ����Դϴ�.
	ON_COMMAND(ID_FILE_PRINT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CScrollView::OnFilePrintPreview)
	ON_WM_MOUSEMOVE()
	ON_WM_RBUTTONDOWN()
END_MESSAGE_MAP()

// CToolView ����/�Ҹ�

CToolView::CToolView()
:m_pGraphicDev(Engine::Get_GraphicDev())
,m_pDevice(NULL)
{



	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.}
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

void CToolView::OnInitialUpdate()
{
	//TILECX * TILEX, (TILECY * 0.5f) * TILEY 
	CView::OnInitialUpdate();


	SetScrollSizes(MM_TEXT, CSize(1) );

	g_hWnd = m_hWnd;

	m_pGraphicDev->InitGraphicDev(Engine::CGraphicDev::MODE_WIN
		, g_hWnd, WINCX, WINCY);

	m_pDevice = m_pGraphicDev->GetDevice();

	m_pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	Engine::Get_ResourceMgr()->AddBuffer(m_pDevice, Engine::RESOURCE_DYNAMIC
		, Engine::BUFFER_CUBETEX, L"Buffer_CubeTex");

	Engine::Get_ResourceMgr()->AddTexture(m_pDevice, Engine::RESOURCE_DYNAMIC
		, Engine::TEXTURE_CUBE, L"BreakCube"
		, L"../Client/bin/Texture/Block/Block%d.dds", 8);

	//Engine::Get_ResourceMgr()->AddTexture(m_pDevice, Engine::RESOURCE_DYNAMIC
	//	, Engine::TEXTURE_CUBE, L"UnBreakCubeFirst"
	//	, L"../Client/bin/Texture/Block/Block_Broken%d.dds", 0);

	//Engine::Get_ResourceMgr()->AddTexture(m_pDevice, Engine::RESOURCE_DYNAMIC
	//	, Engine::TEXTURE_CUBE, L"UnBreakCubeSecond"
	//	, L"../Client/bin/Texture/Box/UnbreakBox/Second/UnBreakBox%d.dds", 1);

	//Engine::Get_ResourceMgr()->AddTexture(m_pDevice, Engine::RESOURCE_DYNAMIC
	//	, Engine::TEXTURE_CUBE, L"ElseCube"
	//	, L"../Client/bin/Texture/Box/Else/Else1/Else%d.dds", 1);

	
	//CAddCube* pAddCube= ((CMainFrame*)AfxGetMainWnd())->GetAddCube();

	//vector<CToolCube*>::iterator iter = m_vecCube.begin();
	//vector<CToolCube*>::iterator iter_end= m_vecCube.end();

	//for( ;iter != iter_end ; ++iter)
	//{
	//	(*iter)->SetMainView(this);
	//}

	
	
	m_pCamera = CToolCamera::Create(m_pDevice);

	Engine::Get_Management()->InitManagement(m_pDevice);


	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
}


// CToolView �׸���

void CToolView::OnDraw(CDC* pDC)
{
	CToolDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	m_pDevice->Clear(0, NULL
		, D3DCLEAR_STENCIL | D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER
		, D3DCOLOR_ARGB(255, 0, 0, 255), 1.f, 0);
	m_pDevice->BeginScene();

	vector<CToolCube*>::iterator iter = m_vecCube.begin();
	vector<CToolCube*>::iterator iter_end= m_vecCube.end();
	for( ;iter != iter_end ; ++iter)
	{
		(*iter)->Update();
		(*iter)->Render();
	}

	
	m_pCamera->Update();

	Invalidate(FALSE);

	m_pDevice->EndScene();
	m_pDevice->Present(NULL, NULL, NULL, NULL);
	

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
#endif //_DEBUG


// CToolView �޽��� ó����




void CToolView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	CScrollView::OnMouseMove(nFlags, point);
	m_pCamera->SetPtPos(point);
}

void CToolView::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	CScrollView::OnRButtonDown(nFlags, point);
	ScreenToClient(&point);
	m_pCamera->SetPtPos(point);

}
