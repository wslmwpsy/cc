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
	功能：设置要显示的文字
	参数：
	    text：要显示的文字
	返回值：
	    true：成功
		false：失败
	*/
	bool set_text(TCHAR *text);
	/*
	功能：设置文字的颜色
	参数：
	    text_color：文字颜色
    返回值：
	    true：成功
		false：失败
	*/
	bool set_text_color(const TCHAR *text_color);
	bool set_text_color(COLORREF text_color);
	/*
	功能：设置字体
	参数：
	    text_font：文字的字体
	返回值：
	    true：成功
		false：失败
	*/
	bool set_text_font(const TCHAR *text_font);
	/*
	功能：设置字体大小
	参数：
	    text_size：文字大小
	返回值；
	   true：成功
	   false：失败
	*/
	bool set_text_size(int text_size);

	/*
	功能：设置文字的背景颜色
	参数：
		text_color：文字颜色
	返回值：
		true：成功
		false：失败
	*/
	bool set_text_Background_color(const TCHAR *text_color);
	/*
	功能：设置消息的类型
	参数：
	    message_type;消息类型
	返回值：
	    true：成功
		false：失败
	*/
	bool set_message_type(char *message_type);
	/*
	功能：设置显示模式
	参数：
	    show_mode：显示模式
	返回值：
	    true：成功
		false：失败
	*/
	bool set_show_mode(const TCHAR *show_mode);
	/*
	功能：设置消息内容的类型
	参数：
	　　content_type：内容类型
    返回值：
	    true：成功
		false：失败
	*/
	bool set_content_type(TCHAR *content_type);
	/*
	功能：设置滚动方式
	参数：
	    scroll_mode;滚动模式
		osd_type：osd类型
	返回值：
	    true：成功
		false：失败
	*/
	bool set_scroll_mode(const TCHAR *scroll_mode,enum MESSAGE_CONTENT_TYPE osd_type);
	bool set_scroll_mode(enum OSD_PLAY_MODE scroll_mode,enum MESSAGE_CONTENT_TYPE osd_type);
	/*
	功能：设置滚动次数
	参数:
	    scroll_count：滚动次数
	返回值：
	    true：成功
		false：失败
	*/
	bool set_scroll_count(TCHAR *scroll_count);
	bool set_scroll_count(int scroll_count);

	/*
	功能：设置滚动速度
	参数：
	    scroll_speed：滚动速度
	返回值：
	    true：成功
		false：失败
	*/
	bool set_scroll_speed(TCHAR *scroll_speed);
	bool set_scroll_speed(int scroll_speed);

	/*
	功能：设置滚动的起始位置
	参数：
	    position：位置坐标
	返回值：
	    true：成功
		false：失败
	*/
	bool set_scroll_position_x(TCHAR *position);
	bool set_scroll_position_y(TCHAR *position);
	bool set_scroll_position_x(int position);
	bool set_scroll_position_y(int position);

	/*
	功能：根据滚动类型，调整起始坐标
	参数；
	    void
	返回值：
	    void
	*/
	void adjust_text_position(int start_x);	// 根据文字滚动类型，确定起始和终止坐标
	void adjust_picture_position();	// 根据图片滚动类型，确定起始和终止坐标

	/*
	功能：返回文字的基本信息类
	参数：
	    text_info：文字的基本信息类
	返回值;
	    true：成功
		false：失败
	*/
	bool get_text_info(text_osd_info &text_info);

	/*
	功能：得到文字的播放参数类
	参数：
	    play_var：播放变量类
	返回值：
	    true：成功
		false：失败
	*/
	bool get_text_play_variable(play_variable &play_var);

	/*
	功能：得到文字的播放参数类
	参数：
		play_var：播放变量类
	返回值：
		true：成功
		false：失败
	*/
	bool get_picture_play_variable(play_variable &play_var);

	/*
	功能：解析发送过来的消息
	参数：
	    msg：消息
	返回值：
	    true：成功
		false：失败
	*/
	bool parse_msg(const char *msg, LPMOVIE_MSG_CONTROL lpMMCtrl = NULL);

	/*
	功能：得到显示模式
	参数：
	    void
	返回值：
	    显示模式
	*/
	MESSAGE_SHOW_MODE get_show_mode(void);

	/*
	功能：得到消息的内容类型
	参数：
	    void
	返回值：
	   内容类型
	*/
	MESSAGE_CONTENT_TYPE get_content_type(void);


	MESSAGE_TYPE  get_message_type(void);

private:
	text_osd_info m_text_info;              //text的基本信息
	play_variable m_text_play_variable;    //文字播放时的参数
	play_variable m_picture_play_variable; //图片播放时的参数
	enum MESSAGE_TYPE m_message_type;	// 消息类型（公告等）
	enum MESSAGE_SHOW_MODE m_show_mode;	// 显示模式
	enum MESSAGE_CONTENT_TYPE m_content_type;	// 消息内容类型（文本或图片）
	enum OSD_PLAY_MODE m_text_scroll_mode;	// 文字滚动方式
	enum OSD_PLAY_MODE m_picture_scroll_mode;	// 图片滚动方式
	int m_scroll_count;                        //滚动次数
};
