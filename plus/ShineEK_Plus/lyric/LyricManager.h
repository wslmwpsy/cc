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
	//��ȡ����ļ�nType(0:QQ 1:�ٶ� 2:���� 3:�ṷ)
	bool readLyric(string fileName, int nType);
	//����һ�и�ʲ��洢
	void analysisOneLine(string str);
	//�õ����ͷ
	void getLyricHeader(string str);
	//utf-8תansi����
	int Utf8ToAnsi(const char *pstrUTF8, char *pstrAnsi);
	//�ַ���ʱ���ʽתdouble(��);bTime��TrueΪ��ʼʱ�䣬FlaseΪ����ʱ�䣩
	double changeStringToDouble(bool bTime);
	int UnicodeToAnsi(WCHAR* wstr, char * strAnsi);

	bool LinkDllFuncs();
	void UnLinkDllFuncs();
public:
	double	m_dLasttime;		//������ź�ĳ���ʱ��
	int		m_nLyricIndex;		//�����������
	int		m_nLyriclineNum ;	//���������
	wstring m_Lheader[4];		//���ͷ
	struct OneLineLyric			//�洢һ�и�ʵĽṹ��
	{
		int lineNum;
		string startTime;
		string endTime;
		string lyricContent;
	} lyric[200]; //��̬�������

	void KrcDecodeAnsi(char*& pBufKrc,long iLenKrc,char*& pBufOut,long& iLenOut);
	Dll_KrcDecodeAnsi* krcDecodeAnsi;
	HMODULE hModule;
};

