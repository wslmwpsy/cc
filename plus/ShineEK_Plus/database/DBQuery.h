#ifndef _DBOPERATE_H_
#define _DBOPERATE_H_

#include "DBDataTypeDef.h"
#include "Sqlite3DBMethod.h"
#include "..\message.h"
#include "..\flash\PageData.h"

//预搜索的记录数
#define PRESEARCH_RECORD_COUNT    30

typedef struct 
{
	char sql[256];    //sql语句
	int row;          //行数
}DB_RECORD_COUNT;

class DB_Query
{
public:
	DB_Query();
	~DB_Query();
	/*
	功能：打开数据库
	参数：
	    file_path:数据库文件的路径
	返回值：
	    true:成功
		false：失败
	*/
	bool open_DB(const TCHAR *file_path,bool presearch_song);
	/*
	功能：关闭数据库
	参数：
	    NULL
	返回值：
	    true：成功
		false：失败
	*/
	bool close_DB(void);
	/*
	功能：得到符合条件的行数
	参数：
		result_columns:结果列
		select_condition:选择条件
		condition_number:查询条件的数目
		page_show_row_count：每页显示的行数
	返回值：
	    成功：行数
		失败：-1
	*/
	int get_row_count(const TCHAR *result_columns,query_condition select_condition[],int condition_number,int page_show_row_count);
	int get_row_count(char *sql);

	/*
	功能：判断符合条件的结果是否存在
	参数：
		result_columns:结果列
		select_condition:选择条件
	返回值：
		true：存在
		false：不存在
	*/
	bool table_data_existence(const TCHAR *result_columns,TCHAR *select_condition);

	/*
	功能：执行不需要分返回结果的sql语句，不如创建表索引等
	参数：
	    sql:sql语句
	返回值：
	    true：成功
		false：失败
	*/
	bool exec_sql(TCHAR *sql);

	/*
	功能：删除无用表的数据
	参数：
	    void
	返回值：
	   void
	*/
	void delete_table_data(void);

	/*
	功能：创建保存录音歌曲的表
	参数：
	   void
   返回值：
       void
	*/
	void create_recorder_song_table(void);

	/*
	功能：得到一定行数的结果表
	参数：
		select_result:返回的结果，按照行顺序存储的，既先存储第一行数据，在存储第二行，一次类推
		column_number:查询结果的列数
		result_columns:结果列
		select_condition:选择条件
		condition_number:查询条件的数目
		group_item：分组字段
		order_item:排序字段和排序模式
		screen_show_page_count:屏幕需要的页数
		page_operate：偏移量
		page_show_row_count：每页显示的行数
	返回值
	    成功：实际得到的行数
		失败：-1
	*/
	int get_table_data(std::wstring select_result[],int column_num,const TCHAR *result_columns, query_condition select_condition[],int condition_number,TCHAR *group_item,TCHAR *order_item,int screen_show_page_count,int page_operate,int page_show_row_count);
	int get_table_data(std::wstring select_result[],int column_num,const TCHAR *result_columns, TCHAR *select_condition,TCHAR *group_item,TCHAR *order_item,TCHAR *sort_mode,int limit_row,int offset);
	/*
	功能：得到一定行数的结果表
	参数：
		select_result:返回的结果，按照行顺序存储的，既先存储第一行数据，在存储第二行，一次类推
		select_result_offset:结果从什么位置开始存放，由于涉及到了两次查询
		column_number:查询结果的列数
		result_columns:结果列
		select_condition:选择条件
		condition_number:查询条件的数目
		group_item：分组字段
		order_item:排序字段和排序模式
		limit_row：限制的行数
		offset：偏移
	返回值
		成功：实际得到的行数
		失败：-1
	*/
	int query_db_get_table_data(std::wstring select_result[],int select_result_offset,int column_num,const TCHAR *result_columns, query_condition select_condition[],int condition_number,TCHAR *group_item,TCHAR *order_item,int limit_row,int offset);
	int query_db_get_table_data(std::wstring select_result[],const TCHAR *result_columns, query_condition select_condition[],int condition_number,int array_size,int limit_row,int offset);
	int query_db_get_table_data(std::wstring select_result[],int array_size,char *sql);

	/*
	功能：开始一个事物
	参数：
		NULL
	返回值：
		true：成功
		false：失败
	*/
	bool begin_transaction(void);
	/*
	功能：结束一个事物
	参数：
		NULL
	返回值：
		true：成功
		false：失败
	*/
	bool commit_transaction(void);
	/*
	功能：回滚一个事物
	参数：
		NULL
	返回值：
		true：成功
		false：失败
	*/
	bool rollback_transaction(void);
	
	/*
	功能：清空所有的条件
	参数：
		select_condition:选择条件
		condition_number:查询条件的数目
	 返回值：
	     true：成功
		 false：失败
	*/
	bool clear_all_conditon(query_condition select_condition[],int condition_number);

	/*
	功能：返回当前页数
	参数：
	    NULL
	返回值：
	    当前页数
	*/
	int get_cur_page_number(void);
	/*
	功能：改变当前页的页码
	参数：
	    scroll_direction：滑动的方向
		page_count：要改变的页数
	返回值：
	   true：成功
	   false：失败
	*/
	bool change_cur_page_number(enum QUICK_SCROLL_DIRECTION scroll_direction,int page_count);

	/*
	功能：设置当前页面
	参数：
	    page_index：当前页码
	返回值：
	    true：成功
		false：失败
	*/
	bool set_cur_page_number(int page_index);

	/*
	功能：得到总的页数
	参数：
	    NULL
	返回值：
	    当前页数
	*/
	int get_total_page_count(void);
	/*
	功能：得到总的行数
	参数：
		NULL
	返回值：
		当前页数
	*/
	int get_total_row_count(void);

	/*
	功能：改变总的行数
	参数：
	    change_row：改变的行数。正数表示加，负数表示减
		page_show_row_count：每页显示的行数
	返回值：
	    总的行数
	*/
	int change_total_row(int change_row,int page_show_row_count);

	/*
	功能：进入下一页时，保存一些必要数据，用于返回
	参数：
	返回值：
		true：成功
		false:失败
	*/
	bool save_data_copy(int page_index);

	/*
	功能：返回时，把保存的副本赋值回来
	参数：
	返回值：
		true：成功
		false：失败
	*/
	bool resume_data_copy(int page_index);
protected:
	/*
	功能：产生sql语句
	参数：
	    sql:返回的sql语句
	    result_columns:结果列
		select_condition:选择条件
		condition_number:查询条件的数目
		group_item：分组字段
		order_item:排序字段和排序模式
		limit_row:查询出来的最大行数，负值：没有限制
		offset:偏移,从0开始
	*/
	bool make_sql(char *sql,const TCHAR *result_columns, query_condition select_condition[],int condition_number,TCHAR *group_item,TCHAR *order_item,int limit_row,int offset);
	bool make_sql(char *sql,const TCHAR *result_columns, TCHAR *select_condition,TCHAR *group_item,TCHAR *order_item,TCHAR *sort_mode,int limit_row,int offset,bool select_picture);

	/*
	功能：预查询行数
	参数：
	    suffix：下标
	返回值：
	    true：成功
		false：失败
	*/
	bool presearch_song_record_count(int suffix);
	bool presearch_singer_record_count(int suffix);
private:
	sqlite3_DB sqlite3_database;
	int m_row_count;
	int m_page_count;
	int m_cur_page_number;
	//副本
	int m_row_count_copy[PAGE_MAX_NUMBER];
	int m_page_count_copy[PAGE_MAX_NUMBER];
	int m_cur_page_number_copy[PAGE_MAX_NUMBER];

	//预查询记录数
	DB_RECORD_COUNT m_presearch_record_count[PRESEARCH_RECORD_COUNT];

};


#endif