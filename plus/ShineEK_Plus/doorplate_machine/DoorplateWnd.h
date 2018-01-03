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
	//创建门牌机窗口
	bool Create(RECT& rect,TCHAR *room_name,bool use_drinks,HWND parent_handle);

protected:
	DECLARE_MESSAGE_MAP()
	DECLARE_EVENTSINK_MAP()

private:
	int m_doorplate_screen_width;                               //屏幕的宽度
	int m_doorplate_screen_height;                              //屏幕的高度
	CString m_doorplate_image_path[DOORPLATE_IMAGE_MAX_COUNT];  //存储门牌机图片路径
	int m_doorplate_image_count;                                //门牌机图片个数
	TCHAR m_doorplate_bg_image_path[256];                       //门牌机的背景图片路径
	int m_image_show_mode;                                      //图片显示模式
	int m_cur_show_image_number;                                //当前显示的图片编号
	RectF m_static_image_rect;                                  //背景图片显示区域
	RectF m_slide_image_rect;                                   //幻灯片显示区域
	int m_window_frame;                                         //窗口架构 0：左右结构 1：上下结构
	bool m_only_show_name_type;                                 //只显示房间名字和类型

	Image *m_doorplate_image;                                   //图片加载类
	RectF  m_show_image_rect;                                   //显示图片的区域
	RectF m_show_image_rect1;                                   //显示图片的区域
	REAL m_image_width;                                         //图片宽度
	REAL m_image_height;                                        //图片高度
	bool m_show_image_finish;                                   //图片显示完整
	REAL m_add_height;                                          //放大模式时，高度增加值
	
	UINT_PTR m_show_image_timer;                                //显示图片的定时器
	UINT_PTR m_draw_image_timer;                                //绘制图片的定时器
	UINT_PTR m_scroll_text_timer;                               //滚动文字定时器

	//图片上显示信息
	TCHAR m_image_room_name[256];                               //显示的包房名称
	TCHAR m_image_room_type[256];                               //包房类型
	TCHAR m_image_open_room_time[256];                          //开房时间
	__time64_t m_open_room_time_second;                         //开房时间秒
	TCHAR m_image_people_count[256];                            //消费人数
	TCHAR m_image_consume_money[256];                           //消费金额
	bool m_thread_run;                                          //线程运行

	//drinks
	bool m_use_drinks_function;                                 //启用酒水功能
	TCHAR m_room_info_text[512];                                //包房信息

	CTimer m_update_room_info_timer;                            //更新包房信息的定时器
	HWND m_parent_handle;                                       //父窗口句柄
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnDestroy();
	//flash界面的消息响应函数
	void FlashCallShockwavefunction(LPCTSTR request);
	//设置显示模式
	void set_image_show_mode(void);
	//显示下一幅图片
	void show_next_image(void);
	//绘制图片
	void paint_image(void);
	//显示左边的背景图片
	void show_left_image(void);
	//接受后台数据的线程
	static UINT recv_room_data_thread(LPVOID pParam);
	void recv_room_data(void);
	//解析接受到的字符串
	void parse_recv_room_data(char *recv_data);
	//把后台传过来的开房时间转化成秒
	void convert_time_to_second(TCHAR *time);
};


