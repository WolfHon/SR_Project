/*!
 * \file SceneSelector.h
 * \date 2017/07/04 11:38
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

#ifndef SceneSelector_h__
#define SceneSelector_h__

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

		case SCENE_STAGE:
			*ppScene = CStage::Create(pDevice);
			break;
		}
		NULL_CHECK_RETURN(*ppScene, E_FAIL);

		return S_OK;
	}
		
private:
	SCENEID		m_eSceneID;
};

#endif // SceneSelector_h__