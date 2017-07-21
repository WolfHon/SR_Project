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
	list<Engine::LPANIFRAME>			m_listAnimation;
	CPlayerAnimation*		m_pPlayer;

	D3DXVECTOR3			m_vPos;
	D3DXVECTOR3			m_vScale;
	float				m_fAngle;
	float				fAngleX;
	float				fAngleY;
	float				fAngleZ;

	Engine::ANIFRAME			m_AnimationInfo;

	Engine::CGraphicDev*		m_pGraphicDev;
	LPDIRECT3DDEVICE9			m_pDevice;

public:
	void SetDevice(LPDIRECT3DDEVICE9 _Device)
	{
		m_pDevice = _Device;
	}

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
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedResetModel();
	afx_msg void OnBnClickedRotYRight();
	afx_msg void OnBnClickedFrSave();
};
