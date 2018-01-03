#ifndef _LOG_H_
#define _LOG_H_

#define WIDEN2(x) L ## x
#define WIDEN(x) WIDEN2(x)
#define __WFILE__ WIDEN(__FILE__)
#define __FL__ __WFILE__,__LINE__ //打印日志

//设置日志文件路径
void SetLogFilePath(const TCHAR* net_file_path);

//获取父目录路径
CString GetParentDir(CString Path);

//目录是否存在
BOOL FolderExists(CString Directory);

//创建目录，可以多层创建；创建成功或者已存在，返回true; 否则返回false
BOOL SuperMkDir(CString Path);

//write log
//@parameter:logtext要输出的日志的内容
void WriteLog(const TCHAR* logtext);

/*
pScrFilePath:源码文件名
nSrcLine:打印日志源码行
pFormat:日志内容
*/
void WriteLog(const TCHAR* pScrFilePath, int nSrcLine, const TCHAR* pFormat, ...);

#endif