/*!
 * \file CPlayerModel
 *
 * \brief 
 *
 * TODO: PlayerModel Pibot Component
 *
 * \note 
 *
 * \date 2017/07/15 16:30
 *
 * \author BW
 *
 * \version 1.0
 *
 * \
 *
 * Contact: user@company.com
 *
*/

#pragma once

#include "Resources.h"

BEGIN(Engine)

class CTexture;
class CTransform;
class CVIBuffer;

class ENGINE_DLL CPlayerModel
	:public CResources
{
private:
	explicit CPlayerModel(LPDIRECT3DDEVICE9 pDevice);
	CPlayerModel(const CPlayerModel& rhs);

public:
	virtual ~CPlayerModel(void);

public:
	virtual CResources* CloneResource(void);

public:
	static CPlayerModel* Create(LPDIRECT3DDEVICE9 pDevice);

	HRESULT Initialize(void);
	void Render(void);

	HRESULT	AddComponent(void);

public:
	virtual DWORD Release(void);

public:
	void	SetAngle(vector<ANIFRAME>	pAniList)
	{
		m_listAni = pAniList;
		m_bFirst = true;

		m_bDiscrimination_Fr_Ani = true;
	};

	void	SetFrame(ANIFRAME	pFrameAngle)
	{
		m_pFrameAngle = pFrameAngle;
		m_bDiscrimination_Fr_Ani = false;
	}

public:
	void	Frame(void);
	void	Animation(void);
	bool	CompareAngle(void);
	bool	CompareHeadAngle(void);
	bool	CompareBodyAngle(void);
	bool	CompareLeftArmAngle(void);
	bool	CompareRightArmAngle(void);
	bool	CompareLeftFootAngle(void);
	bool	CompareRightFootAngle(void);

public:
	D3DXVECTOR3		m_vHeadPos,			m_vHeadPibotPos;
	D3DXVECTOR3		m_vBodyPos,			m_vBodyPosPibotPos;
	D3DXVECTOR3		m_vLeftArmPos,		m_vLeftArmPibotPos;
	D3DXVECTOR3		m_vRightArmPos, 	m_vRightArmPibotPos;
	D3DXVECTOR3		m_vLeftFootPos, 	m_vLeftFootPibotPos;
	D3DXVECTOR3		m_vRightFootPos,	m_vRightFootPibotPos;

	D3DXVECTOR3		m_vHeadScale;
	D3DXVECTOR3		m_vBodyScale;
	D3DXVECTOR3		m_vArmScale;
	D3DXVECTOR3		m_vFootScale;



	D3DXMATRIX		m_matHeadWorld,			m_matHeadTrans,			m_matHeadPibotTrans,		m_matHeadRotate;
	D3DXMATRIX		m_matBodyWorld,			m_matBodyTrans,			m_matBodyPibotTrans,		m_matBodyRotate;
	D3DXMATRIX		m_matRightArmWorld, 	m_matRightArmTrans, 	m_matRightArmPibotTrans,	m_matRightArmRotate;
	D3DXMATRIX		m_matLeftArmWorld,		m_matLeftArmTrans,  	m_matLeftArmPibotTrans,		m_matLeftArmRotate;
	D3DXMATRIX		m_matRightFootWorld,	m_matRightFootTrans,	m_matRightFootPibotTrans,	m_matRightFootRotate;
	D3DXMATRIX		m_matLeftFootWorld,		m_matLeftFootTrans, 	m_matLeftFootPibotTrans,	m_matLeftFootRotate;

	D3DXMATRIX		m_matHeadRotationX,			m_matHeadRotationY,			m_matHeadRotationZ;
	D3DXMATRIX		m_matBodyRotationX,			m_matBodyRotationY,			m_matBodyRotationZ;
	D3DXMATRIX		m_matRightArmRotationX,		m_matRightArmRotationY,		m_matRightArmRotationZ;
	D3DXMATRIX		m_matLeftArmRotationX,		m_matLeftArmRotationY,		m_matLeftArmRotationZ;
	D3DXMATRIX		m_matRightFootRotationX,	m_matRightFootRotationY,	m_matRightFootRotationZ;
	D3DXMATRIX		m_matLeftFootRotationX,		m_matLeftFootRotationY,		m_matLeftFootRotationZ;

	D3DXMATRIX		m_matScale;


protected:
	CTexture*		m_pHeadTexture;
	CTexture*		m_pBodyTexture;
	CTexture*		m_pLeftArmTexture;
	CTexture*		m_pRightArmTexture;
	CTexture*		m_pLeftFootTexture;
	CTexture*		m_pRightFootTexture;

	CVIBuffer*		m_pHeadBuffer;
	CVIBuffer*		m_pBodyBuffer;
	CVIBuffer*		m_pLeftArmBuffer;
	CVIBuffer*		m_pRightArmBuffer;
	CVIBuffer*		m_pLeftFootBuffer;
	CVIBuffer*		m_pRightFootBuffer;

private:
	typedef map<wstring, CComponent*>		MAPCOMPONENT;
	MAPCOMPONENT		m_mapComponent;
	ANIFRAME			m_pFrameAngle;
	ANIFRAME			m_pNextFrame;
	vector<ANIFRAME>	m_listAni;
	vector<ANIFRAME>	m_LastAniList;
	float				m_fScaleSize;
	bool				m_bHeadCom;
	bool				m_bBodyCom;
	bool				m_bLeftArmCom;
	bool				m_bRightArmCom;
	bool				m_bLeftFootCom;
	bool				m_bRightFootCom;
	bool				m_bFirst;
	bool				m_bDiscrimination_Fr_Ani;
	bool				m_bAnimationCh;
};

END