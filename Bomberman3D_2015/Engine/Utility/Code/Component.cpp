#include "Component.h"

Engine::CComponent::CComponent(void)
: m_dwRefCnt(0)
{
}

Engine::CComponent::CComponent(const CComponent& rhs)
: m_dwRefCnt(rhs.m_dwRefCnt)
{
	++m_dwRefCnt;
}

Engine::CComponent::~CComponent(void)
{
}

void Engine::CComponent::AddRefCnt(void)
{
	++m_dwRefCnt;
}

