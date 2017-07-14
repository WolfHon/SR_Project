/*!
 * \class CStage
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

#ifndef __Stage_h__
#define __Stage_h__

#include "Scene.h"

class CStage
	: public Engine::CScene
{
public:
	enum LAYERID {LAYER_ENVIROMENT, LAYER_GAMELOGIC, LAYER_UI};

private:
	explicit CStage(LPDIRECT3DDEVICE9 pDevice);

public:
	virtual ~CStage(void);

public:
	virtual void Update(void);
	virtual void Render(void);

public:
	static CStage* Create(LPDIRECT3DDEVICE9 pDevice);

private:
	HRESULT Initialize(void);
	void Release(void);

private:
	HRESULT Add_Enviroment_Layer(void);
	HRESULT Add_GameLogic_Layer(void);
	HRESULT Add_UI_Layer(void);
};


#endif // __Stage_h__