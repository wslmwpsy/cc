#ifndef __NETWORK_H__
#define __NETWORK_H__

#include "..\DllConst.h"

/*
功能：使用Ping函数之前，应使用WSAStartup进行初始化
参数：
    ip：要ping的机器IP
	time_out：超时，单位-毫秒
返回值：
    耗时
*/
unsigned long KTV_DLL_API ping(const char* ip, int time_out = 1000);

#endif