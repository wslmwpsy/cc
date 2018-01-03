// DogClient.h: interface for the CDogClient class.
//
//////////////////////////////////////////////////////////////////////

#if !defined SHINE_ENCRYPT_DOG_CLIENT_H
#define SHINE_ENCRYPT_DOG_CLIENT_H

#if _MSC_VER > 1000
	#ifndef _SHINE_LINUX_
		#pragma once
	#endif
#endif // _MSC_VER > 1000

#define SHINE_ERROR_MOULDID		-10				//LoginCheck Error  ģ����
#define SHINE_ERROR_COUNT		-11				//LoginCheck Error  ��������
#define SHINE_ERROR_VALIDTIME	-12				//LoginCheck Error  ��Ч�ڳ���
#define SHINE_ERROR_MISMATCH	-13             
#define SHINE_ERROR_COMMONCHECK -14

#define SHINE_ERROR_OTHER		-1
#define SHINE_ERROR_DISCONNECT  -15            //���Ӳ��Ϸ�����

class CDogClient
{
public:
	//�������ƣ�CDogClient
	//����˵���������� 
	//���������ServerIP				--	ָ��������IP��ַ
	//���������ServerPort				--	ָ���������˿�
	//���������strModuleNbr			--	ģ����롶4�ֽ����֡�
	//���������MaxLinkErrors			--	���ӷ����������������,���ڿͻ����жϷ������˿��Ƿ���Ч
	//���������TimeOut					--	�ȴ���������Ӧ�ĳ�ʱʱ��
	//���������WarningTime				--	��Ч���ڱ�����ֵ
	CDogClient (char* ServerIP,int ServerPort, char* strModuleNbr,int MaxLinkErrors,long TimeOut,long WarningTime
				);
	
	//�������ƣ�CDogClient
	//����˵���������� 
	CDogClient ();

	//�������ƣ�~CDogClient
	//����˵������������ 
	virtual ~CDogClient();
	
public:
	//�������ƣ�SetParam
	//����˵������������
	//���������ServerIP				--	ָ��������IP��ַ
	//���������ServerPort				--	ָ���������˿�
	//���������strModuleNbr			--	ģ����롶4�ֽ����֡�
	//���������MaxLinkErrors			--	���ӷ����������������,���ڿͻ����жϷ������˿��Ƿ���Ч
	//���������TimeOut					--	�ȴ���������Ӧ�ĳ�ʱʱ��
	//���������WarningTime				--	��Ч���ڱ�����ֵ
	void SetParam(char* ServerIP, 
					   int ServerPort, 
					   char* strModuleNbr, 
					   int MaxLinkErrors, 
					   long TimeOut, 
					   long WarningTime );
	//�������ƣ�ConnectServer
	//����˵�������Ӽ��ܹ�server
	//����ֵ  ��TRUE		--	�ɹ�
	//          FALSE		--	ʧ��
	bool ConnectServer();

	//�������ƣ�LoginCheck
	//����˵�����ͻ��˵�½��飬���ڽ���ģ�����ע�����
	//���������long & lngValidTime  ��Ч����
	//���������char * strModuleNbr ģ����
	//����ֵ  ��0		--	�ɹ�
	//          !0		--	ʧ��	
	int LoginCheck(long & lngValidTime,char * strModuleNbr);
		
	//�������ƣ�GetData
	//����˵�������ݲ�ͬ�������ӹ��ж�ȡ��Ӧ�����ļ����Ⱥ���Ϣ
	//���������vWhichOne	--	�ļ�������0-�����ļ���1-�ͻ��ļ���2-�������ļ���
	//���������vBufferLen	--	�ļ�����
	//���������vBuffer		--	�ļ�����
	//����ֵ  ��0		--	�ɹ�
	//          !0		--	ʧ��	
	int GetData(int vWhichOne, int & vBufferLen , char*  vBuffer);
	
	//�������ƣ�CommonCheck
	//����˵�����ͻ���������м��ܷ������м��
	//����ֵ  ��0		--	�ɹ�
	//          !0		--	ʧ��	
	int CommonCheck();
	
	//�������ƣ�Logout
	//����˵�����ͻ��˵ǳ�����
	//����ֵ  ����
	void Logout(void);
	
	//�������ƣ�IncSongs
	//����˵�������Ӽ����������
	//���������incSongTimes	--	���ӵļ���ֵ��д����ܹ�
	//���������incSongTimes	--	���ܹ��ڵ��ܼ���ֵ
	//����ֵ  ��0		--	�ɹ�
	//          !0		--	ʧ��	
	int IncSongs(long & incSongTimes); 
	
	//�������ƣ�VerifyTime
	//����˵��������У��������ʱ��
	//����ֵ  ����
	void VerifyTime(void);

	//�������ƣ�GetSongs
	//����˵����ȡ�ü��ܹ��ڵ��ܼ���ֵ
	//���������sumSongs	--	���ܹ��ڵ��ܼ���ֵ
	//����ֵ  ��0		--	�ɹ�
	//          !0		--	ʧ��	
	int GetSongs(long & sumSongs);
	
	//�������ƣ�RunExec
	//����˵����ִ�м��ܹ����㷨
	//���������fileID		--	���ܹ����㷨���� ��ȡֵ��ΧΪ0-38��
	//���������runData		--	������������  ���̶�Ϊ128�ֽ��ַ����顷
	//���������runData		--	������  ����Ϊ���ʱֻ��ʹ��ǰ127�ֽ�,���һ���ֽ���Ч��
	//����ֵ  ��0		--	�ɹ�
	//          !0		--	ʧ��	
	int RunExec(int fileID, char*  runData);
	
	//�������ƣ�Encode
	//����˵����ִ�м��ܹ����㷨�����м��ܲ���
	//���������vInput		--	�����ܵ��ַ���(128�ֽڡ����̶�����)
	//���������vOutput		--	���ܺ���ַ���(128�ֽڡ����̶�����)
	//����ֵ  ��0		--	�ɹ�
	//          !0		--	ʧ��	
	int Encode(char* vInput, char*  vOutput);
	
	//�������ƣ�Decode
	//����˵����ִ�м��ܹ����㷨�����н��ܲ���
	//���������vInput		--	�����ܵ��ַ���(128�ֽڡ����̶�����)
	//���������vOutput		--	���ܺ���ַ���(128�ֽڡ����̶�����)
	//����ֵ  ��0		--	�ɹ�
	//          !0		--	ʧ��	
	int Decode(char* vInput, char*  vOutput);
	
	//�������ƣ�ActiveClockTime
	//����˵����ִ�м��ܹ����㷨������ָ����Ч���ڵ��趨
	//���������ActiveString		--	ʱ�伤����
	//�������������ActiveTime		--	ָ����Ч����
	//����ֵ  ��0		--	�ɹ�
	//          !0		--	ʧ��	
	int ActiveClockTime(char*  ActiveString, long & ActiveTime);

private:
	bool blnInitialize ;
	void AddModule(char* strModuleNbr);
	void RegisterModules();
	
};

#endif // !defined(AFX_SERVERSOCKETMANAGER_H__96F87621_037D_436B_B0C8_3D80D6E3EC32__INCLUDED_)
