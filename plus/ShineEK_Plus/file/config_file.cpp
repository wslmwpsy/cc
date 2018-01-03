#include "stdafx.h"
#include "config_file.h"


config_file_manager::config_file_manager()
{
	init();
};

config_file_manager::~config_file_manager()
{

}

void config_file_manager::init()
{ 
	TCHAR cur_path[MAX_FILE_PATH];

	memset(cur_path,0x0,sizeof(cur_path));

	//得到执行文件路劲
	DWORD len = ::GetModuleFileName(NULL, cur_path, MAX_FILE_PATH);
	//得到执行文件的文件夹路径
	(_tcsrchr(cur_path,'\\'))[0] ='\0';
	//保存路径
	m_exec_file_dir.assign(cur_path);
	//得到配置文件路径
	init(L"Configure.ini");
}

void config_file_manager::init(LPCTSTR lpFile)
{
	memset(m_config_file_path,0x0,sizeof(m_config_file_path));
	swprintf(m_config_file_path,L"%s\\%s",m_exec_file_dir.c_str(),lpFile);
}

std::wstring  config_file_manager::get_exec_file_path()
{
	return m_exec_file_dir;
}

int config_file_manager::read_integer(LPCTSTR szSection, LPCTSTR szKey, int iDefaultValue)
{ 

	int result = GetPrivateProfileInt(szSection,  szKey, iDefaultValue, m_config_file_path); 

	return result;
}

float config_file_manager::read_float(LPCTSTR szSection,LPCTSTR szKey,float fDefaultValue)
{
	TCHAR result[MAX_FILE_PATH];
	TCHAR default_value[MAX_FILE_PATH];
	float ret=0.0;

	memset(result,0x0,sizeof(result));
	memset(default_value,0x0,sizeof(default_value));

	swprintf(default_value,L"%f",fDefaultValue);

	GetPrivateProfileString(szSection,  szKey, default_value, result, MAX_FILE_PATH, m_config_file_path);

	swscanf(result,L"%f",&ret);

	return ret;
}

bool config_file_manager::read_boolean(LPCTSTR szSection, LPCTSTR szKey, bool bolDefaultValue)
{ 
	TCHAR result[MAX_FILE_PATH];
	std::wstring  szDefault(bolDefaultValue ?L"true" : L"false"); 

	memset(result,0x0,sizeof(result));

	GetPrivateProfileString(szSection, szKey, szDefault.c_str(), result, MAX_FILE_PATH, m_config_file_path); 

	bool bResult =  (wcscmp(result, L"True") == 0 || wcscmp(result, L"true") == 0) ? true : false;

	return bResult;
}
std::wstring  config_file_manager::read_string(LPCTSTR szSection, LPCTSTR szKey, LPCTSTR szDefaultValue)
{ 
	TCHAR result[MAX_FILE_PATH];
	std::wstring result_string;
	
	memset(result,0x0,sizeof(result));

	GetPrivateProfileString(szSection,  szKey, szDefaultValue, result, MAX_FILE_PATH, m_config_file_path); 
	result_string.assign(result);

	return result_string;
}
void config_file_manager::write_integer(LPCTSTR szSection, LPCTSTR szKey, int iValue)
{ 
	TCHAR value[MAX_FILE_PATH];

	memset(value,0x0,sizeof(value));

	swprintf(value,L"%d",iValue);

	WritePrivateProfileString(szSection,  szKey, value, m_config_file_path); 
}
void config_file_manager::write_float(LPCTSTR szSection, LPCTSTR szKey, float fltValue)
{ 
	TCHAR value[MAX_FILE_PATH];

	memset(value,0x0,sizeof(value));

	swprintf(value,L"%f",fltValue);
	WritePrivateProfileString(szSection,  szKey, value, m_config_file_path); 
}
void config_file_manager::write_boolean(LPCTSTR szSection, LPCTSTR szKey, bool bolValue)
{ 
	TCHAR value[MAX_FILE_PATH];

	memset(value,0x0,sizeof(value));
	swprintf(value,L"%s", bolValue ? L"true" : L"false");

	WritePrivateProfileString(szSection,  szKey, value, m_config_file_path); 
}
void config_file_manager::write_string(LPCTSTR szSection, LPCTSTR szKey, LPCTSTR szValue)
{ 
	WritePrivateProfileString(szSection,  szKey, szValue, m_config_file_path);
}

