#pragma once

#include "Engine_Include.h"
#include "afxwin.h"
#include "Resource.h"

// CAnimation ��ȭ �����Դϴ�.

namespace Engine
{
	class CGraphicDev;
	class CVIBuffer;
	class CTexture;
	class CPlayerModel;
	class CLayer;
}

class CToolView;
class CPlayerAnimation;

class CAnimation : public CDialog
{
	DECLARE_DYNAMIC(CAnimation)

private:
	vector<Engine::ANIFRAME>			m_vecAnimation;
	vector<vector<Engine::ANIFRAME>>	m_vecSavedAni;
	CPlayerAnimation*		m_pPlayer;

	D3DXVECTOR3			m_vPos;
	D3DXVECTOR3			m_vScale;
	float				m_fAngle;
	float				fAngleX;
	float				fAngleY;
	float				fAngleZ;
	float				fLastX;
	float				fLastY;
	float				fLastZ;
	bool				m_bReset;

	int					iPart;
	int					m_iAniCount;
	int					m_iFrameCount;

	Engine::ANIFRAME			m_AnimationInfo;

	Engine::ANIFRAME			m_TempFrameInfo;

	Engine::ANIFRAME			m_TempFrame;

	Engine::CGraphicDev*		m_pGraphicDev;

	LPDIRECT3DDEVICE9			m_pDevice;

public:
	void SetDevice(LPDIRECT3DDEVICE9 _Device)
	{
		m_pDevice = _Device;
	}
	void SetFrame(void);

	void ResetFrame(Engine::ANIFRAME* pFrame);

	void ResetPos(void);

public:
	void Release(void);

public:
	CAnimation(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CAnimation();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_ANIMATION };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	CSliderCtrl		m_Rot_X;
	CSliderCtrl		m_Rot_Y;
	CSliderCtrl		m_Rot_Z;
	CListBox		m_ListAnimation;
	CListBox		m_ListFrame;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedResetModel();
	afx_msg void OnBnClickedRotYRight();
	afx_msg void OnBnClickedFrSave();
	afx_msg void OnBnClickedRotYLeft();
	afx_msg void OnBnClickedAniSave();
	afx_msg void OnLbnSelchangeAniList();
	afx_msg void OnBnClickedStartAni();
	afx_msg void OnBnClickedFrDelete();
	afx_msg void OnLbnSelchangeFrList();
};
