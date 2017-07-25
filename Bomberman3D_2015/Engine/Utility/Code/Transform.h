/*!
 * \class CTransform
 *
 * \ingroup GroupName
 *
 * \brief 
 *
 * TODO: Transform Component
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

#ifndef __Transform_h__
#define __Transform_h__

#include "Component.h"

BEGIN(Engine)

class ENGINE_DLL CTransform
	: public CComponent
{
private:
	explicit CTransform(const D3DXVECTOR3& vLook);
	virtual ~CTransform(void);

public:
	virtual Engine::OBJECT_RESULT Update(void);

public:
	static CTransform* Create(const D3DXVECTOR3& vLook);

public:
	virtual DWORD Release(void);

public:
	float			m_fAngle[ANGLE_END];
	D3DXVECTOR3		m_vPos;
	D3DXVECTOR3		m_vDir;
	D3DXVECTOR3		m_vScale;
	D3DXMATRIX		m_matWorld;
};

END

#endif // __Transform_h__