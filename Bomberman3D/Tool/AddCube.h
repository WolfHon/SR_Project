#pragma once


// CAddCube 대화 상자입니다.

class CAddCube : public CDialog
{
	DECLARE_DYNAMIC(CAddCube)

public:
	CAddCube(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CAddCube();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_ADDCUBE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEnChangeEditxpos();
	afx_msg void OnBnClickedAddcube();
};
