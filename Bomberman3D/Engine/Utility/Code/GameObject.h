/*!
 * \class CGameObject
 *
 * \ingroup GroupName
 *
 * \brief 
 *
 * TODO: GameObject class
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

#ifndef __GameObject_h__
#define __GameObject_h__

#include "Engine_Include.h"

BEGIN(Engine)

class CComponent;

class ENGINE_DLL CGameObject
{
protected:
	explicit CGameObject(LPDIRECT3DDEVICE9 pDevice);

public:
	virtual ~CGameObject(void);

public:
	CComponent* GetComponent(const wstring& wstrComponentKey);

public:
	virtual Engine::OBJECT_RESULT Update(void);
	virtual void Render(void);

private:
	void Release(void);

protected:
	LPDIRECT3DDEVICE9		m_pDevice;

protected:
	typedef map<wstring, CComponent*>		MAPCOMPONENT;
	MAPCOMPONENT		m_mapComponent;
};

END

#endif // __GameObject_h__