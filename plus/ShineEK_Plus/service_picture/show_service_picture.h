#pragma once
#include <string>
#define MAX_SERVICE_PICTURE_COUNT 50

enum SERVICE_PICTRUE_PAGE_OPERATE
{
	SERVICE_PICTRUE_CUR_PAGE,  //当前页
	SERVICE_PICTRUE_PRE_PAGE,  //服务图片的上一页
	SERVICE_PICTRUE_NEXT_PAGE, //服务图片的下一页
};

//显示服务图片的类
class show_service_picture
{
public:
	show_service_picture(void);
	~show_service_picture(void);
	/*
	功能：初始化
	参数：
	    path：图片文件夹路径
	返回值：
	    true：成功
		false：失败
	*/
	bool initiate(TCHAR *path);

	/*
	功能：得到要显示的图片路径
	参数：
	    page_operate：页操作
		path：得到的文件路径
	返回值：
	    true：成功
		false：失败
	*/
	bool get_show_picture(SERVICE_PICTRUE_PAGE_OPERATE page_operate,TCHAR *path);
	bool get_show_picture(SERVICE_PICTRUE_PAGE_OPERATE page_operate,std::wstring &picture_list_xml);

	/*
	功能：得到总的页数和当前页数
	参数：
	    total_page_count：总的页数
		show_page_number：显示的页编号
	返回值：
	    true：成功
		false：失败
	*/
	bool get_page_info(int &total_page_count, int &show_page_number);

	/*
	功能：设置要显示的页
	参数：
	    page_number：页数
	返回值：
	   void
	*/
	void set_show_page_number(int page_number);


private:
	TCHAR m_picture_path[MAX_SERVICE_PICTURE_COUNT][256]; //图片路径
	int m_total_picture_count;     //总的图片数
	int m_cur_show_picture_number; //当前正在显示的图片编号 ,从1开始
};
