// Db_sql.h
//

#ifndef __DATABASE_SQL__H__
#define __DATABASE_SQL__H__
#include <string>
using namespace std;

// 加入ADO支持库
#pragma warning(disable: 4146)

#import "C:\Program Files\Common Files\System\ado\msado15.dll" 	\
no_namespace 	\
	rename ("EOF", "adoEOF")


// Access数据库结果集
class access_record_set_sql
{
public:
	// 构造函数
	explicit access_record_set_sql(_RecordsetPtr pRecordset) : m_pRecordset(pRecordset)
	{
	}
	// 构造函数
	access_record_set_sql::access_record_set_sql() : m_pRecordset(NULL)
	{
	}

	// 析构函数
	access_record_set_sql::~access_record_set_sql()
	{
		Close();
	}

	// 是否已到末尾
	bool IsEof();

	// 获取记录数
	int GetRecordCount();

	// 保存结果（下一记录）
	bool GetNextRecord();

	// 通过索引获取结果内容
	bool get_item_value_by_index(int index,TCHAR *item_value);
   	 //通过字段名得到值
	CString  GetRecordData(TCHAR* Name);
	//得到某个字段占用的字节数
    long GetRecordDataLeng(TCHAR* Name);
	//获取字段总数
	int GetFieldCount(){return m_pRecordset->GetFields()->Count;};
	//获取字段名
	TCHAR* GetFieldName(int index){_variant_t vt((long)index);return m_pRecordset->GetFields()->Item[vt]->Name;};

	//Open
	
	//移动记录集指针
	void MoveFirst();
	void Move(int n);
	void MoveNext();
	void MoveLast();

	// 关闭记录集
	void Close()
	{
		m_pRecordset->Close();
		m_pRecordset = NULL;
	}
public:
	_RecordsetPtr m_pRecordset;	// 结果集
	_variant_t	varBLOB;
};

//////////////////////////////////////////////////////////////////////////
// sql数据库类
class Db_sql
{
public:
	// 构造和析构函数
	Db_sql();

	// 连接数据库
	bool Connect(void);
	bool Connect(const TCHAR* server_ip,const TCHAR* user_name,const TCHAR* user_pwd,const TCHAR* sql_name);

	/*
	功能：得到数据库中所有表的名字
	参数：
	   all_table_name：所有表的名字
	   table_count：表的个数
   返回值：
       true：成功
	   false：失败
	*/
	bool get_all_table_name(std::wstring *all_table_name,int &table_count);

	/*
	功能：得到指定表的列名
	参数：
	    table_name：表的名字
		column_count：列数
	返回值：
	    true：成功
		false：失败
	*/
	bool get_table_column_name(TCHAR *table_name,std::wstring *column_name,int &column_count);

	// 关闭数据库
	void Close();
	
	// 检查数据库连接
	bool check_connection();

	// 执行SQL语句
	bool Execute(const TCHAR* sql);

	// 类型转换
	_ConnectionPtr handle() { return m_pConnectionPtr; }

	// 查询
	access_record_set_sql* Query(TCHAR* sql);

protected:
	_ConnectionPtr	m_pConnectionPtr;	// 数据库连接（ADO连接）
};


#endif //__DATABASE_ACCESS__H__
