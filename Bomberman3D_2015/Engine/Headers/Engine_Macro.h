/*!
 * \file Engine_Macro.h
 * \date 2017/07/13 21:08
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

#ifndef __Engine_Macro_h__
#define __Engine_Macro_h__

#define MSG_BOX(_message)	MessageBox(NULL, _message, L"System Message", MB_OK)
#define TAGMSG_BOX(_tag,_message)	MessageBox(NULL, _message, _tag, MB_OK)

#ifdef _DEBUG

#define NULL_CHECK( _ptr)	\
	if(_ptr == 0)	\
{ __asm { int 3 }; return; }

#define NULL_CHECK_RETURN( _ptr, _return)	\
	if(_ptr == 0)	\
{ __asm { int 3 }; return _return; }

#define NULL_CHECK_MSG( _ptr, _message )		\
	if(_ptr == 0)	\
{ MSG_BOX(_message); __asm { int 3 }; }

#define NULL_CHECK_RETURN_MSG( _ptr, _return, _message )	\
	if(_ptr == 0)	\
{ MSG_BOX(_message); __asm { int 3 }; return _return; }

#define NULL_CHECK_RETURN_TAGMSG( _ptr, _return, _tag, _message )	\
	if(_ptr == 0)	\
{ TAGMSG_BOX(_tag,_message); __asm { int 3 }; return _return; }

#define FAILED_CHECK(_hr)	\
	if( ((HRESULT)(_hr)) < 0 )	\
{ __asm { int 3 }; return E_FAIL; }

#define FAILED_CHECK_RETURN(_hr, _return)	\
	if( ((HRESULT)(_hr)) < 0 )		\
{ __asm { int 3 }; return _return; }

#define FAILED_CHECK_MSG( _hr, _message)	\
	if( ((HRESULT)(_hr)) < 0 )	\
{ MSG_BOX(_message); __asm { int 3 }; return E_FAIL; }

#define FAILED_CHECK_RETURN_MSG( _hr, _return, _message)	\
	if( ((HRESULT)(_hr)) < 0 )	\
{ MSG_BOX(_message); __asm { int 3 }; return _return; }

#define FAILED_CHECK_RETURN_TAGMSG( _hr, _return, _tag, _message)	\
	if( ((HRESULT)(_hr)) < 0 )	\
{ MSG_BOX(_tag, _message); __asm { int 3 }; return _return; }

#else

#define NULL_CHECK( _ptr)	\
	if(_ptr == 0)	\
{ return; }	

#define NULL_CHECK_RETURN( _ptr, _return)	\
	if(_ptr == 0)	\
{ return _return; }	

#define NULL_CHECK_MSG( _ptr, _message )		\
	if(_ptr == 0)	\
{ MSG_BOX(_message); }

#define NULL_CHECK_RETURN_MSG( _ptr, _return, _message )	\
	if(_ptr == 0)	\
{ MSG_BOX(_message); return _return; }

#define NULL_CHECK_RETURN_TAGMSG( _ptr, _return, _tag, _message )	\
	if(_ptr == 0)	\
{ TAGMSG_BOX(_tag,_message); return _return; }

#define FAILED_CHECK(_hr)	\
	if( ((HRESULT)(_hr)) < 0 )	\
{ return E_FAIL; }

#define FAILED_CHECK_RETURN(_hr, _return)	\
	if( ((HRESULT)(_hr)) < 0 )		\
{ return _return; }

#define FAILED_CHECK_MSG( _hr, _message)	\
	if( ((HRESULT)(_hr)) < 0 )	\
{ MSG_BOX(_message); return E_FAIL; }

#define FAILED_CHECK_RETURN_MSG( _hr, _return, _message)	\
	if( ((HRESULT)(_hr)) < 0 )	\
{ MSG_BOX(_message); return _return; }

#define FAILED_CHECK_RETURN_TAGMSG( _hr, _return, _tag, _message)	\
	if( ((HRESULT)(_hr)) < 0 )	\
{ MSG_BOX(_tag, _message); return _return; }

#endif


#define BEGIN(NAMESPACE) namespace NAMESPACE {
#define END }


#ifdef ENGINE_EXPORTS
#define ENGINE_DLL _declspec(dllexport) 
#else
#define ENGINE_DLL _declspec(dllimport) 
#endif

#define NO_COPY(CLASSNAME)							\
	private:										\
	CLASSNAME(const CLASSNAME&);					\
	CLASSNAME& operator = (const CLASSNAME&);		

#define DECLARE_SINGLETON(CLASSNAME)				\
	NO_COPY(CLASSNAME)								\
	private:										\
	static CLASSNAME*	m_pInstance;				\
	public:											\
	static CLASSNAME*	GetInstance( void );		\
	static void DestroyInstance( void );			

#define IMPLEMENT_SINGLETON(CLASSNAME)				\
	CLASSNAME*	CLASSNAME::m_pInstance = NULL;		\
	CLASSNAME*	CLASSNAME::GetInstance( void )	{	\
		if(NULL == m_pInstance) {					\
			m_pInstance = new CLASSNAME;			\
		}											\
		return m_pInstance;							\
	}												\
	void CLASSNAME::DestroyInstance( void ) {		\
		if(NULL != m_pInstance)	{					\
			delete m_pInstance;						\
			m_pInstance = NULL;						\
		}											\
	}

#endif // __Engine_Macro_h__
