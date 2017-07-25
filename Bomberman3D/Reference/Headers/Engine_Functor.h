/*!
 * \file Engine_Functor.h
 * \date 2017/07/13 21:09
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

#ifndef __Engine_Functor_h__
#define __Engine_Functor_h__

namespace Engine
{
	class CDeleteObj
	{
	public:
		explicit CDeleteObj(void) {}
		~CDeleteObj(void) {}
	public: 
		template <typename T> void operator () (T& pInstance)
		{			
			if(NULL != pInstance)
			{
				delete pInstance;
				pInstance = NULL;
			}
		}
	};

	class CDeleteMap
	{
	public:
		explicit CDeleteMap(void){}
		~CDeleteMap(void){}
	public: 
		template <typename T> void operator () (T& Pair)
		{			
			if(NULL != Pair.second)
			{
				delete Pair.second;
				Pair.second = NULL;
			}
		}
	};

	class CTagFinder
	{
	public:
		explicit CTagFinder(const TCHAR* pTag) : m_pTag(pTag) {}
		~CTagFinder(void) {}
	public:
		template <typename T> bool operator () (T& Pair)
		{
			int iResult = lstrcmp(m_pTag, Pair.first);

			if(0 == iResult)
				return true;
			return false;
		}
	private:
		const TCHAR*				m_pTag;
	};

	class CStringCmp
	{
	public:
		CStringCmp(const TCHAR* pKey)
			: m_pKey(pKey) {}

	public:
		template <typename T>
		bool operator()(T& dst)
		{
			return !_tcscmp(dst.first, m_pKey);
		}

	private:
		const TCHAR*	m_pKey;
	};
}



#endif // __Engine_Functor_h__