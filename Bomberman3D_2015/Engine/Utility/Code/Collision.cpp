#include "Collision.h"

Engine::CCollision::CCollision(void)
{
}

Engine::CCollision::CCollision(const CCollision& rhs)
: CComponent(rhs)
{
}

Engine::CCollision::~CCollision(void)
{
}

Engine::CCollision* Engine::CCollision::GetColObject(void)
{
	AddRefCnt();

	return this;
}
