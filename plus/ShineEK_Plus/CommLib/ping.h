#ifndef __NETWORK_H__
#define __NETWORK_H__

#include "..\DllConst.h"

/*
���ܣ�ʹ��Ping����֮ǰ��Ӧʹ��WSAStartup���г�ʼ��
������
    ip��Ҫping�Ļ���IP
	time_out����ʱ����λ-����
����ֵ��
    ��ʱ
*/
unsigned long KTV_DLL_API ping(const char* ip, int time_out = 1000);

#endif