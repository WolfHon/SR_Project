/*!
 * \class CCollision_OBB
 *
 * \ingroup GroupName
 *
 * \brief 
 *
 * TODO: OBB Collision
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
#ifndef __Collision_OBB_h__
#define __Collision_OBB_h__

#include "Collision.h"

BEGIN(Engine)

class ENGINE_DLL CCollision_OBB
	: public CCollision
{
public:
	enum AXISID {AXIS_X, AXIS_Y, AXIS_Z, AXIS_END};

private:
	typedef struct tagOBB_Info
	{
		D3DXVECTOR3			vCenter;
		D3DXVECTOR3			vProj[AXIS_END]; 
		D3DXVECTOR3			vParallel[AXIS_END]; 
	}OBB;

private:
	CCollision_OBB();
	explicit CCollision_OBB(const CCollision_OBB& rhs);

public:
	virtual ~CCollision_OBB(void);

public:
	const OBB* GetObbInfo(void) const {return &m_tOBB;}

public:
	virtual CCollision* CloneCollision(void);

public:
	void SetColInfo(const D3DXMATRIX* pWorld, const D3DXVECTOR3* pMin = NULL, const D3DXVECTOR3* pMax = NULL);

public:	
	virtual DWORD Release(void);

public:
	void GetColBox(D3DXVECTOR3* pMin, D3DXVECTOR3* pMax);
	void CollisionUpdate(void);
	bool CheckCollision(CCollision_OBB* pTerget);

private:	
	void ComputePoint(void);
	void ComputeAxis(void);

public:
	static CCollision_OBB* Create(void);

private:
	const D3DXMATRIX*	m_pmatWorld;

private:
	D3DXVECTOR3			m_vPoint[8];
	D3DXVECTOR3			m_vMin;
	D3DXVECTOR3			m_vMax;
	OBB					m_tOBB;
};

END

#endif // __Collision_OBB_h__