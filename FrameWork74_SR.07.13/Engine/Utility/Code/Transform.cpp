#include "Transform.h"
#include "Pipeline.h"

Engine::CTransform::CTransform(const D3DXVECTOR3& vLook)
: m_vDir(vLook)
, m_vPos(0.f, 0.f, 0.f)
{
	D3DXMatrixIdentity(&m_matWorld);
	ZeroMemory(m_fAngle, sizeof(float) * ANGLE_END);
}

Engine::CTransform::~CTransform(void)
{

}

void Engine::CTransform::Update(void)
{
	CPipeline::MakeWorldMatrix(&m_matWorld, &D3DXVECTOR3(1.f, 1.f, 1.f)
		, m_fAngle, &m_vPos);
}

Engine::CTransform* Engine::CTransform::Create(const D3DXVECTOR3& vLook)
{
	return new CTransform(vLook);
}

DWORD Engine::CTransform::Release(void)
{
	return 0;
}

