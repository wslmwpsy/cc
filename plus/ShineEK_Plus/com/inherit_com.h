#pragma once
#include ".\com_class.h"
#include "com_value.h"

#include <MMSystem.h>

#define COM_SEND_MAX_GROUP_COUNT   20   //����ÿ�η��͵��������
#define TOUCH_SCREEN_MAX_BYTE      10   //���������͵�����ֽ���

class inherit_com :
	public _thread_com
{
public:
	inherit_com(void);
	~inherit_com(void);
	//���մ�������
	virtual void on_receive();
	/*
	���ܣ��������ڽ��յ�����������浽�����У����ڽ��յ��˲��Ҷ�Ӧ������
	������
	    handle�������
		message�����͵���Ϣ
	����ֵ��
	    true���ɹ�
		false��ʧ��
	*/
	bool init_com(HWND handle,int message,TCHAR *file_name);

	/*
	���ܣ������Ӵ��ڽ��յ���ֵ
	������
	    com_value��δ������ʮ�����Ƶ�ֵ
		recv_value�������õĽ��ܵ���ֵ
	����ֵ��
	    true���ɹ�
		false��ʧ��
	*/
	bool parse_com_recv_value(const TCHAR *com_value,unsigned char *recv_value);

	/*
	���ܣ���������ǽ��尴ť������
	������
		rect����ť����
		number�����
	����ֵ��
		true���ɹ�
		false��ʧ��
	*/
	bool parse_button_rect_value(const TCHAR *rect,int number);

	/*
	���ܣ�����Ҫ���͵����ڵ�ֵ
	������
	    com_value��δ������ʮ�����Ƶ�ֵ
		com_send_flag�����ʹ���ֵ�ı�ʾ
		music_volume�����ֵ�����
		microphone_volume����˷������
		tune������
	����ֵ��
	    true���ɹ�
		false��ʧ��
	*/
	bool parse_com_send_value(const TCHAR *com_value,COM_SEND_VALUE_FLAG com_send_flag,int music_volume,int microphone_volume,int tune);


	/*
	���ܣ�������Ϣ������
	������
	    enum COM_SEND_VALUE_FLAG�����ʹ���ֵ�ı�ʾ
		adjust_count�����ʹ���
		file_name�������ļ�������
		music_volume�����ֵ�����
		microphone_volume����˷������
		tune������
	����ֵ��
	    true���ɹ�
		false��ʧ��
	*/
	bool write_data(enum COM_SEND_VALUE_FLAG com_send_flag,TCHAR *file_name,TCHAR *song_number,int music_volume,int microphone_volume,int tune,int adjust_count=0);

	/*
	���ܣ��������̿ڽ��յ����пغ���Ϣ
	������
	    recv_value�����ܵ���ֵ
	����ֵ��
	    void
	*/
	void parse_ps2_value(int recv_value);

	/*
	���ܣ��ж�һ�������Ǹ�������
	������
		x��������
		y��������
	����ֵ
		void
	*/
	void determine_point_in_rect(int x,int y);

	/*
	���ܣ����ʹ���ֵ���߳�
	������
		pParam�����ݵĲ���
	����ֵ��
	UINT
	*/
	static UINT send_com_value_thread(LPVOID pParam);

	/*
	���ܣ����ʹ�������
	������
	    void
	����ֵ��
	    void
	*/
	void write_com_data(void);
	void write_com_data_timer(void);
	void write_com_data_UDP_IP(char *data);

	/*
	���ܣ���ʱ���ʹ���ֵ
	������
		uTimerID����ʱ����ID
		uMsg����Ϣ
		dwUser���û���ʾ
		dw1,dw2������
	����ֵ��
		void
	*/
	static void WINAPI send_com_callback(UINT uTimerID, UINT uMsg, DWORD dwUser, DWORD dw1, DWORD dw2);
	/*
	���Ƶƹ�Ч��
	*/
	void set_light_value(bool light);
	bool get_light_value();
	/*
	������Ƶƹ��ʶ
	*/
	void set_light_value_ex(bool light_ex);
	bool get_light_value_ex();
private:
	HWND m_parent_handle;      //�����
	int m_com_send_message;    //���ڷ��͵���Ϣ
	unsigned char com_receive_value[COM_RECEIVE_VALUE_FLAG_MAX_COUNT][64];  //���ڽ��յ���ȫ������
	unsigned char m_com_send_value[COM_SEND_MAX_GROUP_COUNT][128];          //�����õ�Ҫ���͵�ֵ
	int m_com_send_value_len[COM_SEND_MAX_GROUP_COUNT];                     //�����õ�ÿ�鴮�����ݵĳ���
	int m_com_send_group_count;                                             //���ڷ��͵�����
	CWinThread *m_send_thread_handle;                                       //���ʹ���ֵ���߳̾��
	int m_com_send_time_elapse;                                             //���ڷ��͵�ʱ����
	CRect m_wall_panel_button_rect[COM_RECEIVE_VALUE_FLAG_MAX_COUNT];       //ǽ��尴ť������
	unsigned char m_recv_com_data[256];                                     //���ܵĴ�������
	int m_recv_data_len;                                                    //���ܵĴ������ݳ���
	int m_conn_audio_effect;                                                //ֱ�ӿ�����Ч��
	bool m_light_control;
	bool m_light_control_ex;
};