#pragma once


// CAddCube ��ȭ �����Դϴ�.

#include "Engine_Include.h"

class CAddCube : public CDialog
{
	DECLARE_DYNAMIC(CAddCube)

private:
	vector<Engine::TILEINFO*>* m_vecCube;



public:
	void Release(void);

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
	
};


