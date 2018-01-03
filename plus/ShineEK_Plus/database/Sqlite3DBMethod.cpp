#include "stdafx.h"
#include "Sqlite3DBMethod.h"


sqlite3_DB::sqlite3_DB()
{
	sqlite3_handle = NULL;
}

sqlite3_DB::~sqlite3_DB()
{
	//析构的时候调用一下关闭数据库
	sqlite3_close_DB();
}

bool sqlite3_DB::sqlite3_open_DB(const char *file_path)
{
	try
	{
		//数据库已经打开就不用在打开了
		if (NULL!=sqlite3_handle)
		{
			return true;
		}
		int result = sqlite3_open(file_path,&sqlite3_handle);
		if (SQLITE_OK==result)
		{
			return true;
		}
		return false;
	}
	catch (...)
	{
		
	}
	return false;
}

bool sqlite3_DB::sqlite3_close_DB(void)
{
	try
	{
		if (NULL!=sqlite3_handle)
		{
			int result = sqlite3_close(sqlite3_handle);
			if (SQLITE_OK!=result)
			{
				return false;
			}
			sqlite3_handle = NULL;
		}

		return true;
	}
	catch (...)
	{

	}
	return false;
}

bool sqlite3_DB::sqlite3_execute_sql(const char *sql)
{
	try
	{
		char *error_msg=NULL;
		int result = 0;

		if (NULL==sqlite3_handle)
		{
			return false;
		}
        result = sqlite3_exec(sqlite3_handle,sql,0,0,&error_msg);
		//错误消息目前没有使用
		sqlite3_free(error_msg);
		if (SQLITE_OK==result)
		{
			return true;
		}
		return false;
	}
	catch (...)
	{

	}
	return false;
}

int sqlite3_DB::row_callback(void* argv,int argc,char **value,char **name)
{
	try
	{
		//把得到的行数返回
		sscanf(value[0],"%d",argv);
	}
	catch (...)
	{
		
	}
	return 0;
}

int sqlite3_DB::sqlite3_row_count(const char *sql)
{
	try
	{
		char *error_msg=NULL;
		int result=0;
		int row_count=0;

		if (NULL==sqlite3_handle)
		{
			return -1;
		}
		result = sqlite3_exec(sqlite3_handle,sql,row_callback,&row_count,&error_msg);
		sqlite3_free(error_msg);
		if (SQLITE_OK==result)
		{
			return row_count;
		}
		return -1;
	}
	catch (...)
	{
		
	}
	return -1;
}

int sqlite3_DB::sqlite3_get_table_data(const char *sql,std::string select_result[])
{
	try
	{
		char **get_result=NULL;
		char *error_msg=NULL;
		int row=0;
		int column=0;
		int result=0;
		int suffix=0;

		if (NULL==sqlite3_handle)
		{
			return -1;
		}
        result = sqlite3_get_table(sqlite3_handle,sql,&get_result,&row,&column,&error_msg);
		sqlite3_free(error_msg);
		if (SQLITE_OK==result)
		{
			//执行成功
			for (int i=column;i<(row+1)*column;i++)
			{
				if ((NULL!=get_result[i])&&(0!=strcmp(get_result[i],"")))
				{
					select_result[suffix] = get_result[i];
				}
				suffix++;
			}
			sqlite3_free_table(get_result);
			return row;
		}

		sqlite3_free_table(get_result);
		return -1;
	}
	catch (...)
	{
		
	}
	return -1;
}

bool sqlite3_DB::sqlite3_begin_transaction(void)
{
	return sqlite3_execute_sql("BEGIN TRANSACTION");
}

bool sqlite3_DB::sqlite3_commit_transaction(void)
{
	return sqlite3_execute_sql("COMMIT TRANSACTION");
}

bool sqlite3_DB::sqlite3_rollback_transaction(void)
{
    return sqlite3_execute_sql("ROLLBACK TRANSACTION");
}