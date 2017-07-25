/*!
 * \class CResourceMgr
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

#ifndef ResourceMgr_h__
#define ResourceMgr_h__

#include "Engine_Include.h"

BEGIN(Engine)

class CResources;
class CComponent;

class ENGINE_DLL CResouceMgr
{
public:
	DECLARE_SINGLETON(CResouceMgr)

private:
	CResouceMgr(void);
	~CResouceMgr(void);

public:
	CComponent* CloneResource(RESOURCETYPE eResourceID, const wstring& wstrResourceKey);

public:
	HRESULT AddBuffer(LPDIRECT3DDEVICE9 pDevice
		, RESOURCETYPE eResourceID
		, BUFFERTYPE eBufferID
		, const wstring& wstrResourceKey
		, const WORD& wCntX = 0, const WORD& wCntZ = 0, const WORD& wItv = 1);

	HRESULT AddTexture(LPDIRECT3DDEVICE9 pDevice
		, RESOURCETYPE eResourceID
		, TEXTURETYPE eTextureID
		, const wstring& wstrResourceKey
		, const wstring& wstrFilePath
		, const WORD& wCnt);

public:
	void ResetDynamic(void);

private:
	void Release(void);

private:
	typedef map<wstring, CResources*>		MAPRESOURCE;
	MAPRESOURCE		m_mapResource[RESOURCE_END];
};

END

#endif // ResourceMgr_h__
