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
	���ܣ�ͨ��URL��������
	������
		url��url
		data���洢���ص�����
		data_len���洢�ռ��С
    ����ֵ��
        �ɹ���0
        ʧ�ܣ�������
	*/
    int download_data(char *url, char *data, int data_len);

	/*
	���ܣ�ͨ��URL�����ļ�������
	������
	    url��utf
		path�����ر���·��
	����ֵ��
	   �ɹ���0
	   ʧ�ܣ�������
	*/
	int download_file(char *url, TCHAR *path);

    /*
	���ܣ������߳�ͨ��URL�����ļ�������
	������
	    url��utf
		path�����ر���·��
	����ֵ��
	   �ɹ���0
	   ʧ�ܣ�������
	*/
	int download_file_by_thread(char *url, TCHAR *path);
	//�����ļ��߳�
	static UINT download_file_thread(LPVOID pParam);

	/*
	���ܣ�post�ļ�
	������
	   ip��IP��ַ
	   port���˿�
	   url_path��url·��
	   file_path����Ҫ�ϴ����ļ�·��
	   reply_data���ظ��Ľ��
	   file_name���������˱����ļ���
   ����ֵ��
       true���ɹ�
	   false��ʧ��
	*/
	int post_file(char *ip, int port, char *url_path, TCHAR *file_path, char *reply_data, int reply_len, char *file_name, char *domain = NULL);

    /*
    ���ܣ�post����
    ������
        url��url
        data������
        data_size�����ݳ���
        reply_data���յ���Ӧ������
    ����ֵ��
        �ɹ���0
        ʧ�ܣ�������
    */
	int post_data(char *url, char *data, int data_size, char *reply_data, int reply_len);

protected:
	/*
    �ӿ���ʱ�����ⲻ��ʹ�ã���ʹ��post_file_to_serverȥpost�ļ�
    ���ܣ�post�ļ�
    ������
        url��url
        file_path��post���ļ�
        reply_data�����ص�Ӧ������
    ����ֵ��
        �ɹ���0
        ʧ�ܣ�������
    */
	int post_file(char *url, TCHAR *file_path, char *reply_data);
	
	/*
	���ܣ���ʼ��������ʼ��
	������
	   void
   ����ֵ��
       void
	*/
	void initialize(void);
	void uninitialize(void);

	/*
	���ܣ���֯post�ļ��ļ�ͷ
	������
	    order����õ��ļ�ͷ
		len�����ݳ���
		path��·��
		ip��ip��ַ
		port���˿�
	*/
	int set_post_head(char *order, int len, char *path, char *ip, int port, char *domain = NULL);

	/*
	���ܣ�����http���ص����ݡ����ж��Ƿ���200 OK����ȥ��httpͷ�����������
	������
		response��http���ؽ��
		return_result��������Ľ����
		buff_size����Ž������buff����
		return_size��������ĳ���
	����ֵ��
		true���ɹ�
		false��ʧ��
	*/
	bool parse_http_response(const char *response, char *return_result, int buff_size, int &return_size);
};


#endif