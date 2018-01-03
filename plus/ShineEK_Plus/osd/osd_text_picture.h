#pragma once

#include "../player/player_data_type.h"
#include "osd_message.h"
#include "../message.h"

class osd_text_picture
{
public:
	osd_text_picture(void);
	~osd_text_picture(void);
	/*
	���ܣ�����Ҫ��ʾ������
	������
	    text��Ҫ��ʾ������
	����ֵ��
	    true���ɹ�
		false��ʧ��
	*/
	bool set_text(TCHAR *text);
	/*
	���ܣ��������ֵ���ɫ
	������
	    text_color��������ɫ
    ����ֵ��
	    true���ɹ�
		false��ʧ��
	*/
	bool set_text_color(const TCHAR *text_color);
	bool set_text_color(COLORREF text_color);
	/*
	���ܣ���������
	������
	    text_font�����ֵ�����
	����ֵ��
	    true���ɹ�
		false��ʧ��
	*/
	bool set_text_font(const TCHAR *text_font);
	/*
	���ܣ����������С
	������
	    text_size�����ִ�С
	����ֵ��
	   true���ɹ�
	   false��ʧ��
	*/
	bool set_text_size(int text_size);

	/*
	���ܣ��������ֵı�����ɫ
	������
		text_color��������ɫ
	����ֵ��
		true���ɹ�
		false��ʧ��
	*/
	bool set_text_Background_color(const TCHAR *text_color);
	/*
	���ܣ�������Ϣ������
	������
	    message_type;��Ϣ����
	����ֵ��
	    true���ɹ�
		false��ʧ��
	*/
	bool set_message_type(char *message_type);
	/*
	���ܣ�������ʾģʽ
	������
	    show_mode����ʾģʽ
	����ֵ��
	    true���ɹ�
		false��ʧ��
	*/
	bool set_show_mode(const TCHAR *show_mode);
	/*
	���ܣ�������Ϣ���ݵ�����
	������
	����content_type����������
    ����ֵ��
	    true���ɹ�
		false��ʧ��
	*/
	bool set_content_type(TCHAR *content_type);
	/*
	���ܣ����ù�����ʽ
	������
	    scroll_mode;����ģʽ
		osd_type��osd����
	����ֵ��
	    true���ɹ�
		false��ʧ��
	*/
	bool set_scroll_mode(const TCHAR *scroll_mode,enum MESSAGE_CONTENT_TYPE osd_type);
	bool set_scroll_mode(enum OSD_PLAY_MODE scroll_mode,enum MESSAGE_CONTENT_TYPE osd_type);
	/*
	���ܣ����ù�������
	����:
	    scroll_count����������
	����ֵ��
	    true���ɹ�
		false��ʧ��
	*/
	bool set_scroll_count(TCHAR *scroll_count);
	bool set_scroll_count(int scroll_count);

	/*
	���ܣ����ù����ٶ�
	������
	    scroll_speed�������ٶ�
	����ֵ��
	    true���ɹ�
		false��ʧ��
	*/
	bool set_scroll_speed(TCHAR *scroll_speed);
	bool set_scroll_speed(int scroll_speed);

	/*
	���ܣ����ù�������ʼλ��
	������
	    position��λ������
	����ֵ��
	    true���ɹ�
		false��ʧ��
	*/
	bool set_scroll_position_x(TCHAR *position);
	bool set_scroll_position_y(TCHAR *position);
	bool set_scroll_position_x(int position);
	bool set_scroll_position_y(int position);

	/*
	���ܣ����ݹ������ͣ�������ʼ����
	������
	    void
	����ֵ��
	    void
	*/
	void adjust_text_position(int start_x);	// �������ֹ������ͣ�ȷ����ʼ����ֹ����
	void adjust_picture_position();	// ����ͼƬ�������ͣ�ȷ����ʼ����ֹ����

	/*
	���ܣ��������ֵĻ�����Ϣ��
	������
	    text_info�����ֵĻ�����Ϣ��
	����ֵ;
	    true���ɹ�
		false��ʧ��
	*/
	bool get_text_info(text_osd_info &text_info);

	/*
	���ܣ��õ����ֵĲ��Ų�����
	������
	    play_var�����ű�����
	����ֵ��
	    true���ɹ�
		false��ʧ��
	*/
	bool get_text_play_variable(play_variable &play_var);

	/*
	���ܣ��õ����ֵĲ��Ų�����
	������
		play_var�����ű�����
	����ֵ��
		true���ɹ�
		false��ʧ��
	*/
	bool get_picture_play_variable(play_variable &play_var);

	/*
	���ܣ��������͹�������Ϣ
	������
	    msg����Ϣ
	����ֵ��
	    true���ɹ�
		false��ʧ��
	*/
	bool parse_msg(const char *msg, LPMOVIE_MSG_CONTROL lpMMCtrl = NULL);

	/*
	���ܣ��õ���ʾģʽ
	������
	    void
	����ֵ��
	    ��ʾģʽ
	*/
	MESSAGE_SHOW_MODE get_show_mode(void);

	/*
	���ܣ��õ���Ϣ����������
	������
	    void
	����ֵ��
	   ��������
	*/
	MESSAGE_CONTENT_TYPE get_content_type(void);


	MESSAGE_TYPE  get_message_type(void);

private:
	text_osd_info m_text_info;              //text�Ļ�����Ϣ
	play_variable m_text_play_variable;    //���ֲ���ʱ�Ĳ���
	play_variable m_picture_play_variable; //ͼƬ����ʱ�Ĳ���
	enum MESSAGE_TYPE m_message_type;	// ��Ϣ���ͣ�����ȣ�
	enum MESSAGE_SHOW_MODE m_show_mode;	// ��ʾģʽ
	enum MESSAGE_CONTENT_TYPE m_content_type;	// ��Ϣ�������ͣ��ı���ͼƬ��
	enum OSD_PLAY_MODE m_text_scroll_mode;	// ���ֹ�����ʽ
	enum OSD_PLAY_MODE m_picture_scroll_mode;	// ͼƬ������ʽ
	int m_scroll_count;                        //��������
};
