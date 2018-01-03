#pragma once
#include <iostream>
#include <iosfwd>
#include <string>
#include <time.h>
#include <vector>
#include <wchar.h>
#include <fstream>

#include "..\message.h"
using namespace std;

typedef void Dll_KrcDecodeAnsi(char*& pBufKrc,long iLenKrc,char*& pBufOut,long& iLenOut);

class CLyricManager
{
public:
	CLyricManager(void);
	~CLyricManager(void);

public:
	//读取歌词文件nType(0:QQ 1:百度 2:酷我 3:酷狗)
	bool readLyric(string fileName, int nType);
	//解析一行歌词并存储
	void analysisOneLine(string str);
	//得到歌词头
	void getLyricHeader(string str);
	//utf-8转ansi编码
	int Utf8ToAnsi(const char *pstrUTF8, char *pstrAnsi);
	//字符串时间格式转double(秒);bTime（True为开始时间，Flase为结束时间）
	double changeStringToDouble(bool bTime);
	int UnicodeToAnsi(WCHAR* wstr, char * strAnsi);

	bool LinkDllFuncs();
	void UnLinkDllFuncs();
public:
	double	m_dLasttime;		//点击播放后的持续时间
	int		m_nLyricIndex;		//歌词行数索引
	int		m_nLyriclineNum ;	//歌词总行数
	wstring m_Lheader[4];		//歌词头
	struct OneLineLyric			//存储一行歌词的结构体
	{
		int lineNum;
		string startTime;
		string endTime;
		string lyricContent;
	} lyric[200]; //动态分配最好

	void KrcDecodeAnsi(char*& pBufKrc,long iLenKrc,char*& pBufOut,long& iLenOut);
	Dll_KrcDecodeAnsi* krcDecodeAnsi;
	HMODULE hModule;
};

