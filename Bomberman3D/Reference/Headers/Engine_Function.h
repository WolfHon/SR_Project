/*!
 * \file Engine_Function.h
 * \date 2017/07/13 21:10
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

#ifndef __Engine_Function_h__
#define __Engine_Function_h__

namespace Engine
{
	template <typename T> void Safe_Delete (T& pointer)
	{
		if(NULL != pointer)
		{
			delete pointer;
			pointer = NULL;
		}
	}


	template <typename T> void Safe_Delete_Array (T& pointer)
	{
		if(NULL != pointer)
		{
			delete [] pointer;
			pointer = NULL;
		}
	}


	template <typename T> DWORD Safe_Release (T& pointer)
	{
		DWORD	dwRefCnt = 0;

		if(NULL != pointer)
		{
			dwRefCnt = pointer->Release();
			if(dwRefCnt == 0)
				pointer = NULL;
		}

		return 0;
	}

	template <typename T> void Safe_Single_Destory(T& pointer)
	{
		if(NULL != pointer)
		{
			pointer->DestroyInstance();
			pointer = NULL;
		}
	}
}

#endif // __Engine_Function_h__
