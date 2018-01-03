// MacAddress.h
//

#ifndef __MAC_ADDRESS__H__
#define __MAC_ADDRESS__H__

#include <string>

using namespace std;

//�����ص�����
typedef int (CALLBACK* DHCPNOTIFYPROC)(LPWSTR, LPWSTR, BOOL, DWORD, DWORD, DWORD, int);

typedef struct tagAdapterInfo
{
	std::wstring strName;		//����������
	std::wstring strDriverDesc;	//����������
	std::wstring strIP;			//IP��ַ
	std::wstring strNetMask;	    //��������
	std::wstring strNetGate;	    //����
}ADAPTER_INFO;


//////////////////////////////////////////////////////////////////////////
//
// ���ܣ���ȡ������ַ

#include <nb30.h>

// ��ȡ��ǰ������������Ϣ���������ٸ�������ÿ�������ı��
BOOL GetNetCardInfo(LANA_ENUM* pLanaEnum);

// ��ȡ������MAC��ַ
BOOL GetNetCardMac(unsigned char lana_num, unsigned char adapter_address[6]);


//-----------------------------------------------------------------
//	�õ�ע����е�IP��Ϣ
//	nIndex��ʱδ����
//-----------------------------------------------------------------
bool RegGetIP(ADAPTER_INFO *pAI, LPCTSTR lpszAdapterName, int nIndex = 0);

//�õ���������Ϣ
bool GetAdapterInfo(ADAPTER_INFO *mac_info);



//-----------------------------------------------------------------
//	����IP��ַ
//	���ֻ��һ��IP��nIndex = 0����ʱδ����һ�������󶨶����ַ
//-----------------------------------------------------------------

bool modify_computer_ip(LPCTSTR lpszAdapterName, int nIndex, LPCTSTR pIPAddress, LPCTSTR pNetMask, LPCTSTR pNetGate);

#endif //__MAC_ADDRESS__H__
