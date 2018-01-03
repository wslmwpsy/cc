#include "stdafx.h"
#include "query_film_manager.h"
#define DEFALUT_IMAGE L"/电影/img/default.jpg"
#include <vector>

query_film_manager::query_film_manager()
{
	Init(NULL);
}

query_film_manager::~query_film_manager()
{
	
}

void query_film_manager::Init(Db_sql *connect)
{
	m_mssql				= connect;
	m_encodation_type		= ALL_TYPE;
	m_encodation_country	= ALL_COUNTRY;
	m_encodation_orderby	= DATETIME;
	m_strcodation_keyword	= L"";
	m_npage_index			= 0;
	m_szWhere[0]			= '\0';
	m_strfilm_id_current		= L"";
}
bool query_film_manager::get_film(std::wstring &out_xml)
{
	out_xml = L""; 
	if(m_mssql == NULL)return false;

	MakeWhereSql();

	//生成orderby
	TCHAR szOrderBy[1024] = {0};
	if(m_encodation_orderby == NAME)
		swprintf(szOrderBy,L"film_name");
	else if(m_encodation_orderby == SCORE)
		swprintf(szOrderBy,L"film_total_score desc");
	else if(m_encodation_orderby == DATETIME)
		swprintf(szOrderBy,L"film_datetime desc");

	//开始查询
	TCHAR szTmp[10240]={'\0'};
	TCHAR szSql[10240]={'\0'};
	int start_row = m_npage_index*FILM_PAGE_ROW_COUNT - FILM_PAGE_ROW_COUNT + 1;
	int end_row = start_row + FILM_PAGE_ROW_COUNT*3;
	swprintf(szTmp,10240,L"select row_number() over(order by %s) as row,* from film_list %s",szOrderBy,m_szWhere);
	swprintf(szSql,10240,L"select * from(%s) as t where t.row>= %d and t.row<%d",szTmp,start_row,end_row);
	access_record_set_sql *record_set_movies = m_mssql->Query(szSql);
	if (record_set_movies == NULL)
		return false;

	//上一页标签封闭处理
	int index = 0;
	if(start_row < 0)
	{
		MakeMoviesXml(out_xml,NULL,0);
		MakeMoviesXml(out_xml,NULL,FILM_PAGE_ROW_COUNT-1);
		index = FILM_PAGE_ROW_COUNT;
	}

	//遍历结果
	record_set_movies->MoveFirst();
	while(!record_set_movies->IsEof())
	{
		MakeMoviesXml(out_xml,record_set_movies,index++);
		record_set_movies->MoveNext();
	}
	delete record_set_movies;
	record_set_movies = NULL;

	//xml封闭标签处理
	while(index < FILM_PAGE_ROW_COUNT*3)
	{
		MakeMoviesXml(out_xml,NULL,index++);
	}
	return true;
}

void query_film_manager::append_condition_sql(TCHAR *szBuffer,TCHAR *sql,const TCHAR* condition)
{
	if(szBuffer == NULL)return;
	if(condition == NULL)return;
	if(szBuffer[0] == '\0')
	{
		wcscat(szBuffer,L"where ");
	}
	else
	{
		wcscat(szBuffer,L" ");
		wcscat(szBuffer,condition);
		wcscat(szBuffer,L" ");
	}
	wcscat(szBuffer,sql);
}

//生成sql条件
void query_film_manager::MakeWhereSql()
{
	TCHAR szTmp[1024] = {0};

	//生成where
	m_szWhere[0] = '\0';
	if(m_encodation_country > 0)
	{
		swprintf(szTmp,L"film_country=%d",m_encodation_country);
		append_condition_sql(m_szWhere,szTmp,L"and");
	}
	if(m_encodation_type > 0)
	{
		swprintf(szTmp,L"film_type&%d>0",m_encodation_type);
		append_condition_sql(m_szWhere,szTmp,L"and");
	}
	if(!m_strcodation_keyword.empty())
	{
		swprintf(szTmp,L"film_name_spell like '%s%%'",m_strcodation_keyword.c_str());
		append_condition_sql(m_szWhere,szTmp,L"and");
	}
}

void query_film_manager::MakeMoviesXml(std::wstring &xml,access_record_set_sql *record,int row_index)
{
	TCHAR szTmpValue[30000] = {0};
	TCHAR szBuffer[1024*10] = {0};
	std::wstring tmp;

	if(row_index == 0)xml.append(L"<pre_list>");
	if(row_index == FILM_PAGE_ROW_COUNT)xml.append(L"<cur_list>");
	if(row_index == FILM_PAGE_ROW_COUNT*2)xml.append(L"<next_list>");

	if(record)
	{
		xml.append(L"<item ");
		int field_count = record->GetFieldCount();
		for(int i=0;i<field_count;i++)
		{
			TCHAR* szFieldName = record->GetFieldName(i);
			if(wcscmp(szFieldName,L"file_introduction")==0)
				continue;

			xml.append(szFieldName);
			xml.append(L"=\"");

			CString val = read_field(record,szFieldName);

			//下列字段需特殊处理
			if(wcscmp(szFieldName,L"film_poster")==0
				|| wcscmp(szFieldName,L"film_poster_small")==0)
			{
				val = read_field(record,L"server_path1") + val;
			}

			xml.append(val);
			xml.append(L"\" ");
		}
		xml.append(L"/>");
	}

	if(row_index == FILM_PAGE_ROW_COUNT-1)xml.append(L"</pre_list>");
	if(row_index == FILM_PAGE_ROW_COUNT*2-1)xml.append(L"</cur_list>");
	if(row_index == FILM_PAGE_ROW_COUNT*3-1)xml.append(L"</next_list>");
}
//电影详情
bool query_film_manager::get_film_detail(std::wstring &xml)
{
	xml = L"";

	//开始查询
	TCHAR szSql[10240]={'\0'};
	swprintf(szSql,10240,L"select * from film_list where film_id='%s'",m_strfilm_id_current.c_str());
	access_record_set_sql *record = m_mssql->Query(szSql);
	if (record == NULL)
		return false;

	//生成xml
	xml = L"<item ";
	int field_count = record->GetFieldCount();
	for(int i=0;i<field_count;i++)
	{
		TCHAR* szFieldName = record->GetFieldName(i);
		xml.append(szFieldName);
		xml.append(L"=\"");

		CString val = read_field(record,szFieldName);

		//下列字段需特殊处理
		if(wcscmp(szFieldName,L"film_poster")==0
			|| wcscmp(szFieldName,L"film_poster_small")==0)
		{
			val = read_field(record,L"server_path1") + val;
		}
		else if(wcscmp(szFieldName,L"film_country")==0)
		{
			val = FilmCountryToString((FILM_COUNTRY)_wtoi(val));
		}
		else if(wcscmp(szFieldName,L"film_type")==0)
		{
			val = FilmTypeToString((FILM_TYPE)_wtoi(val));
		}
		else if(wcscmp(szFieldName,L"film_actor_list")==0)
		{
			std::vector<CString> item_vec;
			item_vec.clear();
			CString strlastVal = val;
			CString strVal = val;
			while(strVal != L"")
			{
				int nPos = val.Find(L";");
				CString strActorItem = strVal.Left(nPos);
				int nItemPos = strActorItem.Find(L":");
				item_vec.push_back(strActorItem.Left(nItemPos));
				strVal = strVal.Mid(nPos + 1);
			}

			val = L"";
			
			for (int i = 0; i < item_vec.size(); i++)
			{
				val += item_vec[i] + L",";
			}
			val.TrimRight(L",");

			val = ActorToString(val);
			
			/*
			//替换饰演
			val += L",";
			CString str;
			while(val != L"")
			{
				int nPos = val.Find(L",");
				str = val.Left(nPos);
			}
			*/
			val.Replace(L",", L" / ");
		}else if (wcscmp(szFieldName,L"film_director")==0)
		{
			val.Replace(L";", L",");
			val.TrimRight(L",");
			
			val = ActorToString(val);

			val.Replace(L",", L" / ");
		}

		xml.append(val);
		xml.append(L"\" ");
	}

	xml.append(L" />");
	return true;
}
//返回页码总数
bool query_film_manager::get_film_count(int &count,int &page)
{
	count = 0;page = 0;
	if(m_mssql == NULL)return false;

	MakeWhereSql();

	//开始查询
	TCHAR szSql[10240]={'\0'};
	swprintf(szSql,10240,L"select count(*) from film_list %s",m_szWhere);
	access_record_set_sql *record_set_movies = m_mssql->Query(szSql);
	if (record_set_movies == NULL)
		return false;

	szSql[0] = '\0';
	if(!record_set_movies->get_item_value_by_index(0,szSql))
		return false;

	count = _wtoi(szSql);

	page = count / FILM_PAGE_ROW_COUNT;
	if(count % FILM_PAGE_ROW_COUNT > 0)
		page++;

	return true;
}

//读取字段
CString query_film_manager::read_field(access_record_set_sql *record,TCHAR* szFieldName)
{
	CString val = record->GetRecordData(szFieldName);

	//替换特殊字符
	val.Replace(L"&",L"");
	val.Replace(L"\"",L"'");
	val.Replace(L"<",L"《");
	val.Replace(L">",L"》");

	return val;
}

//电影类型转换字符串
CString query_film_manager::FilmTypeToString(FILM_TYPE type)
{
	CString str;
	if(type & AIQING)str+=L"爱情/";
	else if(type & XIJU)str+=L"喜剧/";
	else if(type & DONGZUO)str+=L"动作/";
	else if(type & KONGBU)str+=L"恐怖/";
	else if(type & LUNLI)str+=L"伦理/";
	else if(type & XUANYI)str+=L"悬疑/";
	else if(type & KEHUAN)str+=L"科幻/";
	else if(type & FANZUI)str+=L"犯罪/";
	
	if(str == L"")return L"其它";
	return str.Left(str.GetLength()-1);
}
//电影地区转换字符串
CString query_film_manager::FilmCountryToString(FILM_COUNTRY type)
{
	if(type == NEIDI)return L"内地";
	else if(type == XIANGGANG)return L"香港";
	else if(type == TAIWAN)return L"台湾";
	else if(type == MEIGUO)return L"美国";
	else if(type == OUZHOU)return L"欧洲";
	else if(type == HANGUO)return L"韩国";
	else if(type == RIBEN)return L"日本";
	else if(type == TAIGUO)return L"泰国";
	return L"其它";
}
//演员id转换字符串
CString query_film_manager::ActorToString(CString actor)
{
	//开始查询
	TCHAR szSql[10240]={'\0'};
	swprintf(szSql,10240,L"select * from film_actor where actor_id in(%s)",actor);
	access_record_set_sql *record = m_mssql->Query(szSql);
	if (record == NULL)
		return L"";

	CString str;

	//遍历结果
	record->MoveFirst();
	while(!record->IsEof())
	{
		str += record->GetRecordData(L"actor_name")+L",";
		record->MoveNext();
	}
	delete record;
	record = NULL;

	if(str == L"")return L"未知";
	return str.Left(str.GetLength()-1);

	return str;
}

//返回电影信息
access_record_set_sql * query_film_manager::get_film_by_id(const TCHAR* film_id)
{
	TCHAR szSql[10240]={'\0'};
	swprintf(szSql,10240,L"select * from film_list where film_id='%s'",film_id);
	return m_mssql->Query(szSql);
}

//电影好评
bool query_film_manager::PraiseFile(void)
{
	if (m_strfilm_id_current.length() == 0)	return false;
	
	TCHAR szSql[1024]={'\0'};

	swprintf(szSql,10240, L"update film_list set film_total_score = film_total_score+1 where film_id = '%s'", m_strfilm_id_current.c_str());

	if( !m_mssql->Execute(szSql) )	return false;
	
	return true;
}

//电影播放次数
bool query_film_manager::PlayCount(void)
{
	if (m_strfilm_id_current.length() == 0)
		return false;

	TCHAR szSql[1024]={'\0'};

	swprintf(szSql,10240, L"update film_list set film_rank = film_rank+1 where film_id = '%s'",m_strfilm_id_current.c_str());

	if (!m_mssql->Execute(szSql)) return false;

	return true;
}