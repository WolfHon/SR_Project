/*!
 * \class CCameraControl
 *
 * \ingroup GroupName
 *
 * \brief 
 *
 * TODO: Camerea Control
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

#include "Gameobject.h"

namespace Engine
{
	class CCamera;
	class CTransform;
}

class CCameraControl :
	public Engine::CGameObject
{
public:
	enum CAMERATYPE { CAM_ACTION, CAM_FIRST, CAM_END};

public:
	explicit CCameraControl(LPDIRECT3DDEVICE9 pDevice);

public:
	virtual ~CCameraControl(void);

public:
	virtual void Update(void);
	virtual void Render(void);

public:
	void SetCamera(CAMERATYPE NowCam);

public:
	CAMERATYPE GetCamera();

public:
	static CCameraControl* Create(LPDIRECT3DDEVICE9 pDevice, const Engine::CTransform* pTargetInfo);

private:
	HRESULT Initialize(const Engine::CTransform* pTargetInfo);
	void Release(void);

private:
	CAMERATYPE				m_eNowCam;
	Engine::CCamera*		m_pCamera[CAM_END];
};
