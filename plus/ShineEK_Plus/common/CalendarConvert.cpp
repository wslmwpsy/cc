// CalendarConvert.cpp: implementation of the CCalendarConvert class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CalendarConvert.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCalendarConvert::CCalendarConvert()
{

}

CCalendarConvert::~CCalendarConvert()
{

}

//
// �õ���ʾũ��ͨ�ñ�ʾ���ִ�
CString CCalendarConvert::GetLunarString(IN PSYSTEMTIME pSt, bool bEmbolism)
{
	try
	{
		//TCHAR szNongli[30], szNongliDay[10],szShuXiang[10];
		///*�������*/
		//const char *cTianGan[] = {"��","��","��","��","��","��","��","��","��","��"};
		///*��֧����*/
		//const char *cDiZhi[] = {"��","��","��","î","��","��","��",	"δ","��","��","��","��"};
		///*��������*/
		//const char *cShuXiang[] = {"��","ţ","��","��","��","��","��","��","��","��","��","��"};
		///*ũ��������*/
		//const char *cDayName[] = { "*","��һ","����","����","����","����",
		//	"����","����","����","����","��ʮ",
		//	"ʮһ","ʮ��","ʮ��","ʮ��","ʮ��",
		//	"ʮ��","ʮ��","ʮ��","ʮ��","��ʮ",
		//	"إһ","إ��","إ��","إ��","إ��",       
		//	"إ��","إ��","إ��","إ��","��ʮ"};
		///*ũ���·���*/
		//const char *cMonName[] = {"*","��","��","��","��","��","��", "��","��","��","ʮ","ʮһ","��"};

		///*--����ũ����ɡ���֧������ ==> wNongli--*/
		//int nShuXiang = ((pSt->wYear - 4) % 60) % 12;
		//if ( nShuXiang < 0 || nShuXiang >= sizeof(cShuXiang)/sizeof(cShuXiang[0]) )
		//	return "Error Year";
		//wsprintf(szShuXiang,"%s",cShuXiang[nShuXiang]);
		//int nTianGan = ((pSt->wYear - 4) % 60) % 10;
		//if ( nTianGan < 0 || nTianGan >= sizeof(cTianGan)/sizeof(cTianGan[0]) )
		//	return "Error Year";
		//int nDiZhi = ((pSt->wYear - 4) % 60) % 12;
		//if ( nDiZhi < 0 || nDiZhi >= sizeof(cDiZhi)/sizeof(cDiZhi[0]) )
		//	return "Error Year";
		//wsprintf(szNongli,"%s(%s%s)��",szShuXiang,cTianGan[nTianGan],cDiZhi[nDiZhi]);

		///*--����ũ���¡��� ==> wNongliDay--*/
		//if ( pSt->wMonth < 0 || pSt->wMonth >= sizeof(cMonName)/sizeof(cMonName[0]) )
		//	return "Error Month";
		//if ( bEmbolism )
		//{
		//	wsprintf(szNongliDay,"��%s",cMonName[pSt->wMonth]);
		//}
		//else
		//{
		//	strcpy(szNongliDay,cMonName[pSt->wMonth]);
		//}

		//strcat(szNongliDay,"��");
		//if ( pSt->wDay < 0 || pSt->wDay >= sizeof(cDayName)/sizeof(cDayName[0]) )
		//	return "Error Day";
		//strcat(szNongliDay,cDayName[pSt->wDay]);
		//return strcat(szNongli,szNongliDay);
	}
	catch (...)
	{
		
	}
	return L"";
}

//
// ����תũ��
bool CCalendarConvert::Gregorian2Lunar(IN PSYSTEMTIME pSt, OUT PSYSTEMTIME pDst, OUT bool *pEmbolism)
{
	try
	{
		if ( !pSt || !pDst || !pEmbolism ) return false;

		SYSTEMTIME Dst = {0};	
		/*����ÿ��ǰ�������*/
		const int wMonthAdd[12] = {0,31,59,90,120,151,181,212,243,273,304,334};
		/*ũ������*/
		const int wNongliData[100] = {2635,333387,1701,1748,267701,694,2391,133423,1175,396438
			,3402,3749,331177,1453,694,201326,2350,465197,3221,3402
			,400202,2901,1386,267611,605,2349,137515,2709,464533,1738
			,2901,330421,1242,2651,199255,1323,529706,3733,1706,398762
			,2741,1206,267438,2647,1318,204070,3477,461653,1386,2413
			,330077,1197,2637,268877,3365,531109,2900,2922,398042,2395
			,1179,267415,2635,661067,1701,1748,398772,2742,2391,330031
			,1175,1611,200010,3749,527717,1452,2742,332397,2350,3222
			,268949,3402,3493,133973,1386,464219,605,2349,334123,2709
			,2890,267946,2773,592565,1210,2651,395863,1323,2707,265877};
		static int wCurYear,wCurMonth,wCurDay;
		static int nTheDate,nIsEnd,m,k,n,i,nBit;
		/*---ȡ��ǰ�����ꡢ�¡���---*/
		wCurYear = pSt->wYear;
		wCurMonth = pSt->wMonth;
		wCurDay = pSt->wDay;
		/*---���㵽��ʼʱ��1921��2��8�յ�������1921-2-8(���³�һ)---*/
		nTheDate = (wCurYear - 1921) * 365 + (wCurYear - 1921) / 4 + wCurDay + wMonthAdd[wCurMonth - 1] - 38;
		if ( nTheDate < 0 ) return false;
		if((!(wCurYear % 4)) && (wCurMonth > 2))
			nTheDate = nTheDate + 1;

		/*--����ũ����ɡ���֧���¡���---*/
		nIsEnd = 0;
		m = 0;
		while(nIsEnd != 1)
		{
			if(wNongliData[m] < 4095)
				k = 11;
			else
				k = 12;
			n = k;
			while(n>=0)
			{
				//��ȡwNongliData(m)�ĵ�n��������λ��ֵ
				nBit = wNongliData[m];
				for(i=1;i<n+1;i++)
					nBit = nBit/2;

				nBit = nBit % 2;

				if (nTheDate <= (29 + nBit))
				{
					nIsEnd = 1;
					break;
				}

				nTheDate = nTheDate - 29 - nBit;
				n = n - 1;
			}
			if(nIsEnd)
				break;
			m = m + 1;
		}
		wCurYear = 1921 + m;
		wCurMonth = k - n + 1;
		wCurDay = nTheDate;
		if ( wCurDay < 0 ) return false;

		if (k == 12)
		{
			if (wCurMonth == wNongliData[m] / 65536 + 1)
				wCurMonth = 1 - wCurMonth;
			else if (wCurMonth > wNongliData[m] / 65536 + 1)
				wCurMonth = wCurMonth - 1;
		}

		Dst.wYear = (USHORT)wCurYear;
		if (wCurMonth < 1)
		{
			Dst.wMonth = -wCurMonth;
			*pEmbolism = true;
		}
		else
		{
			Dst.wMonth = wCurMonth;
			*pEmbolism = false;
		}
		Dst.wDay = wCurDay;
		memcpy ( pDst, &Dst, sizeof(SYSTEMTIME) );

		return true;
	}
	catch (...)
	{
		
	}
	return false;
}

//
// ũ��ת����
bool CCalendarConvert::Lunar2Gregorian(IN PSYSTEMTIME pSt, IN bool bEmbolism, OUT PSYSTEMTIME pDst)
{
	try
	{

		if ( !pSt || !pDst ) return false;
		COleDateTimeSpan Span(1,0,0,0);
		COleDateTime tStart ( *pSt );
		for ( int i=0; i<100; i++ )
		{
			SYSTEMTIME Src = {0};
			SYSTEMTIME Dst = {0};
			bool bDstEmbolism = false;
			if ( !tStart.GetAsSystemTime ( Src ) )
				return false;

			if ( !Gregorian2Lunar ( &Src, &Dst, &bDstEmbolism ) )
				return false;
			if ( Dst.wYear==pSt->wYear && Dst.wMonth==pSt->wMonth && Dst.wDay==pSt->wDay && bEmbolism==bDstEmbolism )
			{
				memcpy ( pDst, &Src, sizeof(SYSTEMTIME) );
				return true;
			}
			tStart+=Span;
		}

		return false;
	}
	catch (...)
	{
		
	}
	return false;
}