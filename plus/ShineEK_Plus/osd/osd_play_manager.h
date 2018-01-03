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
	功能：初始化
	参数：
	   void
    返回值：
       void
	*/
	void initialize(void);

	/*
	功能：设置要播放的文字
	参数：
	    text：要播放的文字
	返回值：
	    true：成功
		false：失败
	*/
	bool set_osd_text(TCHAR *text);

	/*
	功能：得到背景图片的路径
	参数：
	    path：路径
	返回值：
	    true：成功
		false：失败
	*/
	bool get_background_path(TCHAR *path);
	/*
	功能：得到播放的控制OSD的文件名
	参数：
	   show_content：显示的内容
	   path：控制功能图片的路径
	   x_pos：横坐标
	   y_pos：纵坐标
	   soft_decode：软件标示 true：软解 false：硬解
	   recorder_osd:是否是网络录音
   返回值：
       true：成功
	   false：失败
	*/
	bool get_control_osd_info(enum OSD_SHOW_CONTENT show_content,TCHAR *path,int &x_pos,int &y_pos,bool soft_decode,enum FLASH_USE_LANGUAGE flash_language,bool recorder_osd=false);

	/*
	功能：设置logo的路径
	参数：
	    path：logo文件的路径
	返回值：
	    true：成功
		false：失败
	*/
	bool set_logo_osd_path(TCHAR *path);

	
	/*
	功能：得到logo osd的信息
	参数;
	    path：logo文件的路径
		index：索引
	返回值：
	    true：成功
		false：失败
	*/
	bool get_logo_osd_info(TCHAR *path,int &index);

	/*
	功能：调整控制osd的位置
	参数：
	    screen_width：屏幕宽度
		screen_height：屏幕高度
		soft_decode：软解标示
	返回值：
	    void
	*/
	void adjust_control_osd_coordinate(int screen_width,int screen_height,bool soft_decode);

public:
	osd_text_picture m_osd_text_picture;  //文字或图片信息类
	bool m_show_osd;                       //是否显示osd
	TCHAR m_text_background_path[256];    //文字背景图片路径
	TCHAR m_install_path[256];            //安装路径
	TCHAR m_screen_show_folder_name[64];  //屏幕显示图片文件夹的名字
	enum FILE_ATTRIBUTE  file_attribute;  //记录logo文件的属性
	TCHAR m_logo_path[256];               //logo文件的路径
	osd_logo_list logo_list;              //记录一组logo图片
	int m_control_osd_x;                  //控制osd的横坐标
	int m_control_osd_y;                  //控制osd的纵坐标
	int m_show_osd_suit_number;           //显示的osd组号
};
