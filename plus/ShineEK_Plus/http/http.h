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
	char user_name[64];    //�û���
	char passowrd[64];     //����
	char type[16];         //��¼����
}USER_INFO_t;

#define TAPE_SONG_MAX_COUNT   200
#define USER_MAX_COUNT        16       //��¼���û������

class CHttp_old
{
public:
	CHttp_old(void);
	/*
	���ܣ���ʼ��
	������
	   void
   ����ֵ��
       void
	*/
	void initialize(void);

	/*
	���ܣ��õ�URL
	������
	����web_url:������mp3����URL
    ����ֵ��
	    true���ɹ�
		false��ʧ��
	*/
	bool get_url_from_server(TCHAR *song_number,TCHAR *web_url);

	/*
	���ܣ��ϴ��ļ���������ת������
	������
	   path���ļ�·��
   ����ֵ��
       true���ɹ�
	   false��ʧ��
	*/
	bool upload_file_to_server(song_info video_info);

	/*
	���ܣ��õ�URL���ļ���
	������
	    song_number���������
		URL���������ַ
		file_name���ļ�����
	����ֵ��
	   true���ɹ�
	   false��ʧ��
	*/
	bool get_web_url(const TCHAR *song_number,TCHAR *URL,TCHAR *file_name);

	/*
	���ܣ�����URL
	������
	    song_number���������
	    URL���������ַ
	����ֵ��
	    true���ɹ�
		false��ʧ��
	*/
	bool set_web_url(TCHAR *song_number,TCHAR *URL);

	/*
	���ܣ���֯post�ļ�ͷ
	������
	    order����õ��ļ�ͷ
		len�����ݳ���
		song_name���ļ���
		singer_name��������
		tape_time��¼��ʱ��
		url��������ַ
	*/
	bool set_post_head(char *order,int len,char *song_name,char *singer_name,char *tape_time,char *url,char *song_id);

	/*
	���ܣ���֯get�ļ�ͷ
	������
	    order����õ��ļ�ͷ
		len�����ݳ���
		song_name���ļ���
		singer_name��������
		tape_time��¼��ʱ��
		url��������ַ
	*/
	bool set_get_head(char *order);

	/*
	���ܣ�PCMתmp3
	������
	    wav_path��wav�ļ�·��
		mp3_path��mp3�ļ�·��
	����ֵ��
	    true���ɹ�
		false��ʧ��
	*/
	bool PCM_to_mp3(TCHAR *wave_path,TCHAR *mp3_path);

	/*
	���ܣ��洢�û���Ϣ
	������
	    user_info���û���Ϣ
	����ֵ��
	    true���ɹ�
		false��ʧ��
	*/
	bool save_user_info(char *user_info);

	/*
	���ܣ�ɾ���û���Ϣ
	������
		user_info���û���Ϣ
	����ֵ��
		true���ɹ�
		false��ʧ��
	*/
	bool delete_user_info(char *user_info);

	/*
	���ܣ���������û���Ϣ
	������
	    void
	����ֵ��
	    void
	*/
	void clear_user_info(void);

	/*
	���ܣ��õ��û���Ϣ
	������
	   user_info���û���Ϣ
   ����ֵ��
       true���ɹ�
	   false��ʧ��
	*/
	bool get_user_info(char *user_info);

	/*
	���ܣ�ת���ո��%20
	������
	     src_str��ԭʼ�ַ���
		 des_str��ת��֮����ַ���
	����ֵ��
	    true���ɹ�
		false��ʧ��
	*/
	bool convert_blank_space(char *src_str, char *des_str);

	/*
		���ܣ�����pc��¼����
		������
			date��json��Ϣ
			upload_type:����
	*/
	bool set_current_user_info(const TCHAR* date,int upload_type);
 

public:
	TAPE_AUDIO_URL_t m_share_url[TAPE_SONG_MAX_COUNT];    //�洢�����URL
	char m_server_ip[32];                                 //������IP
	int m_server_port;                                    //�������˿�
	USER_INFO_t m_user_info[USER_MAX_COUNT];              //�û���Ϣ
	int m_login_type;    //��¼����  0��pc���� 1:����
	char m_pc_share_user_info[2048];   //pc��¼����Ϣ
};

#endif