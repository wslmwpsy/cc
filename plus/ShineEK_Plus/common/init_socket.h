//////////////////////////////////////////////////////////
// initsock.h文件
#pragma once

#include <winsock2.h>
#pragma comment(lib, "WS2_32.lib")	// 链接到WS2_32.lib


class CInitSocket
{
public:
	CInitSocket(BYTE minorVer = 2, BYTE majorVer = 2)
	{
		// 初始化WS2_32.dll
		// WSA versions
		BYTE version_count=3;
		WORD socket_version=0;
		int result=0;
        WSADATA wsaData;
		
		//第一维：主版本 第二维：副版本 第三维：结果 1：成功 0：失败
		int version_info[3][3]={
			{1,0,0},
			{1,1,0},
			{2,0,0}
		};
		//******* Dynamically detect winsock version, from newest to oldest
		while(version_count>0)
		{
			//生成socket版本
			socket_version=MAKEWORD(version_info[version_count-1][0],version_info[version_count-1][1]);

			result=WSAStartup(socket_version,&wsaData);
			if (0==result)
			{
				//成功
				version_info[version_count-1][2]=1;
				break;
			}
			else
			{
				//失败
				version_info[version_count-1][2]=0;
			}
			WSACleanup();
			version_count--;
		}
	}

	~CInitSocket()
	{	
		::WSACleanup();	
	}
};
