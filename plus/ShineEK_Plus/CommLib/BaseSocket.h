#ifndef _BASE_SOCKET_H_
#define _BASE_SOCKET_H_

#include "../DllConst.h"

class KTV_DLL_API CBaseSocket
{
public:

	CBaseSocket();
	~CBaseSocket();

	/*
	���ܣ�����TCP Socket
	������void
	����ֵ��
		�ɹ���0
		ʧ�ܣ�������
	*/
	int create_socket_tcp(void);

	/*
	���ܣ������˿�
	������
		Port��Ҫ�����Ķ˿�
	����ֵ��
		�ɹ���0
		ʧ�ܣ�������
	*/
	int listen_tcp(unsigned short port);

	/*
	���ܣ����տͻ��˵�����
	������
		accept_socket���������ӵõ����µ�socket���
		p_client_ip���ͻ���IP
	����ֵ��
		�ɹ���0
		ʧ�ܣ�������
	*/
	int accept_tcp(SOCKET *accept_socket, char *p_client_ip);

	/*
	���ܣ�TCP�������ݣ��������أ����ؽ���size��С
	������
		sock��socket���
		buff�����յ����ݻ�����
		req_size��������յ������ֽ�
		res_size�����ص������ֽ�
		timeout�����ճ�ʱ����λ-����
	����ֵ��
	    0�����յ�����
		1�����ӹر�
		<0���������û�����ݵ���
	*/
	int recv_imm_tcp(SOCKET sock, void *buff, int req_size, int *res_size, int timeout);

	/*
	���ܣ�TCP����ָ���ֽ�����
	������
		sock��socket���
		buff�����յ����ݻ�����
		req_size��������յ������ֽ�
		res_size�����ص������ֽ�
	����ֵ��
		�ɹ���0
		ʧ�ܣ�������
	*/
	int recv_all_tcp(SOCKET sock, void *buff, int req_size, int *res_size);

	/*
	���ܣ�����Socket
	������
		ip�������ַ
		port���˿�
		wait_time���ȴ�ʱ�䣬��λ��
	����ֵ��
		�ɹ���0
		ʧ�ܣ�������
	*/
	int connect_tcp(char *ip, unsigned short port, int wait_time);

	/*
	���ܣ�TCP��������
	������
		sock��socket���
		buff�����͵�����
		size���������ݵ��ֽ���
        send_size��ʵ�ʷ��͵��ֽ���
	����ֵ��
		�ɹ���0
		ʧ�ܣ�������
	*/
	int send_tcp(SOCKET sock, const void *buff, int size, int &send_size);

	/*
	���ܣ��ر�TCP����
	������
		sock��socket���
	����ֵ��
		�ɹ���0
		ʧ�ܣ�������
	*/
	int close_tcp(void);
	int close_tcp(SOCKET sock);

	/*
	���ܣ�����UDP Socket
	������void
	����ֵ��
		�ɹ���0
		ʧ�ܣ�������
	*/
	int create_socket_udp(void);

	/*
	���ܣ�UDP��������
	������
		ip��IP��ַ
		port���˿�
		buff�����͵�����
		size���������ݵ��ֽ���
        send_size��ʵ�ʷ��͵��ֽ���
	����ֵ��
		�ɹ���0
		ʧ�ܣ�������
	*/
	int send_udp(char *ip, unsigned short port, const char *buff, int size, int &send_size);

	/*
	���ܣ�UDP�󶨶˿�
	������
		port���˿�
	����ֵ��
		�ɹ���0
		ʧ�ܣ�������
	*/
	int bind_udp(unsigned short port);

	/*
	���ܣ�UDP��������
	������
		buff���������ݵĻ�����
		req_size��������յ������ֽ�
		res_size�����ص������ֽ�
		ip��IP��ַ
		wait_time��select�ȴ�ʱ�䣬��λ����
    ����ֵ��
        �ɹ���0
        ʧ�ܣ�������
	*/
	int recv_udp(char *buff, int req_size, int *res_size, char *ip, int wait_time);
	int recv_udp(char *buff, int req_size, int *res_size, int wait_time);

	/*
	���ܣ��ر�UDP����
	������void
	����ֵ��
		�ɹ���0
		ʧ�ܣ�������
	*/
	int close_udp(void);

    /*
    ���ܣ����socket���
    ������
        sock�����ص�socket���ֵ
    ����ֵ��
        �ɹ���0
        ʧ�ܣ�������
    */
	int get_socket(SOCKET &sock);

	int get_ip(const char *domain, char *ip);

private:

	//�׽���
	SOCKET m_sock;
};

#endif

