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
		unsigned int iPort = 3306/*默认端口号*/);									//初始化
	bool ConnectServer();							//连接服务器
	void CloseConnect();							//断开连接

	bool Query(char* strIP,char *state);			//根据条件查询，返回单个值
	bool RoomState(char* strIP);                    //查看房间状态 true：开房 false：关房

private:
	char m_strUser[USER_NAME_LENGTH];				//用户名
	char m_strPswd[USER_PSWD_LENGTH];				//密码
	char m_strHost[USER_HOST_LENGTH];				//服务器地址
	char m_strTable[TABLE_NAME_LENGTH];				//数据库名称
	unsigned int m_iPort;							//服务器端口号

	MYSQL m_MySQLCont;
};
