/*!
 * \class CLogo
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

#ifndef __Logo_h__
#define __Logo_h__

#include "Scene.h"

class CLogo
	: public Engine::CScene
{
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

#endif // __Logo_h__