#pragma once


// CAddCube ��ȭ �����Դϴ�.

class CAddCube : public CDialog
{
	DECLARE_DYNAMIC(CAddCube)

public:
	CAddCube(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CAddCube();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_ADDCUBE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEnChangeEditxpos();
	afx_msg void OnBnClickedAddcube();
};
