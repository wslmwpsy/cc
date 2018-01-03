#pragma once
#include <string>

using namespace std;

#define MAX_FILE_PATH   1024

class config_file_manager
{
public:
	config_file_manager();
	~config_file_manager();
	void init();
	void init(LPCTSTR lpFile);
	std::wstring  get_exec_file_path();
	int read_integer(LPCTSTR szSection, LPCTSTR szKey, int iDefaultValue);
	float read_float(LPCTSTR szSection,LPCTSTR szKey,float fDefaultValue);
	bool read_boolean(LPCTSTR szSection, LPCTSTR szKey, bool bolDefaultValue);
	std::wstring  read_string(LPCTSTR szSection, LPCTSTR szKey, LPCTSTR szDefaultValue);
	void write_integer(LPCTSTR szSection, LPCTSTR szKey, int iValue);
	void write_float(LPCTSTR szSection, LPCTSTR szKey, float fltValue);
	void write_boolean(LPCTSTR szSection, LPCTSTR szKey, bool bolValue);
	void write_string(LPCTSTR szSection, LPCTSTR szKey, LPCTSTR szValue);

private:
	TCHAR m_config_file_path[MAX_FILE_PATH]; //配置文件路径
	std::wstring  m_exec_file_dir;			//执行文件的文件夹路径
};
