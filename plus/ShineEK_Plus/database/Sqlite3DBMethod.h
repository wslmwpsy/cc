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
	功能：打开数据库，不存在就创建数据库
	参数：
		file_path：数据库的文件路径
	返回值：
	    true:成功
		false:失败
	*/
	bool sqlite3_open_DB(const char *file_path);
	/*
	功能：关闭数据库
	参数：
	    NULL
	返回值：
	    true:成功
		false:失败
	*/
	bool sqlite3_close_DB(void);
	/*
	功能：执行sql语句，可以是创建、删除表和索引以及录入和删除表中的数据，只能执行单条sql语句
	参数：
	    sql:sql语句
	返回值：
	    true：成功
		false：失败
	*/
	bool sqlite3_execute_sql(const char *sql);

	/*
	功能：得到行数
	参数：
	    sql:sql语句
	返回值：
	   成功：实际得到的行数
	   失败：-1
	*/
	int sqlite3_row_count(const char *sql);
	
	/*
	功能：检索表，得到指定行数的结果
	参数：
		sql:sql语句
		select_result:查询的结果
	返回值：
	    成功：实际得到的行数
		失败：-1
	*/
	int sqlite3_get_table_data(const char *sql,std::string select_result[]);
	/*
	功能：开始一个事物
	参数：
	    NULL
	返回值：
	    true：成功
		false：失败
	*/
	bool sqlite3_begin_transaction(void);
	/*
	功能：结束一个事物
	参数：
	   NULL
   返回值：
       true：成功
	   false：失败
   */
	bool sqlite3_commit_transaction(void);
	/*
	功能：回滚一个事物
	参数：
	    NULL
	返回值：
	    true：成功
		false：失败
	*/
	bool sqlite3_rollback_transaction(void);

protected:
	/*
	功能：回调函数,类的成员函数不能作为回调函数。所以声明为static
	参数：
	    argv：主调函数传递过来的指针，
	    argc：变量的个数，
	    value：变量的值，
	    name：变量的名称，
    返回值：
	    自己定义
	*/
	static int row_callback(void* argv,int argc,char **value,char **name);
private:
	//sqlite3数据库操作的句柄
	sqlite3 *sqlite3_handle;
};



#endif