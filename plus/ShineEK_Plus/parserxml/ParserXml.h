#pragma once

#include "Markup.h"
#include ".\..\message.h"

class CParserXml
{
public:
	CParserXml(void);
	~CParserXml(void);
	/*
	功能：解析flash界面发送过来的消息参数
	参数：
	    request：消息参数字符串
		command:接口的名称
		args：参数
	返回值：
	    true:成功
		false:失败
	*/
	bool parser_flash_request_xml(const TCHAR *request,TCHAR *command,TCHAR *args);
	
	/*
	功能：验证xml是否正确
	参数：
	    xml_string：要验证的xml字符串
	返回值：
	    true：成功
		false：失败
	*/
	bool test_xml_validity(const TCHAR *xml_string);

	/*
	功能：解析xml得到界面类型
	参数：
	    work_path:工作路径
		interface_type：界面类型
		interface_version：界面版本 
		返回值：
	    true：成功
		false：失败
	*/
	bool get_screen_type(TCHAR *work_path,SCREEN_TYPE &interface_type,TCHAR *interface_version,FLASH_USE_LANGUAGE &cur_language,TCHAR *config_value);
	/*
	功能：解析按钮状态字符串
	参数：
	    list_xml：字符串
		out_value1：输出的值
		out_value2：输出的值
		out_value3：输出的值
		out_value4：输出的值
		out_flag：输出标识
	返回值：
	    true：成功
		false：失败
	*/
	bool parse_control_xml(TCHAR *list_xml,int &out_value1,int &out_value2,int &out_value3,int &out_value4,TCHAR *out_flag);

	/*
	功能：修改游戏名字
	参数：
	   game_name：游戏名字数组
   返回值：
       true：成功
	   false：失败
	*/
	bool modify_local_game_name(SONG_GAME_STRUCT game_name[]);
};
