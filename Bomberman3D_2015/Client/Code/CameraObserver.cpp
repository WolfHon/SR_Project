#include "stdafx.h"
#include "CameraObserver.h"

#include "Export_Function.h"
#include "CameraControl.h"

CCameraObserver::CCameraObserver(void)
{	
}

CCameraObserver::~CCameraObserver(void)
{
	Release();
}

HRESULT CCameraObserver::InitObserver(void)
{
	m_eCameraType = CCameraControl::CAM_FIRST;

	return S_OK;
}

void CCameraObserver::Update(const wstring& message, int iDataIndex /*= 0*/)
{
	Engine::DATALIST*		pDataList = Engine::Get_InfoSubject()->GetDatalist(message);
	NULL_CHECK(pDataList);

	m_eCameraType = *((CCameraControl::CAMERATYPE*)(*pDataList->begin()));
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
