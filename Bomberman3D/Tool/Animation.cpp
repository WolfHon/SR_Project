// Animation.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Tool.h"
#include "Animation.h"

#include "Include.h"
#include "MainFrm.h"
#include "ToolPlayerModel.h"
#include "ToolView.h"

// CAnimation ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CAnimation, CDialog)

CAnimation::CAnimation(CWnd* pParent /*=NULL*/)
	: CDialog(CAnimation::IDD, pParent)
	, fAngleX(0.f)
	, fAngleY(0.f)
	, fAngleZ(0.f)
	, fLastX(0.f)
	, fLastY(0.f)
	, fLastZ(0.f)
	, iPart(1)
	, m_iAniCount(0)
	, m_iFrameCount(0)
	, m_bReset(true)
	, m_strPart(_T(""))
{
}

CAnimation::~CAnimation()
{
}

void CAnimation::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_ROTATION_X, m_Rot_X);
	DDX_Control(pDX, IDC_ROTATION_Y, m_Rot_Y);
	DDX_Control(pDX, IDC_ROTATION_Z, m_Rot_Z);
	DDX_Text(pDX, IDC_VALUE_X, fAngleX);
	DDX_Text(pDX, IDC_VALUE_Y, fAngleY);
	DDX_Text(pDX, IDC_VALUE_Z, fAngleZ);
	DDX_Control(pDX, IDC_ANI_LIST, m_ListAnimation);
	DDX_Control(pDX, IDC_FR_LIST, m_ListFrame);
	DDX_Text(pDX, IDC_EDIT_PART, m_strPart);
}


BEGIN_MESSAGE_MAP(CAnimation, CDialog)
	ON_WM_HSCROLL()
	ON_BN_CLICKED(IDC_RESET_MODEL, &CAnimation::OnBnClickedResetModel)
	ON_BN_CLICKED(IDC_ROT_Y_RIGHT, &CAnimation::OnBnClickedRotYRight)
	ON_BN_CLICKED(IDC_FR_SAVE, &CAnimation::OnBnClickedFrSave)
	ON_BN_CLICKED(IDC_ROT_Y_LEFT, &CAnimation::OnBnClickedRotYLeft)
	ON_BN_CLICKED(IDC_ANI_SAVE, &CAnimation::OnBnClickedAniSave)
	ON_LBN_SELCHANGE(IDC_ANI_LIST, &CAnimation::OnLbnSelchangeAniList)
	ON_BN_CLICKED(IDC_START_ANI, &CAnimation::OnBnClickedStartAni)
	ON_BN_CLICKED(IDC_FR_DELETE, &CAnimation::OnBnClickedFrDelete)
	ON_LBN_SELCHANGE(IDC_FR_LIST, &CAnimation::OnLbnSelchangeFrList)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_ROTATION_Y, &CAnimation::OnNMCustomdrawRotationY)
	ON_BN_CLICKED(IDC_SAVE_STRUCT, &CAnimation::OnBnClickedSaveStruct)
	ON_BN_CLICKED(IDC_LOAD_STRUCT2, &CAnimation::OnBnClickedLoadStruct2)
END_MESSAGE_MAP()


// CAnimation �޽��� ó�����Դϴ�.

void CAnimation::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	if(pScrollBar != NULL && pScrollBar->m_hWnd == m_Rot_X.m_hWnd)
	{
		UpdateData(TRUE);
		fAngleX = m_Rot_X.GetPos();
		
		UpdateData(FALSE);
	}

	else if(pScrollBar != NULL && pScrollBar->m_hWnd == m_Rot_Y.m_hWnd)
	{
		UpdateData(TRUE);
		fAngleY = m_Rot_Y.GetPos();
		UpdateData(FALSE);
	}

	else if(pScrollBar != NULL && pScrollBar->m_hWnd == m_Rot_Z.m_hWnd)
	{
		UpdateData(TRUE);
		fAngleZ = m_Rot_Z.GetPos();
		UpdateData(FALSE);
	}

	if(fAngleX != fLastX || fAngleY != fLastY || fAngleZ != fLastZ)
	{
		SetFrame();
	}
	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}

BOOL CAnimation::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_Rot_X.SetRange(0,100);
	m_Rot_Y.SetRange(0,100);
	m_Rot_Z.SetRange(0,100);

	m_Rot_X.SetRangeMin(-180);
	m_Rot_X.SetRangeMax(180);

	m_Rot_Y.SetRangeMin(-180);
	m_Rot_Y.SetRangeMax(180);

	m_Rot_Z.SetRangeMin(-180);
	m_Rot_Z.SetRangeMax(180);

	m_Rot_X.SetPos(5);
	m_Rot_Y.SetPos(5);
	m_Rot_Z.SetPos(5);

	m_Rot_X.SetPageSize(5);
	m_Rot_Y.SetPageSize(5);
	m_Rot_Z.SetPageSize(5);

	//m_AnimationInfo->HeadAngle.AngleX = 0.f;
	//m_AnimationInfo->HeadAngle.AngleY = 0.f;
	//m_AnimationInfo->HeadAngle.AngleZ = 0.f;

	//m_AnimationInfo->BodyAngle.AngleX = 0.f;
	//m_AnimationInfo->BodyAngle.AngleY = 0.f;
	//m_AnimationInfo->BodyAngle.AngleZ = 0.f;

	//m_AnimationInfo->LeftArmAngle.AngleX = 0.f;
	//m_AnimationInfo->LeftArmAngle.AngleY = 0.f;
	//m_AnimationInfo->LeftArmAngle.AngleZ = 0.f;

	//m_AnimationInfo->RightArmAngle.AngleX = 0.f;
	//m_AnimationInfo->RightArmAngle.AngleY = 0.f;
	//m_AnimationInfo->RightArmAngle.AngleZ = 0.f;

	//m_AnimationInfo->LeftFootAngle.AngleX = 0.f;
	//m_AnimationInfo->LeftFootAngle.AngleY = 0.f;
	//m_AnimationInfo->LeftFootAngle.AngleZ = 0.f;

	//m_AnimationInfo->RightFootAngle.AngleX = 0.f;
	//m_AnimationInfo->RightFootAngle.AngleY = 0.f;
	//m_AnimationInfo->RightFootAngle.AngleZ = 0.f;

	//m_vecAnimation.push_back(m_AnimationInfo);

	//UpdateData(TRUE);

	//CToolView*		pAddPlayer = ((CMainFrame*)AfxGetMainWnd())->GetMainView();

	//m_pPlayer = CPlayerAnimation::Create(pAddPlayer->GetDevice());

	//m_pPlayer->SetAnimation(m_AnimationInfo);

	//pAddPlayer->SetPlayer(m_pPlayer);

	//UpdateData(FALSE);
	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.

	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}

void CAnimation::OnBnClickedResetModel()
{
	//m_AnimationInfo.HeadAngle.AngleX = 0.f;
	//m_AnimationInfo.HeadAngle.AngleY = 0.f;
	//m_AnimationInfo.HeadAngle.AngleZ = 0.f;

	//m_AnimationInfo.BodyAngle.AngleX = 0.f;
	//m_AnimationInfo.BodyAngle.AngleY = 0.f;
	//m_AnimationInfo.BodyAngle.AngleZ = 0.f;

	//m_AnimationInfo.LeftArmAngle.AngleX = 0.f;
	//m_AnimationInfo.LeftArmAngle.AngleY = 0.f;
	//m_AnimationInfo.LeftArmAngle.AngleZ = 0.f;

	//m_AnimationInfo.RightArmAngle.AngleX = 0.f;
	//m_AnimationInfo.RightArmAngle.AngleY = 0.f;
	//m_AnimationInfo.RightArmAngle.AngleZ = 0.f;

	//m_AnimationInfo.LeftFootAngle.AngleX = 0.f;
	//m_AnimationInfo.LeftFootAngle.AngleY = 0.f;
	//m_AnimationInfo.LeftFootAngle.AngleZ = 0.f;

	//m_AnimationInfo.RightFootAngle.AngleX = 0.f;
	//m_AnimationInfo.RightFootAngle.AngleY = 0.f;
	//m_AnimationInfo.RightFootAngle.AngleZ = 0.f;

	//m_vecAnimation.push_back(&m_AnimationInfo);

	UpdateData(TRUE);

	iPart = 0;
	ChoicePart();

	m_vecAnimation.clear();
	m_ListFrame.ResetContent();
	ResetFrame(&m_AnimationInfo);
	m_bReset = true;

	m_Rot_X.SetPos(0.f);
	fAngleX = 0.f;
	m_Rot_Y.SetPos(0.f);
	fAngleY = 0.f;
	m_Rot_Z.SetPos(0.f);
	fAngleZ = 0.f;

	CToolView*		pAddPlayer = ((CMainFrame*)AfxGetMainWnd())->GetMainView();

	m_vecAnimation.push_back(m_AnimationInfo);

	m_pPlayer = CPlayerAnimation::Create(pAddPlayer->GetDevice());

	m_pPlayer->SetAnimation(m_vecAnimation);

	pAddPlayer->SetPlayer(m_pPlayer);

	UpdateData(FALSE);
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}

void CAnimation::OnBnClickedRotYRight()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

	UpdateData(TRUE);

	++iPart;

	if(iPart > 5)
		iPart = 5;

	ChoicePart();

	ResetPos();

	UpdateData(FALSE);


}
void CAnimation::OnBnClickedRotYLeft()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData(TRUE);

	--iPart;

	if(iPart < 0)
		iPart = 0;
	ChoicePart();
	ResetPos();

	UpdateData(FALSE);
}


void CAnimation::OnBnClickedFrSave()
{		
	UpdateData(TRUE);
	Engine::ANIFRAME		m_TempFrame;

	ResetFrame(&m_TempFrame);

	m_TempFrame = m_TempFrameInfo;

	m_vecAnimation.push_back(m_TempFrame);
	TCHAR szText[256] = L"";
	wsprintf(szText, L"Frame %d", m_vecAnimation.size() -1);
	m_ListFrame.AddString(szText);

	m_bReset = true;
	UpdateData(FALSE);
}

void CAnimation::OnBnClickedFrDelete()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}


void CAnimation::OnBnClickedAniSave()
{
	UpdateData(TRUE);
	m_vecSavedAni.push_back(m_vecAnimation);
	TCHAR szText[256] = L"";
	wsprintf(szText, L"Animation %d", m_vecSavedAni.size() -1);
	m_ListAnimation.AddString(szText);

	UpdateData(FALSE);
}

void CAnimation::OnLbnSelchangeAniList()
{
	UpdateData(TRUE);

	m_iAniCount = m_ListAnimation.GetCurSel();

	if(m_iAniCount < 0)
		return;

	m_vecAnimation = m_vecSavedAni[m_iAniCount];

	m_ListFrame.ResetContent();
	
	for(int i = 0 ; i < m_vecAnimation.size(); ++i)
	{
		TCHAR szText[256] = L"";
		wsprintf(szText, L"Frame %d", i);
		m_ListFrame.AddString(szText);
	}

	UpdateData(FALSE);
}

void CAnimation::OnLbnSelchangeFrList()
{
	UpdateData(TRUE);
	
	m_iFrameCount = m_ListFrame.GetCurSel();

	if(m_iFrameCount < 0)
		return;

	m_pPlayer->SetFrame(m_vecAnimation[m_iFrameCount]);

	UpdateData(FALSE);
}

void CAnimation::OnBnClickedStartAni()
{
	m_vecAnimation = m_vecSavedAni[m_iAniCount];

	m_pPlayer->SetAnimation(m_vecAnimation);

}

void CAnimation::ResetFrame(Engine::ANIFRAME* pFrame)
{
	pFrame->HeadAngle.AngleX = 0.f;
	pFrame->HeadAngle.AngleY = 0.f;
	pFrame->HeadAngle.AngleZ = 0.f;

	pFrame->BodyAngle.AngleX = 0.f;
	pFrame->BodyAngle.AngleY = 0.f;
	pFrame->BodyAngle.AngleZ = 0.f;

	pFrame->LeftArmAngle.AngleX = 0.f;
	pFrame->LeftArmAngle.AngleY = 0.f;
	pFrame->LeftArmAngle.AngleZ = 0.f;

	pFrame->RightArmAngle.AngleX = 0.f;
	pFrame->RightArmAngle.AngleY = 0.f;
	pFrame->RightArmAngle.AngleZ = 0.f;

	pFrame->LeftFootAngle.AngleX = 0.f;
	pFrame->LeftFootAngle.AngleY = 0.f;
	pFrame->LeftFootAngle.AngleZ = 0.f;

	pFrame->RightFootAngle.AngleX = 0.f;
	pFrame->RightFootAngle.AngleY = 0.f;
	pFrame->RightFootAngle.AngleZ = 0.f;
	pFrame->fTime = 0.f;
}

void CAnimation::ResetPos(void)
{
	fAngleX = 0.f;
	fAngleY = 0.f;
	fAngleZ = 0.f;
	fLastX = fAngleX;
	fLastY = fAngleY;
	fLastZ = fAngleZ;
	m_Rot_X.SetPos(5);
	m_Rot_Y.SetPos(5);
	m_Rot_Z.SetPos(5);
}

void CAnimation::SetFrame(void)
{

	if(m_bReset)
	{
		ResetFrame(&m_TempFrameInfo);
	}

	if(iPart == 0)
	{
		m_TempFrameInfo.HeadAngle.AngleX = fAngleX;
		m_TempFrameInfo.HeadAngle.AngleY = fAngleY;
		m_TempFrameInfo.HeadAngle.AngleZ = fAngleZ;
	}

	else if(iPart == 1)
	{
		m_TempFrameInfo.BodyAngle.AngleX = fAngleX;
		m_TempFrameInfo.BodyAngle.AngleY = fAngleY;
		m_TempFrameInfo.BodyAngle.AngleZ = fAngleZ;
	}

	else if(iPart == 2)
	{
		m_TempFrameInfo.LeftArmAngle.AngleX = fAngleX;
		m_TempFrameInfo.LeftArmAngle.AngleY = fAngleY;
		m_TempFrameInfo.LeftArmAngle.AngleZ = fAngleZ;
	}

	else if(iPart == 3)
	{
		m_TempFrameInfo.RightArmAngle.AngleX = fAngleX;
		m_TempFrameInfo.RightArmAngle.AngleY = fAngleY;
		m_TempFrameInfo.RightArmAngle.AngleZ = fAngleZ;
	}

	else if(iPart == 4)
	{
		m_TempFrameInfo.LeftFootAngle.AngleX = fAngleX;
		m_TempFrameInfo.LeftFootAngle.AngleY = fAngleY;
		m_TempFrameInfo.LeftFootAngle.AngleZ = fAngleZ;
	}

	else if(iPart == 5)
	{
		m_TempFrameInfo.RightFootAngle.AngleX = fAngleX;
		m_TempFrameInfo.RightFootAngle.AngleY = fAngleY;
		m_TempFrameInfo.RightFootAngle.AngleZ = fAngleZ;
	}

	fLastX = fAngleX;
	fLastY = fAngleY;
	fLastZ = fAngleZ;

	m_pPlayer->SetFrame(m_TempFrameInfo);
	m_bReset = false;

}

void CAnimation::ChoicePart(void)
{
	switch(iPart)
	{
	case 0:
		m_strPart = "�Ӹ�";
		break;

	case 1:
		m_strPart = "����";
		break;

	case 2:
		m_strPart = "����";
		break;

	case 3:
		m_strPart = "������";
		break;
	
	case 4:
		m_strPart = "�޴ٸ�";
		break;

	case 5:
		m_strPart = "�����ٸ�";
		break;
	}
}

void CAnimation::OnNMCustomdrawRotationY(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	*pResult = 0;
}

void CAnimation::OnBnClickedSaveStruct()
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

	DWORD dwByte;

	vector<Engine::ANIFRAME>::iterator	iter = (m_vecSavedAni[m_iAniCount]).begin();
	vector<Engine::ANIFRAME>::iterator	iter_end = (m_vecSavedAni[m_iAniCount]).end();

	for(iter; iter != iter_end; ++iter)
	{
		WriteFile(hFile,&(*iter),sizeof(Engine::ANIFRAME), &dwByte, NULL);
	}

	CloseHandle(hFile);
}

void CAnimation::OnBnClickedLoadStruct2()
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

	m_vecAnimation.clear();

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
		Engine::ANIFRAME pFrameData;

		ReadFile(hFile, &pFrameData, sizeof(Engine::ANIFRAME), &dwByte, NULL);

		if(dwByte == 0)
			break;

		m_vecAnimation.push_back(pFrameData);
	}

	CloseHandle(hFile);

	m_vecSavedAni.push_back(m_vecAnimation);
	TCHAR szText[256] = L"";
	wsprintf(szText, L"Animation %d", m_vecSavedAni.size() -1);
	m_ListAnimation.AddString(szText);

	UpdateData(FALSE);
}
