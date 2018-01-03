#include "StdAfx.h"
#include "../common/StringCodeConversion.h"
#include "../file/log.h"
#include "LyricManager.h"
#include <WinDef.h>
#include <Windows.h>
const int MAX_LYRIC_LINE_NUM =200;
const int MAX_LYRCE_REPEAT_NUM = 10;
string header[] = {"ai:", "ar:", "al:", "by:"};

CLyricManager::CLyricManager(void)
{
	m_nLyriclineNum = 0;
	m_nLyricIndex = 0;
}

CLyricManager::~CLyricManager(void)
{
}

bool CLyricManager::readLyric(string fileName, int nType)
{
#ifdef _UNICODE
	char* old_locale = _strdup( setlocale(LC_CTYPE,NULL) ); 
	setlocale( LC_CTYPE, "chs" );
#endif
	memset(lyric, 0x00, sizeof(lyric));
	memset(m_Lheader, 0x00, sizeof(m_Lheader));
	m_nLyriclineNum = 0;
	m_nLyricIndex = 0;
	m_dLasttime = 0;
	ifstream fin;

	fin.open(fileName);
	if(!fin.is_open())
	{
		return false;
	}
	string str;
	getline(fin, str);
	char sztmp[1024] = {0};

	if(nType == 0 || nType == 1)
	{
		Utf8ToAnsi(str.c_str(), sztmp);
		str = sztmp;
	}
	else if (nType == 3)
	{
// 		string_conversion str_conv;
// 		TCHAR szData[1024] = {0x00};
// 		str_conv.multibyte_to_widechar(str.c_str(), szData, 256);
// 		UnicodeToAnsi(szData, sztmp);
// 		str = sztmp;
	}
	while(fin)
	{
		if (m_nLyriclineNum>=200)
		{
			break;
		}
		if(str != "")
		{
			analysisOneLine(str);
		}
		getline(fin, str);

		if(nType == 0 || nType == 1)
		{
			Utf8ToAnsi(str.c_str(), sztmp);
			str = sztmp;
		}
		else if (nType == 3)
		{
// 			string_conversion str_conv;
// 			TCHAR szData[1024] = {0x00};
// 			str_conv.multibyte_to_widechar(str.c_str(), szData, 256);
// 			UnicodeToAnsi(szData, sztmp);
// 			str = sztmp;
		}
	}

	fin.close();
#ifdef _UNICODE
	setlocale( LC_CTYPE, old_locale ); 
	free( old_locale ); 
#endif

	return true;
}

//分析一行 保存到结构体数组
void CLyricManager::analysisOneLine(string str)
{
	if(str[0] != '[')
	{
		WriteLog(__FL__, L"歌词文件格式不正规!\n");
		return;
	}

	//歌词说明 ti:歌曲名称 ar:演唱者 al: by: 制作单位
	getLyricHeader(str);

	int m, n, p = 0;
	string timeTemp[MAX_LYRCE_REPEAT_NUM];//保存信息
	m = str.find_first_of('[');
	n = str.find_first_of(']');
	while(m >= 0 && m <= str.length() && n >= 0 && n <= str.length() && str != "")
	{
		timeTemp[p] = str.substr(m + 1, n - 1);
		p++;
		str = str.substr(n + 1, str.length());
		m = str.find_first_of('[');
		n = str.find_first_of(']');
	}

	string contentTemp = str;

	for(int i = 0; i < p; i++)
	{
		if(m_nLyriclineNum == 1)
		{
			//continue;
		}
		lyric[m_nLyriclineNum].startTime = timeTemp[i];//开始时间

		if(timeTemp[i + 1] != "") //连续的
		{
			lyric[m_nLyriclineNum].endTime = timeTemp[i + 1];
		}

		if(m_nLyriclineNum - 1 >= 0 && i == 0) //设置上一个的endTime
			lyric[m_nLyriclineNum - 1].endTime = lyric[m_nLyriclineNum].startTime;//结束时间(下句开始时间)
		lyric[m_nLyriclineNum].lineNum = m_nLyriclineNum;//行号
		lyric[m_nLyriclineNum].lyricContent = contentTemp;//歌词内容
		m_nLyriclineNum++;
	}
}

void CLyricManager::getLyricHeader(string str)
{
	for(int i = 0; i < 4; i++)
	{
		if(header[i] == str.substr(1, 3))
		{
			TCHAR wide_string[256];
			memset(wide_string,0x0,sizeof(wide_string));
			string_conversion string_conv;
			string_conv.multibyte_to_widechar(str.c_str(),wide_string,sizeof(wide_string)/sizeof(TCHAR));

			m_Lheader[i] = wide_string;
		}
	}
}

int CLyricManager::Utf8ToAnsi(const char *pstrUTF8, char *pstrAnsi)
{
	if (strlen(pstrUTF8)>1024)	return 0;

	int i = 0;
	int j = 0;
	WCHAR strUnicode[1024] = {0};

	i = MultiByteToWideChar(CP_UTF8, 0, pstrUTF8, -1, NULL, 0);
	memset(strUnicode, 0, i);
	MultiByteToWideChar(CP_UTF8, 0, pstrUTF8, -1, strUnicode, i);
	j = WideCharToMultiByte(CP_ACP, 0, strUnicode, -1, NULL, 0, NULL, NULL);
	WideCharToMultiByte(CP_ACP, 0, strUnicode, -1, pstrAnsi, j, NULL, NULL);
	return 0;
}

//将时间转换成秒   
double CLyricManager::changeStringToDouble(bool bTime)  
{  
	string str_time;
	if (bTime)
		str_time = lyric[m_nLyricIndex].startTime;
	else
		str_time = lyric[m_nLyricIndex].endTime;
	string::size_type npos ,npos1 = string::npos;
	 npos=str_time.find(':');
	 npos1=str_time.find('.');
	int min=0, sec=0, msc = 0,nlen=0; //分钟,秒,毫秒 转换成毫秒   
	double time;
	nlen = str_time.length();
	if (nlen <=7 ||npos!=2 || npos1!=5)
	{
		return 0;
	}
	//12:34.56
	min = atof(const_cast<const char *>(str_time.substr(0, 2).c_str()));  
	sec = atof(const_cast<const char *>(str_time.substr(3, 2).c_str()));  
	if(str_time.length() > 5)  
		msc = atof(const_cast<const char *>(str_time.substr(6, 2).c_str()));  
	time = min * 60 + sec + msc*0.01;

	return time;  
} 

//////////////////////////////////////////////////////////////////////////
//    Unicode 转 Ansi 字符串函数
//    入口参数：TCHAR*        (Unicode字符串指针)
//    返回数据：char*         (Ansi字符串指针)
/////////////////////////////////////////////////////////////////////////////////
int CLyricManager::UnicodeToAnsi(WCHAR* wstr, char * strAnsi)
{
	if( !wstr )
		return NULL;
	int nlen = wcslen(wstr);
	int strleng = ::WideCharToMultiByte(CP_ACP, NULL, wstr, nlen, NULL, 0, NULL, NULL);
	//char* str = new char[strleng + 1];
	::WideCharToMultiByte(CP_ACP, NULL, wstr, nlen, strAnsi, strleng, NULL, NULL);
	strAnsi[strleng] = '\0';

	return strleng;
}


bool CLyricManager::LinkDllFuncs()
{
	hModule = LoadLibrary((CString)"KrcDecode.dll");

	if(!hModule) return false;

	//删除图像
	krcDecodeAnsi = (Dll_KrcDecodeAnsi *)GetProcAddress(hModule, "krcDecodeAnsi");
	if(!krcDecodeAnsi) return false;

	return true;
}

void CLyricManager::UnLinkDllFuncs()
{
	if(hModule)  FreeLibrary(hModule);
	hModule=NULL;	
}

void CLyricManager::KrcDecodeAnsi(char*& pBufKrc,long iLenKrc,char*& pBufOut,long& iLenOut)
{
	if ( NULL == krcDecodeAnsi )
		return;

	krcDecodeAnsi(pBufKrc, iLenKrc, pBufOut, iLenOut);
}