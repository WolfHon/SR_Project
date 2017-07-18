
// ToolView.cpp : CToolView 클래스의 구현
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
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CScrollView::OnFilePrintPreview)
	ON_WM_MOUSEMOVE()
	ON_WM_RBUTTONDOWN()
END_MESSAGE_MAP()

// CToolView 생성/소멸

CToolView::CToolView()
:m_pGraphicDev(Engine::Get_GraphicDev())
,m_pDevice(NULL)
{



	// TODO: 여기에 생성 코드를 추가합니다.}
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


	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
}


// CToolView 그리기

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
#endif //_DEBUG


// CToolView 메시지 처리기




void CToolView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CScrollView::OnMouseMove(nFlags, point);
	m_pCamera->SetPtPos(point);
}

void CToolView::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CScrollView::OnRButtonDown(nFlags, point);
	ScreenToClient(&point);
	m_pCamera->SetPtPos(point);

}
