// Main.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Tool.h"
#include "Main.h"


// Main 대화 상자입니다.

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


// Main 메시지 처리기입니다.
