#pragma once

#include "..\common\timer.h"

#define DOORPLATE_IMAGE_MAX_COUNT      100
// CDoorplateWnd

class CDoorplateWnd : public CWnd
{
	DECLARE_DYNAMIC(CDoorplateWnd)

public:
	CDoorplateWnd();
	virtual ~CDoorplateWnd();
	//�������ƻ�����
	bool Create(RECT& rect,TCHAR *room_name,bool use_drinks,HWND parent_handle);

protected:
	DECLARE_MESSAGE_MAP()
	DECLARE_EVENTSINK_MAP()

private:
	int m_doorplate_screen_width;                               //��Ļ�Ŀ��
	int m_doorplate_screen_height;                              //��Ļ�ĸ߶�
	CString m_doorplate_image_path[DOORPLATE_IMAGE_MAX_COUNT];  //�洢���ƻ�ͼƬ·��
	int m_doorplate_image_count;                                //���ƻ�ͼƬ����
	TCHAR m_doorplate_bg_image_path[256];                       //���ƻ��ı���ͼƬ·��
	int m_image_show_mode;                                      //ͼƬ��ʾģʽ
	int m_cur_show_image_number;                                //��ǰ��ʾ��ͼƬ���
	RectF m_static_image_rect;                                  //����ͼƬ��ʾ����
	RectF m_slide_image_rect;                                   //�õ�Ƭ��ʾ����
	int m_window_frame;                                         //���ڼܹ� 0�����ҽṹ 1�����½ṹ
	bool m_only_show_name_type;                                 //ֻ��ʾ�������ֺ�����

	Image *m_doorplate_image;                                   //ͼƬ������
	RectF  m_show_image_rect;                                   //��ʾͼƬ������
	RectF m_show_image_rect1;                                   //��ʾͼƬ������
	REAL m_image_width;                                         //ͼƬ���
	REAL m_image_height;                                        //ͼƬ�߶�
	bool m_show_image_finish;                                   //ͼƬ��ʾ����
	REAL m_add_height;                                          //�Ŵ�ģʽʱ���߶�����ֵ
	
	UINT_PTR m_show_image_timer;                                //��ʾͼƬ�Ķ�ʱ��
	UINT_PTR m_draw_image_timer;                                //����ͼƬ�Ķ�ʱ��
	UINT_PTR m_scroll_text_timer;                               //�������ֶ�ʱ��

	//ͼƬ����ʾ��Ϣ
	TCHAR m_image_room_name[256];                               //��ʾ�İ�������
	TCHAR m_image_room_type[256];                               //��������
	TCHAR m_image_open_room_time[256];                          //����ʱ��
	__time64_t m_open_room_time_second;                         //����ʱ����
	TCHAR m_image_people_count[256];                            //��������
	TCHAR m_image_consume_money[256];                           //���ѽ��
	bool m_thread_run;                                          //�߳�����

	//drinks
	bool m_use_drinks_function;                                 //���þ�ˮ����
	TCHAR m_room_info_text[512];                                //������Ϣ

	CTimer m_update_room_info_timer;                            //���°�����Ϣ�Ķ�ʱ��
	HWND m_parent_handle;                                       //�����ھ��
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnDestroy();
	//flash�������Ϣ��Ӧ����
	void FlashCallShockwavefunction(LPCTSTR request);
	//������ʾģʽ
	void set_image_show_mode(void);
	//��ʾ��һ��ͼƬ
	void show_next_image(void);
	//����ͼƬ
	void paint_image(void);
	//��ʾ��ߵı���ͼƬ
	void show_left_image(void);
	//���ܺ�̨���ݵ��߳�
	static UINT recv_room_data_thread(LPVOID pParam);
	void recv_room_data(void);
	//�������ܵ����ַ���
	void parse_recv_room_data(char *recv_data);
	//�Ѻ�̨�������Ŀ���ʱ��ת������
	void convert_time_to_second(TCHAR *time);
};


