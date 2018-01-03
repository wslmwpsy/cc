#pragma once

#define KTV_LOGO_MAX_COUNT   120   //logo�������

class osd_logo_list
{
public:
	osd_logo_list(void);
	~osd_logo_list(void);

	//��ʼ��
	void initiate(void);

	/*
	���ܣ�����logo�ļ���·���������г�ʼ��
	������
	    logo_directory��logo���ļ���·��
	����ֵ��
	    true���ɹ�
		false��ʧ��
	*/
	bool set_logo_path(TCHAR *logo_directory);

	/*
	���ܣ��õ���ǰ���ŵ�logo���
	������
	    void
	����ֵ:
	    ��ǰҪ���ŵ�logo���
	*/
	int get_cur_logo_index();

	/*
	���ܣ��õ���ǰҪ���ŵ�logo�ļ�·��
	������
	    path��logo�ļ�·��
	����ֵ��
	    true���ɹ�
		false��ʧ��
	*/
	bool get_logo_file_path(TCHAR *path);
	
private:
	TCHAR m_logo_directory[256];                  //logo�ļ��е�·��
	TCHAR m_logo_path[KTV_LOGO_MAX_COUNT][256];  //����logo��·�������100��
	int   m_logo_count;                          //logo������
	int   m_cur_logo_number;                     //��ǰ���ŵ�logo���
};
