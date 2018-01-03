#pragma once

#include <windows.h>
#include <stdio.h>
#include <iostream>
using namespace std;

#include "mysql.h"

const int USER_NAME_LENGTH = 30;
const int USER_PSWD_LENGTH = 30;
const int USER_HOST_LENGTH = 16;
const int TABLE_NAME_LENGTH = 20;


class CMySQL_DB
{
public:
	CMySQL_DB(void);


	~CMySQL_DB(void);

	void Init(const char* strUser, 
		const char* strPswd, 
		const char* strHost, 
		const char* strTable, 
		unsigned int iPort = 3306/*Ĭ�϶˿ں�*/);									//��ʼ��
	bool ConnectServer();							//���ӷ�����
	void CloseConnect();							//�Ͽ�����

	bool Query(char* strIP,char *state);			//����������ѯ�����ص���ֵ
	bool RoomState(char* strIP);                    //�鿴����״̬ true������ false���ط�

private:
	char m_strUser[USER_NAME_LENGTH];				//�û���
	char m_strPswd[USER_PSWD_LENGTH];				//����
	char m_strHost[USER_HOST_LENGTH];				//��������ַ
	char m_strTable[TABLE_NAME_LENGTH];				//���ݿ�����
	unsigned int m_iPort;							//�������˿ں�

	MYSQL m_MySQLCont;
};
