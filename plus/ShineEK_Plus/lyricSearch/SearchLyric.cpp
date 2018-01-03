#include "StdAfx.h"
#include "../common/StringCodeConversion.h"
#include "../common/des.h"
#include "SearchLyric.h"  
#include "../parserxml/ParserXml.h"
#include "../star/decrypt_singer_picture.h"
#include <string>

CSearchLyric::CSearchLyric(void)
{
	
}

CSearchLyric::~CSearchLyric(void)
{
}


bool CSearchLyric::InitLyric(IN TCHAR * work_path)
{
	try
	{
		unsigned char szFileHead[FILE_HEAD_LENGTH] = {0x14,0x18,0x53,0x98,0x7f,0x6e,0x8c,0x9c,0x69,0x02,0x0f,0x5d,0xb0,0xcb,0x17,0x4b};
		TCHAR lyric_path[256];          //歌词的路径
		TCHAR lyric_index_path[256];    //歌词索引路径
		FILE *fp_index=NULL;            //歌曲索引文件指针
		FILE *fp_Lyric=NULL;            //歌曲文件指针
		CMarkup parse_xml_doc;
		bool result = false;
		TCHAR *parse_msg=NULL;
		TCHAR *parse_data = NULL;
		unsigned char *pDataBuffer=NULL;
		string_conversion string_conv; 
		std::wstring itemSongId;
		std::wstring itemSongPos;
		std::wstring itemLen;
		std::wstring itemUser;
		int offset_start = 0;   //歌曲的初始位置
		int song_byte_size = 0;  //歌曲的长度
		char lyricData[2048];
		wstring lyricValue;	//歌词值
		int nLength = 0;
		decrypt_picture decrypt_lyric;
		int nCount = 0;	
		TCHAR WideLyric[2048];
		
		memset(lyric_path,0x0,sizeof(lyric_path));   
		memset(lyric_index_path,0x0,sizeof(lyric_index_path));
		
		swprintf(lyric_path,L"%s\\lyricsfile.dll",work_path);
		swprintf(lyric_index_path,L"%s\\lyricsindex.dll",work_path);

		//打开索引文件
		fp_index = _wfopen(lyric_index_path,L"rb");
		if (NULL==fp_index)
		{
			return false;
		}
		//打开歌词文件
		fp_Lyric = _wfopen(lyric_path,L"rb");
		if (NULL==fp_Lyric)
		{
			if (fp_index)
			{
				fclose(fp_index);
				fp_index = NULL;
			}
			return false;
		}
		fseek(fp_index, 0L, SEEK_END);
		nLength = ftell(fp_index);    //得到索引文件的长度
		fseek(fp_index,0,SEEK_SET);	
		//读取文件头
		fread(szFileHead,0x1,FILE_HEAD_LENGTH,fp_index);
		pDataBuffer = new unsigned char[nLength-FILE_HEAD_LENGTH+1];
		if (NULL==pDataBuffer)
		{
			if (fp_index)
			{
				fclose(fp_index);
				fp_index = NULL;
			}
			if (fp_Lyric)
			{
				fclose(fp_Lyric);
				fp_Lyric = NULL;
			}
			return false;
		}
		
		memset(pDataBuffer,0x0,nLength-FILE_HEAD_LENGTH+1);
		if(fread(pDataBuffer,0x1,nLength-FILE_HEAD_LENGTH,fp_index)<=0) //读出所有的字符串保存到pDataBuffer
		{
			if (fp_index)
			{
				fclose(fp_index);
				fp_index = NULL;
			}
			if (fp_Lyric)
			{
				fclose(fp_Lyric);
				fp_Lyric = NULL;
			}
			if (pDataBuffer)
			{
				delete []pDataBuffer;
				pDataBuffer = NULL;
			}
			return false;
		}
		//解密歌词
		decrypt_lyric.decrypt(pDataBuffer,nLength-FILE_HEAD_LENGTH,szFileHead,DECRYPT);
		//得到宽自己大小
		int nLen = string_conv.get_byte_size_of_widechar((const char *)pDataBuffer);  
		parse_msg = new TCHAR [nLen + 1];
		if (NULL==parse_msg)
		{
			if (fp_index)
			{
				fclose(fp_index);
				fp_index = NULL;
			}
			if (fp_Lyric)
			{
				fclose(fp_Lyric);
				fp_Lyric = NULL;
			}
			if (pDataBuffer)
			{
				delete []pDataBuffer;
				pDataBuffer = NULL;
			}
			return false;
		}
		memset(parse_msg,0x0,sizeof(parse_msg));
		string_conv.multibyte_to_widechar((const char *)pDataBuffer,parse_msg,nLength*sizeof(TCHAR));
		
		//<lyric >
		//	<data id="123456" pos="10" len="100" used="1" />
		//	<data id="123456" pos="100" len="100" used="0" />
		//</ lyric > 
		//解析xml
		result = parse_xml_doc.SetDoc(parse_msg);
		if(result)
		{
			parse_xml_doc.ResetPos();   //lyric 
			result = parse_xml_doc.FindChildElem(); 
			if (result)
			{
				while(true)
				{
					result = parse_xml_doc.IntoElem(); //data    
					if (!result)
					{
						break;
					}

					itemSongId = parse_xml_doc.GetAttrib(L"id");


					itemSongPos = parse_xml_doc.GetAttrib(L"pos");
					swscanf(itemSongPos.c_str(),L"%d",&offset_start);

					itemLen = parse_xml_doc.GetAttrib(L"len");
					swscanf(itemLen.c_str(),L"%d",&song_byte_size);

					itemUser = parse_xml_doc.GetAttrib(L"used");

					parse_xml_doc.OutOfElem();

					//解析歌词
					memset(lyricData,0x0,sizeof(lyricData));
					fseek(fp_Lyric,offset_start,SEEK_SET);
					fread(lyricData,0x1,song_byte_size,fp_Lyric);

					memset(WideLyric,0x0,sizeof(WideLyric));
					string_conv.multibyte_to_widechar(lyricData,WideLyric,sizeof(WideLyric)/sizeof(TCHAR));
					lyricValue.assign(WideLyric);
					if (0 == _tcscmp(L"1",itemUser.c_str()))
					{
						m_lyricMap.insert(pair<wstring,wstring>(itemSongId,lyricValue));
					}

					nCount++;
					result = parse_xml_doc.FindChildElem();
					if (!result)
					{
						break;
					}	
				}
			}	
		}

		//释放空间
		if (pDataBuffer)
		{
			delete []pDataBuffer;
			pDataBuffer = NULL;
		}
		if (parse_msg)
		{
			delete[]parse_msg;
			parse_msg = NULL;
		}

		if (fp_index)
		{
			fclose(fp_index);
			fp_index=NULL;
		}
		if (fp_Lyric)
		{
			fclose(fp_Lyric);
			fp_Lyric=NULL;
		}

		return true;
	}
	catch (...)
	{

	}
	return false; 
}

int CSearchLyric::SearchSongCode(IN TCHAR* songLyricPart,OUT TCHAR* KeyText,IN int ArraySize)
{
	int SongCount=0; //多少首歌曲
	map<wstring,wstring>::iterator m_lyricIter;	 //Map迭代器

	//查询有相同的内容的字段
	for ( m_lyricIter = m_lyricMap.begin(); m_lyricIter != m_lyricMap.end(); m_lyricIter++)
	{
		//判断是否相同
		if (_tcsstr(m_lyricIter->second.c_str(),songLyricPart))
		{
			_tcscat(KeyText,m_lyricIter->first.c_str());
			_tcscat(KeyText,_T(","));
			SongCount++;
			if (_tcslen(KeyText)>(ArraySize-32))
			{
				break;
			}
		}
	}
	if (SongCount>0)
	{
		KeyText[_tcslen(KeyText)-1]='\0';
	}

	return SongCount;
}

bool CSearchLyric::SearchLyric(IN TCHAR* songId,OUT TCHAR* lyric)
{
	try
	{
		wstring songValue;

		songValue.assign(songId);
		map<wstring,wstring>::iterator lyricIter;	 //Map迭代器 

		lyricIter=m_lyricMap.find(songValue);
		if(lyricIter == m_lyricMap.end())
		{
			//没有找到
			return false;
		}

		_tcscpy(lyric,lyricIter->second.c_str());

		return true;
	}
	catch (...)
	{
		
	}
	 
	return false;
}