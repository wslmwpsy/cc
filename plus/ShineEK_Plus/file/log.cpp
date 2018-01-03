#include "stdafx.h"
#include "log.h"

#include "file.h"

#include<shlwapi.h>
#include <string>
#include <time.h>
#include "../common/StringCodeConversion.h"
using namespace std;

//ȫ�ֱ���
TCHAR g_net_log_path[256];     //����·��
TCHAR g_local_log_path[256];  //����·��

void SetLogFilePath(const TCHAR* net_file_path)
{
	try
	{
		TCHAR szFilePath[256];
		CTime ctCurTime;
		CString strLogFileName;

		memset(g_net_log_path,0x0,sizeof(g_net_log_path));
		memset(g_local_log_path,0x0,sizeof(g_local_log_path));

		//get system time
		ctCurTime = CTime::GetCurrentTime();
		strLogFileName = ctCurTime.Format(L"%Y-%m-%d");

		//�õ�����·��
		if((NULL==net_file_path)||(0==_tcscmp(net_file_path,L"")))
		{
			memset(g_net_log_path,0x0,sizeof(g_net_log_path));
		}
		else
		{
			if (!PathFileExists(net_file_path))
			{
				SuperMkDir(net_file_path);
			}
			swprintf(g_net_log_path, L"%s\\ktv10_%s.log",net_file_path,strLogFileName.GetBuffer(0));
		}

		//�����ļ�·��
		//work dir
		GetModuleFileName(NULL,szFilePath,sizeof(szFilePath));
		(wcsrchr(szFilePath,'\\'))[1] ='\0'; 
		//write log to log directory
		wcscat(szFilePath,L"log\\");
		if (!PathFileExists(szFilePath))
		{
			SuperMkDir(szFilePath);
		}
		//log file path
		swprintf(g_local_log_path,L"%sktv10_%s.log",szFilePath,strLogFileName.GetBuffer(0));
	}
	catch (...)
	{

	}
	return;
}

//��ȡ��Ŀ¼·��
CString  GetParentDir(CString Path)
{
	if (!Path.IsEmpty())
	{
		Path.Replace('/','\\');
		return Path.Left(Path.ReverseFind('\\'));
	}
	return NULL;
} 

//Ŀ¼�Ƿ����
BOOL FolderExists(CString Directory)
{
	DWORD dwFolderAttr;   
	dwFolderAttr = GetFileAttributes(Directory);  
	return (dwFolderAttr != (DWORD)(-1)) && (dwFolderAttr & FILE_ATTRIBUTE_DIRECTORY);   
}

//����Ŀ¼�����Զ�㴴���������ɹ������Ѵ��ڣ�����true; ���򷵻�false
BOOL SuperMkDir(CString Path)
{
	if (Path.IsEmpty())
	{
		return false;
	}
	int len=Path.GetLength();
	if ( len <2 )
	{
		//����ַ�������С��2��������Ч��·����ʽ��
		return false;  
	}

	Path.Replace('/','\\');
	if('\\'==Path[len-1])
	{
		Path = Path.Left(len-1);
		len=Path.GetLength();
	}// ɾ��ĩβ��"\"
	if (  len <=0 ) 
	{
		return false;
	}
	if (len <=3) //�������<=3����ô�ض��Ǹ�Ŀ¼��ʽ
	{
		if (FolderExists(Path))return true;//�����Ŀ¼����,����true;
		else return false;              //��������ڣ���Ŀ¼���޷������ģ�����ʧ�ܣ�
	}

	if (FolderExists(Path))return true;//���Ŀ¼����,����true;

	// �ֿ���Ŀ¼�ͱ���Ŀ¼����
	CString Parent;
	Parent=GetParentDir(Path);

	if(Parent.GetLength()<=0)return false; //Ŀ¼���ƴ���

	BOOL Ret=SuperMkDir(Parent);  //�ݹ鴴����Ŀ¼

	if(Ret)      // ��Ŀ¼����,ֱ�Ӵ���Ŀ¼
	{
		SECURITY_ATTRIBUTES sa;
		sa.nLength=sizeof(SECURITY_ATTRIBUTES);
		sa.lpSecurityDescriptor=NULL;
		sa.bInheritHandle=0;
		Ret=(CreateDirectory(Path,&sa)==TRUE);
		return Ret;
	}
	else
		return false;
}

void WriteLog(const TCHAR* logtext)
{
	//TCHAR szLog[10240];
	TCHAR szLog[1024*50];
	CTime ctCurTime;
	file log_file;
	std::wstring strLogTime;
	DWORD buffer_size=0;
	DWORD write_buffer_size=0;
	bool result = false;

	try
	{
		memset(szLog,0x0,sizeof(szLog));

		//get system time
		ctCurTime = CTime::GetCurrentTime();
		strLogTime = ctCurTime.Format(L"%Y-%m-%d %H:%M:%S");
		//log text
		swprintf(szLog,L"    %s\r\n",logtext);

		//���������־
		result = log_file.file_exist(g_local_log_path);
		if (result)
		{
			//����
			result = log_file.open_file(g_local_log_path,FILE_APPEND);
		}
		else
		{
			//������
			result = log_file.open_file(g_local_log_path,FILE_WRITE);
			//д��unicode���ַ�
			DWORD unicode_flag = 0xFEFF;
			log_file.write_file(&unicode_flag,2,&write_buffer_size);
			//ָ���Ƶ������
			log_file.seek_file(0,FILE_END);
		}
		if(result)
		{
			buffer_size = (DWORD)(2*wcslen(strLogTime.c_str()));
			log_file.write_file((LPVOID)strLogTime.c_str(),buffer_size,&write_buffer_size);
			buffer_size = (DWORD)(2*wcslen(szLog));
			log_file.write_file(szLog,buffer_size,&write_buffer_size);
			log_file.close_file();
		}

		//д������־
		/////mzy
		if (0!=_tcscmp(g_net_log_path,L""))
		{
			result = log_file.file_exist(g_net_log_path);
			if (result)
			{
				result = log_file.open_file(g_net_log_path, FILE_APPEND);
			}
			else
			{
				result = log_file.open_file(g_net_log_path, FILE_WRITE);
				if (result)
				{
					DWORD unicode_flag = 0xFEFF;
					log_file.write_file(&unicode_flag,2,&write_buffer_size);
					//ָ���Ƶ������
					log_file.seek_file(0,FILE_END);
				}
				else
				{
					//���ܲ��������Ŀ¼��������ݣ��Ժ���д���
					memset(g_net_log_path, 0, sizeof(g_net_log_path));
				}
			}
			if (result)
			{
				buffer_size = (DWORD)(2*wcslen(strLogTime.c_str()));
				log_file.write_file((LPVOID)strLogTime.c_str(),buffer_size,&write_buffer_size);
				buffer_size = (DWORD)(2*wcslen(szLog));
				log_file.write_file(szLog,buffer_size,&write_buffer_size);
				log_file.close_file();
			}
		}
		////end mzy
	}
	catch(...)
	{

	}
	return;
}

void WriteLog(const TCHAR* pScrFilePath, int nSrcLine, const TCHAR* pFormat, ...)
{
	va_list		args;
	FILE		*log_fp;
	struct tm *	logCurTime;
	time_t 		logTimeFlag;
	wstring strSrcFilePath = pScrFilePath;

	//Դ���ļ���
	int nPos = strSrcFilePath.rfind('\\');
	wstring strSrcFileName(strSrcFilePath.begin()+nPos+1, strSrcFilePath.end());

// 	//��־�ļ�����·��
// 	wstring strLogFileDir = g_local_log_path;
// 	if (!PathFileExists(strLogFileDir.c_str()))
// 	{
// 		_wmkdir(strLogFileDir.c_str());
// 	}

	//��ؼ��Ϸ������ɵ��ı����ʺ��ַ���
	_wsetlocale(0, L"chs");
	//��ȡϵͳʱ����Ϊ��¼ʱ��
	logTimeFlag = time(NULL);
	logCurTime = localtime(&logTimeFlag);
	//����ļ���С
	struct _stat info = {0x00};
	_wstat(g_local_log_path, &info);
	DWORD dwSize = 0;
	dwSize = info.st_size;
	if(dwSize > 1024*1024*50)//50M
	{
		//����50M��ɾ����־�ļ�
		_wremove(g_local_log_path);			
	}

	log_fp = _wfopen(g_local_log_path, L"a+");
	if(log_fp == NULL) return;						//�򿪻򴴽���־�ļ�ʧ��
	//��ʽ����־����
	TCHAR buffer[1024*50] = {0x00};
	va_start(args, pFormat);
	_vsntprintf(buffer, sizeof(buffer)/sizeof(TCHAR), pFormat, args);
	va_end(args);
	//��־ʱ�䣬Դ���ļ�������
	fwprintf(log_fp, L"[%04d/%02d/%02d %02d:%02d:%02d][%18s, %5d��]	", 
		logCurTime->tm_year + 1900, logCurTime->tm_mon+1, logCurTime->tm_mday,
		logCurTime->tm_hour, logCurTime->tm_min, logCurTime->tm_sec, strSrcFileName.c_str(), nSrcLine);
	//��־����
	fwprintf(log_fp, L"%s\r\n", buffer);
	fflush(log_fp);
	fclose(log_fp);

	//д������־
	if (0 != _tcscmp(g_net_log_path, L""))
	{
		log_fp = _wfopen(g_net_log_path, L"a+");
		if(log_fp == NULL) return;//�򿪻򴴽���־�ļ�ʧ��
		//��ʽ����־����
		TCHAR buffer[1024*50] = {0x00};
		va_start(args, pFormat);
		_vsntprintf(buffer, sizeof(buffer)/sizeof(TCHAR), pFormat, args);
		va_end(args);
		//��־ʱ�䣬Դ���ļ�������
		fwprintf(log_fp, L"[%04d/%02d/%02d %02d:%02d:%02d][%18s, %5d��]	", 
			logCurTime->tm_year + 1900, logCurTime->tm_mon+1, logCurTime->tm_mday,
			logCurTime->tm_hour, logCurTime->tm_min, logCurTime->tm_sec, strSrcFileName.c_str(), nSrcLine);
		//��־����
		fwprintf(log_fp, L"%s\r\n", buffer);
		fflush(log_fp);
		fclose(log_fp);
	}
}