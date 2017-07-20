/*!
 * \class CMouseMgr
 *
 * \ingroup GroupName
 *
 * \brief 
 *
 * TODO: long description
 *
 * \note 
 *
 * \author Han
 *
 * \version 1.0
 *
 * \date July 2017
 *
 * Contact: user@company.com
 *
 */

#ifndef __MouseMgr_h__
#define __MouseMgr_h__

#include "Engine_Include.h"

BEGIN(Engine)

class ENGINE_DLL CMouseMgr
{
public:
	DECLARE_SINGLETON(CMouseMgr)

public:
	CMouseMgr(void);
	virtual ~CMouseMgr(void);

public:
	HRESULT	       Initialize(HWND hwnd, WORD WINCX, WORD WINCY);
	void		   Update(void);

public:
	D3DXVECTOR3 GetMousePos();
	D3DXVECTOR3 InitMousePos(void);
	DWORD	GetMouseKey();

private:
	POINT	m_ptMouse;

	DWORD	m_dwMouseKey;	
	bool	m_bPressLBtn;
	bool	m_bPressRBtn;

	HWND	m_hWnd;

	WORD	m_WinCX;
	WORD	m_WinCY;
};

END

#endif	//__MouseMgr_h__