#ifndef _SQLITE3DBMETHOD_H_
#define _SQLITE3DBMETHOD_H_

#include "sqlite3.h"
#include <string>

using namespace std;

class sqlite3_DB
{
public:
	sqlite3_DB();
	~sqlite3_DB();
	/*
	���ܣ������ݿ⣬�����ھʹ������ݿ�
	������
		file_path�����ݿ���ļ�·��
	����ֵ��
	    true:�ɹ�
		false:ʧ��
	*/
	bool sqlite3_open_DB(const char *file_path);
	/*
	���ܣ��ر����ݿ�
	������
	    NULL
	����ֵ��
	    true:�ɹ�
		false:ʧ��
	*/
	bool sqlite3_close_DB(void);
	/*
	���ܣ�ִ��sql��䣬�����Ǵ�����ɾ����������Լ�¼���ɾ�����е����ݣ�ֻ��ִ�е���sql���
	������
	    sql:sql���
	����ֵ��
	    true���ɹ�
		false��ʧ��
	*/
	bool sqlite3_execute_sql(const char *sql);

	/*
	���ܣ��õ�����
	������
	    sql:sql���
	����ֵ��
	   �ɹ���ʵ�ʵõ�������
	   ʧ�ܣ�-1
	*/
	int sqlite3_row_count(const char *sql);
	
	/*
	���ܣ��������õ�ָ�������Ľ��
	������
		sql:sql���
		select_result:��ѯ�Ľ��
	����ֵ��
	    �ɹ���ʵ�ʵõ�������
		ʧ�ܣ�-1
	*/
	int sqlite3_get_table_data(const char *sql,std::string select_result[]);
	/*
	���ܣ���ʼһ������
	������
	    NULL
	����ֵ��
	    true���ɹ�
		false��ʧ��
	*/
	bool sqlite3_begin_transaction(void);
	/*
	���ܣ�����һ������
	������
	   NULL
   ����ֵ��
       true���ɹ�
	   false��ʧ��
   */
	bool sqlite3_commit_transaction(void);
	/*
	���ܣ��ع�һ������
	������
	    NULL
	����ֵ��
	    true���ɹ�
		false��ʧ��
	*/
	bool sqlite3_rollback_transaction(void);

protected:
	/*
	���ܣ��ص�����,��ĳ�Ա����������Ϊ�ص���������������Ϊstatic
	������
	    argv�������������ݹ�����ָ�룬
	    argc�������ĸ�����
	    value��������ֵ��
	    name�����������ƣ�
    ����ֵ��
	    �Լ�����
	*/
	static int row_callback(void* argv,int argc,char **value,char **name);
private:
	//sqlite3���ݿ�����ľ��
	sqlite3 *sqlite3_handle;
};



#endif