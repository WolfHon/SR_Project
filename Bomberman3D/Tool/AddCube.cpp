// AddCube.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Tool.h"
#include "AddCube.h"


// CAddCube ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CAddCube, CDialog)

CAddCube::CAddCube(CWnd* pParent /*=NULL*/)
	: CDialog(CAddCube::IDD, pParent)
{

}

CAddCube::~CAddCube()
{
}

void CAddCube::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CAddCube, CDialog)
	ON_EN_CHANGE(IDC_EDITXPOS, &CAddCube::OnEnChangeEditxpos)
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

