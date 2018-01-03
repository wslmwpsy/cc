#pragma once

//形象页类
class image_animation_show
{
public:
	image_animation_show(void);
	~image_animation_show(void);
	/*
	功能：设置默认形象页路径
	参数：
	   path：路径
   返回值：
       void
	*/
	void set_default_image_path(TCHAR *path);
	/*
	功能：得到形象页路径
	参数：
	    path：路径
	返回值：
	    true：成功
		false：失败
	*/
	bool get_show_image_animation(TCHAR *path);
private:
	TCHAR m_image_path[256];  //形象页的路径
	TCHAR m_default_image_path[256]; //默认星象页路径
};
