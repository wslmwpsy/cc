//////////////////////////////////////////////////////////
// initsock.h�ļ�
#pragma once

#include <winsock2.h>
#pragma comment(lib, "WS2_32.lib")	// ���ӵ�WS2_32.lib


class CInitSocket
{
public:
	CInitSocket(BYTE minorVer = 2, BYTE majorVer = 2)
	{
		// ��ʼ��WS2_32.dll
		// WSA versions
		BYTE version_count=3;
		WORD socket_version=0;
		int result=0;
        WSADATA wsaData;
		
		//��һά�����汾 �ڶ�ά�����汾 ����ά����� 1���ɹ� 0��ʧ��
		int version_info[3][3]={
			{1,0,0},
			{1,1,0},
			{2,0,0}
		};
		//******* Dynamically detect winsock version, from newest to oldest
		while(version_count>0)
		{
			//����socket�汾
			socket_version=MAKEWORD(version_info[version_count-1][0],version_info[version_count-1][1]);

			result=WSAStartup(socket_version,&wsaData);
			if (0==result)
			{
				//�ɹ�
				version_info[version_count-1][2]=1;
				break;
			}
			else
			{
				//ʧ��
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
