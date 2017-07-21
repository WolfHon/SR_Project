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
}


BEGIN_MESSAGE_MAP(CAnimation, CDialog)
	ON_WM_HSCROLL()
	ON_BN_CLICKED(IDC_RESET_MODEL, &CAnimation::OnBnClickedResetModel)
	ON_BN_CLICKED(IDC_ROT_Y_RIGHT, &CAnimation::OnBnClickedRotYRight)
	ON_BN_CLICKED(IDC_FR_SAVE, &CAnimation::OnBnClickedFrSave)
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

	m_AnimationInfo.RightArmAngle.AngleX = fAngleX;
	m_AnimationInfo.RightArmAngle.AngleY = fAngleY;
	m_AnimationInfo.RightArmAngle.AngleZ = fAngleZ;

	m_listAnimation.push_back(&m_AnimationInfo);

	m_pPlayer->SetAnimation(&m_AnimationInfo);
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

	m_Rot_X.SetPos(0);
	m_Rot_Y.SetPos(0);
	m_Rot_Z.SetPos(0);

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

	//m_listAnimation.push_back(m_AnimationInfo);

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

	m_AnimationInfo.HeadAngle.AngleX = 0.f;
	m_AnimationInfo.HeadAngle.AngleY = 0.f;
	m_AnimationInfo.HeadAngle.AngleZ = 0.f;

	m_AnimationInfo.BodyAngle.AngleX = 0.f;
	m_AnimationInfo.BodyAngle.AngleY = 0.f;
	m_AnimationInfo.BodyAngle.AngleZ = 0.f;

	m_AnimationInfo.LeftArmAngle.AngleX = 0.f;
	m_AnimationInfo.LeftArmAngle.AngleY = 0.f;
	m_AnimationInfo.LeftArmAngle.AngleZ = 0.f;

	m_AnimationInfo.RightArmAngle.AngleX = 0.f;
	m_AnimationInfo.RightArmAngle.AngleY = 0.f;
	m_AnimationInfo.RightArmAngle.AngleZ = 0.f;

	m_AnimationInfo.LeftFootAngle.AngleX = 0.f;
	m_AnimationInfo.LeftFootAngle.AngleY = 0.f;
	m_AnimationInfo.LeftFootAngle.AngleZ = 0.f;

	m_AnimationInfo.RightFootAngle.AngleX = 0.f;
	m_AnimationInfo.RightFootAngle.AngleY = 0.f;
	m_AnimationInfo.RightFootAngle.AngleZ = 0.f;

	m_listAnimation.push_back(&m_AnimationInfo);

	UpdateData(TRUE);

	m_Rot_X.SetPos(0.f);
	fAngleX = 0.f;
	m_Rot_Y.SetPos(0.f);
	fAngleY = 0.f;
	m_Rot_Z.SetPos(0.f);
	fAngleZ = 0.f;

	CToolView*		pAddPlayer = ((CMainFrame*)AfxGetMainWnd())->GetMainView();

	m_pPlayer = CPlayerAnimation::Create(pAddPlayer->GetDevice());

	m_pPlayer->SetAnimation(&m_AnimationInfo);

	pAddPlayer->SetPlayer(m_pPlayer);

	UpdateData(FALSE);
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}

void CAnimation::OnBnClickedRotYRight()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

	UpdateData(TRUE);

}

void CAnimation::OnBnClickedFrSave()
{

	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}
