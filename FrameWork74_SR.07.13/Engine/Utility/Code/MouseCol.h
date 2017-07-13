/*!
 * \file MouseCol.h
 * \date 2017/07/12 10:10
 *
 * \author Administrator
 * Contact: user@company.com
 *
 * \brief 
 *
 * TODO: long description
 *
 * \note
*/

#ifndef MouseCol_h__
#define MouseCol_h__

#include "Collision.h"

BEGIN(Engine)

class ENGINE_DLL CMouseCol
	: public CCollision
{
private:
	CMouseCol(void);

public:
	virtual ~CMouseCol(void);

public:
	void PickTerrain(D3DXVECTOR3* pOut
		, const D3DXMATRIX* pmatProj
		, const D3DXMATRIX* pmatView);
	void PickObject(D3DXVECTOR3* pOut
		, const Engine::VTXTEX* pVertex
		, const D3DXMATRIX* pmatProj
		, const D3DXMATRIX* pmatView
		, const D3DXMATRIX* pmatWorld);

public:
	static CMouseCol* Create(HWND hWnd, const VTXTEX* pTerrainVtx);

public:
	virtual DWORD Release(void);

private:
	HRESULT InitCollision(HWND hWnd, const VTXTEX* pTerrainVtx);
	void Translation_ViewSpace(const D3DXMATRIX* pmatProj);
	void Translation_Local(const D3DXMATRIX* pmatView
		, const D3DXMATRIX* pmatWorld);
	POINT GetMousePos(void);

private:
	D3DXVECTOR3		m_vPivotPos;
	D3DXVECTOR3		m_vRayDir;
	HWND			m_hWnd;
	D3DXMATRIX*		m_pmatProj;
	D3DXMATRIX*		m_pmatView;
	const VTXTEX*	m_pTerrainVtx;
};

END

#endif // MouseCol_h__