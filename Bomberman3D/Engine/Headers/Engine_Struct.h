/*!
 * \file Engine_Struct.h
 * \date 2017/07/13 21:07
 *
 * \author Han
 * Contact: user@company.com
 *
 * \brief 
 *
 * TODO: long description
 *
 * \note
*/

#ifndef __Engine_Struct_h__
#define __Engine_Struct_h__

namespace Engine
{
	typedef struct tagVertexColor
	{
		D3DXVECTOR3				vPos;
		DWORD					dwColor;
	}VTXCOL;
	const DWORD VTXFVF_COL = D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX0;

	typedef struct tagVertexCubeTex
	{
		D3DXVECTOR3				vPos;
		D3DXVECTOR3				vTex;
	}VTXCUBE;
	const DWORD VTXFVF_CUBE = D3DFVF_XYZ | D3DFVF_TEX1 | D3DFVF_TEXCOORDSIZE3(0);

	typedef struct tagVertexTexture
	{
		D3DXVECTOR3				vPos;
		D3DXVECTOR3				vNormal;
		D3DXVECTOR2				vTexUV;
	}VTXTEX;
	const DWORD VTXFVF_TEX = D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1;

	typedef struct tagIndex16
	{
		WORD			_1, _2, _3;
	}INDEX16;

	typedef struct tagIndex32
	{
		DWORD			_1, _2, _3;
	}INDEX32;

	typedef struct tagTileInfo
	{
		D3DXVECTOR3				vPos;
		D3DXVECTOR3				vScale;
		float					fAngle;
		TILETYPE				eTileOption;
		TILETEXTURE				eTexture;
		TILESHAPE				eTileShape;

	}TILEINFO;

	typedef struct tagRotationInfo
	{
		float			AngleX; //Positive Y
		float			AngleY; //Negative Y
		float			AngleZ; //Negative X
	}ANGLEINFO, *LPANGLEINFO;

	typedef struct tagAniFrame
	{
		ANGLEINFO		HeadAngle;
		ANGLEINFO		BodyAngle;
		ANGLEINFO		LeftArmAngle;
		ANGLEINFO		RightArmAngle;
		ANGLEINFO		LeftFootAngle;
		ANGLEINFO		RightFootAngle;
	}ANIFRAME,	*LPANIFRAME;

	typedef struct tagItemInfo
	{
		float		fSpeed;
		int			iAddBomb;
		float		fPower;
	}ITEMINFO;
}

#endif // __Engine_Struct_h__