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
	//����·��
	m_strLyricsPath = path;
	m_tagKaraokeObject = NULL;
	m_pParent = NULL;
	m_showThread = NULL;
}

CParseLyricsForKSC::~CParseLyricsForKSC(void)
{
	//���ٶ���
	if (m_tagKaraokeObject)
	{
		delete m_tagKaraokeObject;
		m_tagKaraokeObject = NULL;
	}
}

LPKaraokeKSC CParseLyricsForKSC::Init(const string path /* = "" */)
{
	//�����Ϊ�գ����滻·��
	if (path != "")
	{
		m_strLyricsPath = path;
	}

	//���·��Ϊ�գ��򷵻�
	if (m_strLyricsPath == "")
	{
		return NULL;
	}

	//���ٶ���
	if (m_tagKaraokeObject)
	{
		delete m_tagKaraokeObject;
		m_tagKaraokeObject = NULL;
	}
	//ʵ��������
	m_tagKaraokeObject = new KaraokeKSC();

	FILE *pfile = NULL;
	pfile = fopen(m_strLyricsPath.c_str(), "rb");
	if (pfile)	//���Ƿ�ɹ�
	{
		char szRow[2048] = {0x00};
		string strItem = "";
		//��ȡ�ļ���ÿһ��
		while (true)
		{
			memset(szRow, 0x00, sizeof(szRow));
			if (fgets(szRow, sizeof(szRow), pfile) == NULL) //��ȡ�ɹ�
				break;
			strItem = szRow; //��ֵ

			//ȥ���ַ����еĶ����ַ�
			SetStringReplace(strItem, " ", "");			//ȥ���ո�
			SetStringReplace(strItem, "\r", "");		//ȥ��\r
			SetStringReplace(strItem, "\n", "");		//ȥ��\n
			SetStringReplace(strItem, ";", "");			//ȥ��;

			if (strItem.find(g_KaraokeAdd) == string::npos)
				SetStringReplace(strItem, "'", "");			//ȥ��'

			int iItemLen = strItem.length();
			if (strItem.find(g_Karaoke) != string::npos) //���ڿ�ͷ,������
			{
			}else if (strItem.find(g_KaraokeRow) != string::npos) //��������
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
				SingleLineLyrics sllObj; //���и�ʶ���
				strItem = strItem.substr(g_KaraokeAdd.length(), strItem.length());

				SetStringReplace(strItem, "(", "");			//ȥ��(
				SetStringReplace(strItem, ")", "");			//ȥ��)

				//��ʼʱ��
				string::size_type nPos = strItem.find("','");
				if (nPos != string::npos)
				{
					sllObj.beginTime = time_to_Millisecond(strItem.substr(1, nPos - 1));
					strItem.erase(0, nPos + 3);
				}
				//����ʱ��
				nPos = strItem.find("','");
				if (nPos != string::npos)
				{
					sllObj.endTime = time_to_Millisecond(strItem.substr(0, nPos));
					strItem.erase(0, nPos + 3);
				}
				//����
				nPos = strItem.find("','");
				if (nPos != string::npos)
				{
					sllObj.contents = strItem.substr(0, nPos);
					sllObj.wordsize = sllObj.contents.length();
					int len = sllObj.contents.size();
					strItem.erase(0, nPos + 3);
				}
				//ʱ������
				SetStringReplace(strItem, "'", "");			//ȥ��'
				strItem += ",";
				while (strItem != "")
				{
					nPos = strItem.find(",");
					WordTimeContent wtc;
					wtc.time = atoi(strItem.substr(0, nPos).c_str());
					strItem.erase(0, nPos + 1);
					sllObj.wordTimevec.push_back(wtc);
				}
				
				//Ϊÿ��������ʱ������ - ���ݲ������Ժ�����

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
	//���ٶ���
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
			time = (val * 60 * 1000); //������
		}
		strTime.erase(0, nPos + 1);
	}

	nPos = strTime.find(".");
	if (nPos != string::npos)
	{
		val = atoi(strTime.substr(0, nPos).c_str());
		if (val != 0)
		{
			time += (val * 1000); //����
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
		if (iCurrIndex == Rows) //�����ѵ����һ��
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

	//�˳��߳�
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
			//�������߳���ʾ���
			m_showThread = AfxBeginThread(uShowLyricsThread, lpt);	
		}	
	}else{
		m_run = true;
		//�������߳���ʾ���
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