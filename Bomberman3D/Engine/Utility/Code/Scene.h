/*!
 * \class CScene
 *
 * \ingroup GroupName
 *
 * \brief 
 *
 * TODO: Scene class
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

#ifndef __Scene_h__
#define __Scene_h__

#include "Engine_Include.h"

BEGIN(Engine)

class CLayer;
class CComponent;

class ENGINE_DLL CScene
{
protected:
	explicit CScene(LPDIRECT3DDEVICE9 pDevice);

public:
	virtual ~CScene(void);

public:
	const CComponent* GetComponent(const WORD& LayerID, const wstring& wstrObjKey, const wstring& wstrComponentKey);

public:
	HRESULT InitScene(void);
	virtual void Update(void);
	virtual void Render(void);

private:
	void Release(void);

protected:
	LPDIRECT3DDEVICE9	m_pDevice;

protected:
	typedef map<WORD, CLayer*>		MAPLAYER;
	MAPLAYER		m_mapLayer;
};

END

#endif // __Scene_h__