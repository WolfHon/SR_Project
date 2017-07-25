/*!
 * \file SliceBlock.h
 * \date 2017/07/24 16:09
 *
 * \author Han
 * Contact: user@company.com
 *
 * \brief 
 *
 * TODO: long description
 *
 * \note
*/

#ifndef __SliceBlock_h__
#define __SliceBlock_h__

#include "GameObject.h"

namespace Engine
{
	class CTexture;
	class CVIBuffer;
	class CTransform;
}

class CCollision_OBB;
class CGravity;

class CSliceBlock
	: public Engine::CGameObject
{
public:
	explicit CSliceBlock(LPDIRECT3DDEVICE9 pDevice);

public:
	virtual ~CSliceBlock(void);

public:
	virtual Engine::OBJECT_RESULT Update(void);
	virtual void Render(void);

public:
	static CSliceBlock* Create(LPDIRECT3DDEVICE9 pDevice, D3DXVECTOR3 vPos, Engine::TILETEXTURE	eTexture);

private:
	HRESULT Initialize(D3DXVECTOR3 vPos, Engine::TILETEXTURE eTexture);
	void Move(void);
	HRESULT	AddComponent(void);
	Engine::OBJECT_RESULT DestroyCheck(void);
	void Release(void);

private:
	Engine::CTexture*		m_pTexture;
	Engine::CVIBuffer*		m_pBuffer;
	Engine::CTransform*		m_pInfo;

	CCollision_OBB*	m_pCollisionOBB;
	CGravity*		m_pGravity;

private:
	float			m_fTime;
	float			m_fDestroyTime;
	float			m_fPower;
	float           m_fDecreasePower;

	Engine::TILETEXTURE	m_eTexture;
};

#endif // __SliceBlock_h__