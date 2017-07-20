/*!
 * \class CTexture
 *
 * \ingroup GroupName
 *
 * \brief 
 *
 * TODO: Texture class
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

#ifndef __Texture_h__
#define __Texture_h__

#include "Resources.h"

BEGIN(Engine)

class ENGINE_DLL CTexture
	: public CResources
{
private:
	explicit CTexture(LPDIRECT3DDEVICE9 pDevice);
	CTexture(const CTexture& rhs);

public:
	virtual ~CTexture(void);

public:
	virtual CResources* CloneResource(void);

public:
	HRESULT LoadTexture(TEXTURETYPE eTextureType, const wstring& wstrFilePath, const WORD& wCnt);
	void Render(const DWORD& dwStage, const DWORD& iIndex);
	const DWORD GetMaxSize(void);

public:
	static CTexture* Create(LPDIRECT3DDEVICE9 pGraphicDev
		, TEXTURETYPE eTextureType, const wstring& wstrFilePath, const WORD& wCnt);

public:
	virtual DWORD Release(void);

private:
	typedef vector<IDirect3DBaseTexture9*>		VECTEXTURE;
	VECTEXTURE		m_vecTexture;

private:
	DWORD		m_dwContainerSize;
};

END

#endif // __Texture_h__