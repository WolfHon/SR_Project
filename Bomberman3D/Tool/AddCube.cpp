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



// CAddCube ��ȭ �����Դϴ�.

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
 

// CAddCube �޽��� ó�����Դϴ�.



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
				wsprintf(szText, L"ť�� %d", m_vecCube.size() -1);
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
		wsprintf(szText, L"������ ť�� %d", m_vecSlopeCube.size() -1 );
		m_SlopList.AddString(szText);
	}
	
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

	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
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
	
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
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
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
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
	
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
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
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
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
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
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
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
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
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
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
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
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
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
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
void CAddCube::OnBnClickedRadio3()
{
	UpdateData(TRUE);
	m_iEnum = 2;

	UpdateData(FALSE);

	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
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
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
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


	
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
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

	vector<CToolCube*>::iterator iter = m_vecCube.begin();
	vector<CToolCube*>::iterator iter_end = m_vecCube.end();

	vector<CToolSlopeCube*>::iterator iterslop = m_vecSlopeCube.begin();
	vector<CToolSlopeCube*>::iterator iterslop_end = m_vecSlopeCube.end();



	for(iter; iter != iter_end; ++iter)
	{
		WriteFile(hFile, &(*iter)->GetInfo(), sizeof(Engine::TILEINFO), &dwByte, NULL);
		//1���� : ����� ����
		//2���� : ����(� ������ �����Ұ�����)
		//3���� : ������ ũ��
		//4���� : ������ ũ�Ⱑ ���Ǿ ������ ����
		//5���� : ��Ʈ������ ������� ����.
	}
	for( ;iterslop != iterslop_end ; ++iterslop)
	{

		WriteFile(hFile, &(*iterslop)->GetInfo(), sizeof(Engine::TILEINFO), &dwByte, NULL);

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
		wsprintf(szText, L"ť�� %d", m_vecCube.size() -1);
		m_ListBox.AddString(szText);
		}
		else
		{
			m_pSlopeCube = CToolSlopeCube::Create(pAddCube->GetDevice() , *iter);	
			m_vecSlopeCube.push_back(m_pSlopeCube);

			CToolView* pToolView= ((CMainFrame*)AfxGetMainWnd())->GetMainView();
			pToolView->SetVecSlope(m_vecSlopeCube);

			TCHAR szText[256] = L"";
			wsprintf(szText, L"������ ť�� %d", m_vecSlopeCube.size() -1);
			m_SlopList.AddString(szText);
		}
	}

	UpdateData(FALSE);

	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}


void CAddCube::OnBnClickedRadio4()
{
	UpdateData(TRUE);
	m_Radio1[0].SetCheck(TRUE);
	m_Radio1[1].SetCheck(FALSE);
	UpdateData(FALSE);

	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}

void CAddCube::OnBnClickedRadio5()
{

	UpdateData(TRUE);
	m_Radio1[1].SetCheck(TRUE);
	m_Radio1[0].SetCheck(FALSE);
	UpdateData(FALSE);
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}



