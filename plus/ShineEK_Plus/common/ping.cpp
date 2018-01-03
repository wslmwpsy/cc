// NetworkLib.cpp
//

#include "stdafx.h"
#include "ping.h"

#include <cstdio>
#include <winsock.h>
#include <exception>

//日志文件路径
extern CString strLogPath;
extern HANDLE hsemaphore;

typedef struct {
	unsigned char Ttl;                         // Time To Live
	unsigned char Tos;                         // Type Of Service
	unsigned char Flags;                       // IP header flags
	unsigned char OptionsSize;                 // Size in bytes of options data
	unsigned char *OptionsData;                // Pointer to options data
} IP_OPTION_INFORMATION, * PIP_OPTION_INFORMATION;

typedef struct {
	DWORD Address;                             // Replying address
	unsigned long  Status;                     // Reply status
	unsigned long  RoundTripTime;              // RTT in milliseconds
	unsigned short DataSize;                   // Echo data size
	unsigned short Reserved;                   // Reserved for system use
	void *Data;                                // Pointer to the echo data
	IP_OPTION_INFORMATION Options;             // Reply options
} IP_ECHO_REPLY, * PIP_ECHO_REPLY;


// 定义函数三个指针类型
typedef HANDLE (WINAPI* pfnHV)(VOID);
typedef BOOL (WINAPI* pfnBH)(HANDLE);
typedef DWORD (WINAPI* pfnDHDPWPipPDD)(HANDLE, DWORD, LPVOID, WORD,
		PIP_OPTION_INFORMATION, LPVOID, DWORD, DWORD);

unsigned long ping(const char* szAddress, int nTimeout)
{
	unsigned char acPingBuffer[16];
	FILE *fpLog = NULL;
	unsigned long roundtrip_time = nTimeout;
	struct hostent* phe=NULL;

	memset(acPingBuffer,0x0,sizeof(acPingBuffer));

	try
	{
		// 装载ICMP.DLL连接库
		HINSTANCE hIcmp = LoadLibrary(L"icmp.dll");
		if (hIcmp == 0)
		{
			return roundtrip_time;
		}

		// 查找给定机器的IP地址信息
		if ((phe = gethostbyname(szAddress)) == 0)
		{
			FreeLibrary(hIcmp);
			hIcmp = NULL;
			return roundtrip_time;
		}

		//定义三个指针函数
		pfnHV pIcmpCreateFile;
		pfnBH pIcmpCloseHandle;
		pfnDHDPWPipPDD pIcmpSendEcho;

		//从ICMP.DLL中得到函数入口地址
		pIcmpCreateFile = (pfnHV)GetProcAddress(hIcmp,  "IcmpCreateFile");
		pIcmpCloseHandle = (pfnBH)GetProcAddress(hIcmp, "IcmpCloseHandle");
		pIcmpSendEcho = (pfnDHDPWPipPDD)GetProcAddress(hIcmp, "IcmpSendEcho");
		if ((pIcmpCreateFile == 0) || (pIcmpCloseHandle == 0) || (pIcmpSendEcho == 0))
		{
			FreeLibrary(hIcmp);
			hIcmp = NULL;
			return roundtrip_time;
		}

		// 打开ping服务
		HANDLE hIP = pIcmpCreateFile();
		if (hIP == INVALID_HANDLE_VALUE)
		{
			FreeLibrary(hIcmp);
			hIcmp = NULL;
			return roundtrip_time;
		}

		// 构造ping数据包
		memset(acPingBuffer, 'E', sizeof(acPingBuffer));

		PIP_ECHO_REPLY pIpe = (PIP_ECHO_REPLY)GlobalAlloc( GMEM_FIXED | GMEM_ZEROINIT,
			sizeof(IP_ECHO_REPLY) + sizeof(acPingBuffer)); 
		if (pIpe == 0)
		{	
			FreeLibrary(hIcmp);
			return roundtrip_time;
		}
		//pIpe->Data = acPingBuffer;
		//pIpe->DataSize = sizeof(acPingBuffer);      

		// 发送ping数据包
		DWORD dwStatus = pIcmpSendEcho(hIP, *((DWORD*)phe->h_addr_list[0]), 
			acPingBuffer, sizeof(acPingBuffer), NULL, pIpe,
			sizeof(IP_ECHO_REPLY) + sizeof(acPingBuffer), nTimeout);

		//Check we got the packet back
		BOOL bSuccess = (dwStatus == 1);
		//Check the IP status is OK (O is IP Success)
		if (bSuccess && (pIpe->Status != 0))
		{
			bSuccess = FALSE;
		}

		//Check we got the same amount of data back as we sent
		if (bSuccess)
		{
			bSuccess = (pIpe->DataSize == sizeof(acPingBuffer));
			roundtrip_time = pIpe->RoundTripTime;
		}
		//Check the data we got back is what was sent
		if (bSuccess)
		{
			/*
			char* pReplyData = (char*) pIpe->Data;

			for (int i=0; i<nPacketSize && bSuccess; i++)
			bSuccess = (pReplyData[i] == 'E');*/
		}

		if (pIpe)
		{
			GlobalFree(pIpe);
			pIpe = NULL;
		}
		if (hIP)
		{
			pIcmpCloseHandle(hIP);
			hIP = NULL;
		}
		if (hIcmp)
		{
			FreeLibrary(hIcmp);
			hIcmp = NULL;
		}
	}
	catch (...)
	{
	}
	
	return roundtrip_time;
}
