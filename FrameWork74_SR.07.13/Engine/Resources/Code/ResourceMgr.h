/*!
 * \file ResourceMgr.h
 * \date 2017/07/03 10:40
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

#ifndef ResourceMgr_h__
#define ResourceMgr_h__

#include "Engine_Include.h"

BEGIN(Engine)

class CResources;
class CComponent;

class ENGINE_DLL CReousrceMgr
{
public:
	DECLARE_SINGLETON(CReousrceMgr)

private:
	CReousrceMgr(void);
	~CReousrceMgr(void);

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
