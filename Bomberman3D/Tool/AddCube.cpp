// AddCube.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Tool.h"
#include "AddCube.h"

#include "Engine_Include.h"
#include "Export_Function.h"
#include "Include.h"
#include "ToolCube.h"
#include "MainFrm.h"
#include "ToolView.h"
#include "ToolSlopeCube.h"


void CAddCube::Release( void )
{
	vector<CToolCube*>::iterator iter = m_vecCube.begin();
	vector<CToolCube*>::iterator iter_end = m_vecCube.end();

	for( ;iter != iter_end ; ++iter)
	{
		Safe_Delete(*iter);
	}

	m_vecCube.clear();
	m_vecTileInfo.clear();
}



// CAddCube 대화 상자입니다.

IMPLEMENT_DYNAMIC(CAddCube, CDialog)

CAddCube::CAddCube(CWnd* pParent /*=NULL*/)
	: CDialog(CAddCube::IDD, pParent)
	,m_bRadioButtonStartCheck(true)
	,m_CubeListBoxIndex(0)
	,m_SlopeListBoxIndex(0)
	,m_vPos(0.f, 0.f, 0.f)
	,m_vScale(1.f, 1.f, 1.f)
	,m_fAngle(0.f)
{



}

CAddCube::~CAddCube()
{
	Release();
}

void CAddCube::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDITXPOS, m_vPos.x);
	DDX_Text(pDX, IDC_EDITYPOS, m_vPos.y);
	DDX_Text(pDX, IDC_EDITZPOS, m_vPos.z);
	DDX_Text(pDX, IDC_EDITZPOS2, m_vScale.x );
	DDX_Text(pDX, IDC_EDITZPOS3, m_vScale.y );
	DDX_Text(pDX, IDC_EDITZPOS4, m_vScale.z );
	DDX_Control(pDX, IDC_LIST1, m_ListBox);
	DDX_Control(pDX, IDC_RADIO1, m_Radio[0]);
	DDX_Control(pDX, IDC_RADIO2, m_Radio[1]);
	DDX_Control(pDX, IDC_RADIO3, m_Radio[2]);
	DDX_Control(pDX, IDC_RADIO4, m_Radio1[0]);
	DDX_Control(pDX, IDC_RADIO5, m_Radio1[1]);

	if(m_bRadioButtonStartCheck)
	{
		m_Radio[0].SetCheck(TRUE);
		m_bRadioButtonStartCheck = false;
	}

	DDX_Control(pDX, IDC_LIST2, m_ListBox1);
	DDX_Control(pDX, IDC_LIST3, m_SlopList);
	DDX_Control(pDX, IDC_CHECK1, m_ScaleCheck);

}


BEGIN_MESSAGE_MAP(CAddCube, CDialog)
	ON_BN_CLICKED(IDC_ADDCUBE, &CAddCube::OnBnClickedAddcube)
	ON_LBN_SELCHANGE(IDC_LIST1, &CAddCube::OnLbnSelchangeList1)
	ON_BN_CLICKED(IDC_BUTTON5, &CAddCube::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_DECREASEX, &CAddCube::OnBnClickedDecreasex)
	ON_BN_CLICKED(IDC_INCREASEX, &CAddCube::OnBnClickedIncreasex)
	ON_BN_CLICKED(IDC_DECREASEY, &CAddCube::OnBnClickedDecreasey)
	ON_BN_CLICKED(IDC_INCREASEY, &CAddCube::OnBnClickedIncreasey)
	ON_BN_CLICKED(IDC_DECREASEZ, &CAddCube::OnBnClickedDecreasez)
	ON_BN_CLICKED(IDC_INCREASEZ, &CAddCube::OnBnClickedIncreasez)
	ON_BN_CLICKED(IDC_RADIO1, &CAddCube::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO2, &CAddCube::OnBnClickedRadio2)
	ON_BN_CLICKED(IDC_BACKCUBE, &CAddCube::OnBnClickedBackcube)
	ON_LBN_SELCHANGE(IDC_LIST2, &CAddCube::OnLbnSelchangeList2)
	ON_BN_CLICKED(IDC_SAVECUBE, &CAddCube::OnBnClickedSavecube)
	ON_BN_CLICKED(IDC_LOADCUBE, &CAddCube::OnBnClickedLoadcube)
	ON_BN_CLICKED(IDC_RADIO3, &CAddCube::OnBnClickedRadio3)
	ON_BN_CLICKED(IDC_RADIO4, &CAddCube::OnBnClickedRadio4)
	ON_BN_CLICKED(IDC_RADIO5, &CAddCube::OnBnClickedRadio5)
	ON_LBN_SELCHANGE(IDC_LIST3, &CAddCube::OnLbnSelchangeList3)
	ON_BN_CLICKED(IDC_DECREASEAngle, &CAddCube::OnBnClickedDecreaseangle)
	ON_BN_CLICKED(IDC_INCREASEAngle, &CAddCube::OnBnClickedIncreaseangle)
END_MESSAGE_MAP()
 

// CAddCube 메시지 처리기입니다.



void CAddCube::OnBnClickedAddcube()
{
	UpdateData(TRUE);

	m_vScale = D3DXVECTOR3(1.f , 1.f, 1.f);
	m_fAngle = 0.f;

	CToolView* pAddCube = ((CMainFrame*)AfxGetMainWnd())->GetMainView();

	m_TileInfo.vPos.x = m_vPos.x;
	m_TileInfo.vPos.y = m_vPos.y;
	m_TileInfo.vPos.z = m_vPos.z;

	if(m_Radio1[0].GetCheck())
	{
	
				m_TileInfo.eTileShape = Engine::TILE_CUBE;
				m_pCube = CToolCube::Create(pAddCube->GetDevice() , m_TileInfo);

				m_vecCube.push_back(m_pCube);

				Engine::TILEINFO tagTile;
				tagTile = m_pCube->GetInfo();
				m_vecTileInfo.push_back(tagTile);

				CToolView* pToolView= ((CMainFrame*)AfxGetMainWnd())->GetMainView();
				pToolView->SetVec(m_vecCube);

				TCHAR szText[256] = L"";
				wsprintf(szText, L"큐브 %d", m_vecCube.size() -1);
				m_ListBox.AddString(szText);


	}
	else
	{
		m_TileInfo.eTileShape = Engine::TILE_SLOPE;
		m_pSlopeCube = CToolSlopeCube::Create(pAddCube->GetDevice(), m_TileInfo);
		m_vecSlopeCube.push_back(m_pSlopeCube);

		Engine::TILEINFO tagTile;
		tagTile = m_pSlopeCube->GetInfo();
		m_vecTileInfo.push_back(tagTile);

		CToolView* pToolView= ((CMainFrame*)AfxGetMainWnd())->GetMainView();
		pToolView->SetVecSlope(m_vecSlopeCube);

		TCHAR szText[256] = L"";
		wsprintf(szText, L"슬로프 큐브 %d", m_vecSlopeCube.size() -1 );
		m_SlopList.AddString(szText);
	}
	
	UpdateData(FALSE);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}
void CAddCube::OnLbnSelchangeList2()
{
	UpdateData(TRUE);
	

	int iSelect = m_ListBox1.GetCurSel();

	if(iSelect < 0)
		return;

	switch(iSelect)
	{

	case 0:
		m_TileInfo.eTexture = Engine::TILE_IMAGE0;
		break;

	case 1:
		m_TileInfo.eTexture = Engine::TILE_IMAGE1;
		break;

	case 2:
		m_TileInfo.eTexture = Engine::TILE_IMAGE2;
		break;

	case 3:
		m_TileInfo.eTexture = Engine::TILE_IMAGE3;
		break;
		
	case 4:
		m_TileInfo.eTexture = Engine::TILE_IMAGE4;
		break;

	case 5:
		m_TileInfo.eTexture = Engine::TILE_IMAGE5;
		break;

	case 6:
		m_TileInfo.eTexture = Engine::TILE_IMAGE6;
		break;

	case 7:
		m_TileInfo.eTexture = Engine::TILE_IMAGE7;
		break;

	case 8:
		m_TileInfo.eTexture = Engine::TILE_IMAGE8;
		break;

	}	

	UpdateData(FALSE);

	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CAddCube::OnLbnSelchangeList1()
{
	UpdateData(TRUE);

	for(int i =0; i < 2 ; ++i)
		m_Radio1[i].SetCheck(FALSE);

	m_CubeListBoxIndex = m_ListBox.GetCurSel();

	if(m_CubeListBoxIndex < 0)
		return;	

	m_vPos.x =m_vecCube[m_CubeListBoxIndex]->GetInfo().vPos.x;
	m_vPos.y =m_vecCube[m_CubeListBoxIndex]->GetInfo().vPos.y;
	m_vPos.z =m_vecCube[m_CubeListBoxIndex]->GetInfo().vPos.z;


	for(int i = 0; i < 3; ++i)
		m_Radio[i].SetCheck(FALSE);

	int iA = (int)(m_vecCube[m_CubeListBoxIndex]->GetInfo().eTileOption);

	m_Radio[iA].SetCheck(TRUE);
	m_Radio1[0].SetCheck(TRUE);


	UpdateData(FALSE);
	
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

void CAddCube::OnLbnSelchangeList3()
{
	UpdateData(TRUE);

	for(int i =0; i < 2 ; ++i)
		m_Radio1[i].SetCheck(FALSE);


	m_SlopeListBoxIndex = m_SlopList.GetCurSel();

	if(m_SlopeListBoxIndex < 0 )
		return;

	m_vPos.x = m_vecSlopeCube[m_SlopeListBoxIndex]->GetInfo().vPos.x;
	m_vPos.y = m_vecSlopeCube[m_SlopeListBoxIndex]->GetInfo().vPos.y;
	m_vPos.z = m_vecSlopeCube[m_SlopeListBoxIndex]->GetInfo().vPos.z;


	for(int i = 0; i < 3; ++i)
		m_Radio[i].SetCheck(FALSE);

	int iA = (int)(m_vecSlopeCube[m_SlopeListBoxIndex]->GetInfo().eTileOption);

	m_Radio[iA].SetCheck(TRUE);
	m_Radio1[1].SetCheck(TRUE);


	UpdateData(FALSE);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CAddCube::OnBnClickedDecreasex()
{
	UpdateData(TRUE);

	if(m_ScaleCheck.GetCheck() == FALSE)
	{
		m_vPos.x -= 1.f;
		if(m_Radio1[0].GetCheck())
		{
			m_vecCube[m_CubeListBoxIndex]->SetInfoX(m_vPos.x);
		}
		else
		{
			m_vecSlopeCube[m_SlopeListBoxIndex]->SetInfoX(m_vPos.x);
		}
	}
	else
	{		m_vScale.x -= 0.1f;
		if(m_Radio1[0].GetCheck())
		{
			m_vecCube[m_CubeListBoxIndex]->SetScale(m_vScale);
		}
		else
		{
			m_vecSlopeCube[m_SlopeListBoxIndex]->SetScale(m_vScale);
		}

	}
	UpdateData(FALSE);
	
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

void CAddCube::OnBnClickedIncreasex()
{
	UpdateData(TRUE);
	if(m_ScaleCheck.GetCheck() == FALSE)
		{
			m_vPos.x += 1.f;
			if(m_Radio1[0].GetCheck())
		{
			m_vecCube[m_CubeListBoxIndex ]->SetInfoX(m_vPos.x);
		}
		else
		{
			m_vecSlopeCube[m_SlopeListBoxIndex ]->SetInfoX(m_vPos.x);
		}
	}
	else
	{
		m_vScale.x += 0.1f;
		if(m_Radio1[0].GetCheck())
		{
			m_vecCube[m_CubeListBoxIndex]->SetScale(m_vScale);
		}
		else
		{
			m_vecSlopeCube[m_SlopeListBoxIndex]->SetScale(m_vScale);
		}

	}
	UpdateData(FALSE);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

void CAddCube::OnBnClickedDecreasey()
{
	UpdateData(TRUE);
	if(m_ScaleCheck.GetCheck() == FALSE)
	{
		m_vPos.y -= 1.f;
		if(m_Radio1[0].GetCheck())
		{
			m_vecCube[m_CubeListBoxIndex ]->SetInfoY(m_vPos.y);
		}
		else
		{
			m_vecSlopeCube[m_SlopeListBoxIndex]->SetInfoY(m_vPos.y);
		}
		}
	else
	{
		m_vScale.y -= 0.1f;
		if(m_Radio1[0].GetCheck())
		{
			m_vecCube[m_CubeListBoxIndex]->SetScale(m_vScale);
		}
		else
		{
			m_vecSlopeCube[m_SlopeListBoxIndex]->SetScale(m_vScale);
		}

	}

	UpdateData(FALSE);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

void CAddCube::OnBnClickedIncreasey()
{
	UpdateData(TRUE);
	if(m_ScaleCheck.GetCheck() == FALSE)
	{
		m_vPos.y += 1.f;
		if(m_Radio1[0].GetCheck())
		{
			m_vecCube[m_CubeListBoxIndex ]->SetInfoY(m_vPos.y);
		}
		else
		{
			m_vecSlopeCube[m_SlopeListBoxIndex ]->SetInfoY(m_vPos.y);
		}
		}
	else
	{
		m_vScale.y += 0.1f;
		if(m_Radio1[0].GetCheck())
		{
			m_vecCube[m_CubeListBoxIndex]->SetScale(m_vScale);
		}
		else
		{
			m_vecSlopeCube[m_SlopeListBoxIndex]->SetScale(m_vScale);
		}

	}
		UpdateData(FALSE);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

void CAddCube::OnBnClickedDecreasez()
{
	UpdateData(TRUE);
	if(m_ScaleCheck.GetCheck() == FALSE)
	{
		m_vPos.z -= 1.f;
		if(m_Radio1[0].GetCheck())
		{
			m_vecCube[m_CubeListBoxIndex ]->SetInfoZ(m_vPos.z);
		}
		else
		{
			m_vecSlopeCube[m_SlopeListBoxIndex]->SetInfoZ(m_vPos.z);
		}
	}
	else
	{
		m_vScale.z -= 0.1f;
		if(m_Radio1[0].GetCheck())
		{
			m_vecCube[m_CubeListBoxIndex]->SetScale(m_vScale);
		}
		else
		{
			m_vecSlopeCube[m_SlopeListBoxIndex]->SetScale(m_vScale);
		}

	}
	UpdateData(FALSE);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

void CAddCube::OnBnClickedIncreasez()
{
	UpdateData(TRUE);
	if(m_ScaleCheck.GetCheck() == FALSE)
	{
		m_vPos.z += 1.f;
		if(m_Radio1[0].GetCheck())
		{
			m_vecCube[m_CubeListBoxIndex ]->SetInfoZ(m_vPos.z);
		}
		else
		{
			m_vecSlopeCube[m_SlopeListBoxIndex]->SetInfoZ(m_vPos.z);
		}
		}
	else
	{
		m_vScale.z += 0.1f;
		if(m_Radio1[0].GetCheck())
		{
			m_vecCube[m_CubeListBoxIndex]->SetScale(m_vScale);
		}
		else
		{
			m_vecSlopeCube[m_SlopeListBoxIndex]->SetScale(m_vScale);
		}

	}
	UpdateData(FALSE);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

void CAddCube::OnBnClickedDecreaseangle()
{
	UpdateData(TRUE);
	if(m_ScaleCheck.GetCheck() == FALSE)
	{
		m_fAngle += D3DXToRadian(90.f);
		if(m_Radio1[0].GetCheck())
		{
			m_vecCube[m_CubeListBoxIndex]->SetAngle(m_fAngle);
		}
		else
		{
			m_vecSlopeCube[m_SlopeListBoxIndex]->SetAngle(m_fAngle);
		}
	}
	else
	{
		m_fAngle += D3DXToRadian(90.f);
		if(m_Radio1[0].GetCheck())
		{
			m_vecCube[m_CubeListBoxIndex]->SetAngle(m_fAngle);
		}
		else
		{
			m_vecSlopeCube[m_SlopeListBoxIndex]->SetAngle(m_fAngle);
		}

	}
	UpdateData(FALSE);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

void CAddCube::OnBnClickedIncreaseangle()
{
	UpdateData(TRUE);
	if(m_ScaleCheck.GetCheck() == FALSE)
	{
		m_fAngle -= D3DXToRadian(90.f);
		if(m_Radio1[0].GetCheck())
		{
			m_vecCube[m_CubeListBoxIndex]->SetAngle(m_fAngle);
		}
		else
		{
			m_vecSlopeCube[m_SlopeListBoxIndex]->SetAngle(m_fAngle);
		}
	}
	else
	{
		m_fAngle -= D3DXToRadian(90.f);
		if(m_Radio1[0].GetCheck())
		{
			m_vecCube[m_CubeListBoxIndex]->SetAngle(m_fAngle);
		}
		else
		{
			m_vecSlopeCube[m_SlopeListBoxIndex]->SetAngle(m_fAngle);
		}

	}
	UpdateData(FALSE);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}



void CAddCube::OnBnClickedRadio1()
{
	UpdateData(TRUE);
	m_iEnum = 0;

	UpdateData(FALSE);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

void CAddCube::OnBnClickedRadio2()
{
	UpdateData(TRUE);
	m_iEnum = 1;


	UpdateData(FALSE);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}
void CAddCube::OnBnClickedRadio3()
{
	UpdateData(TRUE);
	m_iEnum = 2;

	UpdateData(FALSE);

	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CAddCube::OnBnClickedButton5()
{
	UpdateData(TRUE);
	if(m_Radio1[0].GetCheck())
	{
	m_vecCube[m_CubeListBoxIndex]->SetOption(m_iEnum);
	m_vecCube[m_CubeListBoxIndex]->SetScale(m_v)
	}
	else
	{
	m_vecSlopeCube[m_SlopeListBoxIndex]->SetOption(m_iEnum);
	}
	UpdateData(FALSE);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}



void CAddCube::OnBnClickedBackcube()
{
	UpdateData(TRUE);

	CString strName;

	if(m_Radio1[0].GetCheck())
	{
	int iSelect = m_ListBox.GetCurSel();

	if(iSelect < 0)
		return;

	m_ListBox.GetText(iSelect , strName);
	m_ListBox.DeleteString(iSelect);

	m_vecCube.erase(m_vecCube.begin() + m_CubeListBoxIndex);
	CToolView* pToolView= ((CMainFrame*)AfxGetMainWnd())->GetMainView();
	pToolView->SetVec(m_vecCube);
	}
	else
	{
		int iSelect = m_SlopList.GetCurSel();

		if(iSelect < 0)
			return;

		m_SlopList.GetText(iSelect , strName);
		m_SlopList.DeleteString(iSelect);

		m_vecSlopeCube.erase(m_vecSlopeCube.begin() + m_SlopeListBoxIndex);
		CToolView* pToolView= ((CMainFrame*)AfxGetMainWnd())->GetMainView();
		pToolView->SetVecSlope(m_vecSlopeCube);

	}
	UpdateData(FALSE);


	
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}



BOOL CAddCube::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_TileInfo.vPos =m_vPos;
	m_TileInfo.vScale = m_vScale;
	m_TileInfo.fAngle = m_fAngle;
	m_TileInfo.eTileOption = Engine::TILE_UNBROKEN;
	m_TileInfo.eTexture = Engine::TILE_IMAGE0;

	TCHAR szText[256] = L"";
	wsprintf(szText, L"Block0");
	m_ListBox1.AddString(szText);
	wsprintf(szText, L"Block1");
	m_ListBox1.AddString(szText);
	wsprintf(szText, L"Block2");
	m_ListBox1.AddString(szText);
	wsprintf(szText, L"Block3");
	m_ListBox1.AddString(szText);
	wsprintf(szText, L"Block4");
	m_ListBox1.AddString(szText);
	wsprintf(szText, L"Block5");
	m_ListBox1.AddString(szText);
	wsprintf(szText, L"Block6");
	m_ListBox1.AddString(szText);
	wsprintf(szText, L"Block7");
	m_ListBox1.AddString(szText);
	wsprintf(szText, L"Block8");
	m_ListBox1.AddString(szText);

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CAddCube::OnBnClickedSavecube()
{
	CFileDialog Dlg(FALSE, 
		L"dat",
		L"*.dat", 
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		L"*.dat",
		this);
	//1인자 : 창속성->저장  FALSE  |   로드 TRUE
	//2인자 : 파일의 확장자 명
	//3인자 : 최초의 띄워줄 파일명
	//4인자 : 중복된 파일에 대한 처리를 관리하는 인자값.
	//5인자 : 파일형식에 띄어줄 확장자명
	//6인자 : 부모창의 주소.


	if(Dlg.DoModal() == IDCANCEL)
		return;


	//DoModal() : 프로세스에 대한 독점권을 말한ㄷ.

	//Dlg.m_ofn.lpstrInitialDir : 저장시킬 기본 경로를 설정.
	Dlg.m_ofn.lpstrInitialDir = L"..\\Data";		//절대경로로 설정을 해보자.


	HANDLE hFile = CreateFile(
		Dlg.GetPathName(),
		GENERIC_WRITE,
		0,
		NULL,
		CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,
		NULL
		);

	//1인자 : 경로
	//2인자 : 파일입출력의 모드(쓰기)
	//3인자 : 공유모드(0 ->  공유모드)
	//4인자 : 기본값으로 NULL을 사용한다.... 
	//5인자 : 파일생성옵션 : 파일이 있으면 덮어씌기, 없으면 새로 생성하는..
	//6인자 : 파일생성옵션 : 기본파일 생성


	DWORD dwByte;

	vector<CToolCube*>::iterator iter = m_vecCube.begin();
	vector<CToolCube*>::iterator iter_end = m_vecCube.end();

	vector<CToolSlopeCube*>::iterator iterslop = m_vecSlopeCube.begin();
	vector<CToolSlopeCube*>::iterator iterslop_end = m_vecSlopeCube.end();



	for(iter; iter != iter_end; ++iter)
	{
		WriteFile(hFile, &(*iter)->GetInfo(), sizeof(Engine::TILEINFO), &dwByte, NULL);
		//1인자 : 개방된 파일
		//2인자 : 버퍼(어떤 파일을 저장할것인지)
		//3인자 : 버퍼의 크기
		//4인자 : 파일의 크기가 계산되어서 들어오는 인자
		//5인자 : 스트림지정 사용하지 않음.
	}
	for( ;iterslop != iterslop_end ; ++iterslop)
	{

		WriteFile(hFile, &(*iterslop)->GetInfo(), sizeof(Engine::TILEINFO), &dwByte, NULL);

	}

	CloseHandle(hFile);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

void CAddCube::OnBnClickedLoadcube()
{
	UpdateData(TRUE);

	CFileDialog Dlg(TRUE, 
		L"dat",
		L"*.dat", 
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		L"*.dat",
		this);

	Dlg.m_ofn.lpstrInitialDir = L"..\\Data";

	if(Dlg.DoModal() == IDCANCEL)
		return;

	Release();
	m_ListBox.ResetContent();

	HANDLE hFile = CreateFile(
		Dlg.GetPathName(),
		GENERIC_READ,
		0,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL
		);

	DWORD dwByte;

	while(true)
	{
		Engine::TILEINFO pTileData;

		ReadFile(hFile, &pTileData, sizeof(Engine::TILEINFO), &dwByte, NULL);

		if(dwByte == 0)
		{
			break;
		}
		m_vecTileInfo.push_back(pTileData);
	}

	CloseHandle(hFile);
	
	CToolView* pAddCube = ((CMainFrame*)AfxGetMainWnd())->GetMainView();

	vector<Engine::TILEINFO>::iterator iter = m_vecTileInfo.begin();
	vector<Engine::TILEINFO>::iterator iter_end = m_vecTileInfo.end();


	for( ;iter != iter_end ; ++iter )
	{
		if((*iter).eTileShape == Engine::TILE_CUBE)
		{

		m_pCube = CToolCube::Create(pAddCube->GetDevice() , (*iter));	
		m_vecCube.push_back(m_pCube);

		CToolView* pToolView= ((CMainFrame*)AfxGetMainWnd())->GetMainView();
		pToolView->SetVec(m_vecCube);

		TCHAR szText[256] = L"";
		wsprintf(szText, L"큐브 %d", m_vecCube.size() -1);
		m_ListBox.AddString(szText);
		}
		else
		{
			m_pSlopeCube = CToolSlopeCube::Create(pAddCube->GetDevice() , *iter);	
			m_vecSlopeCube.push_back(m_pSlopeCube);

			CToolView* pToolView= ((CMainFrame*)AfxGetMainWnd())->GetMainView();
			pToolView->SetVecSlope(m_vecSlopeCube);

			TCHAR szText[256] = L"";
			wsprintf(szText, L"슬로프 큐브 %d", m_vecSlopeCube.size() -1);
			m_SlopList.AddString(szText);
		}
	}

	UpdateData(FALSE);

	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CAddCube::OnBnClickedRadio4()
{
	UpdateData(TRUE);
	m_Radio1[0].SetCheck(TRUE);
	m_Radio1[1].SetCheck(FALSE);
	UpdateData(FALSE);

	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

void CAddCube::OnBnClickedRadio5()
{

	UpdateData(TRUE);
	m_Radio1[1].SetCheck(TRUE);
	m_Radio1[0].SetCheck(FALSE);
	UpdateData(FALSE);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}



