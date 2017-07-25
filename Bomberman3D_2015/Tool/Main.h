#pragma once


// Main 대화 상자입니다.

class Main : public CDialog
{
	DECLARE_DYNAMIC(Main)

public:
	Main(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~Main();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_MAIN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
};
