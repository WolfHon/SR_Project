#include "stdafx.h"
#include "Explosion.h"
#include "Texture.h"
#include "RcTex.h"

#include "Include.h"
#include "Transform.h"
#include "Export_Function.h"

CExplosion::CExplosion(LPDIRECT3DDEVICE9 pDevice)
: Engine::CGameObject(pDevice)
, m_pTexture(NULL)
, m_pBuffer(NULL)
, m_fFrame(0.f)
, m_fFrameSpeed(0.f)
, m_pInfo(NULL)
{

}

CExplosion::~CExplosion(void)
{
	Release();
}

HRESULT CExplosion::Initialize(D3DXVECTOR3 vPos, int iPower)
{
	FAILED_CHECK(AddComponent());
	
	m_pInfo->m_vPos = vPos;
	m_pInfo->m_vScale = D3DXVECTOR3(2.f, 2.f, 2.f);

	m_iPower = iPower;
	m_fFrameSpeed = 30.f;

	return S_OK;
}

Engine::OBJECT_RESULT CExplosion::Update(void)
{
	D3DXVec3TransformNormal(&m_pInfo->m_vDir, &g_vLook, &m_pInfo->m_matWorld);
		
	if(Engine::CGameObject::Update() == Engine::OR_DELETE)
		return Engine::OR_DELETE;

	D3DXMATRIX		matBill;
	D3DXMatrixIdentity(&matBill);
	m_pDevice->GetTransform(D3DTS_VIEW, &matBill);
	ZeroMemory(&matBill.m[3][0], sizeof(D3DXVECTOR3));

	D3DXMatrixInverse(&matBill, NULL, &matBill);

	m_pInfo->m_matWorld = matBill * m_pInfo->m_matWorld;
	
	return Engine::OR_OK;
}

void CExplosion::Render(void)
{	
	m_pDevice->SetTransform(D3DTS_WORLD, &m_pInfo->m_matWorld);
	
	m_pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	m_pDevice->SetRenderState(D3DRS_ALPHAREF, 0x00000088);
	m_pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	m_pTexture->Render(0, 26);
	m_pBuffer->Render();

	m_pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);	
}

CExplosion* CExplosion::Create(LPDIRECT3DDEVICE9 pDevice, D3DXVECTOR3 vPos, int iPower)
{
	CExplosion*	pGameObject = new CExplosion(pDevice);
	if(FAILED(pGameObject->Initialize(vPos, iPower)))
		Safe_Delete(pGameObject);

	return pGameObject;
}

void CExplosion::Release(void)
{
}

HRESULT CExplosion::AddComponent(void)
{
	Engine::CComponent*		pComponent = NULL;

	//Transform
	pComponent = m_pInfo = Engine::CTransform::Create(g_vLook);
	NULL_CHECK_RETURN(m_pInfo, E_FAIL);
	m_mapComponent.insert(MAPCOMPONENT::value_type(L"Transform", pComponent));

	//Texture
	pComponent = Engine::Get_ResourceMgr()->CloneResource(Engine::RESOURCE_DYNAMIC, L"Texture_Explosion");
	m_pTexture = dynamic_cast<Engine::CTexture*>(pComponent);
	NULL_CHECK_RETURN(m_pTexture, E_FAIL);
	m_mapComponent.insert(MAPCOMPONENT::value_type(L"Texture", pComponent));

	//Buffer
	pComponent = Engine::Get_ResourceMgr()->CloneResource(Engine::RESOURCE_STATIC, L"Buffer_RcTex");
	m_pBuffer = dynamic_cast<Engine::CVIBuffer*>(pComponent);
	NULL_CHECK_RETURN(m_pBuffer, E_FAIL);
	m_mapComponent.insert(MAPCOMPONENT::value_type(L"Buffer", pComponent));

	return S_OK;
}