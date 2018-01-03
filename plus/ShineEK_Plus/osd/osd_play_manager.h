#pragma once

#include "osd_text_picture.h"
#include "osd_logo_list.h"
#include "..\file\file.h"

class osd_play_manager
{
public:
	osd_play_manager(void);
	~osd_play_manager(void);
	/*
	���ܣ���ʼ��
	������
	   void
    ����ֵ��
       void
	*/
	void initialize(void);

	/*
	���ܣ�����Ҫ���ŵ�����
	������
	    text��Ҫ���ŵ�����
	����ֵ��
	    true���ɹ�
		false��ʧ��
	*/
	bool set_osd_text(TCHAR *text);

	/*
	���ܣ��õ�����ͼƬ��·��
	������
	    path��·��
	����ֵ��
	    true���ɹ�
		false��ʧ��
	*/
	bool get_background_path(TCHAR *path);
	/*
	���ܣ��õ����ŵĿ���OSD���ļ���
	������
	   show_content����ʾ������
	   path�����ƹ���ͼƬ��·��
	   x_pos��������
	   y_pos��������
	   soft_decode�������ʾ true����� false��Ӳ��
	   recorder_osd:�Ƿ�������¼��
   ����ֵ��
       true���ɹ�
	   false��ʧ��
	*/
	bool get_control_osd_info(enum OSD_SHOW_CONTENT show_content,TCHAR *path,int &x_pos,int &y_pos,bool soft_decode,enum FLASH_USE_LANGUAGE flash_language,bool recorder_osd=false);

	/*
	���ܣ�����logo��·��
	������
	    path��logo�ļ���·��
	����ֵ��
	    true���ɹ�
		false��ʧ��
	*/
	bool set_logo_osd_path(TCHAR *path);

	
	/*
	���ܣ��õ�logo osd����Ϣ
	����;
	    path��logo�ļ���·��
		index������
	����ֵ��
	    true���ɹ�
		false��ʧ��
	*/
	bool get_logo_osd_info(TCHAR *path,int &index);

	/*
	���ܣ���������osd��λ��
	������
	    screen_width����Ļ���
		screen_height����Ļ�߶�
		soft_decode������ʾ
	����ֵ��
	    void
	*/
	void adjust_control_osd_coordinate(int screen_width,int screen_height,bool soft_decode);

public:
	osd_text_picture m_osd_text_picture;  //���ֻ�ͼƬ��Ϣ��
	bool m_show_osd;                       //�Ƿ���ʾosd
	TCHAR m_text_background_path[256];    //���ֱ���ͼƬ·��
	TCHAR m_install_path[256];            //��װ·��
	TCHAR m_screen_show_folder_name[64];  //��Ļ��ʾͼƬ�ļ��е�����
	enum FILE_ATTRIBUTE  file_attribute;  //��¼logo�ļ�������
	TCHAR m_logo_path[256];               //logo�ļ���·��
	osd_logo_list logo_list;              //��¼һ��logoͼƬ
	int m_control_osd_x;                  //����osd�ĺ�����
	int m_control_osd_y;                  //����osd��������
	int m_show_osd_suit_number;           //��ʾ��osd���
};
