#pragma once
#ifndef _WATCH_DOG_H_
#define _WATCH_DOG_H_

#include "DogClient.h"

enum DOG_TYPE{
	FEITIAN_DOG=0,  //飞天狗接口
	SENSE_LOCK,     //深思加密锁
    NO_DOG,         //不需要加密狗
};

//封装的加密狗接口，主要是为了实现兼容多个加密狗接口

class watch_dog
{
public:
	watch_dog(void);
	~watch_dog(void);
	/*
	功能：设置必要的参数给加密狗客户端
	参数：
	    server_ip：指定服务器IP地址
	    server_port：指定服务器端口
	    module_number：模块编码《4字节数字》
	    link_error_number：连接服务器的最大出错次数,用于客户端判断服务器端口是否有效
	    timeout：等待服务器回应的超时时间
	    warn_time：有效日期报警阀值
	返回值：
	    true:成功
		false:失败
	*/
	bool set_parameter(const TCHAR* server_ip, int server_port,const TCHAR* module_number,int link_error_number,long timeout,long warn_time);
	/*
	功能：连接加密狗的服务器
	参数：
	    void
	返回值：
	    true：成功
		false：失败
	*/
	bool connect_server(void);
	/*
	功能：登陆检查
	参数：
	    valid_time[out]：有效日期
        module_number[in]：模块编号
	返回值：
	//返回值  ：0		--	成功
	//          !0		--	失败
	*/
	int login_check(long & valid_time,const TCHAR * module_number);
	/*
	功能：根据不同参数，从狗中读取对应数据文件长度和信息
	参数：
        file_index：文件索引《0-自用文件；1-客户文件；2-代理商文件》
	    data_length：文件长度
		buffer：文件内容
	返回值：
	    true：成功
		false：失败
	*/
	bool get_data(int file_index, int & data_length , char*  buffer);

	/*
	功能：通用检查，检查狗是否存在
	参数：
	    void
	返回值：
	    结果码值
	*/
	int common_check(void);

	/*
	功能：客户端登出
	参数：
	    void
	返回值：
	    true：成功
		false：失败
	*/
	bool logout(void);
	/*
	功能：增加歌曲计数到加密狗中
	参数：
        song_number[in]：增加的计数值，写入加密狗;[out]：加密狗内的总计数值
	返回值：
	    true：成功
		false：失败
	*/
	bool add_song_number(long & song_number);
	/*
	功能：请求校正服务器时钟
	参数：
	    void
	返回值：
        true：成功
		false：失败
	*/
	bool verify_server_time(void);
	/*
	功能：取得加密狗内的歌曲总数
	参数：
	    song_total_number[out]：加密狗内的总计数值
	返回值
	    true：成功
		false：失败
	*/
	bool get_song_number(long & song_total_number);
	/*
	功能：执行加密狗中算法，进行加密操作
	参数：
	    input_data：待加密的字符串(128字节——固定长度)
        output_data：加密后的字符串(128字节——固定长度)
	返回值：
	    true：成功
		false：失败
	*/
	bool encode(TCHAR* input_data, TCHAR*  output_data);

	/*
	功能：执行加密狗中算法，进行解密操作
	参数：
		input_data：待解密的字符串(128字节——固定长度)
		output_data：解密后的字符串(128字节——固定长度)
	返回值：
		true：成功
		false：失败
	*/
	bool decode(TCHAR* input_data, TCHAR*  output_data);

	/*
	功能：执行加密狗中算法，进行指定有效日期的设定
	参数：
	    active_code：时间激活码
        active_time：指定有效日期
	返回值：
		true：成功
		false：失败
	*/
	bool active_clock_time(TCHAR*  active_code, long & active_time);
private:
	CDogClient *feitian_dog;   //飞天狗的接口类
	char m_dog_server_ip[256]; //狗服务的IP地址
};

#endif

