#pragma once

#include "..\com\inherit_com.h"
#include "..\parserxml\Markup.h"
// CAudioEffect

class CAudioEffect : public CWnd
{
	DECLARE_DYNAMIC(CAudioEffect)

public:
	CAudioEffect();
	virtual ~CAudioEffect();

protected:
	DECLARE_MESSAGE_MAP()
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
public:
	TCHAR m_work_path[256];               //����·��
	TCHAR m_config_path[256];             //�����ļ�·��
	TCHAR m_skin_config_path[256];        //Ƥ�������ļ�·��
	TCHAR m_protocol_config_path[256];    //Э�������ʼ�·��
	TCHAR m_src_image_path[256];          //ԭʼͼƬ·��
	Image *m_audio_effect_image;          //��ЧͼƬ
	Image *m_slider_bar_image;            //sliderָʾ��ͼƬ
	Image *m_disable_effect_image;        //���ܲ�����ͼƬ
	Image *m_highlight_status_image;      //����ͼƬ
	Image *m_draw_image;                  //�����õ�ͼ
	_asyn_com m_audio_effect_com;         //��Ч����
	bool m_connect_success;               //���ӳɹ�
	unsigned char m_connect_command[256]; //��������
	int m_connect_command_len;            //��������ĳ���
	unsigned char m_idless_command[256];  //��������
	int m_idless_command_len;             //���������
	bool m_response_mouse_event;          //������Ӧ����¼�
	POINT m_mouse_click_point;            //�������λ��
	TCHAR m_tip_message[256];             //��ʾ��Ϣ
	TCHAR m_upload_server_path[256];      //�ϴ��ķ�����·��
public:
	afx_msg void OnClose();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	virtual BOOL CreateEx(DWORD dwExStyle, LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, LPVOID lpParam = NULL,TCHAR *server_path=NULL);
	afx_msg void OnPaint();
	/*
	���ܣ������еĿؼ����
	������
	     click_point�����������
		 control_number�����еĿؼ����
		 control_type���ؼ�����
		 group_flag�����ʾ
		 radio_value����ѡ��ť��ֵ
		 min_value����Сֵ
		 max_value�����ֵ
	 ����ֵ��
	     true���ɹ�
		 false��ʧ��
	 */
	bool check_click_control_number(POINT &click_point,TCHAR *control_number,TCHAR *control_type,TCHAR *group_flag,int &radio_value,int &min_value,int &max_value);

	/*
	���ܣ���Ӧ�ؼ����¼�
	������
		control_number�����еĿؼ����
		control_type���ؼ�����
		group_flag�����ʾ
		radio_value����ѡ��ť��ֵ
		min_value����Сֵ
		max_value�����ֵ
	����ֵ��
	    true���ɹ�
		false��ʧ��
	*/
	bool reponse_control_event(TCHAR *control_number,TCHAR *control_type,TCHAR *group_flag,int &radio_value,int &min_value,int &max_value);

	/*
	���ܣ�������������
	������
	    com_value����Ҫ������ֵ
		recv_value�������õ�ֵ
		buf_len���ֽ���
	����ֵ��
	    true���ɹ�
		false��ʧ��
	*/
	bool parse_com_value(const TCHAR *com_value,unsigned char *recv_value,int &buf_len);
	/*
	���ܣ���ʾ����
	������
	    text_graphic����ͼ��
	����ֵ��
	    true���ɹ�
		false��ʧ��
	*/
	bool show_control_value(Graphics &text_graphic);

	/*
	���ܣ����Ʋ��ɲ�������͸�������
	������
	    Graphics &text_graphic
	����ֵ��
	    true���ɹ�
		false��ʧ��
	*/
	bool draw_disable_highlight_rect(Graphics &text_graphic);

	/*
	���ܣ���ͼ������
	������
	    void
	����ֵ��
	   void
	*/
	void draw_window(void);
	/*
	���ܣ��õ��ؼ��ĵ�ǰֵ
	������
	    group_number�����ʾ
	����ֵ��
	    true���ɹ�
		false��ʧ��
	*/
	bool get_control_cur_value(const TCHAR *group_number,TCHAR *cur_value);

	/*
	���ܣ���ȡ��Ч����ֵ
	������
	    parse_xml_class������xml����
	����ֵ��
	   void
	*/
	bool read_audio_effect_value(CMarkup &parse_xml_class);
	
	/*
	���ܣ��ж�����¼����߳�
	������
	    pParam������
	����ֵ��
	    UINT
	*/
	static UINT reponse_mouse_thread(LPVOID pParam);
	UINT reponse_mouse_event(void);
	
	/*
	���ܣ��ϴ�������Э�������ļ�
	������
	   upload_flag����ʾ  true���ϴ� false������
   ����ֵ��
      void
	*/
	void upload_download_protocol_file(bool upload_flag);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
};


