#include "stdafx.h"
#include "CameraObserver.h"

#include "Export_Function.h"

CCameraObserver::CCameraObserver(void)
{
	D3DXMatrixIdentity(&m_Matrix[MATRIX_VIEW]);
	D3DXMatrixIdentity(&m_Matrix[MATRIX_PROJECTION]);
}

CCameraObserver::~CCameraObserver(void)
{
	Release();
}

HRESULT CCameraObserver::InitObserver(void)
{
	return S_OK;
}

void CCameraObserver::Update(const wstring& message, int iDataIndex /*= 0*/)
{
	Engine::DATALIST*		pDataList = Engine::Get_InfoSubject()->GetDatalist(message);
	NULL_CHECK(pDataList);

	Engine::DATALIST::iterator	iter = pDataList->begin();
	Engine::DATALIST::iterator	iter_end = pDataList->end();

	for( ; iter != iter_end; ++iter)
	{
		m_Matrix[iDataIndex] = *((D3DXMATRIX*)(*iter));
		++iDataIndex;
	}

	/*for(int i = 0; i < iDataIndex; ++i)
	{
		++iter;
	}
	m_Matrix[iDataIndex] = *((D3DXMATRIX*)(*iter));*/
}

void CCameraObserver::Release(void)
{
	
}

CCameraObserver* CCameraObserver::Create(void)
{
	CCameraObserver*	pObserver = new CCameraObserver;
	if(FAILED(pObserver->InitObserver()))
		Safe_Delete(pObserver);

	return pObserver;
}
