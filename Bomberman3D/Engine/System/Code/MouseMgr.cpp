#include "MouseMgr.h"

IMPLEMENT_SINGLETON(Engine::CMouseMgr)

Engine::CMouseMgr::CMouseMgr(void)
: m_ptMouse(POINT())
, m_dwMouseKey(0)
, m_bPressLBtn(FALSE)
, m_bPressRBtn(FALSE)
{
}

Engine::CMouseMgr::~CMouseMgr(void)
{
}

HRESULT Engine::CMouseMgr::Initialize(HWND hwnd, WORD WINCX, WORD WINCY)
{
	m_hWnd = hwnd;
	m_WinCX = WINCX;
	m_WinCY = WINCY;

	return S_OK;
}

void Engine::CMouseMgr::Update(void)
{
	GetCursorPos(&m_ptMouse);
	ScreenToClient(m_hWnd, &m_ptMouse);

	m_dwMouseKey = 0;

	if (m_ptMouse.x >= 0 && m_ptMouse.x <= m_WinCX
		&& m_ptMouse.y >= 0 && m_ptMouse.y <= m_WinCY)
	{
		if (GetAsyncKeyState(VK_LBUTTON))
		{
			m_dwMouseKey |= Engine::MOUSE_LBUTTON_PRESS;
			m_bPressLBtn = true;
		}
		else
		{
			if(m_bPressLBtn == true)
				m_dwMouseKey |= Engine::MOUSE_LBUTTON_CLICK;
			m_bPressLBtn = false;
		}
		if (GetAsyncKeyState(VK_RBUTTON))
		{
			m_dwMouseKey |= Engine::MOUSE_RBUTTON_PRESS;
			m_bPressRBtn = true;
		}
		else
		{
			if (m_bPressRBtn == true)
				m_dwMouseKey |= Engine::MOUSE_RBUTTON_CLICK;
			m_bPressRBtn = false;
		}
	}
}

D3DXVECTOR3 Engine::CMouseMgr::GetMousePos()
{
	return D3DXVECTOR3((float)m_ptMouse.x, (float)m_ptMouse.y, 0.f);;
}

DWORD Engine::CMouseMgr::GetMouseKey()
{
	return m_dwMouseKey;
}

D3DXVECTOR3 Engine::CMouseMgr::InitMousePos(void)
{
	RECT rc;
	POINT pt;
	D3DXVECTOR3 vExMousePos = D3DXVECTOR3(0.f, 0.f, 0.f);

	GetClientRect(m_hWnd, &rc);

	pt.x = (rc.right - rc.left) / 2;
	pt.y = (rc.bottom - rc.top) / 2;

	vExMousePos.x = float(pt.x);
	vExMousePos.y = float(pt.y);

	ClientToScreen(m_hWnd, &pt);
	SetCursorPos(pt.x, pt.y);

	return vExMousePos;
}