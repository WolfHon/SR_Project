/*!
 * \class CSceneSelector
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

#ifndef __SceneSelector_h__
#define __SceneSelector_h__

#include "Include.h"
#include "Logo.h"
#include "Stage.h"

class CSceneSelector
{
public:
	explicit CSceneSelector(SCENEID eSceneID)
		: m_eSceneID(eSceneID) {}
	~CSceneSelector(void) {};

public:
	HRESULT	operator()(Engine::CScene** ppScene, LPDIRECT3DDEVICE9 pDevice)
	{
		switch(m_eSceneID)
		{
		case SCENE_LOGO:
			*ppScene = CLogo::Create(pDevice);
			break;

		/*case SCENE_STAGE:
			*ppScene = CStage::Create(pDevice);
			break;*/
		}
		NULL_CHECK_RETURN(*ppScene, E_FAIL);

		return S_OK;
	}
		
private:
	SCENEID		m_eSceneID;
};

#endif // __SceneSelector_h__