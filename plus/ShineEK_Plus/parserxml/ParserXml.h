#pragma once

#include "Markup.h"
#include ".\..\message.h"

class CParserXml
{
public:
	CParserXml(void);
	~CParserXml(void);
	/*
	���ܣ�����flash���淢�͹�������Ϣ����
	������
	    request����Ϣ�����ַ���
		command:�ӿڵ�����
		args������
	����ֵ��
	    true:�ɹ�
		false:ʧ��
	*/
	bool parser_flash_request_xml(const TCHAR *request,TCHAR *command,TCHAR *args);
	
	/*
	���ܣ���֤xml�Ƿ���ȷ
	������
	    xml_string��Ҫ��֤��xml�ַ���
	����ֵ��
	    true���ɹ�
		false��ʧ��
	*/
	bool test_xml_validity(const TCHAR *xml_string);

	/*
	���ܣ�����xml�õ���������
	������
	    work_path:����·��
		interface_type����������
		interface_version������汾 
		����ֵ��
	    true���ɹ�
		false��ʧ��
	*/
	bool get_screen_type(TCHAR *work_path,SCREEN_TYPE &interface_type,TCHAR *interface_version,FLASH_USE_LANGUAGE &cur_language,TCHAR *config_value);
	/*
	���ܣ�������ť״̬�ַ���
	������
	    list_xml���ַ���
		out_value1�������ֵ
		out_value2�������ֵ
		out_value3�������ֵ
		out_value4�������ֵ
		out_flag�������ʶ
	����ֵ��
	    true���ɹ�
		false��ʧ��
	*/
	bool parse_control_xml(TCHAR *list_xml,int &out_value1,int &out_value2,int &out_value3,int &out_value4,TCHAR *out_flag);

	/*
	���ܣ��޸���Ϸ����
	������
	   game_name����Ϸ��������
   ����ֵ��
       true���ɹ�
	   false��ʧ��
	*/
	bool modify_local_game_name(SONG_GAME_STRUCT game_name[]);
};
