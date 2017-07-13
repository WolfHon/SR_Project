/*!
 * \file Logo.h
 * \date 2017/07/04 11:32
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

#ifndef Logo_h__
#define Logo_h__

#include "Scene.h"

class CLogo
	: public Engine::CScene
{
public:
	enum LAYERID {LAYER_ENVIROMENT, LAYER_GAMELOGIC, LAYER_UI};

private:
	explicit CLogo(LPDIRECT3DDEVICE9 pDevice);

public:
	virtual ~CLogo(void);

public:
	virtual void Update(void);
	virtual void Render(void);

public:
	static CLogo* Create(LPDIRECT3DDEVICE9 pDevice);

private:
	HRESULT Initialize(void);
	void Release(void);

private:
	HRESULT Add_Enviroment_Layer(void);
	HRESULT Add_GameLogic_Layer(void);
	HRESULT Add_UI_Layer(void);
};

#endif // Logo_h__