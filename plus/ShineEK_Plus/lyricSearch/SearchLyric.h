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
		功能：初始化查询文件，并且加载文件到内存中
		参数：
		   filePath:执行文件路径(输入)
	   返回值：
		  true:则成功，
		  false:则失败。
	*/
	
	bool InitLyric(IN TCHAR * filePath);

	/*
		功能：模糊查询含有该文字的歌曲
		参数：
			songLyricPart：歌词信息(输入)
			KeyText:歌曲id格式(输出)
		返回值:
			返回查找到有多少首歌曲含有该歌词	
	*/
	int SearchSongCode(IN TCHAR* songLyricPart, OUT TCHAR* KeyText,IN int ArraySize);

	/*
		功能：通过id找到相对应的歌词
		参数：
			songId：传入的歌曲Id
			lyric:返回的歌词
		返回值:
			true:查询到并返回
			false:没有找到该歌词
	*/
	bool SearchLyric(IN TCHAR* songId,OUT TCHAR* lyric);

private:
	map<wstring,wstring>m_lyricMap;				 //存储数据的map<歌曲id,歌曲歌词>
};
