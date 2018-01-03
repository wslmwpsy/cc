#pragma once

#define KTV_LOGO_MAX_COUNT   120   //logo的最大数

class osd_logo_list
{
public:
	osd_logo_list(void);
	~osd_logo_list(void);

	//初始化
	void initiate(void);

	/*
	功能：设置logo文件的路径，并进行初始化
	参数：
	    logo_directory：logo的文件夹路径
	返回值：
	    true：成功
		false：失败
	*/
	bool set_logo_path(TCHAR *logo_directory);

	/*
	功能：得到当前播放的logo编号
	参数：
	    void
	返回值:
	    当前要播放的logo编号
	*/
	int get_cur_logo_index();

	/*
	功能：得到当前要播放的logo文件路径
	参数：
	    path：logo文件路径
	返回值：
	    true：成功
		false：失败
	*/
	bool get_logo_file_path(TCHAR *path);
	
private:
	TCHAR m_logo_directory[256];                  //logo文件夹的路径
	TCHAR m_logo_path[KTV_LOGO_MAX_COUNT][256];  //所有logo的路径，最多100个
	int   m_logo_count;                          //logo的总数
	int   m_cur_logo_number;                     //当前播放的logo编号
};
