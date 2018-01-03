#pragma once
#include ".\com_class.h"
#include "com_value.h"

#include <MMSystem.h>

#define COM_SEND_MAX_GROUP_COUNT   20   //窗口每次发送的最大组数
#define TOUCH_SCREEN_MAX_BYTE      10   //触摸屏发送的最大字节数

class inherit_com :
	public _thread_com
{
public:
	inherit_com(void);
	~inherit_com(void);
	//接收串口数据
	virtual void on_receive();
	/*
	功能：解析串口接收到得命令，并保存到变量中，用于接收到了查找对应的命令
	参数：
	    handle：父句柄
		message：发送的消息
	返回值：
	    true：成功
		false：失败
	*/
	bool init_com(HWND handle,int message,TCHAR *file_name);

	/*
	功能：解析从串口接收到的值
	参数：
	    com_value：未解析的十六进制的值
		recv_value：解析好的接受到的值
	返回值：
	    true：成功
		false：失败
	*/
	bool parse_com_recv_value(const TCHAR *com_value,unsigned char *recv_value);

	/*
	功能：解析各个墙面板按钮的坐标
	参数：
		rect：按钮区域
		number：编号
	返回值：
		true：成功
		false：失败
	*/
	bool parse_button_rect_value(const TCHAR *rect,int number);

	/*
	功能：解析要发送到串口的值
	参数：
	    com_value：未解析的十六进制的值
		com_send_flag：发送串口值的标示
		music_volume：音乐的音量
		microphone_volume：麦克风的音量
		tune：音调
	返回值：
	    true：成功
		false：失败
	*/
	bool parse_com_send_value(const TCHAR *com_value,COM_SEND_VALUE_FLAG com_send_flag,int music_volume,int microphone_volume,int tune);


	/*
	功能：发送消息给串口
	参数：
	    enum COM_SEND_VALUE_FLAG：发送串口值的标示
		adjust_count：发送次数
		file_name：配置文件的名字
		music_volume：音乐的音量
		microphone_volume：麦克风的音量
		tune：音调
	返回值：
	    true：成功
		false：失败
	*/
	bool write_data(enum COM_SEND_VALUE_FLAG com_send_flag,TCHAR *file_name,TCHAR *song_number,int music_volume,int microphone_volume,int tune,int adjust_count=0);

	/*
	功能：解析键盘口接收到的中控盒消息
	参数：
	    recv_value：接受到的值
	返回值：
	    void
	*/
	void parse_ps2_value(int recv_value);

	/*
	功能：判断一个点在那个区域中
	参数：
		x：横坐标
		y：纵坐标
	返回值
		void
	*/
	void determine_point_in_rect(int x,int y);

	/*
	功能：发送串口值的线程
	参数：
		pParam：传递的参数
	返回值：
	UINT
	*/
	static UINT send_com_value_thread(LPVOID pParam);

	/*
	功能：发送串口数据
	参数：
	    void
	返回值：
	    void
	*/
	void write_com_data(void);
	void write_com_data_timer(void);
	void write_com_data_UDP_IP(char *data);

	/*
	功能：定时发送串口值
	参数：
		uTimerID：定时器的ID
		uMsg：消息
		dwUser：用户标示
		dw1,dw2：参数
	返回值：
		void
	*/
	static void WINAPI send_com_callback(UINT uTimerID, UINT uMsg, DWORD dwUser, DWORD dw1, DWORD dw2);
	/*
	控制灯光效果
	*/
	void set_light_value(bool light);
	bool get_light_value();
	/*
	额外控制灯光标识
	*/
	void set_light_value_ex(bool light_ex);
	bool get_light_value_ex();
private:
	HWND m_parent_handle;      //父句柄
	int m_com_send_message;    //串口发送的消息
	unsigned char com_receive_value[COM_RECEIVE_VALUE_FLAG_MAX_COUNT][64];  //串口接收到的全部命令
	unsigned char m_com_send_value[COM_SEND_MAX_GROUP_COUNT][128];          //解析好的要发送的值
	int m_com_send_value_len[COM_SEND_MAX_GROUP_COUNT];                     //解析好的每组串口数据的长度
	int m_com_send_group_count;                                             //串口发送的组数
	CWinThread *m_send_thread_handle;                                       //发送串口值的线程句柄
	int m_com_send_time_elapse;                                             //串口发送的时间间隔
	CRect m_wall_panel_button_rect[COM_RECEIVE_VALUE_FLAG_MAX_COUNT];       //墙面板按钮的坐标
	unsigned char m_recv_com_data[256];                                     //接受的串口数据
	int m_recv_data_len;                                                    //接受的串口数据长度
	int m_conn_audio_effect;                                                //直接控制音效器
	bool m_light_control;
	bool m_light_control_ex;
};