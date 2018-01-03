#include "stdafx.h"
#include "mysql_db.h"

CMySQL_DB::CMySQL_DB(void)
{
	memset(m_strUser, 0x0, sizeof(m_strUser));
	memset(m_strPswd, 0x0, sizeof(m_strPswd));
	memset(m_strHost, 0x0, sizeof(m_strHost));
	memset(m_strTable, 0x0, sizeof(m_strTable));
	m_iPort = 3306;								//MySQL������Ĭ�϶˿ں�
}

CMySQL_DB::~CMySQL_DB(void)
{

}


void CMySQL_DB::Init(const char* strUser, 
					 const char* strPswd, 
					 const char* strHost, 
					 const char* strTable, 
					 unsigned int iPort/*Ĭ�϶˿ں�*/)
{
	strcpy(m_strUser, strUser);
	strcpy(m_strPswd, strPswd);
	strcpy(m_strHost, strHost);
	strcpy(m_strTable, strTable);

	m_iPort = iPort;

	mysql_init(&m_MySQLCont);
}

bool CMySQL_DB::ConnectServer()
{
	bool bResult = false;

	if (mysql_real_connect(&m_MySQLCont, m_strHost, m_strUser, m_strPswd, m_strTable, m_iPort,NULL,0))
	{
		mysql_query(&m_MySQLCont, "SET NAMES GBK"); //���ñ����ʽ,������cmd���޷���ʾ����

		bResult = true;
	}

	return bResult;
}

//�Ͽ�����
void CMySQL_DB::CloseConnect()
{
	mysql_close(&m_MySQLCont);
}

//����������ѯ�������ַ���
bool CMySQL_DB::Query(char* strIP,char *state)
{
	try
	{
		if ((NULL==strIP)||(NULL==state))
		{
			return false;
		}
		MYSQL_RES* mySQLResult;
		MYSQL_ROW MySQLRow;
		char strSql[256];

		memset(strSql,0x0,sizeof(strSql));

		sprintf(strSql,"select ifopen from BoxInfo as a,VipPlace as b where a.box_id=b.id and b.ip='%s'",strIP);

		if (!mysql_query(&m_MySQLCont, strSql))
		{
			//�����ѯ�������ݵ�result
			mySQLResult = mysql_store_result(&m_MySQLCont);
			if (mySQLResult)
			{
				MySQLRow = mysql_fetch_row(mySQLResult);
				if (MySQLRow)
				{
					strcpy(state, MySQLRow[0]);
				}
				//�ͷ��ڴ�
				mysql_free_result(mySQLResult);
			}			
		}

		return true;
	}
	catch (...)
	{
		
	}

	return false;;
}

bool CMySQL_DB::RoomState(char* strIP)
{
	try
	{
		char state[256];
		bool result=false;

		memset(state,0x0,sizeof(state));

		//��ѯ�õ�����״̬
		result = Query(strIP,state);
		if ((0==strcmp(state,"Y"))||(0==strcmp(state,"O")))
		{
			//����
			return true;
		}

		//�ط�
		return false;
	}
	catch (...)
	{
		
	}

	return false;
}