// Register.h
//

#pragma once

/*
���ܣ�ע��OCX�ؼ�
������
    ocx_file_name���ؼ����ļ���
	copy_to_system_directory���Ƿ���Ҫ������ϵͳĿ¼
����ֵ��
    0���ɹ�
	��0��ʧ��
*/
int register_ocx(TCHAR* ocx_file_name, bool copy_to_system_directory);

/*
���ܣ�ע��OCX�ؼ�
������
    ocx_file_name���ؼ����ļ���
����ֵ��
	0���ɹ�
	��0��ʧ��
*/

int unregister_ocx(TCHAR* ocx_file_name);

/*
���ܣ�ע������
������
    dir�������ļ����ļ���·��
����ֵ��
    void
*/
void register_font(TCHAR* dir);

/*
���ܣ�ע��ax�ؼ�
������
    ax_directory��ax�ؼ���Ŀ¼
����ֵ��
    true���ɹ�
	false��ʧ��
*/
bool register_ax_control(const TCHAR *ax_directory);