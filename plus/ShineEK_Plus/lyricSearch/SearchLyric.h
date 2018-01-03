#pragma once 
#include <map> 

using namespace std;

class CSearchLyric
{
public:
	CSearchLyric(void);
	~CSearchLyric(void);

public:

	/*
		���ܣ���ʼ����ѯ�ļ������Ҽ����ļ����ڴ���
		������
		   filePath:ִ���ļ�·��(����)
	   ����ֵ��
		  true:��ɹ���
		  false:��ʧ�ܡ�
	*/
	
	bool InitLyric(IN TCHAR * filePath);

	/*
		���ܣ�ģ����ѯ���и����ֵĸ���
		������
			songLyricPart�������Ϣ(����)
			KeyText:����id��ʽ(���)
		����ֵ:
			���ز��ҵ��ж����׸������иø��	
	*/
	int SearchSongCode(IN TCHAR* songLyricPart, OUT TCHAR* KeyText,IN int ArraySize);

	/*
		���ܣ�ͨ��id�ҵ����Ӧ�ĸ��
		������
			songId������ĸ���Id
			lyric:���صĸ��
		����ֵ:
			true:��ѯ��������
			false:û���ҵ��ø��
	*/
	bool SearchLyric(IN TCHAR* songId,OUT TCHAR* lyric);

private:
	map<wstring,wstring>m_lyricMap;				 //�洢���ݵ�map<����id,�������>
};
