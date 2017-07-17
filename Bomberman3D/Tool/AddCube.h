#pragma once


// CAddCube ��ȭ �����Դϴ�.

#include "Engine_Include.h"
#include "afxwin.h"
namespace Engine
{
	class CGraphicDev;
	class CVIBuffer;
	class CTexture;
	class CLayer;

}
class CToolCube;        
class CAddCube : public CDialog
{
	DECLARE_DYNAMIC(CAddCube)

private:
	vector<CToolCube*> m_vecCube;
	vector<Engine::TILEINFO*> m_vecTileInfo;
	CToolCube*				m_pCube;

	bool m_bRadioButtonStartCheck;

	float              fx;
	float			   fY;
	float              fZ;
	int					iSelectIndex;
	int					m_iEnum;

	Engine::TILEINFO			m_TileInfo;

	Engine::CGraphicDev*		m_pGraphicDev;
	LPDIRECT3DDEVICE9			m_pDevice;

public:
	void SetDevice(LPDIRECT3DDEVICE9 _Device)
	{

		m_pDevice = _Device;
		
	}

	vector<CToolCube*>* GetVecCube(void)
	{
		return &m_vecCube;
	}

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
	
	afx_msg void OnBnClickedAddcube();

	afx_msg void OnLbnSelchangeList1();
	CListBox m_ListBox;
	CButton m_Radio[3];
	CEdit m_XPos;
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedDecreasex();
	afx_msg void OnBnClickedIncreasex();
	afx_msg void OnBnClickedDecreasey();
	afx_msg void OnBnClickedIncreasey();
	afx_msg void OnBnClickedDecreasez();
	afx_msg void OnBnClickedIncreasez();
	afx_msg void OnBnClickedRadio1();
	afx_msg void OnBnClickedRadio2();
	afx_msg void OnBnClickedBackcube();
	afx_msg void OnLbnSelchangeList2();
	CListBox m_ListBox1;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedSavecube();
	afx_msg void OnBnClickedLoadcube();
};


