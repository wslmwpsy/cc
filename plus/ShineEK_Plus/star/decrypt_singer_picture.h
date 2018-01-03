#pragma once

//�ļ�ͷ
#define FILE_HEAD_LENGTH   16
//��Կ����
#define KEY_LENGHT         256

class decrypt_picture
{
public:
	decrypt_picture(void);
	~decrypt_picture(void);


	/*
	���ܣ����ܸ���ͼƬ
	������
	    singer_name����������
		singer_sex�������Ա�
		file_number���ļ����
		src_picture_path������ͼƬ���·��
		out_file_path�����ܵ��ļ�·��
	����ֵ��
	    true���ɹ�
		false��ʧ��
	*/
	bool decrypt_singer_picture(TCHAR *singer_name,TCHAR *singer_sex,int file_number,TCHAR *src_picture_path,TCHAR *out_file_path);

	/*
	���ܣ����ܸ���ͼƬ·��
	������
	   song_id���������
	   file_number���ļ����
	   src_picture_path������ͼƬ���·��
	   out_file_path�����ܵ��ļ�·��
   ����ֵ��
       true���ɹ�
	   false��ʧ��
	*/
	bool decrypt_song_picture(TCHAR *song_id,int file_number,TCHAR *src_picture_path,TCHAR *out_file_path);
	
	/*
	���ܣ�����ͼƬ���ļ�
	������
		in_file_path��ԭ�ļ�·��
		out_file_path�����ܵ��ļ�·��
		file_number���ļ����
	����ֵ��
		0��Դ�ļ�û�м��� -1�����ܳ��� 1�����ܳɹ�
	*/
	bool decrypt_picture_file(TCHAR *in_file_path,TCHAR *out_file_path,int file_number);

	/*
	���ܣ�����ͼƬ���ļ�
	������
	     in_file_path��ԭ�ļ�·��
		 out_file_path�����ܵ��ļ�·��
	����ֵ��
	    0��Դ�ļ�û�м��� -1�����ܳ��� 1�����ܳɹ�
	*/
	int decrypt_file(TCHAR *in_file_path,TCHAR *out_file_path);
	//��������
	bool decrypt(unsigned char *data,long data_len,unsigned char *file_head,enum  OPERATE Type);
};
