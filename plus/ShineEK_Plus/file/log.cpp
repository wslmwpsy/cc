#include "stdafx.h"
#include "log.h"

#include "file.h"

#include<shlwapi.h>
#include <string>
#include <time.h>
#include "../common/StringCodeConversion.h"
using namespace std;

//全局变量
TCHAR g_net_log_path[256];     //网络路径
TCHAR g_local_log_path[256];  //本地路径

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

		//得到网络路径
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

		//本地文件路径
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

//获取父目录路径
CString  GetParentDir(CString Path)
{
	if (!Path.IsEmpty())
	{
		Path.Replace('/','\\');
		return Path.Left(Path.ReverseFind('\\'));
	}
	return NULL;
} 

//目录是否存在
BOOL FolderExists(CString Directory)
{
	DWORD dwFolderAttr;   
	dwFolderAttr = GetFileAttributes(Directory);  
	return (dwFolderAttr != (DWORD)(-1)) && (dwFolderAttr & FILE_ATTRIBUTE_DIRECTORY);   
}

//创建目录，可以多层创建；创建成功或者已存在，返回true; 否则返回false
BOOL SuperMkDir(CString Path)
{
	if (Path.IsEmpty())
	{
		return false;
	}
	int len=Path.GetLength();
	if ( len <2 )
	{
		//如果字符串长度小于2，则不是有效的路径格式。
		return false;  
	}

	Path.Replace('/','\\');
	if('\\'==Path[len-1])
	{
		Path = Path.Left(len-1);
		len=Path.GetLength();
	}// 删除末尾的"\"
	if (  len <=0 ) 
	{
		return false;
	}
	if (len <=3) //如果长度<=3，那么必定是根目录格式
	{
		if (FolderExists(Path))return true;//如果根目录存在,返回true;
		else return false;              //如果不存在，根目录是无法创建的，返回失败；
	}

	if (FolderExists(Path))return true;//如果目录存在,返回true;

	// 分开父目录和本身目录名称
	CString Parent;
	Parent=GetParentDir(Path);

	if(Parent.GetLength()<=0)return false; //目录名称错误

	BOOL Ret=SuperMkDir(Parent);  //递归创建父目录

	if(Ret)      // 父目录存在,直接创建目录
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

		//输出本地日志
		result = log_file.file_exist(g_local_log_path);
		if (result)
		{
			//存在
			result = log_file.open_file(g_local_log_path,FILE_APPEND);
		}
		else
		{
			//不存在
			result = log_file.open_file(g_local_log_path,FILE_WRITE);
			//写入unicode的字符
			DWORD unicode_flag = 0xFEFF;
			log_file.write_file(&unicode_flag,2,&write_buffer_size);
			//指针移到到最后
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

		//写网络日志
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
					//指针移到到最后
					log_file.seek_file(0,FILE_END);
				}
				else
				{
					//可能不存在这个目录，清空内容，以后不再写这个
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

	//源码文件名
	int nPos = strSrcFilePath.rfind('\\');
	wstring strSrcFileName(strSrcFilePath.begin()+nPos+1, strSrcFilePath.end());

// 	//日志文件保存路径
// 	wstring strLogFileDir = g_local_log_path;
// 	if (!PathFileExists(strLogFileDir.c_str()))
// 	{
// 		_wmkdir(strLogFileDir.c_str());
// 	}

	//务必加上否则生成的文本是问号字符串
	_wsetlocale(0, L"chs");
	//获取系统时间作为记录时间
	logTimeFlag = time(NULL);
	logCurTime = localtime(&logTimeFlag);
	//检测文件大小
	struct _stat info = {0x00};
	_wstat(g_local_log_path, &info);
	DWORD dwSize = 0;
	dwSize = info.st_size;
	if(dwSize > 1024*1024*50)//50M
	{
		//大于50M，删除日志文件
		_wremove(g_local_log_path);			
	}

	log_fp = _wfopen(g_local_log_path, L"a+");
	if(log_fp == NULL) return;						//打开或创建日志文件失败
	//格式化日志数据
	TCHAR buffer[1024*50] = {0x00};
	va_start(args, pFormat);
	_vsntprintf(buffer, sizeof(buffer)/sizeof(TCHAR), pFormat, args);
	va_end(args);
	//日志时间，源码文件，行数
	fwprintf(log_fp, L"[%04d/%02d/%02d %02d:%02d:%02d][%18s, %5d行]	", 
		logCurTime->tm_year + 1900, logCurTime->tm_mon+1, logCurTime->tm_mday,
		logCurTime->tm_hour, logCurTime->tm_min, logCurTime->tm_sec, strSrcFileName.c_str(), nSrcLine);
	//日志内容
	fwprintf(log_fp, L"%s\r\n", buffer);
	fflush(log_fp);
	fclose(log_fp);

	//写网络日志
	if (0 != _tcscmp(g_net_log_path, L""))
	{
		log_fp = _wfopen(g_net_log_path, L"a+");
		if(log_fp == NULL) return;//打开或创建日志文件失败
		//格式化日志数据
		TCHAR buffer[1024*50] = {0x00};
		va_start(args, pFormat);
		_vsntprintf(buffer, sizeof(buffer)/sizeof(TCHAR), pFormat, args);
		va_end(args);
		//日志时间，源码文件，行数
		fwprintf(log_fp, L"[%04d/%02d/%02d %02d:%02d:%02d][%18s, %5d行]	", 
			logCurTime->tm_year + 1900, logCurTime->tm_mon+1, logCurTime->tm_mday,
			logCurTime->tm_hour, logCurTime->tm_min, logCurTime->tm_sec, strSrcFileName.c_str(), nSrcLine);
		//日志内容
		fwprintf(log_fp, L"%s\r\n", buffer);
		fflush(log_fp);
		fclose(log_fp);
	}
}