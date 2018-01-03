#pragma once
#ifndef _WATCH_DOG_H_
#define _WATCH_DOG_H_

#include "DogClient.h"

enum DOG_TYPE{
	FEITIAN_DOG=0,  //���칷�ӿ�
	SENSE_LOCK,     //��˼������
    NO_DOG,         //����Ҫ���ܹ�
};

//��װ�ļ��ܹ��ӿڣ���Ҫ��Ϊ��ʵ�ּ��ݶ�����ܹ��ӿ�

class watch_dog
{
public:
	watch_dog(void);
	~watch_dog(void);
	/*
	���ܣ����ñ�Ҫ�Ĳ��������ܹ��ͻ���
	������
	    server_ip��ָ��������IP��ַ
	    server_port��ָ���������˿�
	    module_number��ģ����롶4�ֽ����֡�
	    link_error_number�����ӷ����������������,���ڿͻ����жϷ������˿��Ƿ���Ч
	    timeout���ȴ���������Ӧ�ĳ�ʱʱ��
	    warn_time����Ч���ڱ�����ֵ
	����ֵ��
	    true:�ɹ�
		false:ʧ��
	*/
	bool set_parameter(const TCHAR* server_ip, int server_port,const TCHAR* module_number,int link_error_number,long timeout,long warn_time);
	/*
	���ܣ����Ӽ��ܹ��ķ�����
	������
	    void
	����ֵ��
	    true���ɹ�
		false��ʧ��
	*/
	bool connect_server(void);
	/*
	���ܣ���½���
	������
	    valid_time[out]����Ч����
        module_number[in]��ģ����
	����ֵ��
	//����ֵ  ��0		--	�ɹ�
	//          !0		--	ʧ��
	*/
	int login_check(long & valid_time,const TCHAR * module_number);
	/*
	���ܣ����ݲ�ͬ�������ӹ��ж�ȡ��Ӧ�����ļ����Ⱥ���Ϣ
	������
        file_index���ļ�������0-�����ļ���1-�ͻ��ļ���2-�������ļ���
	    data_length���ļ�����
		buffer���ļ�����
	����ֵ��
	    true���ɹ�
		false��ʧ��
	*/
	bool get_data(int file_index, int & data_length , char*  buffer);

	/*
	���ܣ�ͨ�ü�飬��鹷�Ƿ����
	������
	    void
	����ֵ��
	    �����ֵ
	*/
	int common_check(void);

	/*
	���ܣ��ͻ��˵ǳ�
	������
	    void
	����ֵ��
	    true���ɹ�
		false��ʧ��
	*/
	bool logout(void);
	/*
	���ܣ����Ӹ������������ܹ���
	������
        song_number[in]�����ӵļ���ֵ��д����ܹ�;[out]�����ܹ��ڵ��ܼ���ֵ
	����ֵ��
	    true���ɹ�
		false��ʧ��
	*/
	bool add_song_number(long & song_number);
	/*
	���ܣ�����У��������ʱ��
	������
	    void
	����ֵ��
        true���ɹ�
		false��ʧ��
	*/
	bool verify_server_time(void);
	/*
	���ܣ�ȡ�ü��ܹ��ڵĸ�������
	������
	    song_total_number[out]�����ܹ��ڵ��ܼ���ֵ
	����ֵ
	    true���ɹ�
		false��ʧ��
	*/
	bool get_song_number(long & song_total_number);
	/*
	���ܣ�ִ�м��ܹ����㷨�����м��ܲ���
	������
	    input_data�������ܵ��ַ���(128�ֽڡ����̶�����)
        output_data�����ܺ���ַ���(128�ֽڡ����̶�����)
	����ֵ��
	    true���ɹ�
		false��ʧ��
	*/
	bool encode(TCHAR* input_data, TCHAR*  output_data);

	/*
	���ܣ�ִ�м��ܹ����㷨�����н��ܲ���
	������
		input_data�������ܵ��ַ���(128�ֽڡ����̶�����)
		output_data�����ܺ���ַ���(128�ֽڡ����̶�����)
	����ֵ��
		true���ɹ�
		false��ʧ��
	*/
	bool decode(TCHAR* input_data, TCHAR*  output_data);

	/*
	���ܣ�ִ�м��ܹ����㷨������ָ����Ч���ڵ��趨
	������
	    active_code��ʱ�伤����
        active_time��ָ����Ч����
	����ֵ��
		true���ɹ�
		false��ʧ��
	*/
	bool active_clock_time(TCHAR*  active_code, long & active_time);
private:
	CDogClient *feitian_dog;   //���칷�Ľӿ���
	char m_dog_server_ip[256]; //�������IP��ַ
};

#endif

