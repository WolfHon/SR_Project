#pragma once


// Main ��ȭ �����Դϴ�.

class Main : public CDialog
{
	DECLARE_DYNAMIC(Main)

public:
	Main(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~Main();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_MAIN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};
