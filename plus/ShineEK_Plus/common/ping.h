// NetworkLib.h
//

#ifndef __NETWORK_H__
#define __NETWORK_H__

// ʹ��Ping����֮ǰ��Ӧʹ��WSAStartup���г�ʼ��
//����ֵ��ʹ�õ�ʱ��
unsigned long ping(const char* szAddress, int nTimeout=1000);

#endif //__NETWORK_H__
