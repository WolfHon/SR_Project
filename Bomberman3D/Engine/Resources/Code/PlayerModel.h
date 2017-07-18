/*!
 * \file CPlayerModel
 *
 * \brief 
 *
 * TODO: PlayerModel Pibot Component
 *
 * \note 
 *
 * \date 2017/07/15 16:30
 *
 * \author BW
 *
 * \version 1.0
 *
 * \
 *
 * Contact: user@company.com
 *
*/

#pragma once

#include "Resources.h"

BEGIN(Engine)

class CTexture;
class CTransform;
class CVIBuffer;

class ENGINE_DLL CPlayerModel
	:public CResources
{
private:
	explicit CPlayerModel(LPDIRECT3DDEVICE9 pDevice);
	CPlayerModel(const CPlayerModel& rhs);

public:
	virtual ~CPlayerModel(void);

public:
	virtual CResources* CloneResource(void);

public:
	static CPlayerModel* Create(LPDIRECT3DDEVICE9 pDevice);

	HRESULT Initialize(void);
	void Update(void);
	void Render(void);

	HRESULT	AddComponent(void);

public:
	virtual DWORD Release(void);

public:
	D3DXVECTOR3		m_vHeadPos;
	D3DXVECTOR3		m_vBodyPos;
	D3DXVECTOR3		m_vLeftArmPos;
	D3DXVECTOR3		m_vRightArmPos;
	D3DXVECTOR3		m_vLeftFootPos;
	D3DXVECTOR3		m_vRightFootPos;

	D3DXVECTOR3		m_vHeadScale;
	D3DXVECTOR3		m_vBodyScale;
	D3DXVECTOR3		m_vArmScale;
	D3DXVECTOR3		m_vFootScale;



	D3DXMATRIX		m_matHeadWorld;
	D3DXMATRIX		m_matBodyWorld;
	D3DXMATRIX		m_matRightArmWorld;
	D3DXMATRIX		m_matLeftArmWorld;
	D3DXMATRIX		m_matRightFootWorld;
	D3DXMATRIX		m_matLeftFootWorld;
	D3DXMATRIX		m_matScale;

protected:
	CTexture*		m_pHeadTexture;
	CTexture*		m_pBodyTexture;
	CTexture*		m_pLeftArmTexture;
	CTexture*		m_pRightArmTexture;
	CTexture*		m_pLeftFootTexture;
	CTexture*		m_pRightFootTexture;

	CVIBuffer*		m_pHeadBuffer;
	CVIBuffer*		m_pBodyBuffer;
	CVIBuffer*		m_pLeftArmBuffer;
	CVIBuffer*		m_pRightArmBuffer;
	CVIBuffer*		m_pLeftFootBuffer;
	CVIBuffer*		m_pRightFootBuffer;

private:
	typedef map<wstring, CComponent*>		MAPCOMPONENT;
	MAPCOMPONENT		m_mapComponent;
	float			m_fScaleSize;
};

END