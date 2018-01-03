#include "stdafx.h"
#include "timer.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CTimer::CTimer()
{
	//��ʼ��ʱ���Բ�������һ�³�ʼ��
	clear();
}

bool CTimer::clear()
{
	LARGE_INTEGER tmp;
	BOOL result=FALSE;

	//��ʼ��
	m_timer_status = false;
	m_sum_time = 0;
	m_start_time=0;
	//����Ӳ��֧�ֵĸ߾��ȼ�������Ƶ��
	result = QueryPerformanceFrequency(&tmp);
	if (result)
	{
		//�õ�cpuƵ��
		m_counter_frequency = tmp.QuadPart;
		return true;
	}
	return false;
}

bool CTimer::start()
{
	LARGE_INTEGER tmp;
	BOOL result=FALSE;

	//�õ��߾��ȼ�ʱ����ֵ
	result = QueryPerformanceCounter(&tmp);
	if (result)
	{
		m_start_time = tmp.QuadPart;
		m_timer_status = true;

		return true;
	}
	return false;	
}

bool CTimer::pause()
{
	LARGE_INTEGER tmp;
	BOOL result=FALSE;

	//�õ��߾��ȼ�ʱ����ֵ
	result = QueryPerformanceCounter(&tmp);
	if (result)
	{
		m_sum_time += tmp.QuadPart - m_start_time;
		m_timer_status = false;
		return true;
	}
	return false;
}

double CTimer::last_time()
{
	double seconds=0.0;
	BOOL result=FALSE;
	LONGLONG sum_time=0;

	if (m_timer_status)
	{
		LARGE_INTEGER tmp;

		//�õ��߾��ȼ�ʱ����ֵ
		result=QueryPerformanceCounter(&tmp);
		if (result)
		{
			sum_time = tmp.QuadPart - m_start_time;
			seconds = (double)sum_time/m_counter_frequency;
			return seconds;
		}
	}
	return 0.0;
}

double CTimer::stop()
{
	double seconds=0.0;
	BOOL result=FALSE;
	
	if (m_timer_status)
	{
		LARGE_INTEGER tmp;

		//�õ��߾��ȼ�ʱ����ֵ
		result=QueryPerformanceCounter(&tmp);
		if (result)
		{
			m_sum_time += tmp.QuadPart - m_start_time;
			seconds = (double)m_sum_time/m_counter_frequency;
			return seconds;
		}
	}
	return 0.0;
}
