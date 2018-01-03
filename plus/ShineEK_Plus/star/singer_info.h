#pragma once


#include <string>
using namespace std;


class singer_info
{
public:
	singer_info(void);
	~singer_info(void);
	//赋值
	bool set_singer_name(const TCHAR *value);
	bool set_singer_region(const TCHAR *value);
	bool set_singer_sex(const TCHAR *value);
	bool set_singer_id(const TCHAR *value);

	//得到属性值
	bool get_singer_name(TCHAR *value);
	bool get_singer_region(TCHAR *value);
	bool get_singer_sex(TCHAR *value);
	bool get_singer_id(TCHAR *value);

	//初始化变量
    void initialized_variables(void);
private:
	TCHAR singer_name[256];            //歌星的名字
	TCHAR singer_region[256];          //歌星的区域
	TCHAR singer_sex[256];             //歌星性别
	TCHAR singer_id[256];              //歌星id
};
