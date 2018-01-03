#ifndef _DBOPERATE_H_
#define _DBOPERATE_H_

#include "DBDataTypeDef.h"
#include "Sqlite3DBMethod.h"
#include "..\message.h"
#include "..\flash\PageData.h"

//Ԥ�����ļ�¼��
#define PRESEARCH_RECORD_COUNT    30

typedef struct 
{
	char sql[256];    //sql���
	int row;          //����
}DB_RECORD_COUNT;

class DB_Query
{
public:
	DB_Query();
	~DB_Query();
	/*
	���ܣ������ݿ�
	������
	    file_path:���ݿ��ļ���·��
	����ֵ��
	    true:�ɹ�
		false��ʧ��
	*/
	bool open_DB(const TCHAR *file_path,bool presearch_song);
	/*
	���ܣ��ر����ݿ�
	������
	    NULL
	����ֵ��
	    true���ɹ�
		false��ʧ��
	*/
	bool close_DB(void);
	/*
	���ܣ��õ���������������
	������
		result_columns:�����
		select_condition:ѡ������
		condition_number:��ѯ��������Ŀ
		page_show_row_count��ÿҳ��ʾ������
	����ֵ��
	    �ɹ�������
		ʧ�ܣ�-1
	*/
	int get_row_count(const TCHAR *result_columns,query_condition select_condition[],int condition_number,int page_show_row_count);
	int get_row_count(char *sql);

	/*
	���ܣ��жϷ��������Ľ���Ƿ����
	������
		result_columns:�����
		select_condition:ѡ������
	����ֵ��
		true������
		false��������
	*/
	bool table_data_existence(const TCHAR *result_columns,TCHAR *select_condition);

	/*
	���ܣ�ִ�в���Ҫ�ַ��ؽ����sql��䣬���紴����������
	������
	    sql:sql���
	����ֵ��
	    true���ɹ�
		false��ʧ��
	*/
	bool exec_sql(TCHAR *sql);

	/*
	���ܣ�ɾ�����ñ������
	������
	    void
	����ֵ��
	   void
	*/
	void delete_table_data(void);

	/*
	���ܣ���������¼�������ı�
	������
	   void
   ����ֵ��
       void
	*/
	void create_recorder_song_table(void);

	/*
	���ܣ��õ�һ�������Ľ����
	������
		select_result:���صĽ����������˳��洢�ģ����ȴ洢��һ�����ݣ��ڴ洢�ڶ��У�һ������
		column_number:��ѯ���������
		result_columns:�����
		select_condition:ѡ������
		condition_number:��ѯ��������Ŀ
		group_item�������ֶ�
		order_item:�����ֶκ�����ģʽ
		screen_show_page_count:��Ļ��Ҫ��ҳ��
		page_operate��ƫ����
		page_show_row_count��ÿҳ��ʾ������
	����ֵ
	    �ɹ���ʵ�ʵõ�������
		ʧ�ܣ�-1
	*/
	int get_table_data(std::wstring select_result[],int column_num,const TCHAR *result_columns, query_condition select_condition[],int condition_number,TCHAR *group_item,TCHAR *order_item,int screen_show_page_count,int page_operate,int page_show_row_count);
	int get_table_data(std::wstring select_result[],int column_num,const TCHAR *result_columns, TCHAR *select_condition,TCHAR *group_item,TCHAR *order_item,TCHAR *sort_mode,int limit_row,int offset);
	/*
	���ܣ��õ�һ�������Ľ����
	������
		select_result:���صĽ����������˳��洢�ģ����ȴ洢��һ�����ݣ��ڴ洢�ڶ��У�һ������
		select_result_offset:�����ʲôλ�ÿ�ʼ��ţ������漰�������β�ѯ
		column_number:��ѯ���������
		result_columns:�����
		select_condition:ѡ������
		condition_number:��ѯ��������Ŀ
		group_item�������ֶ�
		order_item:�����ֶκ�����ģʽ
		limit_row�����Ƶ�����
		offset��ƫ��
	����ֵ
		�ɹ���ʵ�ʵõ�������
		ʧ�ܣ�-1
	*/
	int query_db_get_table_data(std::wstring select_result[],int select_result_offset,int column_num,const TCHAR *result_columns, query_condition select_condition[],int condition_number,TCHAR *group_item,TCHAR *order_item,int limit_row,int offset);
	int query_db_get_table_data(std::wstring select_result[],const TCHAR *result_columns, query_condition select_condition[],int condition_number,int array_size,int limit_row,int offset);
	int query_db_get_table_data(std::wstring select_result[],int array_size,char *sql);

	/*
	���ܣ���ʼһ������
	������
		NULL
	����ֵ��
		true���ɹ�
		false��ʧ��
	*/
	bool begin_transaction(void);
	/*
	���ܣ�����һ������
	������
		NULL
	����ֵ��
		true���ɹ�
		false��ʧ��
	*/
	bool commit_transaction(void);
	/*
	���ܣ��ع�һ������
	������
		NULL
	����ֵ��
		true���ɹ�
		false��ʧ��
	*/
	bool rollback_transaction(void);
	
	/*
	���ܣ�������е�����
	������
		select_condition:ѡ������
		condition_number:��ѯ��������Ŀ
	 ����ֵ��
	     true���ɹ�
		 false��ʧ��
	*/
	bool clear_all_conditon(query_condition select_condition[],int condition_number);

	/*
	���ܣ����ص�ǰҳ��
	������
	    NULL
	����ֵ��
	    ��ǰҳ��
	*/
	int get_cur_page_number(void);
	/*
	���ܣ��ı䵱ǰҳ��ҳ��
	������
	    scroll_direction�������ķ���
		page_count��Ҫ�ı��ҳ��
	����ֵ��
	   true���ɹ�
	   false��ʧ��
	*/
	bool change_cur_page_number(enum QUICK_SCROLL_DIRECTION scroll_direction,int page_count);

	/*
	���ܣ����õ�ǰҳ��
	������
	    page_index����ǰҳ��
	����ֵ��
	    true���ɹ�
		false��ʧ��
	*/
	bool set_cur_page_number(int page_index);

	/*
	���ܣ��õ��ܵ�ҳ��
	������
	    NULL
	����ֵ��
	    ��ǰҳ��
	*/
	int get_total_page_count(void);
	/*
	���ܣ��õ��ܵ�����
	������
		NULL
	����ֵ��
		��ǰҳ��
	*/
	int get_total_row_count(void);

	/*
	���ܣ��ı��ܵ�����
	������
	    change_row���ı��������������ʾ�ӣ�������ʾ��
		page_show_row_count��ÿҳ��ʾ������
	����ֵ��
	    �ܵ�����
	*/
	int change_total_row(int change_row,int page_show_row_count);

	/*
	���ܣ�������һҳʱ������һЩ��Ҫ���ݣ����ڷ���
	������
	����ֵ��
		true���ɹ�
		false:ʧ��
	*/
	bool save_data_copy(int page_index);

	/*
	���ܣ�����ʱ���ѱ���ĸ�����ֵ����
	������
	����ֵ��
		true���ɹ�
		false��ʧ��
	*/
	bool resume_data_copy(int page_index);
protected:
	/*
	���ܣ�����sql���
	������
	    sql:���ص�sql���
	    result_columns:�����
		select_condition:ѡ������
		condition_number:��ѯ��������Ŀ
		group_item�������ֶ�
		order_item:�����ֶκ�����ģʽ
		limit_row:��ѯ�����������������ֵ��û������
		offset:ƫ��,��0��ʼ
	*/
	bool make_sql(char *sql,const TCHAR *result_columns, query_condition select_condition[],int condition_number,TCHAR *group_item,TCHAR *order_item,int limit_row,int offset);
	bool make_sql(char *sql,const TCHAR *result_columns, TCHAR *select_condition,TCHAR *group_item,TCHAR *order_item,TCHAR *sort_mode,int limit_row,int offset,bool select_picture);

	/*
	���ܣ�Ԥ��ѯ����
	������
	    suffix���±�
	����ֵ��
	    true���ɹ�
		false��ʧ��
	*/
	bool presearch_song_record_count(int suffix);
	bool presearch_singer_record_count(int suffix);
private:
	sqlite3_DB sqlite3_database;
	int m_row_count;
	int m_page_count;
	int m_cur_page_number;
	//����
	int m_row_count_copy[PAGE_MAX_NUMBER];
	int m_page_count_copy[PAGE_MAX_NUMBER];
	int m_cur_page_number_copy[PAGE_MAX_NUMBER];

	//Ԥ��ѯ��¼��
	DB_RECORD_COUNT m_presearch_record_count[PRESEARCH_RECORD_COUNT];

};


#endif