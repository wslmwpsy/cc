#ifndef _HTTP_H_OLD
#define _HTTP_H_OLD

#include "..\song\song_info.h"

typedef struct TAPE_AUDIO_URL
{
	TCHAR song_number[128];
	TCHAR URL[256];
}TAPE_AUDIO_URL_t;


typedef struct USER_INFO
{
	char user_name[64];    //用户名
	char passowrd[64];     //密码
	char type[16];         //登录类型
}USER_INFO_t;

#define TAPE_SONG_MAX_COUNT   200
#define USER_MAX_COUNT        16       //登录的用户最大数

class CHttp_old
{
public:
	CHttp_old(void);
	/*
	功能：初始化
	参数：
	   void
   返回值：
       void
	*/
	void initialize(void);

	/*
	功能：得到URL
	参数：
	　　web_url:发布的mp3外网URL
    返回值：
	    true：成功
		false：失败
	*/
	bool get_url_from_server(TCHAR *song_number,TCHAR *web_url);

	/*
	功能：上传文件到场所中转服务器
	参数：
	   path：文件路径
   返回值：
       true：成功
	   false：失败
	*/
	bool upload_file_to_server(song_info video_info);

	/*
	功能：得到URL和文件名
	参数：
	    song_number：歌曲编号
		URL：分享的网址
		file_name：文件名字
	返回值：
	   true：成功
	   false：失败
	*/
	bool get_web_url(const TCHAR *song_number,TCHAR *URL,TCHAR *file_name);

	/*
	功能：设置URL
	参数：
	    song_number：歌曲编号
	    URL：分享的网址
	返回值：
	    true：成功
		false：失败
	*/
	bool set_web_url(TCHAR *song_number,TCHAR *URL);

	/*
	功能：组织post文件头
	参数：
	    order：组好的文件头
		len：数据长度
		song_name：文件名
		singer_name：歌星名
		tape_time：录制时间
		url：分享网址
	*/
	bool set_post_head(char *order,int len,char *song_name,char *singer_name,char *tape_time,char *url,char *song_id);

	/*
	功能：组织get文件头
	参数：
	    order：组好的文件头
		len：数据长度
		song_name：文件名
		singer_name：歌星名
		tape_time：录制时间
		url：分享网址
	*/
	bool set_get_head(char *order);

	/*
	功能：PCM转mp3
	参数：
	    wav_path：wav文件路径
		mp3_path：mp3文件路径
	返回值：
	    true：成功
		false：失败
	*/
	bool PCM_to_mp3(TCHAR *wave_path,TCHAR *mp3_path);

	/*
	功能：存储用户信息
	参数：
	    user_info：用户信息
	返回值：
	    true：成功
		false：失败
	*/
	bool save_user_info(char *user_info);

	/*
	功能：删除用户信息
	参数：
		user_info：用户信息
	返回值：
		true：成功
		false：失败
	*/
	bool delete_user_info(char *user_info);

	/*
	功能：清空所有用户信息
	参数：
	    void
	返回值：
	    void
	*/
	void clear_user_info(void);

	/*
	功能：得到用户信息
	参数：
	   user_info：用户信息
   返回值：
       true：成功
	   false：失败
	*/
	bool get_user_info(char *user_info);

	/*
	功能：转换空格成%20
	参数：
	     src_str：原始字符串
		 des_str：转换之后的字符串
	返回值：
	    true：成功
		false：失败
	*/
	bool convert_blank_space(char *src_str, char *des_str);

	/*
		功能：设置pc登录数据
		参数：
			date：json信息
			upload_type:类型
	*/
	bool set_current_user_info(const TCHAR* date,int upload_type);
 

public:
	TAPE_AUDIO_URL_t m_share_url[TAPE_SONG_MAX_COUNT];    //存储分享的URL
	char m_server_ip[32];                                 //服务器IP
	int m_server_port;                                    //服务器端口
	USER_INFO_t m_user_info[USER_MAX_COUNT];              //用户信息
	int m_login_type;    //登录类型  0：pc分享 1:其他
	char m_pc_share_user_info[2048];   //pc登录的信息
};

#endif