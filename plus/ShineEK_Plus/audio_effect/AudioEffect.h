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
	TCHAR m_work_path[256];               //工作路径
	TCHAR m_config_path[256];             //配置文件路径
	TCHAR m_skin_config_path[256];        //皮肤配置文件路径
	TCHAR m_protocol_config_path[256];    //协议配置问价路径
	TCHAR m_src_image_path[256];          //原始图片路径
	Image *m_audio_effect_image;          //音效图片
	Image *m_slider_bar_image;            //slider指示条图片
	Image *m_disable_effect_image;        //不能操作的图片
	Image *m_highlight_status_image;      //高亮图片
	Image *m_draw_image;                  //绘制用的图
	_asyn_com m_audio_effect_com;         //音效串口
	bool m_connect_success;               //连接成功
	unsigned char m_connect_command[256]; //连接命名
	int m_connect_command_len;            //连接命令的长度
	unsigned char m_idless_command[256];  //空闲命令
	int m_idless_command_len;             //空闲命令长度
	bool m_response_mouse_event;          //正在响应鼠标事件
	POINT m_mouse_click_point;            //鼠标点击的位置
	TCHAR m_tip_message[256];             //提示信息
	TCHAR m_upload_server_path[256];      //上传的服务器路径
public:
	afx_msg void OnClose();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	virtual BOOL CreateEx(DWORD dwExStyle, LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, LPVOID lpParam = NULL,TCHAR *server_path=NULL);
	afx_msg void OnPaint();
	/*
	功能：检测点中的控件编号
	参数：
	     click_point：点击的坐标
		 control_number：点中的控件编号
		 control_type：控件类型
		 group_flag：组标示
		 radio_value：单选按钮的值
		 min_value：最小值
		 max_value：最大值
	 返回值：
	     true：成功
		 false：失败
	 */
	bool check_click_control_number(POINT &click_point,TCHAR *control_number,TCHAR *control_type,TCHAR *group_flag,int &radio_value,int &min_value,int &max_value);

	/*
	功能：响应控件的事件
	参数：
		control_number：点中的控件编号
		control_type：控件类型
		group_flag：组标示
		radio_value：单选按钮的值
		min_value：最小值
		max_value：最大值
	返回值：
	    true：成功
		false：失败
	*/
	bool reponse_control_event(TCHAR *control_number,TCHAR *control_type,TCHAR *group_flag,int &radio_value,int &min_value,int &max_value);

	/*
	功能：解析串口数据
	参数：
	    com_value：需要解析的值
		recv_value：解析好的值
		buf_len：字节数
	返回值：
	    true：成功
		false：失败
	*/
	bool parse_com_value(const TCHAR *com_value,unsigned char *recv_value,int &buf_len);
	/*
	功能：显示数字
	参数：
	    text_graphic：绘图类
	返回值：
	    true：成功
		false：失败
	*/
	bool show_control_value(Graphics &text_graphic);

	/*
	功能：绘制不可操作区域和高亮区域
	参数：
	    Graphics &text_graphic
	返回值：
	    true：成功
		false：失败
	*/
	bool draw_disable_highlight_rect(Graphics &text_graphic);

	/*
	功能：绘图到界面
	参数：
	    void
	返回值：
	   void
	*/
	void draw_window(void);
	/*
	功能：得到控件的当前值
	参数：
	    group_number：组标示
	返回值：
	    true：成功
		false：失败
	*/
	bool get_control_cur_value(const TCHAR *group_number,TCHAR *cur_value);

	/*
	功能：读取音效器的值
	参数：
	    parse_xml_class：解析xml的类
	返回值：
	   void
	*/
	bool read_audio_effect_value(CMarkup &parse_xml_class);
	
	/*
	功能：判断鼠标事件的线程
	参数：
	    pParam：参数
	返回值：
	    UINT
	*/
	static UINT reponse_mouse_thread(LPVOID pParam);
	UINT reponse_mouse_event(void);
	
	/*
	功能：上传、下载协议配置文件
	参数：
	   upload_flag：标示  true：上传 false：下载
   返回值：
      void
	*/
	void upload_download_protocol_file(bool upload_flag);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
};


