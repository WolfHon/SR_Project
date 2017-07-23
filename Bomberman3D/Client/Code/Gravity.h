/*!
 * \file Gravity.h
 * \date 2017/07/23 21:11
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

#ifndef __Gravity_h__
#define __Gravity_h__

#include "Component.h"

#define GRAVITY 9.8f

class CGravity : public Engine::CComponent
{
private:
	CGravity(void);
	explicit CGravity(const CGravity& rhs);

public:
	virtual ~CGravity(void);

public:
	void SetInfo(D3DXVECTOR3* vPoint, D3DXVECTOR3* vPos, D3DXMATRIX* matWorld, float Height);

public:
	float GetExHeight(void) { return m_fExHeight; }
	bool GetStopDown(void) { return m_bStopDown; }

public:	
	virtual Engine::OBJECT_RESULT Update(void);
	virtual DWORD Release(void);

private:
	void InitializeGravity(void);

public:
	static CGravity* Create();

private:
	float			m_fAcc;
	float			m_fDownSpeed;

	D3DXMATRIX*			m_pMatWorld;
	D3DXVECTOR3*		m_pPos;
	D3DXVECTOR3			m_vPoint[4];
	float				m_fExHeight;
	float				m_fModelHeight;

	bool				m_bStopDown;
};

#endif // __Collision_OBB_h__