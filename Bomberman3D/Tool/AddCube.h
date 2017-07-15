#pragma once


// CAddCube 대화 상자입니다.

#include "Engine_Include.h"

class CAddCube : public CDialog
{
	DECLARE_DYNAMIC(CAddCube)

private:
	vector<Engine::TILEINFO*>* m_vecCube;



public:
	void Release(void);

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
	
};


