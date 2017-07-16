// AddCube.cpp : 구현 파일입니다.
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



// CAddCube 대화 상자입니다.

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


// CAddCube 메시지 처리기입니다.

void CAddCube::OnEnChangeEditxpos()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialog::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CAddCube::OnBnClickedAddcube()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}
