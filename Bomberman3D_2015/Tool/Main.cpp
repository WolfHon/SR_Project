// Main.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Tool.h"
#include "Main.h"


// Main ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(Main, CDialog)

Main::Main(CWnd* pParent /*=NULL*/)
	: CDialog(Main::IDD, pParent)
{

}

Main::~Main()
{
}

void Main::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(Main, CDialog)
END_MESSAGE_MAP()


// Main �޽��� ó�����Դϴ�.
