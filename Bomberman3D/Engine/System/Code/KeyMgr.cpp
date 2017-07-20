#include "KeyMgr.h"

IMPLEMENT_SINGLETON(Engine::CKeyMgr)

Engine::CKeyMgr::CKeyMgr()
: m_dwKey(0)
{
	ZeroMemory(m_bPress, sizeof(bool) * 6);
}

Engine::CKeyMgr::~CKeyMgr()
{
}

void Engine::CKeyMgr::Update(void)
{
	m_dwKey = 0;

	if (GetAsyncKeyState('W'))
	{
		m_dwKey |= KEY_W_PRESS;
		m_bPress[0] = true;
	}
	else
	{
		if(m_bPress[0] == true)
			m_dwKey |= KEY_W_CLICK;
		m_bPress[0] = false;
	}
	if (GetAsyncKeyState('A'))
	{
		m_dwKey |= KEY_A_PRESS;
		m_bPress[1] = true;
	}
	else
	{
		if (m_bPress[1] == true)
			m_dwKey |= KEY_A_CLICK;
		m_bPress[1] = false;
	}
	if (GetAsyncKeyState('S'))
	{
		m_dwKey |= KEY_S_PRESS;
		m_bPress[2] = true;
	}
	else
	{
		if (m_bPress[2] == true)
			m_dwKey |= KEY_S_CLICK;
		m_bPress[2] = false;
	}
	if (GetAsyncKeyState('D'))
	{
		m_dwKey |= KEY_D_PRESS;
		m_bPress[3] = true;
	}
	else
	{
		if (m_bPress[3] == true)
			m_dwKey |= KEY_D_CLICK;
		m_bPress[3] = false;
	}
	if (GetAsyncKeyState(VK_SPACE))
	{
		m_dwKey |= KEY_SPACE_PRESS;
		m_bPress[4] = true;
	}
	else
	{
		if (m_bPress[4] == true)
			m_dwKey |= KEY_SPACE_CLICK;
		m_bPress[4] = false;
	}
	if (GetAsyncKeyState(VK_RETURN))
	{
		m_dwKey |= KEY_ENTER_PRESS;
		m_bPress[5] = true;
	}
	else
	{
		if (m_bPress[5] == true)
			m_dwKey |= KEY_ENTER_CLICK;
		m_bPress[5] = false;
	}
}
