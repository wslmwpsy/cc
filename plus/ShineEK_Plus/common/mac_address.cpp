// MacAddress.cpp
//

#include "StdAfx.h"
#include "mac_address.h"
#include "TCHAR.h"
#include "StringCodeConversion.h"
#include "init_socket.h"

//////////////////////////////////////////////////////////////////////////
//
// 功能：获取网卡地址
//

#pragma comment(lib, "netapi32.lib")
#pragma warning(disable: 4267)

// 获取当前机器的网卡信息，包括多少个网卡，每张网卡的编号
BOOL GetNetCardInfo(LANA_ENUM* pLanaEnum)
{
	NCB ncb;
	UCHAR uRetCode;
	
	// 向网卡发送NCBENUM命令，以获取当前机器的网卡信息
	memset(&ncb, 0, sizeof(ncb));
	ncb.ncb_command = NCBENUM;
	ncb.ncb_buffer = (unsigned char*)pLanaEnum;
	ncb.ncb_length = sizeof(LANA_ENUM);
	uRetCode = Netbios(&ncb);
	if (uRetCode != 0)
		return FALSE;
	
	return TRUE;
}

// 获取网卡的MAC地址
BOOL GetNetCardMac(unsigned char lana_num, unsigned char adapter_address[6])
{
	typedef struct _ASTAT_	// 此结构用于存放返回的网卡信息
	{
		ADAPTER_STATUS adapt;
		NAME_BUFFER NameBuff[30];
	}ASTAT, *PASTAT;
	
	ASTAT Adapter;
	NCB ncb;
	UCHAR uRetCode;
	
	// 首先对选定的网卡发送一个NCBRESET命令，以便进行初始化
	memset(&ncb, 0, sizeof(ncb));
	ncb.ncb_command = NCBRESET;
	ncb.ncb_lana_num = lana_num;	// 指定网卡号
	uRetCode = Netbios(&ncb);
	if (uRetCode != 0)
		return FALSE;
	
	// 接着，可以发送NCBASTAT命令以获取网卡的信息
	memset(&ncb, 0, sizeof(ncb));
	ncb.ncb_command = NCBASTAT;
	ncb.ncb_lana_num = lana_num;	// 指定网卡号
	_tcscpy((TCHAR*)ncb.ncb_callname, L"*               ");
	ncb.ncb_buffer = (unsigned char*)&Adapter;	// 指定返回的信息存放的变量
	ncb.ncb_length = sizeof(Adapter);
	uRetCode = Netbios(&ncb);
	if (uRetCode != 0)
		return FALSE;
	
	memcpy(adapter_address, Adapter.adapt.adapter_address, 6);
	return TRUE;
}


bool GetAdapterInfo(ADAPTER_INFO *mac_info)
{
	try
	{
		// 这里的代码适合WINDOWS2000，对于NT需要读取HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows NT\CurrentVersion\NetworkCards
		HKEY hKey, hSubKey, hNdiIntKey;

		if(RegOpenKeyEx(HKEY_LOCAL_MACHINE,L"System\\CurrentControlSet\\Control\\Class\\{4d36e972-e325-11ce-bfc1-08002be10318}",0,KEY_READ,	&hKey) != ERROR_SUCCESS)
		{
			return false;
		}

		DWORD dwIndex = 0;
		DWORD dwBufSize = 256;
		DWORD dwDataType;
		TCHAR szSubKey[256];
		BYTE szData[256];
		bool result=false;

		memset(szSubKey,0x0,sizeof(szSubKey));

		while(RegEnumKeyEx(hKey, dwIndex++, szSubKey, &dwBufSize, NULL, NULL, NULL, NULL) == ERROR_SUCCESS)
		{
			if(RegOpenKeyEx(hKey, szSubKey, 0, KEY_READ, &hSubKey) == ERROR_SUCCESS)
			{		
				if(RegOpenKeyEx(hSubKey, L"Ndi\\Interfaces", 0, KEY_READ, &hNdiIntKey) == ERROR_SUCCESS)
				{
					memset(szData,0x0,sizeof(szData));
					dwBufSize = sizeof(szData);
					if(RegQueryValueEx(hNdiIntKey, L"LowerRange", 0, &dwDataType, szData, &dwBufSize) == ERROR_SUCCESS)
					{
						if(_tcscmp((LPCTSTR)szData, L"ethernet") == 0)		//	判断是不是以太网卡
						{
							memset(szData,0x0,sizeof(szData));
							dwBufSize = sizeof(szData);
							if(RegQueryValueEx(hSubKey, L"DriverDesc", 0, &dwDataType, szData, &dwBufSize) == ERROR_SUCCESS)
							{
								mac_info->strDriverDesc = (LPCTSTR)szData;
								memset(szData,0x0,sizeof(szData));
								dwBufSize = sizeof(szData);
								if(RegQueryValueEx(hSubKey, L"NetCfgInstanceID", 0, &dwDataType, szData, &dwBufSize) == ERROR_SUCCESS)
								{
									mac_info->strName = (LPCTSTR)szData;
									result = RegGetIP(mac_info, (LPCTSTR)szData);
									if (result)
									{
										return true;
									}
								}
							}
						}
					}
					RegCloseKey(hNdiIntKey);
				}
				RegCloseKey(hSubKey);
			}

			dwBufSize = sizeof(szSubKey)/sizeof(TCHAR);
			memset(szSubKey,0x0,sizeof(szSubKey));
		}	/* end of while */

		RegCloseKey(hKey);

		return false;
	}
	catch (...)
	{
		
	}
	return false;
}

bool RegGetIP(ADAPTER_INFO *pAI, LPCTSTR lpszAdapterName, int nIndex/* =0 */)
{
	try
	{
		if (NULL==pAI)
		{
			return false;
		}
		HKEY hKey;
		TCHAR key_name[1024];
		BYTE szData[256];
		DWORD dwDataType, dwBufSize;
		TCHAR temp_data[1024];
		string_conversion string_conv;

		memset(key_name,0x0,sizeof(key_name));
		memset(szData,0x0,sizeof(szData));

		//得到键值
		swprintf(key_name,L"SYSTEM\\CurrentControlSet\\Services\\Tcpip\\Parameters\\Interfaces\\%s",lpszAdapterName);
		if(RegOpenKeyEx(HKEY_LOCAL_MACHINE,key_name,0,KEY_READ,	&hKey) != ERROR_SUCCESS)
		{
			return false;
		}

		memset(szData,0x0,sizeof(szData));
		dwBufSize = sizeof(szData);
		if(RegQueryValueEx(hKey, L"IPAddress", 0, &dwDataType, (LPBYTE)szData, &dwBufSize) == ERROR_SUCCESS)
		{
			if (dwBufSize>15)
			{
				//unicode
				pAI->strIP = (LPCTSTR)szData;
			}
			else
			{
				//ansic
				memset(temp_data,0x0,sizeof(temp_data));
				string_conv.multibyte_to_widechar((const char *)szData,temp_data,sizeof(temp_data)/sizeof(TCHAR));
				pAI->strIP = temp_data;

			}
		}
			

		memset(szData,0x0,sizeof(szData));
		dwBufSize = sizeof(szData);
		if(RegQueryValueEx(hKey, L"SubnetMask", 0, &dwDataType, (LPBYTE)szData, &dwBufSize) == ERROR_SUCCESS)
		{
			if (dwBufSize>15)
			{
				//unicode
				pAI->strNetMask = (LPCTSTR)szData;
			}
			else
			{
				//ansic
				memset(temp_data,0x0,sizeof(temp_data));
				string_conv.multibyte_to_widechar((const char *)szData,temp_data,sizeof(temp_data)/sizeof(TCHAR));
				pAI->strNetMask = temp_data;

			}
		}

		memset(szData,0x0,sizeof(szData));
		dwBufSize = sizeof(szData);
		if(RegQueryValueEx(hKey, L"DefaultGateway", 0, &dwDataType, (LPBYTE)szData, &dwBufSize) == ERROR_SUCCESS)
		{
			if (dwBufSize>15)
			{
				//unicode
				pAI->strNetGate = (LPCTSTR)szData;
			}
			else
			{
				//ansic
				memset(temp_data,0x0,sizeof(temp_data));
				string_conv.multibyte_to_widechar((const char *)szData,temp_data,sizeof(temp_data)/sizeof(TCHAR));
				pAI->strNetGate = temp_data;

			}
		}

		RegCloseKey(hKey);

		return true;
	}
	catch (...)
	{
		
	}
	return false;
}


//-----------------------------------------------------------------
//	设置注册表中的IP信息
//-----------------------------------------------------------------

BOOL RegSetIP(LPCTSTR lpszAdapterName, int nIndex, LPCTSTR pIPAddress, LPCTSTR pNetMask, LPCTSTR pNetGate)
{
	try
	{
		HKEY hKey;
		TCHAR key_name[1024];
		size_t nIP=0, nMask=0, nGate=0;
		TCHAR ip_address[256];
		TCHAR net_mask[256];
		TCHAR net_gate[256];

		memset(key_name,0x0,sizeof(key_name));
		memset(ip_address,0x0,sizeof(ip_address));
		memset(net_mask,0x0,sizeof(net_mask));
		memset(net_gate,0x0,sizeof(net_gate));

		if ((NULL==lpszAdapterName)||(NULL==pIPAddress)||(NULL==pNetMask)||(NULL==pNetGate))
		{
			return FALSE;
		}

		//打开注册表键值
		swprintf(key_name,L"SYSTEM\\CurrentControlSet\\Services\\Tcpip\\Parameters\\Interfaces\\%s",lpszAdapterName);
		if(RegOpenKeyEx(HKEY_LOCAL_MACHINE,key_name,0,KEY_WRITE,&hKey) != ERROR_SUCCESS)
		{
			return FALSE;
		}

		_tcscpy(ip_address,pIPAddress);
		_tcscpy(net_mask,pNetMask);
		_tcscpy(net_gate,pNetGate);

		//需要两个结束符号
		nIP = _tcslen(ip_address)*2+4;
		nMask = _tcslen(net_mask)*2+4;
		nGate = _tcslen(net_gate)*2+4;

		RegSetValueEx(hKey, L"IPAddress", 0, REG_MULTI_SZ, (unsigned char*)ip_address, nIP);
		RegSetValueEx(hKey, L"SubnetMask", 0, REG_MULTI_SZ, (unsigned char*)net_mask, nMask);
		//RegSetValueEx(hKey, L"DefaultGateway", 0, REG_MULTI_SZ, (unsigned char*)net_gate, nGate);

		RegCloseKey(hKey);

		return TRUE;
	}
	catch (...)
	{
		
	}
	return FALSE;
}

//-----------------------------------------------------------------
//	通知IP地址的改变
//-----------------------------------------------------------------

BOOL NotifyIPChange(LPCTSTR lpszAdapterName, int nIndex, const char * pIPAddress, const char * pNetMask)
{
	try
	{
		BOOL			bResult = FALSE;
		HINSTANCE		hDhcpDll;
		DHCPNOTIFYPROC	pDhcpNotifyProc;

		if ((NULL==lpszAdapterName)||(NULL==pIPAddress)||(NULL==pNetMask))
		{
			return FALSE;
		}

		//加载动态库
		if((hDhcpDll = LoadLibrary(L"dhcpcsvc")) == NULL)
		{
			return FALSE;
		}

		//得到函数入口地址
		if((pDhcpNotifyProc = (DHCPNOTIFYPROC)GetProcAddress(hDhcpDll, "DhcpNotifyConfigChange")) != NULL)
		{
			
			if((pDhcpNotifyProc)(NULL, (LPWSTR)lpszAdapterName, TRUE, nIndex, inet_addr(pIPAddress), inet_addr(pNetMask), 0) == ERROR_SUCCESS)
			{
				bResult = TRUE;
			}
		}
		//释放动态库
		FreeLibrary(hDhcpDll);

		return bResult;
	}
	catch (...)
	{
		
	}
	return FALSE;
}

bool modify_computer_ip(LPCTSTR lpszAdapterName, int nIndex, LPCTSTR pIPAddress, LPCTSTR pNetMask, LPCTSTR pNetGate)
{
	string_conversion string_conv;
	char ip_address[256];
	char net_mask[256];

    memset(ip_address,0x0,sizeof(ip_address));
	memset(net_mask,0x0,sizeof(net_mask));

	//做合法性检测
	string_conv.widechar_to_multibyte(pIPAddress,ip_address,sizeof(ip_address));
	string_conv.widechar_to_multibyte(pNetMask,net_mask,sizeof(net_mask));

	if ((INADDR_NONE==inet_addr(ip_address))||(INADDR_NONE==inet_addr(net_mask)))
	{
		return false;
	}

	if(!RegSetIP(lpszAdapterName, nIndex, pIPAddress, pNetMask, pNetGate))
		return false;

	if(!NotifyIPChange(lpszAdapterName, nIndex, ip_address, net_mask))
		return false;

	return true;
}