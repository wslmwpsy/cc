#pragma once

#define PICTURE_AD_MAX_COUNT    50

class AD_manager
{
public:
	AD_manager(void);
	~AD_manager(void);
	/*
	���ܣ���ʼ��ͼƬ���
	������
	    folder_name���ļ�������
	����ֵ��
	    void
	*/
	void init_picture_ad(const TCHAR *folder_name);

	/*
	���ܣ��õ�Ҫ���ŵ���һ�����·��
	����:
	    path:���ͼƬ·��
	����ֵ��
	    ture���ɹ�
		false��ʧ��
	*/
	bool get_next_play_ad_picture(TCHAR *path);
private:
	TCHAR m_picture_ad_path[PICTURE_AD_MAX_COUNT][256];   //ͼƬ����·��
	int m_picture_ad_total_count;                         //ͼƬ����
	int m_picture_ad_play_number;                         //ͼƬ��浱ǰ���ŵ�����
};
