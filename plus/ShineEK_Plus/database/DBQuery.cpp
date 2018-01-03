#include "stdafx.h"
#include "DBQuery.h"
#include "..\common\StringCodeConversion.h"

//外部声明
extern select_expr song_select_expr;
extern select_expr singer_select_expr;
extern query_condition song_query_condition[SONG_CONDITION_NUMS];
extern query_condition singer_query_condition[SINGER_CONDITION_NUMS];

DB_Query::DB_Query()
{
	m_row_count=0;
	m_page_count=0;
	m_cur_page_number=0;
	for(int i=0;i<PAGE_MAX_NUMBER;i++)
	{
		m_row_count_copy[i]=0;
		m_page_count_copy[i]=0;
		m_cur_page_number_copy[i]=0;
	}
}

DB_Query::~DB_Query()
{

}

bool DB_Query::open_DB(const TCHAR *file_path,bool presearch_song)
{
	bool result=false;
	string_conversion str_conv;
	char path[256];

	memset(path,0x0,sizeof(path));

	//unicode转化成utf-8字符串
	result = str_conv.widechar_to_utf8(file_path,path,sizeof(path));
	if (!result)
	{
		return false;
	}
	//打开数据库
	result = sqlite3_database.sqlite3_open_DB(path);
	if (result && presearch_song)
	{
		//预查询记录数
		for(int i=0;i<PRESEARCH_RECORD_COUNT;i++)
		{
			memset(&m_presearch_record_count[i],0x0,sizeof(DB_RECORD_COUNT));
		}

		//预查询歌曲总行数
		presearch_song_record_count(0);
		//不允许播放DJ
		clear_all_conditon(song_query_condition,SONG_CONDITION_NUMS);
		song_query_condition[SONG_THEME_SUFFIX].operation_symbols = L"!=\"";
		song_query_condition[SONG_THEME_SUFFIX].expression = L"1";
		song_query_condition[SONG_THEME_SUFFIX].wildcard = L"\"";
		presearch_song_record_count(1);
		//戏剧
		clear_all_conditon(song_query_condition,SONG_CONDITION_NUMS);
		song_query_condition[SONG_THEME_SUFFIX].operation_symbols = L"=\'";
		song_query_condition[SONG_THEME_SUFFIX].expression = L"29";
		song_query_condition[SONG_THEME_SUFFIX].wildcard = L"\'";
		presearch_song_record_count(2);
		//新歌
		clear_all_conditon(song_query_condition,SONG_CONDITION_NUMS);
		song_query_condition[SONG_THEME_SUFFIX].operation_symbols = L"!=\"";
		song_query_condition[SONG_THEME_SUFFIX].expression = L"1";
		song_query_condition[SONG_THEME_SUFFIX].wildcard = L"\"";
		song_query_condition[NEW_SONG_DATA_SUFFIX].expression = L"datetime('now','-12 month')";
		presearch_song_record_count(3);
		song_query_condition[NEW_SONG_DATA_SUFFIX].expression = L"datetime('now','-3 month')";
		presearch_song_record_count(4);
		song_query_condition[NEW_SONG_DATA_SUFFIX].expression = L"datetime('now','-1 month')";
		presearch_song_record_count(5);
		//影视金曲
		clear_all_conditon(song_query_condition,SONG_CONDITION_NUMS);
		song_query_condition[SONG_THEME_SUFFIX].operation_symbols = L"=\'";
		song_query_condition[SONG_THEME_SUFFIX].expression = L"32";
		song_query_condition[SONG_THEME_SUFFIX].wildcard = L"\'";
		presearch_song_record_count(6);

		//预查询歌星总行数
		singer_query_condition[SINGER_INTRODUCTION_SUFFIX].expression = L"\"0\"";
		presearch_singer_record_count(20);
		//歌星分类预查询
		singer_query_condition[SINGER_REGION_SUFFIX].column_name = L"singer_region_new";
		singer_query_condition[SINGER_REGION_SUFFIX].operation_symbols = L" = \"";
		singer_query_condition[SINGER_REGION_SUFFIX].expression = L"1";       //华人男星
		singer_query_condition[SINGER_REGION_SUFFIX].wildcard = L"\"";
		presearch_singer_record_count(21);
		singer_query_condition[SINGER_REGION_SUFFIX].expression = L"2";   //华人女星
		presearch_singer_record_count(22);
		singer_query_condition[SINGER_REGION_SUFFIX].expression = L"3"; //
		presearch_singer_record_count(23);
		singer_query_condition[SINGER_REGION_SUFFIX].expression = L"4"; //韩日歌星
		presearch_singer_record_count(24);
		singer_query_condition[SINGER_REGION_SUFFIX].expression = L"5"; //欧美歌星
		presearch_singer_record_count(25);
		singer_query_condition[SINGER_REGION_SUFFIX].expression = L"6";  //外国组合
		presearch_singer_record_count(26);
	}

	return result;
}


bool DB_Query::presearch_song_record_count(int suffix)
{
	try
	{
		bool result=false;
		char sql[1024];

		memset(sql,0x0,sizeof(sql));

		result = make_sql(sql,song_select_expr.row_count_expr.c_str(),song_query_condition,SONG_CONDITION_NUMS,NULL,NULL,-1,0);
		if (result)
		{
			strcpy(m_presearch_record_count[suffix].sql,sql);
			m_presearch_record_count[suffix].row = sqlite3_database.sqlite3_row_count(sql);
		}

		return true;
	}
	catch (...)
	{

	}
	return false;
}


bool DB_Query::presearch_singer_record_count(int suffix)
{
	try
	{
		bool result=false;
		char sql[1024];

		memset(sql,0x0,sizeof(sql));

		result = make_sql(sql,singer_select_expr.row_count_expr.c_str(),singer_query_condition,SINGER_CONDITION_NUMS,NULL,NULL,-1,0);
		if (result)
		{
			strcpy(m_presearch_record_count[suffix].sql,sql);
			m_presearch_record_count[suffix].row = sqlite3_database.sqlite3_row_count(sql);
		}

		return true;
	}
	catch (...)
	{

	}
	return false;
}


bool DB_Query::close_DB(void)
{
	bool result=false;

	result = sqlite3_database.sqlite3_close_DB();

	return result;
}

bool DB_Query::make_sql(char *sql,const TCHAR *result_columns, TCHAR *select_condition,TCHAR *group_item,TCHAR *order_item,TCHAR *sort_mode,int limit_row,int offset,bool select_picture)
{
	try
	{
		TCHAR wsql[2048];
		string_conversion str_conv;
		int byte_size=0;
		TCHAR limit_offset[64];
		bool result=false;

		memset(wsql,0x0,sizeof(wsql));

		//组织sql语句
		_tcscpy(wsql,result_columns);
		if (select_condition)
		{
			_tcscat(wsql,L" WHERE ");
			_tcscat(wsql,select_condition);
		}
		//分组
		if (group_item)
		{
			_tcscat(wsql,L" GROUP BY ");
			_tcscat(wsql,group_item);
		}
		//排序
		if (order_item)
		{
			_tcscat(wsql,L" ORDER BY ");
			_tcscat(wsql,order_item);
			_tcscat(wsql,L" ");
			_tcscat(wsql,sort_mode);
		}
		//限制的行数和偏移
		memset(limit_offset,0x0,sizeof(limit_offset));
		swprintf(limit_offset,L" limit %d offset %d",limit_row,offset);
		wcscat(wsql,limit_offset);


		byte_size = str_conv.get_byte_size_of_utf8(wsql);
		if (byte_size>0)
		{
			result = str_conv.widechar_to_utf8(wsql,sql,byte_size);
		}

		return result;
	}
	catch (...)
	{

	}
	return false;
} 

bool DB_Query::make_sql(char *sql,const TCHAR *result_columns, query_condition select_condition[],int condition_number,TCHAR *group_item,TCHAR *order_item,int limit_row,int offset)
{
	try
	{
		if ((NULL==sql) || (NULL==result_columns))
		{
			return false;
		}
		TCHAR condition[10240];
		bool first_condition=true;
		TCHAR limit_offset[64];
		string_conversion str_conv;
		int byte_size=0;
		bool result=false;
		TCHAR wsql[10240];

		memset(wsql,0x0,sizeof(wsql));

		memset(condition,0x0,sizeof(condition));
		//开始组织sql语句
		//选择列
		wcscat(wsql,result_columns);
		//条件
		for (int i=0;i<condition_number;i++)
		{
			//如果不是空就添加条件
			if (0!=wcscmp(select_condition[i].expression.c_str(),L""))
			{
				if (first_condition)
				{
					//第一个条件增加where关键字
					wcscat(wsql,L" where ");
					first_condition = false;
				}
				else
				{
					wcscat(wsql,L" and ");
				}
				if (0==wcscmp(select_condition[i].expression.c_str(),L"singer_id"))
				{
					memset(condition,0x0,sizeof(condition));
					swprintf(condition,L" (%s %s%s%s)",select_condition[i].column_name.c_str(),select_condition[i].operation_symbols.c_str(),L"",select_condition[i].wildcard.c_str());
					wcscat(wsql,condition);
				}else{
					memset(condition,0x0,sizeof(condition));
					swprintf(condition,L" (%s %s%s%s)",select_condition[i].column_name.c_str(),select_condition[i].operation_symbols.c_str(),select_condition[i].expression.c_str(),select_condition[i].wildcard.c_str());
					wcscat(wsql,condition);
				}
			}
		}
		//分组
		if (group_item)
		{
			wcscat(wsql,L" group by ");
			wcscat(wsql,group_item);
		}
		//排序
		if (order_item && (0!=_tcscmp(order_item,L"")))
		{
			wcscat(wsql,L" order by ");
			wcscat(wsql,order_item);
		}
		//限制的行数和偏移
		memset(limit_offset,0x0,sizeof(limit_offset));
		swprintf(limit_offset,L" limit %d offset %d",limit_row,offset);
		wcscat(wsql,limit_offset);

		//得到做字节占用的字节数
		byte_size = str_conv.get_byte_size_of_utf8(wsql);
		if (byte_size<=0)
		{
			return false;
		}
		//unicode转化成多字节字符串
		result = str_conv.widechar_to_utf8(wsql,sql,byte_size);
		if (!result)
		{
			return false;
		}

		return true;
	}
	catch (...)
	{
		
	}
	return false;
}

int DB_Query::get_row_count(const TCHAR *result_columns,query_condition select_condition[],int condition_number,int page_show_row_count)
{
	try
	{
		char sql[10240];
		bool result=false;
		int row_count=0;
		int page_count=0;

		memset(sql,0x0,sizeof(sql));

		result = make_sql(sql,result_columns,select_condition,condition_number,NULL,NULL,-1,0);
		if (!result)
		{
			return -1;
		}
		row_count = sqlite3_database.sqlite3_row_count(sql);
		//记录行数
		m_row_count= row_count;

		page_count = row_count/page_show_row_count;
		if (0!=row_count%page_show_row_count)
		{
			page_count++;
		}
		//记录总页数和当前页数
		m_page_count = page_count;
		if(0==m_page_count)
		{
			m_cur_page_number=0;
		}
		else
		{
			m_cur_page_number = 1;
		}

		//返回行数
		return row_count;
	}
	catch (...)
	{
		
	}
	return -1;
}

int DB_Query::get_row_count(char *sql)
{
	try
	{
		int row_count=0;
		
		//得到行数
		row_count = sqlite3_database.sqlite3_row_count(sql);

		return row_count;
	}
	catch (...)
	{
		
	}
	return -1;
}

bool DB_Query::table_data_existence(const TCHAR *result_columns,TCHAR *select_condition)
{
	try
	{
		TCHAR sql[2048];
		char use_sql[2048];
		bool result=false;
		int row=0;
		string_conversion string_conv;

		memset(sql,0x0,sizeof(sql));
		memset(use_sql,0x0,sizeof(use_sql));

		swprintf(sql,L"%s where %s limit 1 offset 0",result_columns,select_condition);
		string_conv.widechar_to_utf8(sql,use_sql,sizeof(use_sql));
		row = sqlite3_database.sqlite3_row_count(use_sql);
		if (row>0)
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

int DB_Query::get_cur_page_number(void)
{
	return m_cur_page_number;
}

bool DB_Query::change_cur_page_number(enum QUICK_SCROLL_DIRECTION scroll_direction,int page_count)
{
	if (QUICK_SCROLL_RIGHT==scroll_direction)
	{
		//手指向右滑动
		m_cur_page_number += page_count;
		if (m_cur_page_number>m_page_count)
		{
			m_cur_page_number=1;
		}
	}
	else if (QUICK_SCROLL_LEFT==scroll_direction)
	{
		m_cur_page_number -= page_count;
		if (m_cur_page_number<=0)
		{
			m_cur_page_number=m_page_count;
		}
	}
	else
	{
		//错误
	}
	return true;
}

bool DB_Query::set_cur_page_number(int page_index)
{
	if (page_index<=0)
	{
		m_cur_page_number=1;
	}
	else if (page_index>m_page_count)
	{
		m_cur_page_number = m_page_count;
	}
	else
	{
		m_cur_page_number = page_index;
	}

	return true;
}

int DB_Query::get_total_page_count(void)
{
	return m_page_count;
}

int DB_Query::get_total_row_count(void)
{
	return m_row_count;
}

int DB_Query::change_total_row(int change_row,int page_show_row_count)
{
	m_row_count += change_row;
	if (m_row_count<0)
	{
		m_row_count = 0;
	}
	m_page_count = m_row_count/page_show_row_count;
	if (0!=m_row_count%page_show_row_count)
	{
		m_page_count++;
	}
	if (m_cur_page_number>m_page_count)
	{
		m_cur_page_number = m_page_count;
	}
	return m_row_count;
}

bool DB_Query::exec_sql(TCHAR *sql)
{
	try
	{
		char *szsql=NULL;
		int byte_size=0;
		string_conversion str_conv;
		bool result=false;

		//得到做字节占用的字节数
		byte_size = str_conv.get_byte_size_of_utf8(sql);
		if (byte_size<=0)
		{
			return false;
		}
		szsql = new char[byte_size];
		if (NULL==szsql)
		{
			return false;
		}
		//unicode转化成多字节字符串
		result = str_conv.widechar_to_utf8(sql,szsql,byte_size);
		if (!result)
		{
			delete []szsql;
			szsql = NULL;
			return false;
		}

		result = sqlite3_database.sqlite3_execute_sql(szsql);
		if (szsql)
		{
			delete []szsql;
			szsql = NULL;
		}

		return result;
	}
	catch (...)
	{
		
	}
	return false;
}

void DB_Query::delete_table_data(void)
{
	try
	{
		char sql[1024];
		bool result=false;

		memset(sql,0x0,sizeof(sql));

		//删除录音数据
		sprintf(sql,"DELETE FROM song_recorder");
		result = sqlite3_database.sqlite3_execute_sql(sql);
		if (!result)
		{
			//如果失败在执行一次
			result = sqlite3_database.sqlite3_execute_sql(sql);
		}
		//删除已唱歌曲数据
		memset(sql,0x0,sizeof(sql));

		//删除录音数据
		sprintf(sql,"DELETE FROM sing_song");
		result = sqlite3_database.sqlite3_execute_sql(sql);
		if (!result)
		{
			//如果失败在执行一次
			result = sqlite3_database.sqlite3_execute_sql(sql);
		}

	}
	catch (...)
	{
		
	}
	return;
}

void DB_Query::create_recorder_song_table(void)
{
	try
	{
		char sql[1024];
		bool result=false;

		memset(sql,0x0,sizeof(sql));

		sprintf(sql,"CREATE TABLE IF NOT EXISTS  song_recorder(song_id text PRIMARY KEY,song_name text,singer_name text,video_path text,culture_code text,wave_path text,start_time INTEGER,datetime text)");
		result = sqlite3_database.sqlite3_execute_sql(sql);
		if (!result)
		{
			//如果失败在执行一次
			result = sqlite3_database.sqlite3_execute_sql(sql);
		}
	}
	catch (...)
	{
		
	}
	return;
}

int DB_Query::get_table_data(std::wstring select_result[],int column_num,const TCHAR *result_columns, TCHAR *select_condition,TCHAR *group_item,TCHAR *order_item,TCHAR *sort_mode,int limit_row,int offset)
{
	try
	{
		std::string *result_string=NULL;
		string_conversion str_conv;
		bool result=false;
		char sql[2048];
		int row=0;
		int array_size=0;

		memset(sql,0x0,sizeof(sql));

		array_size = column_num*limit_row;
		result_string = new std::string[array_size];
		if (NULL==result_string)
		{
			return -1;
		}
		result =  make_sql(sql,result_columns,select_condition,group_item,order_item,sort_mode,limit_row,offset,true);
		if (!result)
		{
			return -1;
		}
		row = sqlite3_database.sqlite3_get_table_data(sql,result_string);
		if (row>=0)
		{
			TCHAR *temp_conv=NULL;
			int byte_size=0;

			//进行字符串编码装换
			for (int i=0;i<array_size;i++)
			{
				if (0!=strcmp(result_string[i].c_str(),""))
				{
					byte_size = str_conv.get_byte_size_of_widechar_utf8(result_string[i].c_str());
					if (byte_size<=0)
					{
						continue;
					}
					temp_conv =  new TCHAR[byte_size];
					if (temp_conv)
					{
						result = str_conv.utf8_to_widechar(result_string[i].c_str(),temp_conv,byte_size);
						if (result)
						{
							select_result[i] = temp_conv;
						}
						delete []temp_conv;
						temp_conv=NULL;
					}
				}
			}
			delete []result_string;
			result_string=NULL;
			return row;
		}

		delete []result_string;
		result_string=NULL;
		return -1;
	}
	catch (...)
	{

	}
	return -1;
}



int DB_Query::get_table_data(std::wstring select_result[],int column_num,const TCHAR *result_columns, query_condition select_condition[],int condition_number,TCHAR *group_item,TCHAR *order_item,int screen_show_page_count,int page_operate,int page_show_row_count)
{
	try
	{
		int row=0;
		int offset=0;
		int limit_row=0;
		int result_offset=0;

		if (FIRST_PAGE_OPERATE==page_operate)
		{
			m_cur_page_number=1;
			if (m_page_count<=screen_show_page_count)
			{
				//如果总的页数小于flash需要的页数，永远从0开始，既全部取出
				offset = 0;
				limit_row = screen_show_page_count*page_show_row_count;
				row = query_db_get_table_data(select_result,0,column_num,result_columns,select_condition,condition_number,group_item,order_item,limit_row,offset);
			}
			else
			{
				//第一次查询，从最后查询一页，从前面查询两页				
				result_offset=0;
				offset = (m_page_count-1)*page_show_row_count;
				limit_row = page_show_row_count;
				row = query_db_get_table_data(select_result,0,column_num,result_columns,select_condition,condition_number,group_item,order_item,limit_row,offset);

				//再从前面取两页
				result_offset = limit_row*column_num;
				offset = 0;
				limit_row = 2*page_show_row_count;
				row += query_db_get_table_data(select_result,result_offset,column_num,result_columns,select_condition,condition_number,group_item,order_item,limit_row,offset);

			}
		}
		else if (PRE_PAGE_OPERATE==page_operate)
		{
			//向前翻页
			m_cur_page_number--;
			if (m_page_count<=screen_show_page_count)
			{
				//如果总的页数小于flash需要的页数，永远从0开始，既全部取出
				if (m_cur_page_number<1)
				{
					m_cur_page_number = m_page_count;
				}
				offset = 0;
				limit_row = screen_show_page_count*page_show_row_count;
				row = query_db_get_table_data(select_result,0,column_num,result_columns,select_condition,condition_number,group_item,order_item,limit_row,offset);
			}
			else
			{
				//如果大于要显示的页数
				if (1==m_cur_page_number)
				{
					//要显示第一页.从最后取一页，从前面取两页
					//先从后面取一页
					offset = (m_page_count-1)*page_show_row_count;
					limit_row = (screen_show_page_count/2)*page_show_row_count;
					row = query_db_get_table_data(select_result,0,column_num,result_columns,select_condition,condition_number,group_item,order_item,limit_row,offset);

					result_offset = limit_row*column_num;
					//再从前面取一页
					offset = 0;
					limit_row = (screen_show_page_count/2+1)*page_show_row_count;
					row += query_db_get_table_data(select_result,result_offset,column_num,result_columns,select_condition,condition_number,group_item,order_item,limit_row,offset);

				}
				else if (m_cur_page_number<=0)
				{
					//要显示最后一页.从前面取一页，从后面去两页
					m_cur_page_number = m_page_count;
					//先从后面取一页
					offset = (m_page_count-2)*page_show_row_count;
					limit_row = (screen_show_page_count/2+1)*page_show_row_count;
					row = query_db_get_table_data(select_result,0,column_num,result_columns,select_condition,condition_number,group_item,order_item,limit_row,offset);

					result_offset = limit_row*column_num;
					//再从前面取两页
					offset = 0;
					limit_row = (screen_show_page_count/2)*page_show_row_count;
					row += query_db_get_table_data(select_result,result_offset,column_num,result_columns,select_condition,condition_number,group_item,order_item,limit_row,offset);
				}
				else
				{
					offset = (m_cur_page_number-2)*page_show_row_count;
					limit_row = screen_show_page_count*page_show_row_count;
					row = query_db_get_table_data(select_result,0,column_num,result_columns,select_condition,condition_number,group_item,order_item,limit_row,offset);
				}
			}
		}
		else if (NEXT_PAGE_OPERATE==page_operate)
		{
			//向后翻页
			m_cur_page_number++;
			if (m_page_count<=screen_show_page_count)
			{
				//如果总的页数小于flash需要的页数，永远从0开始，既全部取出
				if (m_cur_page_number>m_page_count)
				{
					m_cur_page_number = 1;
				}
				offset = 0;
				limit_row = screen_show_page_count*page_show_row_count;
				row = query_db_get_table_data(select_result,0,column_num,result_columns,select_condition,condition_number,group_item,order_item,limit_row,offset);
			}
			else
			{
				if (m_cur_page_number>m_page_count)
				{
					//要显示第一页.从最后取一页，从前面取两页
					m_cur_page_number=1;
					//先从后面取一页
					offset = (m_page_count-1)*page_show_row_count;
					limit_row = (screen_show_page_count/2)*page_show_row_count;
					row = query_db_get_table_data(select_result,0,column_num,result_columns,select_condition,condition_number,group_item,order_item,limit_row,offset);

					result_offset = limit_row*column_num;
					//再从前面取一页
					offset = 0;
					limit_row = (screen_show_page_count/2+1)*page_show_row_count;
					row += query_db_get_table_data(select_result,result_offset,column_num,result_columns,select_condition,condition_number,group_item,order_item,limit_row,offset);

				}
				else if (m_cur_page_number==m_page_count)
				{
					//要显示最后一页，从后面取两页，从前面取一页
					//先从后面取两页
					offset = (m_page_count-2)*page_show_row_count;
					limit_row = (screen_show_page_count/2+1)*page_show_row_count;
					row = query_db_get_table_data(select_result,0,column_num,result_columns,select_condition,condition_number,group_item,order_item,limit_row,offset);

					result_offset = limit_row*column_num;
					//再从前面取两页
					offset = 0;
					limit_row = (screen_show_page_count/2)*page_show_row_count;
					row += query_db_get_table_data(select_result,result_offset,column_num,result_columns,select_condition,condition_number,group_item,order_item,limit_row,offset);
				}
				else
				{
					if (m_cur_page_number>m_page_count)
					{
						m_cur_page_number=1;
					}
					offset = (m_cur_page_number-2)*page_show_row_count;
					limit_row = screen_show_page_count*page_show_row_count;
					row = query_db_get_table_data(select_result,0,column_num,result_columns,select_condition,condition_number,group_item,order_item,limit_row,offset);
				}
			}
		}
		else if(CUR_PAGE_OPERATE==page_operate)
		{
			//显示当前页
			if (m_page_count<=screen_show_page_count)
			{
				//如果总的页数小于flash需要的页数，永远从0开始，既全部取出
				offset = 0;
				limit_row = screen_show_page_count*page_show_row_count;
				row = query_db_get_table_data(select_result,0,column_num,result_columns,select_condition,condition_number,group_item,order_item,limit_row,offset);
			}
			else
			{
				if (1==m_cur_page_number)
				{
					//要显示第一页.从最后取一页，从前面取两页
					//先从后面取一页
					offset = (m_page_count-1)*page_show_row_count;
					limit_row = (screen_show_page_count/2)*page_show_row_count;
					row = query_db_get_table_data(select_result,0,column_num,result_columns,select_condition,condition_number,group_item,order_item,limit_row,offset);

					result_offset = limit_row*column_num;
					//再从前面取一页
					offset = 0;
					limit_row = (screen_show_page_count/2+1)*page_show_row_count;
					row += query_db_get_table_data(select_result,result_offset,column_num,result_columns,select_condition,condition_number,group_item,order_item,limit_row,offset);

				}
				else if (m_cur_page_number==m_page_count)
				{
					//要显示最后一页，从后面取两页，从前面取一页
					//先从后面取两页
					offset = (m_page_count-2)*page_show_row_count;
					limit_row = (screen_show_page_count/2+1)*page_show_row_count;
					row = query_db_get_table_data(select_result,0,column_num,result_columns,select_condition,condition_number,group_item,order_item,limit_row,offset);

					result_offset = limit_row*column_num;
					//再从前面取两页
					offset = 0;
					limit_row = (screen_show_page_count/2)*page_show_row_count;
					row += query_db_get_table_data(select_result,result_offset,column_num,result_columns,select_condition,condition_number,group_item,order_item,limit_row,offset);
				}
				else
				{
					if (m_cur_page_number>m_page_count)
					{
						m_cur_page_number=1;
					}
					offset = (m_cur_page_number-2)*page_show_row_count;
					limit_row = screen_show_page_count*page_show_row_count;
					row = query_db_get_table_data(select_result,0,column_num,result_columns,select_condition,condition_number,group_item,order_item,limit_row,offset);

				}
			}
		}

		return row;
	}
	catch (...)
	{

	}
	return -1;
}

int DB_Query::query_db_get_table_data(std::wstring select_result[],int select_result_offset,int column_num,const TCHAR *result_columns, query_condition select_condition[],int condition_number,TCHAR *group_item,TCHAR *order_item,int limit_row,int offset)
{
	try
	{
		std::string *result_string=NULL;
		string_conversion str_conv;
		bool result=false;
		char sql[10240];
		int row=0;
		int array_size=0;

		memset(sql,0x0,sizeof(sql));

		result = make_sql(sql,result_columns,select_condition,condition_number,group_item,order_item,limit_row,offset);
		if (!result)
		{
			return -1;
		}
		array_size = column_num*limit_row;
		result_string = new std::string[array_size];
		if (NULL==result_string)
		{
			return -1;
		}
		row = sqlite3_database.sqlite3_get_table_data(sql,result_string);
		if (row>=0)
		{
			TCHAR *temp_conv=NULL;
			int byte_size=0;

			//进行字符串编码装换
			for (int i=0;i<array_size;i++)
			{
				if (0!=strcmp(result_string[i].c_str(),""))
				{
					byte_size = str_conv.get_byte_size_of_widechar_utf8(result_string[i].c_str());
					if (byte_size<=0)
					{
						continue;
					}
					temp_conv =  new TCHAR[byte_size];
					if (temp_conv)
					{
						result = str_conv.utf8_to_widechar(result_string[i].c_str(),temp_conv,byte_size);
						if (result)
						{
							select_result[select_result_offset] = temp_conv;
						}
						delete []temp_conv;
						temp_conv=NULL;
					}
				}

				select_result_offset++;
			}
			delete []result_string;
			result_string=NULL;
			return row;
		}

		delete []result_string;
		result_string=NULL;
		return -1;
	}
	catch (...)
	{
		
	}
	return -1;
}

int DB_Query::query_db_get_table_data(std::wstring select_result[],const TCHAR *result_columns, query_condition select_condition[],int condition_number,int array_size,int limit_row,int offset)
{
	try
	{
		std::string *result_string=NULL;
		string_conversion str_conv;
		bool result=false;
		char sql[10240];
		int row=0;

		memset(sql,0x0,sizeof(sql));

		//根据数据大小限制行数
		result = make_sql(sql,result_columns,select_condition,condition_number,NULL,NULL,limit_row,offset);
		if (!result)
		{
			return -1;
		}

		result_string = new std::string[array_size];
		if (NULL==result_string)
		{
			return -1;
		}
		row = sqlite3_database.sqlite3_get_table_data(sql,result_string);
		if (row>=0)
		{
			TCHAR *temp_conv=NULL;
			int byte_size=0;

			//进行字符串编码装换
			for (int i=0;i<array_size;i++)
			{
				if (0!=strcmp(result_string[i].c_str(),""))
				{
					byte_size = str_conv.get_byte_size_of_widechar_utf8(result_string[i].c_str());
					if (byte_size<=0)
					{
						continue;
					}
					temp_conv =  new TCHAR[byte_size];
					if (temp_conv)
					{
						result = str_conv.utf8_to_widechar(result_string[i].c_str(),temp_conv,byte_size);
						if (result)
						{
							select_result[i] = temp_conv;
						}
						delete []temp_conv;
						temp_conv=NULL;
					}
				}

			}
			delete []result_string;
			result_string=NULL;
			return row;
		}

		delete []result_string;
		result_string=NULL;
		return -1;
	}
	catch (...)
	{

	}
	return -1;
}


int DB_Query::query_db_get_table_data(std::wstring select_result[],int array_size,char *sql)
{
	try
	{
		std::string *result_string=NULL;
		string_conversion str_conv;
		bool result=false;
		int row=0;

		if (NULL==sql)
		{
			return -1;
		}

		result_string = new std::string[array_size];
		if (NULL==result_string)
		{
			return -1;
		}
		row = sqlite3_database.sqlite3_get_table_data(sql,result_string);
		if (row>=0)
		{
			TCHAR *temp_conv=NULL;
			int byte_size=0;

			//进行字符串编码装换
			for (int i=0;i<array_size;i++)
			{
				if (0!=strcmp(result_string[i].c_str(),""))
				{
					byte_size = str_conv.get_byte_size_of_widechar_utf8(result_string[i].c_str());
					if (byte_size<=0)
					{
						continue;
					}
					temp_conv =  new TCHAR[byte_size];
					if (temp_conv)
					{
						result = str_conv.utf8_to_widechar(result_string[i].c_str(),temp_conv,byte_size);
						if (result)
						{
							select_result[i] = temp_conv;
						}
						delete []temp_conv;
						temp_conv=NULL;
					}
				}

			}
			delete []result_string;
			result_string=NULL;
			return row;
		}

		delete []result_string;
		result_string=NULL;
		return -1;
	}
	catch (...)
	{

	}
	return -1;
}

bool DB_Query::begin_transaction(void)
{
	return sqlite3_database.sqlite3_begin_transaction();
}

bool DB_Query::commit_transaction(void)
{
	return sqlite3_database.sqlite3_commit_transaction();
}

bool DB_Query::rollback_transaction(void)
{
	return sqlite3_database.sqlite3_rollback_transaction();
}

bool DB_Query::clear_all_conditon(query_condition select_condition[],int condition_number)
{
	try
	{
		for (int i=0;i<condition_number;i++)
		{
			select_condition[i].expression.clear(); 
		}
		return true;
	}
	catch (...)
	{
		
	}
	return false;
}

bool DB_Query::save_data_copy(int page_index)
{
	m_row_count_copy[page_index] = m_row_count;
	m_page_count_copy[page_index] = m_page_count;
	m_cur_page_number_copy[page_index] = m_cur_page_number;

	return true;
}

bool DB_Query::resume_data_copy(int page_index)
{
	m_row_count=m_row_count_copy[page_index];
	m_page_count=m_page_count_copy[page_index];
	m_cur_page_number=m_cur_page_number_copy[page_index];

	return true;
}