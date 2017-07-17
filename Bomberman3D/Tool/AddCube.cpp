// AddCube.cpp : ���� �����Դϴ�.
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


void CAddCube::Release( void )
{
	vector<CToolCube*>::iterator iter = m_vecCube.begin();
	vector<CToolCube*>::iterator iter_end = m_vecCube.end();

	for( ;iter != iter_end ; ++iter)
	{
		Engine::Safe_Delete(*iter);
	}

	m_vecCube.clear();

	vector<Engine::TILEINFO*>::iterator iterINFO = m_vecTileInfo.begin();
	vector<Engine::TILEINFO*>::iterator iterINFO_end = m_vecTileInfo.end();

	for( ;iterINFO != iterINFO_end ; ++iterINFO)
	{
		Engine::Safe_Delete(*iterINFO);
	}

	m_vecTileInfo.clear();
}



// CAddCube ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CAddCube, CDialog)

CAddCube::CAddCube(CWnd* pParent /*=NULL*/)
	: CDialog(CAddCube::IDD, pParent)
	,fx(0)
	,fY(0)
	,fZ(0)
	,m_bRadioButtonStartCheck(true)
	,iSelectIndex(0)
{



}

CAddCube::~CAddCube()
{
	//Release();
}

void CAddCube::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDITXPOS, fx);
	DDX_Text(pDX, IDC_EDITYPOS, fY);
	DDX_Text(pDX, IDC_EDITZPOS, fZ);
	DDX_Control(pDX, IDC_LIST1, m_ListBox);
	DDX_Control(pDX, IDC_EDITXPOS, m_XPos);
	DDX_Control(pDX, IDC_RADIO1, m_Radio[0]);
	DDX_Control(pDX, IDC_RADIO2, m_Radio[1]);
	DDX_Control(pDX, IDC_RADIO3, m_Radio[2]);

	if(m_bRadioButtonStartCheck)
	{
		m_Radio[0].SetCheck(TRUE);
		m_bRadioButtonStartCheck = false;
	}

	DDX_Control(pDX, IDC_LIST2, m_ListBox1);
}


BEGIN_MESSAGE_MAP(CAddCube, CDialog)
	ON_EN_CHANGE(IDC_EDITXPOS, &CAddCube::OnEnChangeEditxpos)
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
END_MESSAGE_MAP()


// CAddCube �޽��� ó�����Դϴ�.

void CAddCube::OnEnChangeEditxpos()
{
	// TODO:  RICHEDIT ��Ʈ���� ���, �� ��Ʈ����
	// CDialog::OnInitDialog() �Լ��� ������ 
	//�ϰ� ����ũ�� OR �����Ͽ� ������ ENM_CHANGE �÷��׸� �����Ͽ� CRichEditCtrl().SetEventMask()�� ȣ������ ������
	// �� �˸� �޽����� ������ �ʽ��ϴ�.

	// TODO:  ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}


void CAddCube::OnBnClickedAddcube()
{
	UpdateData(TRUE);

	CToolView* pAddCube = ((CMainFrame*)AfxGetMainWnd())->GetMainView();

	m_pCube = CToolCube::Create(pAddCube->GetDevice() , m_TileInfo);	

	m_vecCube.push_back(m_pCube);

	Engine::TILEINFO* tagTile = new Engine::TILEINFO;
	tagTile = &m_pCube->GetInfo();
	m_vecTileInfo.push_back(tagTile);

	CToolView* pToolView= ((CMainFrame*)AfxGetMainWnd())->GetMainView();
	pToolView->SetVec(m_vecCube);

	TCHAR szText[256] = L"";
	wsprintf(szText, L"ť�� %d", m_vecCube.size() -1);
	m_ListBox.AddString(szText);
	
	UpdateData(FALSE);
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
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

	}	

	UpdateData(FALSE);

	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}


void CAddCube::OnLbnSelchangeList1()
{
	UpdateData(TRUE);

	iSelectIndex = m_ListBox.GetCurSel();

	fx = m_vecCube[iSelectIndex]->GetInfo().vPos.x;
	fY = m_vecCube[iSelectIndex]->GetInfo().vPos.y;
	fZ = m_vecCube[iSelectIndex]->GetInfo().vPos.z;

	for(int i = 0; i < 3; ++i)
		m_Radio[i].SetCheck(FALSE);

	int iA = (int)(m_vecCube[iSelectIndex]->GetInfo().eTileOption);

	m_Radio[iA].SetCheck(TRUE);


	UpdateData(FALSE);
	
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}


void CAddCube::OnBnClickedDecreasex()
{
	UpdateData(TRUE);
	fx -= 1.f;
	m_vecCube[iSelectIndex]->SetInfoX(fx);
	UpdateData(FALSE);
	
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}

void CAddCube::OnBnClickedIncreasex()
{
	UpdateData(TRUE);
	fx += 1.f;
	m_vecCube[iSelectIndex]->SetInfoX(fx);
	UpdateData(FALSE);
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}

void CAddCube::OnBnClickedDecreasey()
{
	UpdateData(TRUE);
	fY -= 1.f;
	m_vecCube[iSelectIndex]->SetInfoY(fY);
	UpdateData(FALSE);
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}

void CAddCube::OnBnClickedIncreasey()
{
	UpdateData(TRUE);
	fY += 1.f;
	m_vecCube[iSelectIndex]->SetInfoY(fY);
		UpdateData(FALSE);
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}

void CAddCube::OnBnClickedDecreasez()
{
	UpdateData(TRUE);
	fZ -= 1.f;
	m_vecCube[iSelectIndex]->SetInfoZ(fZ);
	UpdateData(FALSE);
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}

void CAddCube::OnBnClickedIncreasez()
{
	UpdateData(TRUE);
	fZ += 1.f;
	m_vecCube[iSelectIndex]->SetInfoZ(fZ);
	UpdateData(FALSE);
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}

void CAddCube::OnBnClickedRadio1()
{
	UpdateData(TRUE);
	m_iEnum = 0;
	UpdateData(FALSE);
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}

void CAddCube::OnBnClickedRadio2()
{
	UpdateData(TRUE);
	m_iEnum = 1;
	UpdateData(FALSE);
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}

void CAddCube::OnBnClickedButton5()
{
	UpdateData(TRUE);
	m_vecCube[iSelectIndex]->SetOption(m_iEnum);
	UpdateData(FALSE);
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}


void CAddCube::OnBnClickedBackcube()
{
	UpdateData(TRUE);

	CString strName;

	int iSelect = m_ListBox.GetCurSel();

	if(iSelect < 0)
		return;

	m_ListBox.GetText(iSelect , strName);
	m_ListBox.DeleteString(iSelect);



	m_vecCube.erase(m_vecCube.begin() + iSelectIndex);
	CToolView* pToolView= ((CMainFrame*)AfxGetMainWnd())->GetMainView();
	pToolView->SetVec(m_vecCube);


	UpdateData(FALSE);


	
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}


BOOL CAddCube::OnInitDialog()
{
	CDialog::OnInitDialog();

	TCHAR szText[256] = L"";
	wsprintf(szText, L"BreakCube");
	m_ListBox1.AddString(szText);
	wsprintf(szText, L"UnBreakCube1");
	m_ListBox1.AddString(szText);
	wsprintf(szText, L"UnBreakCube2");
	m_ListBox1.AddString(szText);
	wsprintf(szText, L"ElseCube");
	m_ListBox1.AddString(szText);

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.

	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}

void CAddCube::OnBnClickedSavecube()
{
	CFileDialog Dlg(FALSE, 
		L"dat",
		L"*.dat", 
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		L"*.dat",
		this);
	//1���� : â�Ӽ�->����  FALSE  |   �ε� TRUE
	//2���� : ������ Ȯ���� ��
	//3���� : ������ ����� ���ϸ�
	//4���� : �ߺ��� ���Ͽ� ���� ó���� �����ϴ� ���ڰ�.
	//5���� : �������Ŀ� ����� Ȯ���ڸ�
	//6���� : �θ�â�� �ּ�.


	if(Dlg.DoModal() == IDCANCEL)
		return;


	//DoModal() : ���μ����� ���� �������� ���Ѥ�.

	//Dlg.m_ofn.lpstrInitialDir : �����ų �⺻ ��θ� ����.
	Dlg.m_ofn.lpstrInitialDir = L"..\\Data";		//�����η� ������ �غ���.


	HANDLE hFile = CreateFile(
		Dlg.GetPathName(),
		GENERIC_WRITE,
		0,
		NULL,
		CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,
		NULL
		);

	//1���� : ���
	//2���� : ����������� ���(����)
	//3���� : �������(0 ->  �������)
	//4���� : �⺻������ NULL�� ����Ѵ�.... 
	//5���� : ���ϻ����ɼ� : ������ ������ �����, ������ ���� �����ϴ�..
	//6���� : ���ϻ����ɼ� : �⺻���� ����


	DWORD dwByte;

	vector<CToolCube*>::iterator iter;
	vector<CToolCube*>::iterator iter_end;

	iter	 = m_vecCube.begin();
	iter_end = m_vecCube.end();

	for(iter; iter != iter_end; ++iter)
	{
		WriteFile(hFile, &(*iter)->GetInfo(), sizeof(Engine::TILEINFO), &dwByte, NULL);
		//1���� : ����� ����
		//2���� : ����(� ������ �����Ұ�����)
		//3���� : ������ ũ��
		//4���� : ������ ũ�Ⱑ ���Ǿ ������ ����
		//5���� : ��Ʈ������ ������� ����.
	}

	CloseHandle(hFile);
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
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
		Engine::TILEINFO* pTileData = new Engine::TILEINFO;

		ReadFile(hFile, pTileData, sizeof(Engine::TILEINFO), &dwByte, NULL);

		if(dwByte == 0)
		{
			Safe_Delete(pTileData);
			break;
		}
		m_vecTileInfo.push_back(pTileData);
	}

	CloseHandle(hFile);
	
	CToolView* pAddCube = ((CMainFrame*)AfxGetMainWnd())->GetMainView();

	vector<Engine::TILEINFO*>::iterator iter = m_vecTileInfo.begin();
	vector<Engine::TILEINFO*>::iterator iter_end = m_vecTileInfo.end();

	int i = 0;

	for( ;iter != iter_end ; ++iter )
	{

		
		m_pCube = CToolCube::Create(pAddCube->GetDevice() , *(*iter));	
		++i;

		m_vecCube.push_back(m_pCube);

		CToolView* pToolView= ((CMainFrame*)AfxGetMainWnd())->GetMainView();
		pToolView->SetVec(m_vecCube);

		TCHAR szText[256] = L"";
		wsprintf(szText, L"ť�� %d", m_vecCube.size() -1);
		m_ListBox.AddString(szText);
	}



	UpdateData(FALSE);


	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}
