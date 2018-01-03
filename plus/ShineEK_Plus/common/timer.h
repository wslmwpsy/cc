#ifndef _CTIME_H_
#define _CTIME_H_

class CTimer
{
private:
	bool	 m_timer_status;  // TRUE or FALSE, indicate the status of timer
	LONGLONG m_counter_frequency;  // counts for a second,cpu Frequency
	LONGLONG m_start_time;	// start time 
	LONGLONG m_sum_time;		// total time
public:
	CTimer();
	bool	clear();	// set the timer to zero
	bool	start();	// the timer begins work
	bool	pause();	// pause the timer, the total time is increased
    double	last_time();  // seconds from last start
	double stop();      //total seconds from first start
};



#endif