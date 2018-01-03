#ifndef _BASE_SOCKET_H_
#define _BASE_SOCKET_H_

#include "../DllConst.h"

class KTV_DLL_API CBaseSocket
{
public:

	CBaseSocket();
	~CBaseSocket();

	/*
	功能：创建TCP Socket
	参数：void
	返回值：
		成功：0
		失败：错误码
	*/
	int create_socket_tcp(void);

	/*
	功能：监听端口
	参数：
		Port：要监听的端口
	返回值：
		成功：0
		失败：错误码
	*/
	int listen_tcp(unsigned short port);

	/*
	功能：接收客户端的连接
	参数：
		accept_socket：接收连接得到的新的socket句柄
		p_client_ip：客户端IP
	返回值：
		成功：0
		失败：错误码
	*/
	int accept_tcp(SOCKET *accept_socket, char *p_client_ip);

	/*
	功能：TCP接收数据，立即返回，不必接收size大小
	参数：
		sock：socket句柄
		buff：接收的数据缓冲区
		req_size：请求接收的数据字节
		res_size：返回的数据字节
		timeout：接收超时，单位-毫秒
	返回值：
	    0：接收到数据
		1：连接关闭
		<0：错误或者没有数据到达
	*/
	int recv_imm_tcp(SOCKET sock, void *buff, int req_size, int *res_size, int timeout);

	/*
	功能：TCP接收指定字节数据
	参数：
		sock：socket句柄
		buff：接收的数据缓冲区
		req_size：请求接收的数据字节
		res_size：返回的数据字节
	返回值：
		成功：0
		失败：错误码
	*/
	int recv_all_tcp(SOCKET sock, void *buff, int req_size, int *res_size);

	/*
	功能：连接Socket
	参数：
		ip：网络地址
		port：端口
		wait_time：等待时间，单位秒
	返回值：
		成功：0
		失败：错误码
	*/
	int connect_tcp(char *ip, unsigned short port, int wait_time);

	/*
	功能：TCP发送数据
	参数：
		sock：socket句柄
		buff：发送的数据
		size：发送数据的字节数
        send_size：实际发送的字节数
	返回值：
		成功：0
		失败：错误码
	*/
	int send_tcp(SOCKET sock, const void *buff, int size, int &send_size);

	/*
	功能：关闭TCP连接
	参数：
		sock：socket句柄
	返回值：
		成功：0
		失败：错误码
	*/
	int close_tcp(void);
	int close_tcp(SOCKET sock);

	/*
	功能：创建UDP Socket
	参数：void
	返回值：
		成功：0
		失败：错误码
	*/
	int create_socket_udp(void);

	/*
	功能：UDP发送数据
	参数：
		ip：IP地址
		port：端口
		buff：发送的数据
		size：发送数据的字节数
        send_size：实际发送的字节数
	返回值：
		成功：0
		失败：错误码
	*/
	int send_udp(char *ip, unsigned short port, const char *buff, int size, int &send_size);

	/*
	功能：UDP绑定端口
	参数：
		port：端口
	返回值：
		成功：0
		失败：错误码
	*/
	int bind_udp(unsigned short port);

	/*
	功能：UDP接收数据
	参数：
		buff：接收数据的缓冲区
		req_size：请求接收的数据字节
		res_size：返回的数据字节
		ip：IP地址
		wait_time：select等待时间，单位毫秒
    返回值：
        成功：0
        失败：错误码
	*/
	int recv_udp(char *buff, int req_size, int *res_size, char *ip, int wait_time);
	int recv_udp(char *buff, int req_size, int *res_size, int wait_time);

	/*
	功能：关闭UDP连接
	参数：void
	返回值：
		成功：0
		失败：错误码
	*/
	int close_udp(void);

    /*
    功能：获得socket句柄
    参数：
        sock：返回的socket句柄值
    返回值：
        成功：0
        失败：错误码
    */
	int get_socket(SOCKET &sock);

	int get_ip(const char *domain, char *ip);

private:

	//套接字
	SOCKET m_sock;
};

#endif

