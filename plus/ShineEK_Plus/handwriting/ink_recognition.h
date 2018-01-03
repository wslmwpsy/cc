#pragma once

#include "sink_event.h"

enum INK_RECOGNIZER_LANGUAGE
{
	INK_RECOGNIZER_LANGUAGE_US_ENGLISH=0,          //美式英文
	INK_RECOGNIZER_LANGUAGE_SIMPLIFIED_CHINESE,    //简体中文
	INK_RECOGNIZER_LANGUAGE_TRADITIONAL_CHINESE,   //繁体中文
	INK_RECOGNIZER_LANGUAGE_JAPANESE,              //日语
	INK_RECOGNIZER_LANGUAGE_KOREA,                 //韩语
	
	INK_RECOGNIZER_LANGUAGE_MAX_INDEX,
};

class ink_recognition
{
public:
	ink_recognition(void);
	~ink_recognition(void);

	/*
	功能：初始化控件
	参数：
		hwnd：手写窗口设置句柄
		result_nums：识别出来的文字个数
	返回值：
		true：成功
		false：失败
	*/
	bool init_ink_control(HWND hwnd,int result_nums,long left,long right,long top,long bottom);

	/*
	功能：识别手写
	参数：
	    void
	返回值：
	    true：成功
		false：失败
	*/
	bool on_recognizer(void);

	/*
	功能：清空
	参数：
	    void
	返回值：
	    true：成功
		false：失败
	*/
	bool clear_window(void);

	/*
	功能：得到识别出来的字符串
	参数：
	    result_string：结果字符串
	返回值：
	    true：成功
		false：失败
	*/
	bool get_recognize_result(CString *result_string);

	/*
	功能：改变语言
	参数：
	   language：语言
   返回值：
       true：成功
	   false：失败
	*/
	bool set_language(INK_RECOGNIZER_LANGUAGE language);

	/*
	功能：设置画笔属性
	参数：
	    color：颜色
		width：画笔宽度
	返回值：
	    true：成功
		false：失败
	*/
	bool set_pen_attribute(long color,float width);

private:
	HWND m_parent_hwnd;  //父句柄
	CMyInkEvents m_InkEvents; //事件
	CComPtr<IInkCollector>          m_spIInkCollector;
	CComPtr<IInkDisp>               m_spIInkDisp;
	CComPtr<IInkRectangle>          m_spIInkRectangle;
	CComPtr<IInkRecognizerGuide>    m_spIInkREcognizeGuide;
	CComPtr<IInkRecognizerContext>  m_spIInkRecoContext;
	CComPtr<IInkRecognizers>        m_spIInkRecognizers;

	int m_recognize_alternate_nums; //识别出来的文字个数 
	CString   *m_recognize_result;  //存储识别出来的字符
	long m_recognizers_count;       //可以识别的语言数

	int m_ink_language_index[INK_RECOGNIZER_LANGUAGE_MAX_INDEX];
};
