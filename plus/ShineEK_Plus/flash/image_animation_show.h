#pragma once

//����ҳ��
class image_animation_show
{
public:
	image_animation_show(void);
	~image_animation_show(void);
	/*
	���ܣ�����Ĭ������ҳ·��
	������
	   path��·��
   ����ֵ��
       void
	*/
	void set_default_image_path(TCHAR *path);
	/*
	���ܣ��õ�����ҳ·��
	������
	    path��·��
	����ֵ��
	    true���ɹ�
		false��ʧ��
	*/
	bool get_show_image_animation(TCHAR *path);
private:
	TCHAR m_image_path[256];  //����ҳ��·��
	TCHAR m_default_image_path[256]; //Ĭ������ҳ·��
};
