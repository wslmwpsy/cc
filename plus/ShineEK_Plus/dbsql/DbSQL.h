// Db_sql.h
//

#ifndef __DATABASE_SQL__H__
#define __DATABASE_SQL__H__
#include <string>
using namespace std;

// ����ADO֧�ֿ�
#pragma warning(disable: 4146)

#import "C:\Program Files\Common Files\System\ado\msado15.dll" 	\
no_namespace 	\
	rename ("EOF", "adoEOF")


// Access���ݿ�����
class access_record_set_sql
{
public:
	// ���캯��
	explicit access_record_set_sql(_RecordsetPtr pRecordset) : m_pRecordset(pRecordset)
	{
	}
	// ���캯��
	access_record_set_sql::access_record_set_sql() : m_pRecordset(NULL)
	{
	}

	// ��������
	access_record_set_sql::~access_record_set_sql()
	{
		Close();
	}

	// �Ƿ��ѵ�ĩβ
	bool IsEof();

	// ��ȡ��¼��
	int GetRecordCount();

	// ����������һ��¼��
	bool GetNextRecord();

	// ͨ��������ȡ�������
	bool get_item_value_by_index(int index,TCHAR *item_value);
   	 //ͨ���ֶ����õ�ֵ
	CString  GetRecordData(TCHAR* Name);
	//�õ�ĳ���ֶ�ռ�õ��ֽ���
    long GetRecordDataLeng(TCHAR* Name);
	//��ȡ�ֶ�����
	int GetFieldCount(){return m_pRecordset->GetFields()->Count;};
	//��ȡ�ֶ���
	TCHAR* GetFieldName(int index){_variant_t vt((long)index);return m_pRecordset->GetFields()->Item[vt]->Name;};

	//Open
	
	//�ƶ���¼��ָ��
	void MoveFirst();
	void Move(int n);
	void MoveNext();
	void MoveLast();

	// �رռ�¼��
	void Close()
	{
		m_pRecordset->Close();
		m_pRecordset = NULL;
	}
public:
	_RecordsetPtr m_pRecordset;	// �����
	_variant_t	varBLOB;
};

//////////////////////////////////////////////////////////////////////////
// sql���ݿ���
class Db_sql
{
public:
	// �������������
	Db_sql();

	// �������ݿ�
	bool Connect(void);
	bool Connect(const TCHAR* server_ip,const TCHAR* user_name,const TCHAR* user_pwd,const TCHAR* sql_name);

	/*
	���ܣ��õ����ݿ������б������
	������
	   all_table_name�����б������
	   table_count����ĸ���
   ����ֵ��
       true���ɹ�
	   false��ʧ��
	*/
	bool get_all_table_name(std::wstring *all_table_name,int &table_count);

	/*
	���ܣ��õ�ָ���������
	������
	    table_name���������
		column_count������
	����ֵ��
	    true���ɹ�
		false��ʧ��
	*/
	bool get_table_column_name(TCHAR *table_name,std::wstring *column_name,int &column_count);

	// �ر����ݿ�
	void Close();
	
	// ������ݿ�����
	bool check_connection();

	// ִ��SQL���
	bool Execute(const TCHAR* sql);

	// ����ת��
	_ConnectionPtr handle() { return m_pConnectionPtr; }

	// ��ѯ
	access_record_set_sql* Query(TCHAR* sql);

protected:
	_ConnectionPtr	m_pConnectionPtr;	// ���ݿ����ӣ�ADO���ӣ�
};


#endif //__DATABASE_ACCESS__H__
