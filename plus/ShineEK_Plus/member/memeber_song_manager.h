#pragma once
#include "../message.h"


#include <string>
using namespace std;

//会员管理
class memeber_song_manager
{
public:
	memeber_song_manager(void);
	~memeber_song_manager(void);

	//初始化变量
	void initialized_variables(void);

	MEMBER_FLAG get_login_flags();  //得到会员登录标志
	bool get_user_name(TCHAR* value);
	bool get_user_password(TCHAR* value);
	bool get_user_sex(TCHAR* value);
	bool get_nick_name(TCHAR* value);
	bool get_user_head(TCHAR* value);
	bool get_user_identitycard(TCHAR* value);
	bool get_member_down_address(TCHAR* value);

	bool set_login_flags(int value);
	bool set_user_name(const TCHAR* value);
	bool set_user_password(const TCHAR* value);
	bool set_user_sex(const TCHAR* value);
	bool set_nick_name(const TCHAR* value);
	bool set_user_head(const TCHAR* value);
	bool set_user_identitycard(const TCHAR* value);

	int get_total_member_count();

	int get_total_member_page();

	int get_current_member_page();
	
	/*
		功能：设置当前页面
		参数：
			page_operate:页面标示
			page_number:设置页面
	*/
	void set_current_member_page(PAGE_OPERATE page_operate/*,int page_number*/);

	/*
		功能：解析会员信息
		参数：
			recv_data:服务器发过来的数据
	*/
	bool parse_member_info(char *recv_data);

	/*
		功能：解析会员歌曲信息
	*/
	bool parse_memeber_song_info(char* recv_data,std::wstring &song_id_list);

	/*
		功能：解析出头像的名称
		参数：
			down_addr:头像的下载地址 
	*/
	bool parse_memeber_head_picture_name(IN TCHAR* down_addr);

private:
 
	MEMBER_FLAG member_flags; //会员标志
	TCHAR user_name[256];  //会员的名字
	TCHAR user_password[256];  //会员密码
	TCHAR user_sex[10];           //性别
	TCHAR nick_name[256];      //用户昵称
	TCHAR user_head[256];     //用户头像
	TCHAR user_identitycard[256];    //会员的唯一id
	TCHAR member_down_address[256];   //会员头像下载地址
	TCHAR m_service_server_ip[256];   //服务器ip
	int m_member_song_total_count;   //会员歌曲总条数
	int m_member_song_total_page;     //会员歌曲总页数
	int m_member_current_page;       //当前页面
};

