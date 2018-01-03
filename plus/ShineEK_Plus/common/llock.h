#ifndef _LLOCK_
#define _LLOCK_

#ifdef _WIN32
#include <windows.h>
#else
#include <pthread.h>
#endif
 
//互斥锁类

namespace shine
{
	class llock
	{
	public:

	 inline llock(void)
	 {
	  m_bInit=true;
	#ifdef _WIN32
	  ::InitializeCriticalSection(&m_lock);
	#else
	  ::pthread_mutex_init(&m_lock,NULL);
	#endif
	 }

	 inline ~llock(void)
	 {
	  if(m_bInit)
	  {
	   m_bInit=false;
	#ifdef _WIN32
	   ::DeleteCriticalSection(&m_lock);
	#else
	   ::pthread_mutex_destroy(&m_lock);
	#endif
	  }
	 }
				   //锁定（进入互斥锁）
	 inline void lock(void)
	 {
	  if(m_bInit)
	  {
	#ifdef _WIN32
	   ::EnterCriticalSection(&m_lock);
	#else
	   ::pthread_mutex_lock(&m_lock);
	#endif
	  }
	 }
					//解锁（离开互斥锁）
	 inline void unlock(void)
	 {
	  if(m_bInit)
	  {
	#ifdef _WIN32
	   ::LeaveCriticalSection(&m_lock);
	#else
	   ::pthread_mutex_unlock(&m_lock);
	#endif
	  }
	 }

	private:
	 bool volatile  m_bInit;
	#ifdef _WIN32
	 CRITICAL_SECTION m_lock;
	#else
	 pthread_mutex_t  m_lock;
	#endif
	};

	//自动锁定类（内联方式使用）

	class lautolock
	{
	public:
	  inline lautolock(llock& lock):m_lock(lock)
	  {
		m_lock.lock();
	  }
	  inline ~lautolock()
	  {
		m_lock.unlock();
	  }
	private:
	  llock& m_lock;
	};
}
#endif
