/*!
 * \class CTerrainInfo
 *
 * \ingroup GroupName
 *
 * \brief 
 *
 * TODO: long description
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

#ifndef __TerrainInfo_h__
#define __TerrainInfo_h__

#include "Engine_Include.h"
#include "Collision_OBB.h"

class CBlock;

class CTerrainInfo 
{
public:
	DECLARE_SINGLETON(CTerrainInfo)

private:
	CTerrainInfo(void);
	virtual ~CTerrainInfo(void);

public:
	void InsertInfo(CBlock* Block);
	void EraseInfo(CBlock* Block);
	CBlock* CheckCollision(CCollision_OBB* srcObb, D3DXVECTOR3 vPos);

private:
	typedef struct tagMapVector
	{
		float x;
		float y;
		float z;

		bool operator < (const tagMapVector &rhs) const
		{
			if(fabs(x - rhs.x) < 0.000001f)
			{
				if(fabs(y - rhs.y) < 0.000001f)
				{
					if(fabs(z - rhs.z) < 0.000001f)
					{
						return false;
					}
					else if (z < rhs.z)
						return true;
					else if(z > rhs.z)
						return false;
				}
				else if (y < rhs.y)
					return true;
				else if(y > rhs.y)
					return false;
			}
			else if (x < rhs.x)
				return true;
			else if(x > rhs.x)
				return false;

			return false;
		}
	}MAPVECTOR;

private:
	map<MAPVECTOR, CBlock*> mapBlock;
};

#endif __TerrainInfo_h__