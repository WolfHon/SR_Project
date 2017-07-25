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

	static unsigned long state[16] = 
	{ (unsigned long)time(NULL), (unsigned long)time(NULL), (unsigned long)time(NULL), (unsigned long)time(NULL),
	(unsigned long)time(NULL), (unsigned long)time(NULL), (unsigned long)time(NULL), (unsigned long)time(NULL),
	(unsigned long)time(NULL), (unsigned long)time(NULL), (unsigned long)time(NULL), (unsigned long)time(NULL),
	(unsigned long)time(NULL), (unsigned long)time(NULL), (unsigned long)time(NULL), (unsigned long)time(NULL)};
	static unsigned int index = 0;

	static int getInt(int nMin, int nMax)
	{	
		unsigned long a, b, c, d;
		a = state[index];
		c = state[(index + 13) & 15];
		b = a^c ^ (a << 16) ^ (c << 15);
		c = state[(index + 9) & 15];
		c ^= (c >> 11);
		a = state[index] = b^c;
		d = a ^ ((a << 5) & 0xDA442D20UL);
		index = (index + 15) & 15;
		a = state[index];
		state[index] = a^b^d ^ (a << 2) ^ (b << 18) ^ (c << 28);

		return (int)(state[index] % (nMax - nMin)) + nMin;
	}
}

#endif // __Engine_Function_h__
