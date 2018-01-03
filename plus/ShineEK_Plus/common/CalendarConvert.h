// CalendarConvert.h: interface for the CCalendarConvert class.
//
//////////////////////////////////////////////////////////////////////

/*公历（阳历）和农历（阴历）相互转换，公历转农历代码是从网上当的，我做了农历转公历的代码并写了示例程序。
其实网上也有很多有关公历转农历的控件，但作为一个程序员就是不太习惯于使用别人的控件，因为那样将不便调试
和差错。
*/

#if !defined(AFX_CALENDARCONVERT_H__98D06A45_DA45_4309_BF79_A4AECDA1B72D__INCLUDED_)
#define AFX_CALENDARCONVERT_H__98D06A45_DA45_4309_BF79_A4AECDA1B72D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CCalendarConvert  
{
public:
	CCalendarConvert();
	virtual ~CCalendarConvert();
	//得到农历字符串
	CString GetLunarString(IN PSYSTEMTIME pSt, bool bEmbolism);
	//公历转农历
	bool Gregorian2Lunar(IN PSYSTEMTIME pSt, OUT PSYSTEMTIME pDst, OUT bool *pEmbolism);
	//农历转公历
	bool Lunar2Gregorian(IN PSYSTEMTIME pSt, IN bool bEmbolism, OUT PSYSTEMTIME pDst);
};

#endif // !defined(AFX_CALENDARCONVERT_H__98D06A45_DA45_4309_BF79_A4AECDA1B72D__INCLUDED_)
