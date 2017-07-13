/*!
 * \file TerrainCol.h
 * \date 2017/07/10 10:27
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

#ifndef TerrainCol_h__
#define TerrainCol_h__

#include "Collision.h"

BEGIN(Engine)

class ENGINE_DLL CTerrainCol
	: public CCollision
{
private:
	CTerrainCol(void);

public:
	virtual ~CTerrainCol(void);

public:
	void SetTerrainVtx(const VTXTEX* pTerrainVtx);
	void SetColInfo(D3DXVECTOR3* pPos);

public:
	virtual void Update(void);
	virtual DWORD Release(void);

public:
	static CTerrainCol* Create(void);

private:
	D3DXVECTOR3*		m_pPos;
	const VTXTEX*		m_pTerrainVtx;
};

END

#endif // TerrainCol_h__