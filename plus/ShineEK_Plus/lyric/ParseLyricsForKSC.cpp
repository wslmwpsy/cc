#include "stdafx.h"
#include "ParseLyricsForKSC.h"
#include <stdio.h>
#include <xstring>

const string g_Karaoke				= "Karaoke:";
const string g_KaraokeRow			= "Karaoke.rows:=";
const string g_KaraokeClear			= "Karaoke.clear";
const string g_KaraokeSongName		= "Karaoke.songname:=";
const string g_KaraokeSinger		= "Karaoke.singer:=";
const string g_KaraokeAdd			= "Karaoke.Add";

CParseLyricsForKSC::CParseLyricsForKSC(const string path /* = "" */)
{
	//设置路径
	m_strLyricsPath = path;
	m_tagKaraokeObject = NULL;
	m_pParent = NULL;
	m_showThread = NULL;
}

CParseLyricsForKSC::~CParseLyricsForKSC(void)
{
	//销毁对象
	if (m_tagKaraokeObject)
	{
		delete m_tagKaraokeObject;
		m_tagKaraokeObject = NULL;
	}
}

LPKaraokeKSC CParseLyricsForKSC::Init(const string path /* = "" */)
{
	//如果不为空，则替换路径
	if (path != "")
	{
		m_strLyricsPath = path;
	}

	//如果路径为空，则返回
	if (m_strLyricsPath == "")
	{
		return NULL;
	}

	//销毁对象
	if (m_tagKaraokeObject)
	{
		delete m_tagKaraokeObject;
		m_tagKaraokeObject = NULL;
	}
	//实例化对象
	m_tagKaraokeObject = new KaraokeKSC();

	FILE *pfile = NULL;
	pfile = fopen(m_strLyricsPath.c_str(), "rb");
	if (pfile)	//打开是否成功
	{
		char szRow[2048] = {0x00};
		string strItem = "";
		//读取文件的每一行
		while (true)
		{
			memset(szRow, 0x00, sizeof(szRow));
			if (fgets(szRow, sizeof(szRow), pfile) == NULL) //读取成功
				break;
			strItem = szRow; //赋值

			//去除字符串中的多余字符
			SetStringReplace(strItem, " ", "");			//去掉空格
			SetStringReplace(strItem, "\r", "");		//去掉\r
			SetStringReplace(strItem, "\n", "");		//去掉\n
			SetStringReplace(strItem, ";", "");			//去掉;

			if (strItem.find(g_KaraokeAdd) == string::npos)
				SetStringReplace(strItem, "'", "");			//去掉'

			int iItemLen = strItem.length();
			if (strItem.find(g_Karaoke) != string::npos) //等于开头,不处理
			{
			}else if (strItem.find(g_KaraokeRow) != string::npos) //等于行数
			{
				m_tagKaraokeObject->rows = atoi(strItem.substr(g_KaraokeRow.length(), iItemLen - g_KaraokeRow.length()).c_str());
			}else if (strItem.find(g_KaraokeClear) != string::npos)
			{
				m_tagKaraokeObject->clear = true;
			}else if (strItem.find(g_KaraokeSongName) != string::npos)
			{
				m_tagKaraokeObject->songName = strItem.substr(g_KaraokeSongName.length(), iItemLen - g_KaraokeSongName.length());
			}else if (strItem.find(g_KaraokeSinger) != string::npos)
			{
				m_tagKaraokeObject->singerName = strItem.substr(g_KaraokeSinger.length(), iItemLen - g_KaraokeSinger.length());
			}else if (strItem.find(g_KaraokeAdd) != string::npos)
			{
				SingleLineLyrics sllObj; //单行歌词对象
				strItem = strItem.substr(g_KaraokeAdd.length(), strItem.length());

				SetStringReplace(strItem, "(", "");			//去掉(
				SetStringReplace(strItem, ")", "");			//去掉)

				//开始时间
				string::size_type nPos = strItem.find("','");
				if (nPos != string::npos)
				{
					sllObj.beginTime = time_to_Millisecond(strItem.substr(1, nPos - 1));
					strItem.erase(0, nPos + 3);
				}
				//结束时间
				nPos = strItem.find("','");
				if (nPos != string::npos)
				{
					sllObj.endTime = time_to_Millisecond(strItem.substr(0, nPos));
					strItem.erase(0, nPos + 3);
				}
				//内容
				nPos = strItem.find("','");
				if (nPos != string::npos)
				{
					sllObj.contents = strItem.substr(0, nPos);
					sllObj.wordsize = sllObj.contents.length();
					int len = sllObj.contents.size();
					strItem.erase(0, nPos + 3);
				}
				//时间内容
				SetStringReplace(strItem, "'", "");			//去掉'
				strItem += ",";
				while (strItem != "")
				{
					nPos = strItem.find(",");
					WordTimeContent wtc;
					wtc.time = atoi(strItem.substr(0, nPos).c_str());
					strItem.erase(0, nPos + 1);
					sllObj.wordTimevec.push_back(wtc);
				}
				
				//为每个字设置时间内容 - 内容不定，稍后在做

				m_tagKaraokeObject->lpSingleLineLrcvec.push_back(sllObj);
			}
		}
	}
	return m_tagKaraokeObject;
}

void CParseLyricsForKSC::SetStringReplace(string &strBase, string strSrc, string strDes)  
{  
	string::size_type pos = 0;  
	string::size_type srcLen = strSrc.size();  
	string::size_type desLen = strDes.size();  
	pos=strBase.find(strSrc, pos);   
	while ((pos != string::npos))  
	{  
		strBase.replace(pos, srcLen, strDes);  
		pos=strBase.find(strSrc, (pos+desLen));  
	}  
} 

void CParseLyricsForKSC::Destory()
{
	//销毁对象
	if (m_tagKaraokeObject)
	{
		delete m_tagKaraokeObject;
		m_tagKaraokeObject = NULL;
	}	
}

long CParseLyricsForKSC::time_to_Millisecond(string strTime)
{
	long time = 0;
	long val = 0;
	string::size_type nPos = strTime.find(":");
	if (nPos != string::npos)
	{
		val = atoi(strTime.substr(0, nPos).c_str());
		if (val != 0)
		{
			time = (val * 60 * 1000); //分钟秒
		}
		strTime.erase(0, nPos + 1);
	}

	nPos = strTime.find(".");
	if (nPos != string::npos)
	{
		val = atoi(strTime.substr(0, nPos).c_str());
		if (val != 0)
		{
			time += (val * 1000); //秒数
		}
		strTime.erase(0, nPos + 1);
	}
	val = atoi(strTime.c_str());
	time += val;
	return time;
}

void call(LyricsCallback callback, ENUM_LYRICS_MODE mode, string content, bool location, CWnd* pWnd)
{
	PLAYLYRICSSTATE state;
	state.elm = mode;
	state.content = content;
	state.location = location;
	state.pWnd = pWnd;
	callback(state);
}
UINT CParseLyricsForKSC::uShowLyricsThread(LPVOID pParam)
{
	LPLYRICSPARAMTHREAD lpParamThread = (LPLYRICSPARAMTHREAD)pParam;
	CParseLyricsForKSC *pObj = (CParseLyricsForKSC*)lpParamThread->pObj;
	LyricsCallback callback = lpParamThread->callback;

	delete lpParamThread;
	lpParamThread = NULL;

	int iCurrIndex = 0;
	ENUM_PLAY_STATE enPlayState = PLAY_FIRST;
	bool tb = true;
	long lfrontTime = 0;
	SingleLineLyrics singleOneLineObj;
	SingleLineLyrics singleTwoLineObj;
	int Rows = pObj->m_tagKaraokeObject->lpSingleLineLrcvec.size();
	while(pObj->m_run)
	{
		if (iCurrIndex == Rows) //代表已到最后一行
		{
			Sleep(5*1000);
			call(callback, LYRICS_MODE_HIDE, "", tb, pObj->m_pParent);
			call(callback, LYRICS_MODE_HIDE, "", !tb, pObj->m_pParent);
			break;
		}

		switch(enPlayState)
		{
		case PLAY_FIRST: 
			{
				singleOneLineObj = pObj->m_tagKaraokeObject->lpSingleLineLrcvec.at(iCurrIndex);
				singleTwoLineObj = pObj->m_tagKaraokeObject->lpSingleLineLrcvec.at(++iCurrIndex);

				Sleep(singleOneLineObj.beginTime - 3*1000);			
				call(callback, LYRICS_MODE_SHOW, singleOneLineObj.contents, tb, pObj->m_pParent);
				enPlayState = PLAY_TOP;
				Sleep(3*1000);	
				call(callback, LYRICS_MODE_BEGIN, singleOneLineObj.contents, tb, pObj->m_pParent);
			}
			break;
		case PLAY_TOP:
		case PLAY_BOTTOM:
			{
				switch(tb)
				{
				case true:
					singleTwoLineObj = pObj->m_tagKaraokeObject->lpSingleLineLrcvec.at(iCurrIndex);
					break;
				case false:
					singleOneLineObj = pObj->m_tagKaraokeObject->lpSingleLineLrcvec.at(iCurrIndex);
					break;
				}
			}
			break;
		}
		switch(tb)
		{
		case true:
			Sleep((singleOneLineObj.endTime - singleOneLineObj.beginTime)/2);
			break;
		case false:
			Sleep((singleTwoLineObj.endTime - singleTwoLineObj.beginTime)/2);
			break;
		}		
		call(callback, LYRICS_MODE_SHOW, tb ? singleTwoLineObj.contents:singleOneLineObj.contents, !tb, pObj->m_pParent);

		switch(tb)
		{
		case true:
			Sleep((singleOneLineObj.endTime - singleOneLineObj.beginTime)/2);
			break;
		case false:
			Sleep((singleTwoLineObj.endTime - singleTwoLineObj.beginTime)/2);
			break;
		}		
		call(callback, LYRICS_MODE_HIDE, "", tb, pObj->m_pParent);

		long fix = 0;
		switch(tb)
		{
		case true:
			fix = singleTwoLineObj.beginTime - singleOneLineObj.endTime;
			break;
		case false:
			fix = singleOneLineObj.beginTime - singleTwoLineObj.endTime;
			break;
		}
		
		Sleep(fix);
		call(callback, LYRICS_MODE_BEGIN, tb ? singleTwoLineObj.contents:singleOneLineObj.contents, !tb, pObj->m_pParent);
		enPlayState = PLAY_BOTTOM;
		tb = !tb;
		iCurrIndex++;
	}

	//退出线程
	/*DWORD dwExitCode;
	GetExitCodeThread(pObj->m_showThread->m_hThread, &dwExitCode);
	AfxEndThread(dwExitCode);*/
	pObj->m_showThread = NULL;
	return 0;
}
long CParseLyricsForKSC::Play(LyricsCallback callback)
{
	LPLYRICSPARAMTHREAD lpt = new LYRICSPARAMTHREAD();
	lpt->pObj = this;
	lpt->callback = callback;
	
	if(m_showThread != NULL)
	{
		DWORD dwWait = WaitForSingleObject(m_showThread->m_hThread, INFINITE);
		if (dwWait == WAIT_OBJECT_0)
		{
			m_run = true;
			//启动个线程显示歌词
			m_showThread = AfxBeginThread(uShowLyricsThread, lpt);	
		}	
	}else{
		m_run = true;
		//启动个线程显示歌词
		m_showThread = AfxBeginThread(uShowLyricsThread, lpt);	
	}
	return 0;
}

void CParseLyricsForKSC::SetWnd(CWnd* pParent)
{
	m_pParent = pParent;
}

void CParseLyricsForKSC::vTerminateThread()
{
	m_run = false;
	Sleep(500);
}