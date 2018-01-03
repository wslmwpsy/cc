// MacAddress.h
//

#ifndef __MAC_ADDRESS__H__
#define __MAC_ADDRESS__H__

#include <string>

using namespace std;

//声明回调函数
typedef int (CALLBACK* DHCPNOTIFYPROC)(LPWSTR, LPWSTR, BOOL, DWORD, DWORD, DWORD, int);

typedef struct tagAdapterInfo
{
	std::wstring strName;		//适配器名称
	std::wstring strDriverDesc;	//适配器描述
	std::wstring strIP;			//IP地址
	std::wstring strNetMask;	    //子网掩码
	std::wstring strNetGate;	    //网关
}ADAPTER_INFO;


//////////////////////////////////////////////////////////////////////////
//
// 功能：获取网卡地址

#include <nb30.h>

// 获取当前机器的网卡信息，包括多少个网卡，每张网卡的编号
BOOL GetNetCardInfo(LANA_ENUM* pLanaEnum);

// 获取网卡的MAC地址
BOOL GetNetCardMac(unsigned char lana_num, unsigned char adapter_address[6]);


//-----------------------------------------------------------------
//	得到注册表中的IP信息
//	nIndex暂时未处理
//-----------------------------------------------------------------
bool RegGetIP(ADAPTER_INFO *pAI, LPCTSTR lpszAdapterName, int nIndex = 0);

//得到适配器信息
bool GetAdapterInfo(ADAPTER_INFO *mac_info);



//-----------------------------------------------------------------
//	设置IP地址
//	如果只绑定一个IP，nIndex = 0，暂时未处理一个网卡绑定多个地址
//-----------------------------------------------------------------

bool modify_computer_ip(LPCTSTR lpszAdapterName, int nIndex, LPCTSTR pIPAddress, LPCTSTR pNetMask, LPCTSTR pNetGate);

#endif //__MAC_ADDRESS__H__
