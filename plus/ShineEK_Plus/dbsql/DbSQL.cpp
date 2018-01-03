// Db_sql.cpp
//

#include "StdAfx.h"
#include "DbSQL.h"
#include <shlwapi.h>
#include <stdio.h>
#include "../file/log.h"
#include "../file/config_file.h" 
#include "../common/StringCodeConversion.h"
#include <ATLComTime.h>

// �Ƿ��ѵ�ĩβ
bool access_record_set_sql::IsEof()
{
	if (m_pRecordset->adoEOF)
		return true;
	else
		return false;
}

// ��ȡ��¼��
int access_record_set_sql::GetRecordCount()
{
	int nCount = 0;

	try
	{
		nCount = m_pRecordset->GetRecordCount();
	}
	catch (...)
	{
		nCount = -1;
	}
	return nCount;
}

// ����������һ��¼��
bool access_record_set_sql::GetNextRecord()
{
	try
	{
		if (IsEof() != false) 
			return false;
		m_pRecordset->MoveNext();
		if (IsEof() != false) 
			return false;
	}
	catch (...)
	{
		return false;
	}

	return true;
}

// ��ȡ�������
bool access_record_set_sql::get_item_value_by_index(int index,TCHAR *item_value)
{
	try
	{
		_variant_t var;
		var = m_pRecordset->GetCollect((long)index);
		switch (var.vt)
		{
		case VT_NULL:
			return false;

		case VT_I2:
		case VT_I4:
		case VT_INT:
			swprintf(item_value, L"%d", (long)(var));
			return true;

		case VT_BSTR:
		case VT_DATE:
			if (lstrlen(_bstr_t(var)) > 1023)
				_tcsncpy(item_value, _bstr_t(var), 1023);
			else
				_tcscpy(item_value, _bstr_t(var));
			return true;

		default:
			return false;
		}
	}
	catch (...)
	{
		return 0;
	}
}

void access_record_set_sql::MoveFirst()
{
	try
	{
		if (!m_pRecordset->BOF)
			m_pRecordset->MoveFirst();
	}
	catch (...)
	{
	}
}

void access_record_set_sql::MoveLast()
{
	try
	{
		m_pRecordset->MoveLast();
	}
	catch (...)
	{
	}
}

void access_record_set_sql::Move(int n)
{
	try
	{
		m_pRecordset->Move(n);
	}
	catch (...)
	{
	}
}

void access_record_set_sql::MoveNext()
{
	try
	{
		m_pRecordset->MoveNext();
	}
	catch (...)
	{
	}
}

CString access_record_set_sql::GetRecordData(TCHAR* Name)
{
	CString  str = L"";
	_variant_t var;
	var = m_pRecordset->GetFields()->GetItem(Name)->Value;
    switch (var.vt)
		{
		case VT_NULL:
			break;
		case VT_I2:
		case VT_I4:
		case VT_INT:
			str.Format( L"%d", (long)(var));
			break;
		case VT_BSTR:
			str =  var.bstrVal;
			break;
		case VT_DATE:
			{
				COleDateTime date_time(var.date);
				str = date_time.Format(L"%Y/%m/%d");
			}
			break;
		default:
			break;
		}
		
	return str;
}

long access_record_set_sql::GetRecordDataLeng(TCHAR* Name)
{
	return m_pRecordset->GetFields()->GetItem(Name)->ActualSize;
}


// ���캯��
Db_sql::Db_sql() 
{
	m_pConnectionPtr = NULL;
}
	
// �������ݿ�
bool Db_sql::Connect(void)
{
	// ��ADO�����н��������Ҫ����try...catch()�����������Ϣ��
	try
	{
		TCHAR conn_string[1024];
		HRESULT result=0;

		char  connstr[1024] ; 
		char data_temp[256];
		memset(connstr,0x0,sizeof(connstr));
		memset(data_temp,0x0,sizeof(data_temp));
		std::wstring data_source;
		config_file_manager config_file;
		string_conversion str_conver;


		memset(conn_string,0x0,sizeof(conn_string));
		
		if (m_pConnectionPtr == NULL)
		{
			// ��������
 			result = m_pConnectionPtr.CreateInstance("ADODB.Connection");
			if (S_OK!=result)
			{
				WriteLog(__FL__, L"_ConnectionPtr��CreateInstance()ʧ��");
				return false;
			}
		}

		// �ж��ļ��Ƿ����
		//if (!PathFileExists(database_path))
		//	return false;

		// �������ݿ��ļ�����Ϊ��ͨ
		//SetFileAttributes(database_path, FILE_ATTRIBUTE_NORMAL);
		//ok Provider=SQLOLEDB.1;Persist Security Info=True;User ID=sa;Password=temp;Initial Catalog=Dog2.1;Data Source=PC-201109141545
		//sprintf(conn_string,"Provider=SQL SERVER;Server=192.168.0.8\SQLEXPRESS;uid=sa;pwd=temp1234; Data Source=%s",database_path);
		//const char  connstr[512] = ("Provider=SQLOLEDB.1;Persist Security Info=True;Initial Catalog=Dog2.1;Data Source=PC-201109141545;User ID=sa;Password=temp");
		//result = m_pConnectionPtr->Open(_bstr_t(connstr), "","", adModeUnknown);
	//const char  connstr[256] = ("Provider=SQLOLEDB.1;Persist Security Info=True;Initial Catalog=Dog2.1;Data Source=KTVDEVSERVER;User ID=sa;Password=temp");KTVDEVSE10.0.3.155\\DOGRVER\\DOG
	//	const char  connstr[256] = ("Provider=SQLOLEDB.1;Persist Security Info=True;Initial Catalog=Dog2.1;Data Source=RJ\DOG;User ID=sa;Password=temp");
		//const char  connstr[256] = ("Provider=SQLOLEDB.1;Persist Security Info=True;User ID=sa;Password=shine;Initial Catalog=BIGSTAR;Data Source=topbox\\DOG");//
		data_source =  config_file.read_string(L"database",L"service_name",L"");

		str_conver.widechar_to_multibyte(data_source.c_str(),data_temp,sizeof(data_temp));
		 
		//sprintf(connstr,"Provider=SQLOLEDB.1;Persist Security Info=True;User ID=sa;Password=shine;Initial Catalog=KTV_SMS;Data Source=%s",data_temp);
		sprintf(connstr,"Provider=SQLOLEDB.1;Persist Security Info=True;User ID=ktvvoduser;Password=*y&u%%x$y2u;Initial Catalog=KTV_SMS;Data Source=%s",data_temp);

		result = m_pConnectionPtr->Open(_bstr_t(connstr), "","", adModeUnknown); 
		if (S_OK != result)
		{
			return false;
		}

		WriteLog(__FL__, L"���ӹܿط�������SQL Server���ݿ�ɹ���");

		return true;
	}
	catch(_com_error e)///��׽�쳣   
	{
		WriteLog(__FL__, L"���ӹܿط�������SQL Server���ݿ�ʧ��");
	}      

    return false;
}


// �������ݿ�
bool Db_sql::Connect(const TCHAR* server_ip,const TCHAR* user_name,const TCHAR* user_pwd,const TCHAR* sql_name)
{
	// ��ADO�����н��������Ҫ����try...catch()�����������Ϣ��
	try
	{
		TCHAR conn_string[1024];
		HRESULT result=0;

		char  connstr[1024] ; 
		char data_temp[256];
		memset(connstr,0x0,sizeof(connstr));
		memset(data_temp,0x0,sizeof(data_temp));
		std::wstring data_source;
		config_file_manager config_file;
		string_conversion str_conver;


		memset(conn_string,0x0,sizeof(conn_string));

		if (m_pConnectionPtr == NULL)
		{
			// ��������
			result = m_pConnectionPtr.CreateInstance("ADODB.Connection");
			if (S_OK!=result)
			{
				WriteLog(__FL__, L"_ConnectionPtr��CreateInstance()ʧ��");
				return false;
			}
		}

		swprintf(conn_string,L"provider=SQLOLEDB;data source=%s;Address=%s,1433;initial catalog=%s;userID=%s;Password=%s;",\
			server_ip,server_ip,sql_name,user_name,user_pwd);

		//data_source =  config_file.read_string(L"database",L"service_name",L"");

		//str_conver.widechar_to_multibyte(data_source.c_str(),data_temp,sizeof(data_temp));

		//sprintf(connstr,"Provider=SQLOLEDB.1;Persist Security Info=True;User ID=sa;Password=shine;Initial Catalog=KTV_SMS;Data Source=%s",data_temp);
		//sprintf(connstr,"Provider=SQLOLEDB.1;Persist Security Info=True;User ID=ktvvoduser;Password=*y&u%%x$y2u;Initial Catalog=KTV_SMS;Data Source=%s",data_temp);
		result = m_pConnectionPtr->Open(_bstr_t(conn_string), _bstr_t(user_name), _bstr_t(user_pwd), -1);

		if (S_OK != result)
		{
			return false;
		}

		WriteLog(__FL__, L"���ӹܿط�������SQL Server���ݿ�ɹ���");

		return true;
	}
	catch(_com_error e)///��׽�쳣   
	{   
		WriteLog(__FL__, L"���ӹܿط�������SQL Server���ݿ�ʧ��");
	}      

	return false;
}

bool Db_sql::get_all_table_name(std::wstring *all_table_name,int &table_count)
{
	try
	{
		_RecordsetPtr pRecordset;
		int table_number=0;

		pRecordset.CreateInstance(__uuidof(Recordset));
		//��ʼ��ѯ���б�����   
		pRecordset = m_pConnectionPtr->OpenSchema(adSchemaTables);//ö�ٱ�����ƴ��� 
		if (NULL==pRecordset)
		{
			return false;
		}
		pRecordset->MoveFirst();
		while(!(pRecordset->adoEOF))   
		{   
			_bstr_t table_name = pRecordset->Fields->GetItem("TABLE_NAME")->Value;//��ȡ�������  
			_bstr_t table_type = pRecordset->Fields->GetItem("TABLE_TYPE")->Value;//��ȡ�������

			if(0==_tcscmp(table_type,L"TABLE"))
			{   
				 all_table_name[table_number].assign(table_name);
				 table_number++;
			}   

			pRecordset->MoveNext();   
		}
		pRecordset->Close();   
		m_pConnectionPtr->Close();

		//��¼��ĸ���
		table_count = table_number;

		return true;
	}
	catch (...)
	{
		
	}
	return false;
}

bool Db_sql::get_table_column_name(TCHAR *table_name,std::wstring *column_name,int &column_count)
{
	try
	{
		_RecordsetPtr pRecordset; 
		int nCount = 0;

		//��ʼ�򿪱��Ա�õ���Ľṹ           
		pRecordset.CreateInstance(__uuidof(Recordset));   
		pRecordset->Open(table_name, m_pConnectionPtr.GetInterfacePtr(),adOpenDynamic, adLockOptimistic, adCmdTable);   
		//�õ����е��ֶ�
		FieldsPtr fds = pRecordset->GetFields();   

		//�õ��ֶ���Ŀ
		column_count = fds->GetCount();
		//���ζ�ȡ�ֶ�
		for(int i = 0; i < fds->GetCount(); i++)   
		{   
			FieldPtr fd = fds->GetItem(_variant_t(short(i)));   
			if(fd->Value.vt != NULL)   
			{   
				//�ֶε�����fd->GetName() �ֶε����� GetType(fd->GetType()) �ֶδ�Сfd->GetDefinedSize()   
				column_name[i].assign(fd->GetName());
			}
		}   

		pRecordset->Close();   

		return true;
	}
	catch (...)
	{
		
	}
	return false;
}

// �ر����ݿ�
void Db_sql::Close()
{
	try
	{
		if (m_pConnectionPtr->State)
		{
			m_pConnectionPtr->Close();
			m_pConnectionPtr = NULL;
		}
	}
	catch (...)
	{
	}
	return;
}

// ������ݿ�����
bool Db_sql::check_connection()
{
	if (m_pConnectionPtr != NULL)
	{
		return true;
	}
	return Connect();
}

// ִ��SQL���
bool Db_sql::Execute(const TCHAR* sql)
{
	try
	{
		m_pConnectionPtr->Execute(sql, 0, adOptionUnspecified);

		return true;
	}
	catch(_com_error e)///��׽�쳣   
	{
		WriteLog(__FL__, L"����");
	}
	catch(...)
	{

	}

	return false;
}

// ��ѯ
access_record_set_sql* Db_sql::Query(TCHAR* sql)
{	
	try
	{
		_RecordsetPtr m_pRecordset = NULL;	
		m_pRecordset.CreateInstance(__uuidof(Recordset));
	
		m_pRecordset->Open(sql,m_pConnectionPtr.GetInterfacePtr(),adOpenDynamic, adLockOptimistic, adCmdText);
		access_record_set_sql* pRS = new access_record_set_sql(m_pRecordset);

		return pRS;
	}
	catch(_com_error e)///��׽�쳣   
	{   
		WriteLog(__FL__, L"����");
		return NULL;
	}      
}