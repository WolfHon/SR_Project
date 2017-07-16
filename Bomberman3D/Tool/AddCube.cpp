// AddCube.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Tool.h"
#include "AddCube.h"



void CAddCube::Release( void )
{
	vector<Engine::TILEINFO*>::iterator iter = m_vecCube->begin();
	vector<Engine::TILEINFO*>::iterator iter_end = m_vecCube->end();

	for( ;iter != iter_end ; ++iter)
	{
		Safe_Delete(*iter);
	}
	m_vecCube->clear();
}



// CAddCube ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CAddCube, CDialog)

CAddCube::CAddCube(CWnd* pParent /*=NULL*/)
	: CDialog(CAddCube::IDD, pParent)
{

}

CAddCube::~CAddCube()
{
	Release();
}

void CAddCube::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CAddCube, CDialog)
	ON_EN_CHANGE(IDC_EDITXPOS, &CAddCube::OnEnChangeEditxpos)
	ON_BN_CLICKED(IDC_ADDCUBE, &CAddCube::OnBnClickedAddcube)
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
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}
