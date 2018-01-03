#ifndef _LOG_H_
#define _LOG_H_

#define WIDEN2(x) L ## x
#define WIDEN(x) WIDEN2(x)
#define __WFILE__ WIDEN(__FILE__)
#define __FL__ __WFILE__,__LINE__ //��ӡ��־

//������־�ļ�·��
void SetLogFilePath(const TCHAR* net_file_path);

//��ȡ��Ŀ¼·��
CString GetParentDir(CString Path);

//Ŀ¼�Ƿ����
BOOL FolderExists(CString Directory);

//����Ŀ¼�����Զ�㴴���������ɹ������Ѵ��ڣ�����true; ���򷵻�false
BOOL SuperMkDir(CString Path);

//write log
//@parameter:logtextҪ�������־������
void WriteLog(const TCHAR* logtext);

/*
pScrFilePath:Դ���ļ���
nSrcLine:��ӡ��־Դ����
pFormat:��־����
*/
void WriteLog(const TCHAR* pScrFilePath, int nSrcLine, const TCHAR* pFormat, ...);

#endif