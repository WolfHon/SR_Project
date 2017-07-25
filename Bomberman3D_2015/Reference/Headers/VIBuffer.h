/*!
 * \class CVIBuffer
 *
 * \ingroup GroupName
 *
 * \brief 
 *
 * TODO: VIBuffer Class
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

#ifndef __VIBuffer_h__
#define __VIBuffer_h__

#include "Resources.h"

BEGIN(Engine)

class ENGINE_DLL CVIBuffer
	: public CResources
{
protected:
	explicit CVIBuffer(LPDIRECT3DDEVICE9 pDevice);
	explicit CVIBuffer(const CVIBuffer& rhs);

public:
	virtual ~CVIBuffer(void);

public:
	void GetVtxInfo(void* pVertex);

public:
	void SetVtxInfo(void* pVertex);

public:
	HRESULT CreateBuffer(void);

public:
	virtual void Render(void);

public:
	virtual DWORD Release(void);

protected:
	LPDIRECT3DVERTEXBUFFER9		m_pVB;
	DWORD		m_dwVtxSize;
	DWORD		m_dwVtxCnt;
	DWORD		m_dwVtxFVF;

	LPDIRECT3DINDEXBUFFER9		m_pIB;
	DWORD		m_dwIdxSize;
	DWORD		m_dwTriCnt;
	D3DFORMAT	m_IdxFmt;
};

END


#endif // __VIBuffer_h__