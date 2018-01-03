// Register.h
//

#pragma once

/*
功能：注册OCX控件
参数：
    ocx_file_name：控件的文件名
	copy_to_system_directory：是否需要拷贝到系统目录
返回值：
    0：成功
	非0：失败
*/
int register_ocx(TCHAR* ocx_file_name, bool copy_to_system_directory);

/*
功能：注销OCX控件
参数：
    ocx_file_name：控件的文件名
返回值：
	0：成功
	非0：失败
*/

int unregister_ocx(TCHAR* ocx_file_name);

/*
功能：注册字体
参数：
    dir：字体文件的文件家路径
返回值：
    void
*/
void register_font(TCHAR* dir);

/*
功能：注册ax控件
参数：
    ax_directory：ax控件的目录
返回值：
    true：成功
	false：失败
*/
bool register_ax_control(const TCHAR *ax_directory);