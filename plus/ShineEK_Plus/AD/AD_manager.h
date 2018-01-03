#pragma once

#define PICTURE_AD_MAX_COUNT    50

class AD_manager
{
public:
	AD_manager(void);
	~AD_manager(void);
	/*
	功能：初始化图片广告
	参数：
	    folder_name：文件夹名字
	返回值：
	    void
	*/
	void init_picture_ad(const TCHAR *folder_name);

	/*
	功能：得到要播放的下一个广告路径
	参数:
	    path:广告图片路径
	返回值：
	    ture：成功
		false：失败
	*/
	bool get_next_play_ad_picture(TCHAR *path);
private:
	TCHAR m_picture_ad_path[PICTURE_AD_MAX_COUNT][256];   //图片广告的路径
	int m_picture_ad_total_count;                         //图片总数
	int m_picture_ad_play_number;                         //图片广告当前播放的总数
};
