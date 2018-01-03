// NetworkLib.h
//

#ifndef __NETWORK_H__
#define __NETWORK_H__

// 使用Ping函数之前，应使用WSAStartup进行初始化
//返回值：使用的时间
unsigned long ping(const char* szAddress, int nTimeout=1000);

#endif //__NETWORK_H__
