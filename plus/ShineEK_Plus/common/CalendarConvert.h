// CalendarConvert.h: interface for the CCalendarConvert class.
//
//////////////////////////////////////////////////////////////////////

/*��������������ũ�����������໥ת��������תũ�������Ǵ����ϵ��ģ�������ũ��ת�����Ĵ��벢д��ʾ������
��ʵ����Ҳ�кܶ��йع���תũ���Ŀؼ�������Ϊһ������Ա���ǲ�̫ϰ����ʹ�ñ��˵Ŀؼ�����Ϊ�������������
�Ͳ��
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
	//�õ�ũ���ַ���
	CString GetLunarString(IN PSYSTEMTIME pSt, bool bEmbolism);
	//����תũ��
	bool Gregorian2Lunar(IN PSYSTEMTIME pSt, OUT PSYSTEMTIME pDst, OUT bool *pEmbolism);
	//ũ��ת����
	bool Lunar2Gregorian(IN PSYSTEMTIME pSt, IN bool bEmbolism, OUT PSYSTEMTIME pDst);
};

#endif // !defined(AFX_CALENDARCONVERT_H__98D06A45_DA45_4309_BF79_A4AECDA1B72D__INCLUDED_)
