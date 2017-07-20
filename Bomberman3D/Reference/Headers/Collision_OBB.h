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

class CCubeColor;

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
	CCollision_OBB(LPDIRECT3DDEVICE9 pDevice);
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
	void Render(const DWORD& dwColor);
	virtual DWORD Release(void);

public:
	void CollisionUpdate(void);
	void AABBUpdate(void);
	bool CheckCollision(D3DXVECTOR3 vPos, Engine::OBJLIST* listObj);

public:
	const D3DXVECTOR3* GetMin(void) const {return &m_vColliderMin;}
	const D3DXVECTOR3* GetMax(void) const {return &m_vColliderMax;}
	const D3DXMATRIX* GetMatrix(void) const {return &m_matColliderMatrix;}

private:	
	HRESULT	InitCollision(void);
	bool CheckAABB(CCollision_OBB* pTarget);	
	bool ProcessingCollision(CCollision_OBB* pTarget);
	void ComputePoint(void);
	void ComputeAxis(void);

public:
	static CCollision_OBB* Create(LPDIRECT3DDEVICE9 pDevice);

private:
	const D3DXMATRIX*	m_pmatWorld;
	D3DXMATRIX			m_matColliderMatrix;

private:
	LPDIRECT3DDEVICE9		m_pDevice;

	D3DXVECTOR3			m_vPoint[8];
	D3DXVECTOR3			m_vMin;
	D3DXVECTOR3			m_vMax;
	OBB					m_tOBB;

	D3DXVECTOR3			m_vColliderMin;
	D3DXVECTOR3			m_vColliderMax;

	Engine::CCubeColor*		m_pCubeColor;
	Engine::VTXCOL*	pVertex;
};

END

#endif // __Collision_OBB_h__