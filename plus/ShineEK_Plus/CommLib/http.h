#ifndef _HTTP_H_
#define _HTTP_H_

#include "../DllConst.h"

#include <map>
using namespace std;

typedef struct MemoryStruct 
{
	char *memory;
	size_t length;
	size_t size;
}MemoryStruct;


class KTV_DLL_API CHTTP
{
public:
	CHTTP();
	~CHTTP();

	/*
	功能：通过URL下载数据
	参数：
		url：url
		data：存储下载的数据
		data_len：存储空间大小
    返回值：
        成功：0
        失败：错误码
	*/
    int download_data(char *url, char *data, int data_len);

	/*
	功能：通过URL下载文件到本地
	参数：
	    url：utf
		path：本地保存路径
	返回值：
	   成功：0
	   失败：错误码
	*/
	int download_file(char *url, TCHAR *path);

    /*
	功能：启动线程通过URL下载文件到本地
	参数：
	    url：utf
		path：本地保存路径
	返回值：
	   成功：0
	   失败：错误码
	*/
	int download_file_by_thread(char *url, TCHAR *path);
	//下载文件线程
	static UINT download_file_thread(LPVOID pParam);

	/*
	功能：post文件
	参数：
	   ip：IP地址
	   port：端口
	   url_path：url路径
	   file_path：需要上传的文件路径
	   reply_data：回复的结果
	   file_name：建议服务端保存文件名
   返回值：
       true：成功
	   false：失败
	*/
	int post_file(char *ip, int port, char *url_path, TCHAR *file_path, char *reply_data, int reply_len, char *file_name, char *domain = NULL);

    /*
    功能：post数据
    参数：
        url：url
        data：数据
        data_size：数据长度
        reply_data：收到的应答数据
    返回值：
        成功：0
        失败：错误码
    */
	int post_data(char *url, char *data, int data_size, char *reply_data, int reply_len);

protected:
	/*
    接口暂时有问题不能使用，请使用post_file_to_server去post文件
    功能：post文件
    参数：
        url：url
        file_path：post的文件
        reply_data：返回的应答数据
    返回值：
        成功：0
        失败：错误码
    */
	int post_file(char *url, TCHAR *file_path, char *reply_data);
	
	/*
	功能：初始化及反初始化
	参数：
	   void
   返回值：
       void
	*/
	void initialize(void);
	void uninitialize(void);

	/*
	功能：组织post文件文件头
	参数：
	    order：组好的文件头
		len：数据长度
		path：路径
		ip：ip地址
		port：端口
	*/
	int set_post_head(char *order, int len, char *path, char *ip, int port, char *domain = NULL);

	/*
	功能：解析http返回的内容。先判断是否是200 OK，再去掉http头将结果串返回
	参数：
		response：http返回结果
		return_result：解析后的结果串
		buff_size：存放结果串的buff长度
		return_size：结果串的长度
	返回值：
		true：成功
		false：失败
	*/
	bool parse_http_response(const char *response, char *return_result, int buff_size, int &return_size);
};


#endif