#pragma once

#include "..\common\show_picture.h"
#include "screen_saver_variable.h"

class screen_saver_picture :public show_picture
{
public:
	screen_saver_picture(void);
	~screen_saver_picture(void);
	void set_screen_rect(int screen_width,int screen_height);
	void unload_picture(void);
	BOOL Show(HDC hDC, LPRECT pDrawRect,enum SCREEN_SAVER_SHOW_MODE show_mode);
private:
	int m_screen_width;  //屏幕的宽度
	int m_screen_height; //屏幕的高度
};
